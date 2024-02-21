#include "Lib.h"
#include "LibConst.h"
#pragma warning(disable:6385)

using namespace std;

CMathLib::CMathLib()
{
	m_strToken.clear();
	Init();
}

CMathLib::CMathLib(string strToken) : m_strToken(strToken)
{
	Init();
}

CMathLib::CMathLib(const CMathLib& rhs)
{
	*this = rhs;
}

CMathLib::~CMathLib()
{
}

CMathLib& CMathLib::operator = (const CMathLib& rhs)
{
	if (this != &rhs)
	{
		m_strToken = rhs.m_strToken;
		Init();
	}
	return *this;
}

string CMathLib::WB()
{
	return huns[nHuns - 1];
}

int CMathLib::ExpandLHS(string strInput, string& strResult)
{
	if (strInput.empty())
		return -1;

	int iResult = 0;
	bool bNegative = false;
	int digs, ld, nd, nh;

	strResult.clear();
	if (*(strInput.begin()) == '-')
	{
		bNegative = true;
		strInput = strInput.substr(1);
	}

start:
	digs = (int)strInput.length() - 1;
	nh = digs / 3;
	if (nh <= nHuns)
	{
		ld = digs % 3;
		switch (ld)
		{
		case 0:
			nd = 1;
			break;
		case 1:
			nd = 2;
			break;
		case 2:
			nd = 3;
			break;
		default:
			break;
		}

		string strInput2 = strInput.substr(0, nd);
		int input2, digs2, div, l;
		try
		{
			input2 = stoi(strInput2);
		}
		catch (invalid_argument)
		{
			iResult = -1;
		}

		if (iResult == 0)
		{
			bool b10 = false;
		start2:
			digs2 = 0;
			if (input2 > 0)
				digs2 = (int)(floor(log10((double)input2)));
			div = 1;
			for (l = 0; l < digs2; l++)
				div *= 10;

			if (input2 < 20)
			{
				if (!strResult.empty())
					strResult += (b10 ? "-" : " ");
				strResult += ones[input2];
				b10 = false;
			}
			else if (input2 < 100)
			{
				if (!strResult.empty())
					strResult += " ";
				strResult += tens[input2 / div];
				b10 = true;
				if ((input2 % div) != 0)
				{
					input2 = input2 % div;
					goto start2;
				}
			}
			else if (input2 < 1000)
			{
				if (!strResult.empty())
					strResult += " ";
				strResult += ones[input2 / div] + " " + tens[nTens - 1];
				if ((input2 % div) != 0)
				{
					input2 = input2 % div;
					goto start2;
				}
			}

			if (strInput.length() > 3)
			{
				if (!strResult.empty())
					strResult += " ";
				strResult += huns[nh - 1];
			}

			strInput = strInput.substr(nd);
			strInput.erase(0, strInput.find_first_not_of('0'));
			if (strInput.length())
				goto start;
		}
	}
	else
		iResult = -2;

	if (bNegative && iResult == 0)
		strResult = "Negative " + strResult;
	return iResult;
}

int CMathLib::ExpandRHS(string strInput, string& strResult)
{
	if (strInput.empty())
		return -1;

	int iResult = 0, iDigit;
	string strDigit, strDigitResult;

	strResult.clear();

	for (string::iterator it = strInput.begin(); iResult == 0 && it != strInput.end(); ++it)
	{
		strDigit = *it;
		try
		{
			iDigit = stoi(strDigit);
			strResult += ones[iDigit];
			if (it + 1 != strInput.end())
				strResult += " ";
		}
		catch (invalid_argument)
		{
			iResult = -1;
			break;
		}
	}
	return iResult;
}

int CMathLib::Contract(string strInput, string& strResult)
{
	if (strInput.empty())
		return -1;
	strResult.clear();

	int iResult = 0;
	bool bNegative = false;
	bool bPoint = false;

	vector<string> vstrTokens;
	Split(strInput, vstrTokens);

	bool bFound = false;
	vector<string> vstrNumbers;
	vector<vector<string> > vvstrNumbers;
	map<string, string>::iterator mit;
	vector<string>::iterator it;
	for (it = vstrTokens.begin(); !bPoint && it != vstrTokens.end(); ++it)
	{
		bFound = false;
		string strToken = *it;

		mit = m_mapWordTo99.find(strToken);
		if (mit != m_mapWordTo99.end())
		{
			vstrNumbers.push_back(mit->second);
			bFound = true;
		}
		else
		{
			mit = m_mapWordTo100.find(strToken);
			if (mit != m_mapWordTo100.end())
			{
				vstrNumbers.push_back(mit->second);
				vvstrNumbers.push_back(vstrNumbers);
				vstrNumbers.clear();
				bFound = true;
			}
		}

		if (!bFound)
		{
			if (strToken == "Negative")  // Make case insensitive
				bNegative = true;
			else if (strToken == "Point")
				bPoint = true;
			else
			{
				iResult = -1;
				break;
			}
		}
	}

	if ((bFound || bPoint) && !vstrNumbers.empty())
		vvstrNumbers.push_back(vstrNumbers);

	if (iResult == -1)
		return iResult;

	// Process the number groups
	string strNumber;
	for (vector<vector<string> >::iterator vvit = vvstrNumbers.begin(); vvit != vvstrNumbers.end(); ++vvit)
	{
		string strGroupNumber = *((*vvit).begin());
		for (vector<string>::iterator vit = (*vvit).begin() + 1; vit != (*vvit).end(); ++vit)
		{
			strNumber = *vit;
			if (strNumber.length() > 2 &&
				*(strNumber.end() - 1) == '0')
				strGroupNumber.append(strNumber.begin() + 1, strNumber.end());
			else
				strGroupNumber.replace(strGroupNumber.end() - strNumber.length(), strGroupNumber.end(), strNumber);
		}

		if (!strResult.empty())
			strResult.replace(strResult.end() - strGroupNumber.length(), strResult.end(), strGroupNumber);
		else
			strResult = strGroupNumber;
	}

	if (bNegative)
		strResult = "-" + strResult;

	if (bPoint)
	{
		strResult += ".";
		for (; iResult == 0 && it != vstrTokens.end(); ++it)
		{
			string strToken = *it;
			mit = m_mapWordTo99.find(strToken);
			if (mit != m_mapWordTo99.end())
				strResult += mit->second;
			else
				iResult = -1;
		}

	}
	return iResult;
}

int CMathLib::Expand(string strInput, string & strResult)
{
	int iResult = 0;
	if (strInput.empty())
		iResult = -1;
	else
	{
		size_t stP1 = strInput.find_first_of('.');
		size_t stP2 = string::npos;
		if (stP1 != string::npos)
		{
			stP2 = strInput.find_first_of('.', stP1 + 1);
			if (stP2 != string::npos)
				iResult = -1;
		}

		if (iResult == 0)
		{
			if (stP1 == string::npos)
				iResult = ExpandLHS(strInput, strResult);
			else
			{
				string strLhs = strInput.substr(0, stP1);
				iResult = ExpandLHS(strLhs, strResult);
				if (iResult == 0)
				{
					string strResult2;
					string strRhs = strInput.substr(stP1 + 1);
					iResult = ExpandRHS(strRhs, strResult2);
					if (iResult == 0)
						strResult += " Point " + strResult2;
				}
			}
		}
	}
	return iResult;
}

int CMathLib::Contract(string& strResult)
{
	if (m_Type == Type::Word)
	{
		if (m_strResult.empty())
		{
			int iRet = Contract(m_strToken, strResult);
			if (iRet == 0)
				m_strResult = strResult;
			return iRet;
		}
		else
		{
			strResult = m_strResult;
			return 0;
		}
	}
	else
		return -3;
}

int CMathLib::Expand(string& strResult)
{
	if (m_Type == Type::Number)
	{
		if (m_strResult.empty())
		{
			int iRet = Expand(m_strToken, strResult);
			if (iRet == 0)
				m_strResult = strResult;
			return iRet;
		}
		else
		{
			strResult = m_strResult;
			return 0;
		}
	}
	else
		return -3;
}

// Commented code works and sets up a slower lookup mechanism than the map
void CMathLib::Init()
{
	m_strResult.clear();
	for (int iOne = 0; iOne < nOnes; ++iOne)
		m_mapWordTo99[ones[iOne]] = nones[iOne];

	for (int iTen = 2; iTen < nTens; ++iTen)
		m_mapWordTo99[tens[iTen]] = ntens[iTen];

	for (int iTen = 2; iTen < nTens - 1; ++iTen)
	{
		for (int iOne = 1; iOne < 10; ++iOne)
		{
			string strWord = tens[iTen] + "-" + ones[iOne];
			string strNum = to_string(iTen * 10 + iOne);
			m_mapWordTo99[strWord] = strNum;
		}
	}

	for (int iHun = 0, nZero = 3; iHun < nHuns; iHun++, nZero += 3)
	{
		string strHun(nZero, '0');
		strHun = "1" + strHun;
		m_mapWordTo100[huns[iHun]] = strHun;
	}

	// Set the numbers type
	SetType();
}

void CMathLib::Split(string strInput, vector<string>& vstrTokens)
{
	if (strInput.empty())
		return;

	std::string strToken;
	size_t ipos;

	do
	{
		ipos = strInput.find(' ');
		if (ipos == string::npos)
			vstrTokens.push_back(strInput);
		else
		{
			strToken = strInput.substr(0, ipos);
			vstrTokens.push_back(strToken);
			ipos = strInput.find(' ');
			if (ipos != string::npos)
				strInput.erase(0, ipos + 1);
		}
	} while (ipos != string::npos);
}

void CMathLib::SetType()
{
	if (!m_strToken.empty())
	{
		if (Expand(m_strToken, m_strResult) == 0)
			m_Type = Type::Number;
		else if (Contract(m_strToken, m_strResult) == 0)
			m_Type = Type::Word;
	}
	else
		m_Type = Type::NotSet;
}

int CMathLib::BinarySearch(string& strSearch, const vector<string> & vec, int nSize)
{
	int nLeft = 0;
	int nRight = nSize - 1;
	int nMiddle;

	while (nLeft <= nRight)
	{
		nMiddle = nLeft + ((nRight - nLeft) / 2);
		if (vec[nMiddle].compare(strSearch) < 0)
			nLeft = nMiddle + 1;
		else if (vec[nMiddle].compare(strSearch) > 0)
			nRight = nMiddle - 1;
		else
			return nMiddle;
	}
	return -1;
}
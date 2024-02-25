#include "Lib.h"
#include "LibConst.h"
#pragma warning(disable:6385)

using namespace std;

mutex g_map_mutex;
bool g_bInit = false;
std::map<std::string, std::string, CILT> g_mapWordTo99;
std::map<std::string, std::string, CILT> g_mapWordTo100;

CMathLib::CMathLib()
{
	Init();

	m_Type = Type::NotSet;
}

CMathLib::CMathLib(string strToken) : m_strToken(strToken)
{
	Init();

	SetType();
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
		m_strResult = rhs.m_strResult;
		m_Type = rhs.m_Type;
	}
	return *this;
}

CMathLib& CMathLib::operator + (const CMathLib& rhs)
{
	CMathLib MLOut;
	if (m_Type != Type::NotSet && rhs.m_Type != Type::NotSet)
	{
		vector<CByte>::iterator lhs_it;
		vector<CByte>::const_iterator rhs_it;
		lhs_it = m_vBytes.begin();
		rhs_it = rhs.m_vBytes.begin();

		CByte ByteOut;
		do
		{
			ByteOut = *lhs_it++ + *rhs_it++;
		} while (lhs_it != m_vBytes.end() && rhs_it != rhs.m_vBytes.end());

		*this = MLOut;
	}
	return *this;
}

string CMathLib::WB()
{
	return g_huns[g_nHuns - 1];
}

int CMathLib::Expand(string strInput, string& strResult)
{
	if (strInput.empty())
		return -1;

	int iResult = 0;
	bool bNegative = false;
	int digs, ld, nd, nh;

	string strLhs;
	size_t stP1 = strInput.find_first_of('.');
	if (stP1 == string::npos)
		strLhs = strInput;
	else
		strLhs = strInput.substr(0, stP1);

	strResult.clear();
	if (*(strLhs.begin()) == '-')
	{
		bNegative = true;
		strLhs = strLhs.substr(1);
	}

start:
	digs = (int)strLhs.length() - 1;
	nh = digs / 3;
	if (nh <= g_nHuns)
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

		string strLhs2 = strLhs.substr(0, nd);
		int iLhs2, digs2, div, l;
		try
		{
			iLhs2 = stoi(strLhs2);
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
			if (iLhs2 > 0)
				digs2 = (int)(floor(log10((double)iLhs2)));
			div = 1;
			for (l = 0; l < digs2; l++)
				div *= 10;

			if (iLhs2 < 20)
			{
				if (!strResult.empty())
					strResult += (b10 ? "-" : " ");
				strResult += g_ones[iLhs2];
				b10 = false;
			}
			else if (iLhs2 < 100)
			{
				if (!strResult.empty())
					strResult += " ";
				strResult += g_tens[iLhs2 / div];
				b10 = true;
				if ((iLhs2 % div) != 0)
				{
					iLhs2 = iLhs2 % div;
					goto start2;
				}
			}
			else if (iLhs2 < 1000)
			{
				if (!strResult.empty())
					strResult += " ";
				strResult += g_ones[iLhs2 / div] + " " + g_tens[g_nTens - 1];
				if ((iLhs2 % div) != 0)
				{
					iLhs2 = iLhs2 % div;
					goto start2;
				}
			}

			if (strLhs.length() > 3)
			{
				if (!strResult.empty())
					strResult += " ";
				strResult += g_huns[nh - 1];
			}

			strLhs = strLhs.substr(nd);
			strLhs.erase(0, strLhs.find_first_not_of('0'));
			if (strLhs.length())
				goto start;
		}
	}
	else
		iResult = -2;

	if (bNegative && iResult == 0)
		strResult = "Negative " + strResult;

	if (iResult == 0 && stP1 != string::npos)
	{
		strResult += " Point";
		for (string::iterator it = strInput.begin() + stP1 + 1; iResult == 0 && it != strInput.end(); ++it)
		{
			try
			{
				strResult += " " + g_ones[*it - '0'];
			}
			catch (invalid_argument)
			{
				iResult = -1;
				break;
			}
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

		mit = g_mapWordTo99.find(strToken);
		if (mit != g_mapWordTo99.end())
		{
			vstrNumbers.push_back(mit->second);
			bFound = true;
		}
		else
		{
			mit = g_mapWordTo100.find(strToken);
			if (mit != g_mapWordTo100.end())
			{
				vstrNumbers.push_back(mit->second);
				vvstrNumbers.push_back(vstrNumbers);
				vstrNumbers.clear();
				bFound = true;
			}
		}

		if (!bFound)
		{
			if (Equal(strToken, "Negative"))
				bNegative = true;
			else if (Equal(strToken, "Point"))
				bPoint = true;
			if (!bNegative && !bPoint)
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
			mit = g_mapWordTo99.find(strToken);
			if (mit != g_mapWordTo99.end())
				strResult += mit->second;
			else
				iResult = -1;
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

void CMathLib::Init()
{
	lock_guard<mutex> guard(g_map_mutex);

	if (g_bInit)
		return;

	for (int iOne = 0; iOne < g_nOnes; ++iOne)
		g_mapWordTo99[g_ones[iOne]] = g_nones[iOne];

	for (int iTen = 2; iTen < g_nTens; ++iTen)
		g_mapWordTo99[g_tens[iTen]] = g_ntens[iTen];

	for (int iTen = 2; iTen < g_nTens - 1; ++iTen)
	{
		for (int iOne = 1; iOne < 10; ++iOne)
		{
			string strWord = g_tens[iTen] + "-" + g_ones[iOne];
			string strNum = to_string(iTen * 10 + iOne);
			g_mapWordTo99[strWord] = strNum;
		}
	}

	for (int iHun = 0, nZero = 3; iHun < g_nHuns; iHun++, nZero += 3)
	{
		string strHun(nZero, '0');
		strHun = "1" + strHun;
		g_mapWordTo100[g_huns[iHun]] = strHun;
	}

	g_bInit = true;
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
		if (m_Type != Type::NotSet)
			ToBase2();
	}
	else
		m_Type = Type::NotSet;
}

int CMathLib::ToBase2()
{
	if (m_strToken.empty())
		return -1;

	string strIn;
	if (m_Type == Type::Number)
		strIn = m_strToken;
	else
	{
		int iRet = Contract(m_strToken, strIn);
		if (iRet != 0)
			return iRet;
	}

	string strOut;
	uint8_t idnm = 0, icnt = 0, sum = 0;
	deque<char> binary;
	m_vBytes.clear();

	string::iterator it = strIn.begin();
	for (;;)
	{
		// Compute the denominator of the division
		idnm = idnm * 10 + *it - '0';
		if (idnm < 2 && it + 1 != strIn.end())
		{
			// Carry a 0
			if (!strOut.empty())
				strOut += '0';

			// The denominator has to be greater than 2 now
			idnm = idnm * 10 + (*(it + 1) - '0');

			// Move to the next character
			it += 2;
		}
		else
		{
			// Check for the sentinel that completes the conversion
			if (strIn.length() == 1 && idnm < 2)
			{
				binary.push_front('0' + idnm);
				if (idnm)
					sum += g_bitval[icnt];
				m_vBytes.push_back(CByte(sum));
				break;
			}

			// Move to the next character
			it++;
		}

		// Append the digit to the output that becomes the new input from integer division by 2
		strOut += '0' + idnm / 2;
		idnm = idnm % 2;

		// Has the input been processed
		if (it == strIn.end())
		{
			// Add the remainder of 0 or 1 to the binary string
			binary.push_front('0' + idnm);
			if (idnm)
				sum += g_bitval[icnt];
			icnt++;
			if (icnt == 8)
			{
				m_vBytes.push_back(CByte(sum));
				icnt = 0;
				sum = 0;
			}

			// Reset and start over
			strIn = strOut;
			strOut.clear();
			idnm = 0;
			it = strIn.begin();
		}
	}
	
	// Append the binary string
	m_strBinary.append(binary.begin(), binary.end());

	return 0;
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

bool Equal(const std::string& strLHS, const std::string& strRHS)
{
	bool bEqual = true;
	if (strLHS.length() != strRHS.length())
		bEqual = false;
	else
	{
		for (size_t stIdx = 0; bEqual && stIdx < strLHS.length(); ++stIdx)
		{
			if (tolower(*(strLHS.begin() + stIdx)) !=
				tolower(*(strRHS.begin() + stIdx)))
				bEqual = false;
		}
	}
	return bEqual;
}

string Base10toBase2(string strin)
{
	vector<CByte> vb;
	string strout;
	string strbin;
	uint8_t idnm = 0, icnt = 0, sum = 0;
	string::iterator it = strin.begin();
	for (;;)
	{
		// Compute the denominator of the division
		idnm = idnm * 10 + *it - '0';
		if (idnm < 2 && it + 1 != strin.end())
		{
			// Carry a 0
			if (!strout.empty())
				strout += '0';

			// The denominator has to be greater than 2 now
			idnm = idnm * 10 + (*(it + 1) - '0');

			// Move to the next character
			it += 2;
		}
		else
		{
			// Check for the sentinel that completes the conversion
			if (strin.length() == 1 && idnm < 2)
			{
				strbin += '0' + idnm;
				if (idnm)
					sum += g_bitval[icnt];
				vb.push_back(CByte(sum));
				break;
			}

			// Move to the next character
			it++;
		}

		// Append the digit to the output that becomes the new input from integer division by 2
		strout += '0' + idnm / 2;
		idnm = idnm % 2;

		// Has the input been processed
		if (it == strin.end())
		{
			// Add the remainder of 0 or 1 to the binary string
			strbin += '0' + idnm;
			if (idnm)
				sum += g_bitval[icnt];
			icnt++;
			if (icnt == 8)
			{
				vb.push_back(CByte(sum));
				icnt = 0;
				sum = 0;
			}

			// Reset and start over
			strin = strout;
			strout.clear();
			idnm = 0;
			it = strin.begin();
		}
	}
	//	for (std::string::reverse_iterator rit = strbin.rbegin(); rit != strbin.rend(); ++rit)
	//		cout << *rit;
	//	cout << endl;
	std::reverse(strbin.begin(), strbin.end());
	//	cout << strbin << endl;
	return strbin;
}

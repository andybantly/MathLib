#include "Number.h"
#include "Constants.h"
#pragma warning(disable:6385)

using namespace std;

mutex g_map_mutex;
bool g_bInit = false;
std::map<std::string, std::string, CILT> g_mapWordTo99;
std::map<std::string, std::string, CILT> g_mapWordTo100;

CNumber::CNumber()
{
	Init();
}

CNumber::CNumber(string strToken)
{
	Init();

	int iRet;
	iRet = Expand(strToken, m_strPhrase);
	if (iRet == 0)
		m_strNumber = strToken;
	else
	{
		iRet = Contract(strToken, m_strNumber);
		if (iRet == 0)
			m_strPhrase = strToken;
		else
			throw(std::exception("Invalid number"));
	}
	if (iRet == 0)
		ToBase2();
}

CNumber::CNumber(const CNumber& rhs)
{
	*this = rhs;
}

CNumber::~CNumber()
{
}

CNumber& CNumber::operator = (const CNumber& rhs)
{
	if (this != &rhs)
	{
		m_strNumber = rhs.m_strNumber;
		m_strPhrase = rhs.m_strPhrase;
		m_strBinary = rhs.m_strBinary;
	}
	return *this;
}

CNumber& CNumber::operator + (const CNumber& rhs)
{/*
	CNumber MLOut;
	if (m_Type != Type::NotSet && rhs.m_Type != Type::NotSet)
	{
		vector<CByte>::iterator lhs_it;
		vector<CByte>::const_iterator rhs_it;
		CByte Zero(0);
		unsigned int iCIn = 0;
		for (lhs_it = m_vBytes.begin(), rhs_it = rhs.m_vBytes.begin(); 
			lhs_it != m_vBytes.end() || rhs_it != rhs.m_vBytes.end();)
		{
			CByte & lhsb = lhs_it != m_vBytes.end() ? *lhs_it++ : Zero;
			const CByte & rhsb = rhs_it != rhs.m_vBytes.end() ? *rhs_it++ : Zero;
			lhsb.m_c.C.C0 = iCIn;
			CByte sumb = lhsb + rhsb;
			iCIn = sumb.m_c.C.C0;
			sumb.m_c.U = 0;
			MLOut.m_vBytes.push_back(sumb);
		}
		if (iCIn)
			MLOut.m_vBytes.push_back(CByte(1));

		if ((m_Type == Type::Number) && (rhs.m_Type == Type::Number))
		{ }
		else if ((m_Type == Type::Number) && (rhs.m_Type == Type::Word))
		{ }
		else if ((m_Type == Type::Word) && (rhs.m_Type == Type::Number))
		{ }
		else if ((m_Type == Type::Word) && (rhs.m_Type == Type::Word))
		{ }

		// Expand the binary to decimal
		ExpandBinary();

		*this = MLOut;
	}
	*/
	return *this;
}

string CNumber::WB()
{
	return g_huns[g_nHuns - 1];
}

int CNumber::Expand(string strInput, string& strResult)
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

int CNumber::Contract(string strInput, string& strResult)
{
	if (strInput.empty())
		return -1;
	strResult.clear();

	int iResult = 0;
	bool bNegative = false;
	bool bPoint = false;

	// Build the token list
	vector<string> vstrTokens;
	Split(strInput, vstrTokens);

	// Build the number groups
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

void CNumber::Init()
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

void CNumber::Split(const string& strInput, vector<string>& vstrTokens)
{
	if (strInput.empty())
		return;

	std::string strToken;
	size_t istart = 0, ipos;
	do
	{
		ipos = strInput.find(' ', istart);
		if (ipos == string::npos)
			vstrTokens.push_back(strInput.substr(istart));
		else
		{
			strToken = strInput.substr(istart, ipos - istart);
			vstrTokens.push_back(strToken);
			istart = ipos + 1;
		}
	} while (ipos != string::npos);
}

int CNumber::ToBase2()
{
	string strOut;
	uint8_t idnm = 0, icnt = 0, sum = 0;
	deque<char> binary;
	m_vBytes.clear();

	string strIn = m_strNumber;
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
			// Check for completion the conversion
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

			// If 8 bits have been processed, store the numerical value
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

void CNumber::ExpandBinary()
{
	unsigned int bit;
	uint64_t uiPos = 1;
	string strLastNum = "0", strNum = "1";
	string strSum;

	vector<CByte>::iterator bits = m_vBytes.begin();
	CByte Byte = *bits;
	do
	{
		uint8_t iProd;
		deque<char> mout;
		bool bCarry = false;
		for (string::reverse_iterator rit = strNum.rbegin(); rit != strNum.rend(); )
		{
			uint8_t iMP = *rit++ - '0';
			iProd = 2 * iMP;
			if (bCarry)
			{
				iProd++;
				bCarry = false;
			}
			if (iProd >= 10)
			{
				iProd -= 10;
				bCarry = true;
			} // suspect that multiplying by larger like 3,4,5,...,9 changes carry prod
			mout.push_front('0' + iProd);
		}
		if (bCarry)
			mout.push_front('1');

		bit = Byte.m_b.U & uiPos;
		if (bit)
		{
			Add(strNum, strLastNum, strSum);
			strLastNum = strSum;
		}
		strNum = string(mout.begin(), mout.end());

		uiPos *= 2;
		if ((uiPos % 256) == 0)
		{
			bits++;
			if (bits != m_vBytes.end())
			{
				Byte = *bits;
				uiPos = 1;
			}
		}
	} while (bits != m_vBytes.end());
}

void CNumber::Add(const string& strS1, const string& strS2, string& strSum)
{
	uint8_t iSum;
	deque<char> Sum;
	bool bCarry = false;
	char cZero = '0';

	string::const_reverse_iterator S1_rit;
	string::const_reverse_iterator S2_rit;
	for (S1_rit = strS1.rbegin(), S2_rit = strS2.rbegin();
		S1_rit != strS1.rend() || S2_rit != strS2.rend();)
	{
		iSum = ((S1_rit != strS1.rend() ? *S1_rit++ : cZero) - '0') +
			((S2_rit != strS2.rend() ? *S2_rit++ : cZero) - '0');
		if (bCarry)
		{
			iSum++;
			bCarry = false;
		}
		if (iSum >= 10)
		{
			iSum -= 10;
			bCarry = true;
		}
		Sum.push_front('0' + iSum);
	}
	if (bCarry)
		Sum.push_front('1');
	strSum = string(Sum.begin(), Sum.end());
}

int CNumber::BinarySearch(const string& strSearch, const vector<string> & vec, int nSize)
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
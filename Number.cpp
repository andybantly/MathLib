#include "Number.h"
#include "Constants.h"
#pragma warning(disable:6385)

using namespace std;

mutex g_map_mutex;
bool g_bInit = false;
std::map<std::string, std::string, CILT> g_mapWordTo99;
std::map<std::string, std::string, CILT> g_mapWordTo100;

CNumber::CNumber() : m_bNegative(false)
{
	Init();
}

CNumber::CNumber(const string& strInput) : m_bNegative(false)
{
	Init();
	
	SetNumber(strInput);
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
		m_bNegative = rhs.m_bNegative;
		m_strNumber = rhs.m_strNumber;
		m_strPhrase = rhs.m_strPhrase;
		m_strBinary = rhs.m_strBinary;
	}
	return *this;
}

CNumber& CNumber::operator = (const string& rhs)
{
	SetNumber(rhs);
	return *this;
}

CNumber CNumber::operator + (const CNumber& rhs)
{
	CNumber Out;
	if (m_bNegative == rhs.m_bNegative)
		Add(*this, rhs, m_bNegative, Out);
	else
	{
		pair<int, int> GT = Greater(*this, rhs);
		if (!m_bNegative && rhs.m_bNegative) // LHS positive, RHS negative
		{
			switch (GT.second)
			{
			case -1: // RHS > LHS
				Sub(rhs, *this, true, Out);
				break;
			case 1: // LHS > RHS
				Sub(*this, rhs, false, Out);
				break;
			default:
				Out = "0";
			}
		}
		else // LHS negative, RHS positive
		{
			switch (GT.second)
			{
			case -1: // RHS > LHS
				Sub(rhs, *this, false, Out);
				break;
			case 1: // LHS > RHS
				Sub(*this, rhs, true, Out);
				break;
			default:
				Out = "0";
			}
		}
	}
	return Out;
}

CNumber CNumber::operator - (const CNumber& rhs)
{
	CNumber Out;
	if ((!m_bNegative && rhs.m_bNegative) || // LHS positive, RHS negative
		(m_bNegative && !rhs.m_bNegative)) // LHS negative, RHS positive
		Add(*this, rhs, m_bNegative, Out);
	else
	{
		pair<int, int> GT = Greater(*this, rhs);
		if (!m_bNegative && !rhs.m_bNegative) // Both positive
		{
			switch (GT.first)
			{
			case -1: // ABS(RHS) > ABS(LHS)
				Sub(rhs, *this, true, Out);
				break;
			case 1: // ABS(LHS) > ABS(RHS)
				Sub(*this, rhs, false, Out);
				break;
			default:
				Out = "0"; // ABS(LHS) = ABS(RHS)
			}
		}
		else // Both negative
		{
			switch (GT.first)
			{
			case -1: // ABS(LHS) > ABS(RHS)
				Sub(*this, rhs, true, Out);
				break;
			case 1: // ABS(RHS) > ABS(LHS)
				Sub(rhs, *this, false, Out);
				break;
			default:
				Out = "0";
			}
		}
	}

	return Out;
}

void CNumber::SetNumber(const string& strInput)
{
	m_bNegative = false;
	if (!strInput.empty())
		m_bNegative = *(strInput.begin()) == '-';
	m_strNumber = strInput;
	m_strPhrase.clear();
	m_strBinary.clear();
}

string CNumber::WB()
{
	return g_huns[g_nHuns - 1];
}

int CNumber::Expand(const string& strInput, string& strResult)
{
	if (strInput.empty())
		return -1;

	int iResult = 0;
	m_bNegative = false;
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
		m_bNegative = true;
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
			strLhs.erase(0, strLhs.find_first_not_of(g_cZero));
			if (strLhs.length())
				goto start;
		}
	}
	else
		iResult = -2;

	if (m_bNegative && iResult == 0)
		strResult = "Negative " + strResult;

	if (iResult == 0 && stP1 != string::npos)
	{
		strResult += " Point";
		for (string::const_iterator it = strInput.begin() + stP1 + 1; iResult == 0 && it != strInput.end(); ++it)
		{
			try
			{
				strResult += " " + g_ones[*it - g_cZero];
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

int CNumber::Contract(const string& strInput, string& strResult)
{
	if (strInput.empty())
		return -1;
	strResult.clear();

	int iResult = 0;
	m_bNegative = false;
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
				m_bNegative = true;
			else if (Equal(strToken, "Point"))
				bPoint = true;
			if (!m_bNegative && !bPoint)
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
				*(strNumber.end() - 1) == g_cZero)
				strGroupNumber.append(strNumber.begin() + 1, strNumber.end());
			else
				strGroupNumber.replace(strGroupNumber.end() - strNumber.length(), strGroupNumber.end(), strNumber);
		}

		if (!strResult.empty())
			strResult.replace(strResult.end() - strGroupNumber.length(), strResult.end(), strGroupNumber);
		else
			strResult = strGroupNumber;
	}

	if (m_bNegative)
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
		string strHun(nZero, g_cZero);
		strHun = "1" + strHun;
		g_mapWordTo100[g_huns[iHun]] = strHun;
	}

	g_bInit = true;
}

int CNumber::Convert()
{
	int iRet = Expand(m_strNumber, m_strPhrase);
	if (iRet != 0)
	{
		m_strPhrase = m_strNumber;
		iRet = Contract(m_strPhrase, m_strNumber);
		if (iRet != 0)
			throw(std::exception("Invalid Number"));
	}
	return iRet;
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

const string& CNumber::GetNumber()
{
	return m_strNumber;
}

const string& CNumber::GetPhrase()
{
	if (m_strPhrase.empty())
		Convert();
	return m_strPhrase;
}

const string& CNumber::GetBinary()
{
	if (m_strBinary.empty())
		ToBase2(m_strNumber, m_strBinary);
	return m_strBinary;
}

void CNumber::ToBase2(const string& strInput, string& strResult)
{
	if (strInput.empty())
		return;
	string strOut;
	uint8_t idnm = 0;
	deque<char> binary;

	string strIn = strInput;
	string::iterator it = strIn.begin();
	if (m_bNegative)
		it++;
	for (;;)
	{
		// Compute the denominator of the division
		idnm = idnm * 10 + *it - g_cZero;
		if (idnm < 2 && it + 1 != strIn.end())
		{
			// Carry a 0
			if (!strOut.empty())
				strOut += g_cZero;

			// The denominator has to be greater than 2 now
			idnm = idnm * 10 + (*(it + 1) - g_cZero);

			// Move to the next character
			it += 2;
		}
		else
		{
			// Check for completion the conversion
			if (strIn.length() == 1 && idnm < 2)
			{
				binary.push_front(g_cZero + idnm);
				break;
			}

			// Move to the next character
			it++;
		}

		// Append the digit to the output that becomes the new input from integer division by 2
		strOut += g_cZero + idnm / 2;
		idnm = idnm % 2;

		// Has the input been processed
		if (it == strIn.end())
		{
			// Add the remainder of 0 or 1 to the binary string
			binary.push_front(g_cZero + idnm);

			// Reset and start over
			strIn = strOut;
			strOut.clear();
			idnm = 0;
			it = strIn.begin();
		}
	}
	if (m_bNegative)
		binary.push_front('-');

	// Append the binary string
	strResult.append(binary.begin(), binary.end());
}

void CNumber::ToBase10(const string& strInput, string& strResult)
{
	strResult = "0";
	if (strInput == "0")
		return;

	CNumber Out;
	uint64_t uiPos = 1;
	string strNum = "1";
	string::const_reverse_iterator crit = strInput.rbegin();
	do
	{
		uint8_t iProd;
		deque<char> mout;
		bool bCarry = false;
		for (string::reverse_iterator rit = strNum.rbegin(); rit != strNum.rend(); )
		{
			uint8_t iMP = *rit++ - g_cZero;
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
			mout.push_front(g_cZero + iProd);
		}

		if (bCarry)
			mout.push_front(g_cOne);

		if (*crit++ == g_cOne)
		{
			Add(CNumber(strNum), CNumber(strResult), false, Out);
			strResult = Out.GetNumber();
		}
		strNum = string(mout.begin(), mout.end());
	} while (crit != strInput.rend());
}

void CNumber::Add(const CNumber& Num1, const CNumber& Num2, bool bNeg, CNumber& Out)
{
	uint8_t iSum;
	deque<char> Sum;
	bool bCarry = false;

	const string& strS1 = Num1.m_strNumber;
	const string& strS2 = Num2.m_strNumber;

	string::const_reverse_iterator S1_crend = (Num1.m_bNegative ? strS1.rend() - 1 : strS1.rend());
	string::const_reverse_iterator S2_crend = (Num2.m_bNegative ? strS2.rend() - 1 : strS2.rend());

	for (string::const_reverse_iterator S1_crit = strS1.rbegin(), S2_crit = strS2.rbegin();
		S1_crit != S1_crend	|| S2_crit != S2_crend;)
	{
		uint8_t S1 = S1_crit != S1_crend ? *S1_crit++ : g_cZero;
		uint8_t S2 = S2_crit != S2_crend ? *S2_crit++ : g_cZero;

		uint8_t N1 = S1 - g_cZero;
		uint8_t N2 = S2 - g_cZero;

		iSum = N1 +	N2;

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

		Sum.push_front(g_cZero + iSum);
	}

	if (bCarry)
		Sum.push_front(g_cOne);

	if (bNeg)
		Sum.push_front('-');

	Out.SetNumber(string(Sum.begin(), Sum.end()));
}

void CNumber::Sub(const CNumber& Num1, const CNumber& Num2, bool bNeg, CNumber& Out)
{
	uint8_t iSum = 0, iSub = 0;
	deque<char> Sum;
	deque<char> LZ;

	const string& strS1 = Num1.m_strNumber;
	const string& strS2 = Num2.m_strNumber;

	string::const_reverse_iterator S1_crend = (Num1.m_bNegative ? strS1.rend() - 1 : strS1.rend());
	string::const_reverse_iterator S2_crend = (Num2.m_bNegative ? strS2.rend() - 1 : strS2.rend());

	for (string::const_reverse_iterator S1_crit = strS1.rbegin(), S2_crit = strS2.rbegin();
		S1_crit != S1_crend || S2_crit != S2_crend;)
	{
		uint8_t S1 = S1_crit != S1_crend ? *S1_crit++ : g_cZero;
		uint8_t S2 = S2_crit != S2_crend ? *S2_crit++ : g_cZero;

		uint8_t N1 = S1 - g_cZero;
		uint8_t N2 = S2 - g_cZero;

		if (N1 >= N2)
		{
			iSum = N1 - N2;
			if (iSub)
			{
				iSum -= iSub;
				iSub = 0;
			}
		}
		else
		{
			iSum = N1 + 10 - N2 - iSub;
			iSub = 1;
		}

		if (iSum)
		{
			if (!LZ.empty())
			{
				for (deque<char>::const_iterator cit = LZ.begin(); cit != LZ.end(); ++cit)
					Sum.push_front(g_cZero);
				LZ.clear();
			}
			Sum.push_front(g_cZero + iSum);
		}
		else
			LZ.push_front(g_cZero);
	}

	if (Sum.empty())
		Sum.push_front(g_cZero);
	else if (bNeg)
		Sum.push_front('-');

	Out.SetNumber(string(Sum.begin(), Sum.end()));
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

// Greater.first is LHS > RHS
// Greater.second is ABS(LHS) > ABS(RHS)
pair<int, int> CNumber::Greater(const CNumber& LHS, const CNumber& RHS)
{
	pair<int, int> GT(0, 0);

	const string& strLHS = LHS.m_strNumber;
	const string& strRHS = RHS.m_strNumber;

	if (LHS.m_bNegative && !RHS.m_bNegative)
		GT.first = -1;
	else if (!LHS.m_bNegative && RHS.m_bNegative)
		GT.first = 1;
	else if (!LHS.m_bNegative && !RHS.m_bNegative && strLHS.length() != strRHS.length())
		GT.first = strLHS.length() > strRHS.length() ? 1 : -1;
	else if (LHS.m_bNegative && RHS.m_bNegative && strLHS.length() != strRHS.length())
		GT.first = strLHS.length() > strRHS.length() ? -1 : 1;

	size_t n1Len = strLHS.length() - (LHS.m_bNegative ? 1 : 0);
	size_t n2Len = strRHS.length() - (RHS.m_bNegative ? 1 : 0);

	if (n1Len > n2Len)
		GT.second = 1;
	else if (n1Len < n2Len)
		GT.second = -1;

	string::const_iterator LHS_cbeg = (LHS.m_bNegative ? strLHS.begin() + 1 : strLHS.begin());
	string::const_iterator RHS_cbeg = (RHS.m_bNegative ? strRHS.begin() + 1 : strRHS.begin());

	for (string::const_iterator LHS_cit = LHS_cbeg, RHS_cit = RHS_cbeg;
		GT.second == 0 && (LHS_cit != strLHS.end() || RHS_cit != strRHS.end());)
	{
		uint8_t iLHS = (LHS_cit != strLHS.end() ? *LHS_cit++ : g_cZero) - g_cZero;
		uint8_t iRHS = (RHS_cit != strRHS.end() ? *RHS_cit++ : g_cZero) - g_cZero;

		if (iLHS < iRHS)
			GT.second = -1;
		else if (iLHS > iRHS)
			GT.second = 1;
	}

	if (GT.second)
	{
		if (GT.second == -1)
		{
			if ((!LHS.m_bNegative && !RHS.m_bNegative) ||
				(LHS.m_bNegative && !RHS.m_bNegative))
				GT.first = -1;
			else if ((!LHS.m_bNegative && RHS.m_bNegative) ||
				(LHS.m_bNegative && RHS.m_bNegative))
				GT.first = 1;
		}
		else if (GT.second == 1)
		{
			if ((!LHS.m_bNegative && !RHS.m_bNegative) ||
				(!LHS.m_bNegative && RHS.m_bNegative))
				GT.first = 1;
			else if ((LHS.m_bNegative && !RHS.m_bNegative) ||
				(LHS.m_bNegative && RHS.m_bNegative))
				GT.first = -1;
		}
	}
		
	return GT;
}
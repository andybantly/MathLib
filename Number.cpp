#include "Number.h"
#include "Constants.h"
#include <sstream>
#pragma warning(disable:6385)

using namespace std;

static map<string, string, CILT> g_mapWordTo99;
static map<string, string, CILT> g_mapWordTo100; 

static const CNumber g_None("-1");
static const CNumber g_Zero("0");
static const CNumber g_One("1");
static const CNumber g_Two("2");

static const string g_one("1");
static const string g_none("-1");

CNumber::CNumber() : m_bNegative(false), m_bZero(false), m_iDecPos(0)
{
	m_strNumber.clear();
	m_strPhrase.clear();
	m_strBinary.clear();
}

CNumber::CNumber(const string& strInput)
{
	SetNumber(strInput);
}

CNumber::CNumber(const char* pInput)
{
	SetNumber(pInput);
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
		m_bZero = rhs.m_bZero;
		m_strNumber = rhs.m_strNumber;
		m_iDecPos   = rhs.m_iDecPos;
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

CNumber& CNumber::operator = (const char* prhs)
{
	SetNumber(prhs);
	return *this;
}

CNumber CNumber::operator + (const CNumber& rhs)
{
	CNumber Out;
	if (m_bNegative == rhs.m_bNegative)
		Add(*this, rhs, m_bNegative, Out);
	else
	{
		const int iGT = Greater(*this, rhs, GT::Absolute);
		if (!m_bNegative && rhs.m_bNegative) // LHS positive, RHS negative
		{
			switch (iGT)
			{
			case -1:
				Sub(rhs, *this, true, Out);
				break;
			case 1:
				Sub(*this, rhs, false, Out);
				break;
			default:
				Out = "0";
			}
		}
		else // LHS negative, RHS positive
		{
			switch (iGT)
			{
			case -1:
				Sub(rhs, *this, false, Out);
				break;
			case 1:
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
		const int iGT = Greater(*this, rhs);
		if (!m_bNegative)
		{
			switch (iGT)
			{
			case -1:
				Sub(rhs, *this, true, Out);
				break;
			case 1:
				Sub(*this, rhs, false, Out);
				break;
			default:
				Out = "0";
			}
		}
		else
		{
			switch (iGT)
			{
			case -1:
				Sub(*this, rhs, true, Out);
				break;
			case 1:
				Sub(rhs, *this, false, Out);
				break;
			default:
				Out = "0";
			}
		}
	}

	return Out;
}

CNumber CNumber::operator * (const CNumber& rhs)
{
	CNumber Out;
	Mul(*this, rhs, m_bNegative != rhs.m_bNegative, Out);
	return Out;
}

CNumber CNumber::operator / (const CNumber& rhs)
{
	CNumber Out;
	Div(*this, rhs, m_bNegative != rhs.m_bNegative, Out);
	return Out;
}

CNumber CNumber::operator % (const CNumber& rhs)
{
	CNumber Rem;
	Mod(*this, rhs, m_bNegative, Rem);
	return Rem;
}

const bool CNumber::operator < (const CNumber& rhs) const
{
	return Greater(*this, rhs) < 0;
}

const bool CNumber::operator <= (const CNumber& rhs) const
{
	return Greater(*this, rhs) <= 0;
}

const bool CNumber::operator > (const CNumber& rhs) const
{
	return Greater(*this, rhs) > 0;
}

const bool CNumber::operator >= (const CNumber& rhs) const
{
	return Greater(*this, rhs) >= 0;
}

const bool CNumber::operator == (const CNumber& rhs) const
{
	return Greater(*this, rhs) == 0;
}

const bool CNumber::operator != (const CNumber& rhs) const
{
	return Greater(*this, rhs) != 0;
}

void CNumber::SetNumber(const string& strInput)
{
	if (!strInput.empty())
	{
		m_bZero = true;
		m_bNegative = false;
		bool bDigit = false;
		bool bDec = false;
		deque<char> dqInput;
		string::const_iterator cit;
		for (cit = strInput.begin(); cit != strInput.end(); ++cit)
		{
			if (*cit == ' ')
				continue;
			break;
		}
		for (; cit != strInput.end(); ++cit)
		{
			if (!m_bNegative && *cit == '-')
			{
				if (bDigit || bDec || m_bNegative)
					throw(exception("Invalid Number"));
				dqInput.push_front('-');
				m_bNegative = true;
				continue;
			}

			if (*cit == g_cDecSep)
			{
				if (bDec)
					throw(exception("Invalid Number"));
				bDec = true;
				if (dqInput.size() == 0)
					dqInput.push_back(g_cZero);
				dqInput.push_back(g_cDecSep);
				continue;
			}

			if (isdigit(*cit))
			{
				if (*cit == g_cZero)
				{
					if (dqInput.size() == 0)
						continue;
					if (m_bNegative && dqInput.size() == 1)
						continue;
				}

				if (m_bZero && *cit != g_cZero)
					m_bZero = false;
				dqInput.push_back(*cit);
				bDigit = true;
				continue;
			}
			
			if (!isdigit(*cit))
			{
				string strResult;
				if (Contract(strInput, strResult) == 0)
					SetNumber(strResult); // Sometimes recursion is good
				return;
			}
		}

		while (bDec && dqInput.size() > 0 && *(dqInput.end() - 1) == g_cZero)
			dqInput.pop_back();
		if (dqInput.size() > 0 && *(dqInput.end() - 1) == g_cDecSep)
			dqInput.pop_back();
		if (dqInput.size() > 0)
			m_strNumber = string(dqInput.begin(), dqInput.end());
		else
			m_strNumber = "0";

		size_t stPos = m_strNumber.find(g_cDecSep);
		m_iDecPos = stPos != string::npos ? m_strNumber.length() - stPos : 0;
	}
	else
	{
		m_strNumber.clear();
		m_bNegative = false;
		m_bZero = false;
		m_iDecPos = 0;
	}

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
	strResult.clear();

	int iResult = 0;
	m_bNegative = false;
	int digs, nd, nh;

	string strLhs;
	size_t stP1 = strInput.find(g_cDecSep);
	if (stP1 == string::npos)
		strLhs = strInput;
	else
		strLhs = strInput.substr(0, stP1);
	if (strLhs.empty())
		strLhs = g_cZero;

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
		nd = digs % 3 + 1;
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
		for (string::const_iterator cit = strInput.begin() + stP1 + 1; iResult == 0 && cit != strInput.end(); ++cit)
		{
			try
			{
				strResult += " " + g_ones[*cit - g_cZero];
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
			if (TextEqual(strToken, "Negative"))
				m_bNegative = true;
			else if (TextEqual(strToken, "Point"))
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

int CNumber::Convert()
{
	int iRet = Expand(m_strNumber, m_strPhrase);
	if (iRet != 0)
	{
		m_strPhrase = m_strNumber;
		iRet = Contract(m_strPhrase, m_strNumber);
		if (iRet != 0)
			throw(exception("Invalid Number"));
	}
	return iRet;
}

void CNumber::Split(const string& strInput, vector<string>& vstrTokens, const char cFind)
{
	vstrTokens.clear();
	if (strInput.empty())
		return;

	string strToken;
	size_t istart = 0, ipos;
	do
	{
		ipos = strInput.find(cFind, istart);
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

int CNumber::ToBase2(const string& strInput, string& strResult)
{
	if (strInput.empty())
		return -1;
	strResult.clear();

	vector<string> vstrBinary;
	Split(strInput, vstrBinary, g_cDecSep);

	string strOut;
	uint8_t idnm = 0;
	deque<char> binary;

	string strIn;
	if (m_bNegative)
		strIn = vstrBinary[0].substr(1);
	else
		strIn = vstrBinary[0];
	if (strIn.empty())
		strIn = "0";

	string::const_iterator cit = strIn.begin();
	for (;;)
	{
		// Compute the denominator of the division
		idnm = idnm * 10 + *cit - g_cZero;
		if (idnm < 2 && cit + 1 != strIn.end())
		{
			// Carry a 0
			if (!strOut.empty())
				strOut += g_cZero;

			// The denominator has to be greater than 2 now
			idnm = idnm * 10 + (*(cit + 1) - g_cZero);

			// Move to the next character
			cit += 2;
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
			cit++;
		}

		// Append the digit to the output that becomes the new input from integer division by 2
		strOut += g_cZero + idnm / 2;
		idnm = idnm % 2;

		// Has the input been processed
		if (cit == strIn.end())
		{
			// Add the remainder of 0 or 1 to the binary string
			binary.push_front(g_cZero + idnm);

			// Reset and start over
			strIn = strOut;
			strOut.clear();
			idnm = 0;
			cit = strIn.begin();
		}
	}

	// Now handle the fractional part
	if (vstrBinary.size() != 1)
	{
		binary.push_back(g_cDecSep);
		CNumber Fraction("0." + vstrBinary[1]);
		for (int nDigs = 0;nDigs < 64 && !Fraction.m_bZero; ++nDigs)
		{
			Fraction = Fraction + Fraction;
			if (Fraction >= g_One)
			{
				binary.push_back(g_cOne);
				if (Fraction == g_One)
					break;
				Split(Fraction.GetNumber(), vstrBinary, g_cDecSep);
				Fraction.SetNumber("0." + vstrBinary[1]);
			}
			else
				binary.push_back(g_cZero);
		}
	}

	if (m_bNegative)
		binary.push_front('-');

	// Append the binary string
	strResult.append(binary.begin(), binary.end());
	return 0;
}

int CNumber::ToBase10(const string& strInput, string& strResult)
{
	if (strInput.empty())
		return -1;
	strResult = "0";

	CNumber Out;
	string strNum = g_one;
	string::const_reverse_iterator crit = strInput.rbegin();
	string::const_reverse_iterator crend = m_bNegative ? strInput.rend() - 1 : strInput.rend();
	do
	{
		uint8_t iProd;
		deque<char> mout;
		bool bCarry = false;
		for (string::const_reverse_iterator crit2 = strNum.rbegin(); crit2 != strNum.rend(); )
		{
			uint8_t iMP = *crit2++ - g_cZero;
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
			}
			mout.push_front(g_cZero + iProd);
		}

		if (bCarry)
			mout.push_front(g_cOne);

		if (*crit++ == g_cOne)
		{
			Add(CNumber(strNum), CNumber(strResult), m_bNegative, Out);
			strResult = Out.GetNumber();
		}
		strNum = string(mout.begin(), mout.end());
	} while (crit != crend);
	return 0;
}

void CNumber::Add(const CNumber& Num1, const CNumber& Num2, bool bNeg, CNumber& Out)
{
	uint8_t iSum;
	deque<char> Sum;
	bool bCarry = false;

	const string& strS1 = Num1.m_strNumber;
	const string& strS2 = Num2.m_strNumber;

	size_t N1DP = Num1.m_iDecPos;
	size_t N2DP = Num2.m_iDecPos;
	size_t SDP = max(N1DP, N2DP);

	string::const_reverse_iterator S1_crend = (Num1.m_bNegative ? strS1.rend() - 1 : strS1.rend());
	string::const_reverse_iterator S2_crend = (Num2.m_bNegative ? strS2.rend() - 1 : strS2.rend());

	for (string::const_reverse_iterator S1_crit = strS1.rbegin(), S2_crit = strS2.rbegin();
		S1_crit != S1_crend || S2_crit != S2_crend;)
	{
		uint8_t S1, S2;
		if (N1DP != N2DP)
		{
			if (N1DP > N2DP)
			{
				S1 = S1_crit != S1_crend ? *S1_crit++ : g_cZero;
				S2 = g_cZero;
				N1DP--;
			}
			else
			{
				S1 = g_cZero;
				S2 = S2_crit != S2_crend ? *S2_crit++ : g_cZero;
				N2DP--;
			}
		}
		else
		{
			S1 = S1_crit != S1_crend ? *S1_crit++ : g_cZero;
			S2 = S2_crit != S2_crend ? *S2_crit++ : g_cZero;
		}

		if (S1 == g_cDecSep || S2 == g_cDecSep)
		{
			Sum.push_front(g_cDecSep);
			continue;
		}

		uint8_t N1 = S1 - g_cZero;
		uint8_t N2 = S2 - g_cZero;

		iSum = N1 + N2;

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

	if (*Sum.begin() == g_cDecSep)
		Sum.push_front(g_cZero);

	if (m_iDecPos > 0)
	{
		while (*(Sum.end() - 1) == g_cZero)
			Sum.pop_back();
		if (*(Sum.end() - 1) == g_cDecSep)
			Sum.pop_back();
	}

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

	size_t N1DP = Num1.m_iDecPos;
	size_t N2DP = Num2.m_iDecPos;
	size_t SDP = max(N1DP, N2DP);

	string::const_reverse_iterator S1_crend = (Num1.m_bNegative ? strS1.rend() - 1 : strS1.rend());
	string::const_reverse_iterator S2_crend = (Num2.m_bNegative ? strS2.rend() - 1 : strS2.rend());

	for (string::const_reverse_iterator S1_crit = strS1.rbegin(), S2_crit = strS2.rbegin();
		S1_crit != S1_crend || S2_crit != S2_crend;)
	{
		uint8_t S1, S2;
		if (N1DP != N2DP)
		{
			if (N1DP > N2DP)
			{
				S1 = S1_crit != S1_crend ? *S1_crit++ : g_cZero;
				S2 = g_cZero;
				N1DP--;
			}
			else
			{
				S1 = g_cZero;
				S2 = S2_crit != S2_crend ? *S2_crit++ : g_cZero;
				N2DP--;
			}
		}
		else
		{
			S1 = S1_crit != S1_crend ? *S1_crit++ : g_cZero;
			S2 = S2_crit != S2_crend ? *S2_crit++ : g_cZero;
		}

		if (S1 == g_cDecSep || S2 == g_cDecSep)
		{
			if (!LZ.empty())
			{
				for (deque<char>::const_reverse_iterator crit = LZ.rbegin(); crit != LZ.rend(); ++crit)
					Sum.push_front(*crit);
				LZ.clear();
			}
			Sum.push_front(g_cDecSep);
			continue;
		}

		uint8_t N1 = S1 - g_cZero;
		uint8_t N2 = S2 - g_cZero;

		if (N1 >= N2 + iSub)
		{
			iSum = N1 - N2 - iSub;
			iSub = 0;
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
				for (deque<char>::const_reverse_iterator crit = LZ.rbegin(); crit != LZ.rend(); ++crit)
					Sum.push_front(*crit);
				LZ.clear();
			}
			Sum.push_front(g_cZero + iSum);
		}
		else
			LZ.push_front(g_cZero);
	}

	if (Sum.empty())
		Sum.push_front(g_cZero);
	else
	{
		if (*Sum.begin() == g_cDecSep)
			Sum.push_front(g_cZero);

		if (m_iDecPos > 0)
		{
			while (*(Sum.end() - 1) == g_cZero)
				Sum.pop_back();
			if (*(Sum.end() - 1) == g_cDecSep)
				Sum.pop_back();
		}

		if (bNeg)
			Sum.push_front('-');
	}

	Out.SetNumber(string(Sum.begin(), Sum.end()));
}

void CNumber::Mul(const CNumber& Num1, const CNumber& Num2, bool bNeg, CNumber& Out)
{
	if (Num1.m_bZero || Num2.m_bZero)
	{
		Out.SetNumber("0");
		return;
	}

	deque<char> Mult, LZ;
	vector<string> vSum;
	uint8_t nZero = 0, iProd = 0, iRem = 0;

	const string& strS1 = Num1.m_strNumber;
	const string& strS2 = Num2.m_strNumber;

	string::const_reverse_iterator S1_crend = (Num1.m_bNegative ? strS1.rend() - 1 : strS1.rend());
	string::const_reverse_iterator S2_crend = (Num2.m_bNegative ? strS2.rend() - 1 : strS2.rend());

	for (string::const_reverse_iterator S2_crit = strS2.rbegin(); S2_crit != S2_crend; ++S2_crit)
	{
		for (int iZero = 0; iZero < nZero; ++iZero)
			LZ.push_front(g_cZero);

		uint8_t iCarry = 0;
		for (string::const_reverse_iterator S1_crit = strS1.rbegin(); S1_crit != S1_crend; ++S1_crit)
		{
			if (*S1_crit == g_cDecSep)
				S1_crit++;
			if (*S2_crit == g_cDecSep)
				S2_crit++;

			uint8_t N1 = (S1_crit != S1_crend ? *S1_crit : g_cZero) - g_cZero;
			uint8_t N2 = (S2_crit != S2_crend ? *S2_crit : g_cZero) - g_cZero;

			iProd = N1 * N2;

			if (iCarry)
			{
				iProd += iCarry;
				iCarry = 0;
			}

			uint8_t iVal;
			if (iProd >= 10)
			{
				iCarry = iProd / 10;
				iRem = iProd % 10;
				iVal = iRem;
			}
			else
				iVal = iProd;

			if (iVal)
			{
				if (!LZ.empty())
				{
					for (deque<char>::const_iterator cit = LZ.begin(); cit != LZ.end(); ++cit)
						Mult.push_front(g_cZero);
					LZ.clear();
				}
				Mult.push_front(iVal + g_cZero);
			}
			else
				LZ.push_front(g_cZero);
		}
		
		if (iCarry)
		{
			if (!LZ.empty())
			{
				for (deque<char>::const_iterator cit = LZ.begin(); cit != LZ.end(); ++cit)
					Mult.push_front(g_cZero);
			}
			Mult.push_front(iCarry + g_cZero);
		}

		if (!Mult.empty())
		{
			if (*(Mult.begin()) == g_cDecSep)
				Mult.push_front(g_cZero);
			if (bNeg)
				Mult.push_front('-');
			vSum.push_back(string(Mult.begin(), Mult.end()));
		}
		Mult.clear();
		LZ.clear();
		
		nZero++;
	}

	if (Mult.size())
	{
		vSum.push_back(string(Mult.begin(), Mult.end()));
		Mult.clear();
	}
	
	if (vSum.size())
	{
		vector<string>::const_iterator vcit = vSum.begin();
		Out.SetNumber(*vcit++);
		for (; vcit != vSum.end(); ++vcit)
			Out = Out + *vcit;
		size_t iDP = 0;
		if (Num1.m_iDecPos)
			iDP += Num1.m_iDecPos - 1;
		if (Num2.m_iDecPos)
			iDP += Num2.m_iDecPos - 1;
		if (iDP)
		{
			string & strNumber = Out.m_strNumber;
			strNumber.insert(strNumber.begin() + strNumber.length() - iDP, g_cDecSep);
			if (*(strNumber.begin()) == g_cDecSep)
				strNumber.insert(strNumber.begin(), g_cZero);
			size_t nSize = strNumber.length();
			string::const_reverse_iterator rbeg = strNumber.rbegin();
			while (*rbeg == g_cZero)
			{
				rbeg++;
				nSize--;
			}
			if (*rbeg == g_cDecSep)
				nSize--;
			strNumber.resize(nSize);
			Out.SetNumber(strNumber);
		}
	}
	else
		Out.SetNumber("0");
}

void CNumber::Div(const CNumber& Num1, const CNumber& Num2, bool bNeg, CNumber& Out)
{
	if (Num2.m_bZero)
		return; // DIV BY 0

	if (Num1.m_bZero)
	{
		Out = g_Zero;
		return; // 0 DIV BY
	}

	if (Greater(Num1.m_strNumber, Num2.m_strNumber, GT::Absolute) == 0)
	{
		Out = !bNeg ? g_One : g_None;
		return;
	}
	else
		Out = g_Zero;

	CNumber NBIN = !bNeg ? g_One : g_None;
	CNumber N2DB = Num2;
	CNumber TMP;
	vector<pair<CNumber, CNumber> > vMultTableVec;
	vMultTableVec.push_back(pair<CNumber, CNumber>(NBIN, N2DB));
	while (Greater(Num1, N2DB, GT::Absolute) >= 0)
	{
		Mul(N2DB, g_Two, bNeg, TMP); N2DB = TMP;
		Mul(NBIN, g_Two, bNeg, TMP); NBIN = TMP;
		vMultTableVec.push_back(pair<CNumber, CNumber>(NBIN, N2DB));
	}

	CNumber REM = Num1;
	vector<pair<CNumber, CNumber> >::reverse_iterator vit = vMultTableVec.rbegin() + 1;
	for (; vit != vMultTableVec.rend(); ++vit)
	{
		if (Greater(REM, vit->second, GT::Absolute) >= 0)
		{
			Sub(REM, vit->second, bNeg, REM);
			Add(vit->first, Out, bNeg, Out);
			if (Greater(REM, Num2, GT::Absolute) < 0)
				break;
		}
	}
}

void CNumber::Mod(const CNumber& Num1, const CNumber& Num2, bool bNeg, CNumber& Rem)
{
	if (Num2.m_bZero)
		return;

	if (Num1.m_bZero || Greater(Num1.m_strNumber, Num2.m_strNumber, GT::Absolute) == 0)
	{
		Rem.SetNumber("0");
		return;
	}

	CNumber NBIN(!bNeg ? g_one : g_none);
	CNumber N2DB = Num2;
	CNumber TMP;
	vector<pair<CNumber, CNumber> > vMultTableMap;
	vMultTableMap.push_back(pair<CNumber, CNumber>(NBIN, N2DB));
	while (Greater(Num1, N2DB, GT::Absolute) >= 0)
	{
		Mul(N2DB, g_Two, bNeg, TMP); N2DB = TMP;
		Mul(NBIN, g_Two, bNeg, TMP); NBIN = TMP;
		vMultTableMap.push_back(pair<CNumber, CNumber>(NBIN, N2DB));
	}

	CNumber N1 = Num1;
	vector<pair<CNumber, CNumber> >::reverse_iterator vit = vMultTableMap.rbegin() + 1;
	for (;vit != vMultTableMap.rend(); ++vit)
	{
		if (Greater(N1, vit->second, GT::Absolute) >= 0)
		{
			Sub(N1, vit->second, bNeg, N1);
			Add(vit->first, Rem, bNeg, Rem);
			if (Greater(N1, Num2, GT::Absolute) < 0)
				break;
		}
	}
	Rem = N1;
}

void CNumber::DivFP(const CNumber& Num1, const CNumber& Num2, bool bNeg, CNumber& Out)
{
	if (Num2.m_bZero)
		return; // DIV BY 0

	if (Num1.m_bZero)
	{
		Out.SetNumber("0");
		return; // 0 DIV BY
	}

	if (Greater(Num1.m_strNumber, Num2.m_strNumber, GT::Absolute) == 0)
	{
		Out = !bNeg ? g_one : g_none;
		return;
	}
	else
		Out.SetNumber("0");

	CNumber NBIN(!bNeg ? g_one : g_none);
	CNumber N2DB = Num2;
	vector<pair<CNumber, CNumber> > vMultTableVec;
	vMultTableVec.push_back(pair<CNumber, CNumber>(NBIN, N2DB));
	while (Greater(Num1, N2DB, GT::Absolute) >= 0)
	{
		Mul(N2DB, g_Two, bNeg, N2DB);
		Mul(NBIN, g_Two, bNeg, NBIN);
		vMultTableVec.push_back(pair<CNumber, CNumber>(NBIN, N2DB));
	}

	CNumber REM = Num1;
	vector<pair<CNumber, CNumber> >::reverse_iterator vit = vMultTableVec.rbegin() + 1;
	for (; vit != vMultTableVec.rend(); ++vit)
	{
		if (Greater(REM, vit->second, GT::Absolute) >= 0)
		{
			Sub(REM, vit->second, bNeg, REM);
			Add(vit->first, Out, bNeg, Out);
			if (Greater(REM, Num2, GT::Absolute) < 0)
				break;
		}
	}

	if (REM != g_Zero)
	{
	}
}

bool TextEqual(const string& strLHS, const string& strRHS)
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

const int CNumber::Greater(const CNumber& LHS, const CNumber& RHS, const GT Type) const
{
	if (LHS.m_bZero && RHS.m_bZero)
		return 0;

	if (Type == GT::Regular)
	{
		if (LHS.m_bNegative && !RHS.m_bNegative)
			return -1;
		else if (!LHS.m_bNegative && RHS.m_bNegative)
			return 1;
	}
	const string& strLHS = LHS.m_strNumber;
	const string& strRHS = RHS.m_strNumber;

	size_t iOff1 = LHS.m_bNegative ? 1 : 0;
	size_t iOff2 = RHS.m_bNegative ? 1 : 0;

	size_t nLHS = strLHS.length() - iOff1 - LHS.m_iDecPos;
	size_t nRHS = strRHS.length() - iOff2 - RHS.m_iDecPos;

	uint8_t iLHS, iRHS;
	while (nLHS != nRHS)
	{
		if (nLHS > nRHS)
		{
			if (Type == GT::Regular)
				return LHS.m_bNegative ? -1 : 1;
			else
				return 1;
		}
		else if (nLHS < nRHS)
		{
			if (Type == GT::Regular)
				return LHS.m_bNegative ? 1 : -1;
			else
				return -1;
		}
	}

	string::const_iterator LHS_cit = strLHS.begin() + iOff1;
	string::const_iterator RHS_cit = strRHS.begin() + iOff2;

	string::const_iterator LHS_cend = strLHS.end();
	string::const_iterator RHS_cend = strRHS.end();

	while (LHS_cit != LHS_cend || RHS_cit != RHS_cend)
	{
		if (LHS_cit != LHS_cend && *LHS_cit == g_cDecSep)
			LHS_cit++;
		if (RHS_cit != RHS_cend && *RHS_cit == g_cDecSep)
			RHS_cit++;

		iLHS = (LHS_cit != LHS_cend ? *LHS_cit++ : g_cZero) - g_cZero;
		iRHS = (RHS_cit != RHS_cend ? *RHS_cit++ : g_cZero) - g_cZero;

		if (iLHS != iRHS)
		{
			if (iLHS > iRHS)
			{
				if (Type == GT::Regular)
					return LHS.m_bNegative ? -1 : 1;
				else
					return 1;
			}
			else if (iLHS < iRHS)
			{
				if (Type == GT::Regular)
					return LHS.m_bNegative ? 1 : -1;
				else
					return -1;
			}
		}
	}
	return 0;
}

void CNumber::Init()
{
	string strTen, strWord, strNum, strHun;
	for (int iOne = 0; iOne < g_nOnes; ++iOne)
		g_mapWordTo99[g_ones[iOne]] = g_nones[iOne];

	for (int iTen = 2; iTen < g_nTens; ++iTen)
		g_mapWordTo99[g_tens[iTen]] = g_ntens[iTen];

	for (int iTen = 2, iTens; iTen < g_nTens - 1; ++iTen)
	{
		iTens = iTen * 10;
		strTen = g_tens[iTen] + "-";
		for (int iOne = 1; iOne < 10; ++iOne)
		{
			strWord = strTen + g_ones[iOne];
			strNum = to_string(iTens + iOne);
			g_mapWordTo99[strWord] = strNum;
		}
	}

	for (int iHun = 0, nZero = 3; iHun < g_nHuns; iHun++, nZero += 3)
	{
		strHun = g_one + string(nZero, g_cZero);
		g_mapWordTo100[g_huns[iHun]] = strHun;
	}
}

ostream& operator<<(ostream& out, const CNumber& Number)
{
	out << Number.m_strNumber;
	return out;
}

// error C2338 : static_assert failed : 'Test writer must define specialization of ToString<const Q& q> 
// for your class class std::basic_string<wchar_t,struct std::char_traits<wchar_t>,class std::allocator<wchar_t> > 
// __cdecl Microsoft::VisualStudio::CppUnitTestFramework::ToString<class CNumber>(const class CNumber &).
wstring CNumber::ToString(const CNumber& rhs)
{
	string strNumber = rhs.m_strNumber;
	wstringstream wstrStream;
	wstrStream << strNumber.c_str();
	return wstrStream.str();
}
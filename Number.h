#pragma once
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <stack>
#include <ctime>
#include <thread>
#include <functional>

bool TextEqual(const std::string& strLHS, const std::string& strRHS);

class CNumber
{
    enum GT { Regular, Absolute};

public:
    // Constructor and copy constructors
    CNumber();
    CNumber(const char* pInput);
    CNumber(const std::string& strInput);
    CNumber(const CNumber& rhs);

    // Destructor
    ~CNumber();

public:
    // Assignment operators
    CNumber& operator = (const CNumber& rhs);
    CNumber& operator = (const std::string& rhs);
    CNumber& operator = (const char* prhs);

    // Arithmetic operators
    CNumber operator + (const CNumber& rhs);
    CNumber operator - (const CNumber& rhs);
    CNumber operator * (const CNumber& rhs);
    CNumber operator / (const CNumber& rhs);
    CNumber operator % (const CNumber& rhs);

    // Comparison operators
    const bool operator < (const CNumber& rhs) const;
    const bool operator <= (const CNumber& rhs) const;
    const bool operator > (const CNumber& rhs) const;
    const bool operator >= (const CNumber& rhs) const;
    const bool operator == (const CNumber& rhs) const;
    const bool operator != (const CNumber& rhs) const;

public:
    void SetNumber(const std::string& strInput);
    void SetPrecision(const int iPrecision);
    int Contract(const std::string& strInput, std::string& strResult);
	int Expand(const std::string& strInput, std::string& strResult);
    int ToBase2(const std::string& strInput, std::string& strResult);
    int ToBase10(const std::string& strInput, std::string& strResult);
    static std::string WB();
    const std::string& GetNumber();
    const std::string& GetPhrase();
    const std::string& GetBinary();
    static void Init();
    friend std::ostream& operator<<(std::ostream& out, const CNumber& Number);

    // error C2338 : static_assert failed : 'Test writer must define specialization of ToString<const Q& q> 
    // for your class class std::basic_string<wchar_t,struct std::char_traits<wchar_t>,class std::allocator<wchar_t> > 
    // __cdecl Microsoft::VisualStudio::CppUnitTestFramework::ToString<class CNumber>(const class CNumber &).
    static std::wstring ToString(const CNumber& Number);

protected:
    int Convert();
    void Split(const std::string& strInput, std::vector<std::string>& vstrTokens, const char cFind = ' ');
    void Add(const CNumber& Num1, const CNumber& Num2, bool bNeg, CNumber& Out);
    void Sub(const CNumber& Num1, const CNumber& Num2, bool bNeg, CNumber& Out);
    void Mul(const CNumber& Num1, const CNumber& Num2, bool bNeg, CNumber& Out);
    void Div(const CNumber& Num1, const CNumber& Num2, bool bNeg, CNumber& Out, CNumber& Rem, bool bMod = false);
    const int Greater(const CNumber& LHS, const CNumber& RHS, const GT Type = Regular) const;

    bool m_bNegative;
    bool m_bZero;
    size_t m_iDecPos; // 0 = Integer, > 0 = Floating Point
    int m_iFracRpt; // 0 = beginning of fractional part which means the whole fraction repeats vs. a subset of it, or -1 for does not repeat
    int m_iPrecision; // -1 to set the cutoff at 32, 0 for fractional part, > 0 for setting the number of decimals of precision

    std::string m_strNumber;
    std::string m_strPhrase;
    std::string m_strBinary;
};

struct CILT
{
    struct Compare
    {
        bool operator() (const unsigned char& c1, const unsigned char& c2) const
        {
            return tolower(c1) < tolower(c2);
        }
    };

    bool operator() (const std::string& strLhs, const std::string& strRhs) const
    {
        return std::lexicographical_compare
        (
            strLhs.begin(), strLhs.end(),
            strRhs.begin(), strRhs.end(),
            Compare()
        );
    }
};

class CDuration
{
	std::string m_str;
	clock_t start;
	clock_t finish;

public:
	CDuration(std::string str) : m_str(str), start(clock()), finish(start) {	}

	~CDuration()
	{
		finish = clock();
		double d = (double)(finish - start) / CLOCKS_PER_SEC;
		std::cout << m_str << " " << d << " seconds" << std::endl;
	}
};

class CStatistics
{
public:
    CStatistics() : m_nobs(0), m_dmean(0.0), m_s(0.0), m_dvar(0.0), m_dstddev(0.0) {};
    ~CStatistics() {};

protected:
    unsigned long m_nobs;
    long double m_dmean;
    long double m_s;
    long double m_dvar;
    long double m_dstddev;

    void update()
    {
        if (m_nobs > 1)
        {
            m_dvar = m_s / (m_nobs - 1);
            m_dstddev = sqrt(m_dvar);
        }
        else if (m_nobs == 0)
        {
            m_dmean = 0;
            m_dvar = 0;
            m_dstddev = 0;
        }
        else
        {
            m_dstddev = 0;
            m_dvar = 0;
        }
    }

public:
    bool RemObs(unsigned long iwght, long double dval, unsigned long nobs)
    {
        long double dlmean = (m_dmean * m_nobs - dval * iwght) / (m_nobs - iwght);
        if (m_nobs > nobs)
        {
            long double dls = m_s - iwght * (dval - dlmean) * (dval - (dlmean + iwght * (dval - dlmean) / m_nobs));
            if (dls > 0)
            {
                m_s = dls;
                m_dvar = m_s / (m_nobs - iwght - 1);
                m_dstddev = sqrt(m_dvar);
                m_dmean = dlmean;
                m_nobs -= iwght;

                return true;
            }
        }
        return false;
    }

    void AddObs(unsigned long iwght, double dv)
    {
        unsigned long uin = m_nobs + iwght;
        long double dx = iwght * (dv - m_dmean);
        long double dmean = m_dmean + dx / uin;
        long double ds = m_s + dx * (dv - dmean);

        if (_finite(ds))
        {
            m_nobs = uin;
            m_dmean = dmean;
            m_s = ds;
            update();
        }
    }

    void print() const
    {
        std::cout << "mean=" << m_dmean << " variance=" << m_dvar << " stddev=" << m_dstddev << std::endl;
    }
};

class Number
{
protected:
    class CByte
    {
    public:
        struct _Bits
        {
            unsigned B1 : 1;
            unsigned B2 : 1;
            unsigned B3 : 1;
            unsigned B4 : 1;
            unsigned B5 : 1;
            unsigned B6 : 1;
            unsigned B7 : 1;
            unsigned B8 : 1;
        };

        struct _Xtra
        {
            unsigned X0 : 1;
            unsigned X1 : 1;
            unsigned X2 : 1;
            unsigned X3 : 1;
            unsigned X4 : 1;
            unsigned X5 : 1;
            unsigned X6 : 1;
            unsigned X7 : 1;
        };

        union BITS
        {
            struct _Bits B;
            uint8_t U;
        };

        union XTRA
        {
            struct _Xtra X;
            uint8_t U;
        };

        CByte()
        {
            m_b.U = 0;
            m_x.U = 0;
        }

        CByte(uint8_t byte)
        {
            m_b.U = byte;
            m_x.U = 0;
        };

        CByte(const CByte& rhs)
        {
            *this = rhs;
        }

        CByte& operator = (const CByte& rhs)
        {
            if (this != &rhs)
            {
                m_b = rhs.m_b;
                m_x = rhs.m_x;
            }
            return *this;
        }

        operator std::string() const
        {
            char s[8];
            s[7] = m_b.B.B1 ? '1' : '0';
            s[6] = m_b.B.B2 ? '1' : '0';
            s[5] = m_b.B.B3 ? '1' : '0';
            s[4] = m_b.B.B4 ? '1' : '0';
            s[3] = m_b.B.B5 ? '1' : '0';
            s[2] = m_b.B.B6 ? '1' : '0';
            s[1] = m_b.B.B7 ? '1' : '0';
            s[0] = m_b.B.B8 ? '1' : '0';
            std::string bits = std::string(s, 8);
            return bits;
        }

        CByte& operator + (const CByte& rhs)
        {
            CByte Out;

            Out.m_b.B.B1 = m_x.X.X0 ^ (m_b.B.B1 ^ rhs.m_b.B.B1);  // SUM: Carry-in XOR (A XOR B)
            m_x.X.X1 = (m_b.B.B1 & rhs.m_b.B.B1) | (rhs.m_b.B.B1 & m_x.X.X0) | (m_b.B.B1 & m_x.X.X0); // CARRY: Carry-out AB OR BC OR ACin

            Out.m_b.B.B2 = m_x.X.X1 ^ (m_b.B.B2 ^ rhs.m_b.B.B2);
            m_x.X.X2 = (m_b.B.B2 & rhs.m_b.B.B2) | (rhs.m_b.B.B2 & m_x.X.X1) | (m_b.B.B2 & m_x.X.X1);

            Out.m_b.B.B3 = m_x.X.X2 ^ (m_b.B.B3 ^ rhs.m_b.B.B3);
            m_x.X.X3 = (m_b.B.B3 & rhs.m_b.B.B3) | (rhs.m_b.B.B3 & m_x.X.X2) | (m_b.B.B3 & m_x.X.X2);

            Out.m_b.B.B4 = m_x.X.X3 ^ (m_b.B.B4 ^ rhs.m_b.B.B4);
            m_x.X.X4 = (m_b.B.B4 & rhs.m_b.B.B4) | (rhs.m_b.B.B4 & m_x.X.X3) | (m_b.B.B4 & m_x.X.X3);

            Out.m_b.B.B5 = m_x.X.X4 ^ (m_b.B.B5 ^ rhs.m_b.B.B5);
            m_x.X.X5 = (m_b.B.B5 & rhs.m_b.B.B5) | (rhs.m_b.B.B5 & m_x.X.X4) | (m_b.B.B5 & m_x.X.X4);

            Out.m_b.B.B6 = m_x.X.X5 ^ (m_b.B.B6 ^ rhs.m_b.B.B6);
            m_x.X.X6 = (m_b.B.B6 & rhs.m_b.B.B6) | (rhs.m_b.B.B6 & m_x.X.X5) | (m_b.B.B6 & m_x.X.X5);

            Out.m_b.B.B7 = m_x.X.X6 ^ (m_b.B.B7 ^ rhs.m_b.B.B7);
            m_x.X.X7 = (m_b.B.B7 & rhs.m_b.B.B7) | (rhs.m_b.B.B7 & m_x.X.X6) | (m_b.B.B7 & m_x.X.X6);

            Out.m_b.B.B8 = m_x.X.X7 ^ (m_b.B.B8 ^ rhs.m_b.B.B8);
            Out.m_x.X.X0 = (m_b.B.B8 & rhs.m_b.B.B8) | (rhs.m_b.B.B8 & m_x.X.X7) | (m_b.B.B8 & m_x.X.X7);

            *this = Out;
            return *this;
        }

        CByte& operator - (const CByte& rhs)
        {
            CByte Out;

            Out.m_b.B.B1 = (m_b.B.B1 ^ rhs.m_b.B.B1) ^ m_x.X.X0; // DIFFERENCE: (A XOR B) XOR Borrow-in
            m_x.X.X1 = (~m_b.B.B1 & m_x.X.X0) | (~m_b.B.B1 & rhs.m_b.B.B1) | (rhs.m_b.B.B1 & m_x.X.X0); // BORROW: A'Borrow-in OR A'B OR AB (' = 2's complement)

            Out.m_b.B.B2 = (m_b.B.B2 ^ rhs.m_b.B.B2) ^ m_x.X.X1;
            m_x.X.X2 = (~m_b.B.B2 & m_x.X.X1) | (~m_b.B.B2 & rhs.m_b.B.B2) | (rhs.m_b.B.B2 & m_x.X.X1);

            Out.m_b.B.B3 = (m_b.B.B3 ^ rhs.m_b.B.B3) ^ m_x.X.X2;
            m_x.X.X3 = (~m_b.B.B3 & m_x.X.X2) | (~m_b.B.B3 & rhs.m_b.B.B3) | (rhs.m_b.B.B3 & m_x.X.X2);

            Out.m_b.B.B4 = (m_b.B.B4 ^ rhs.m_b.B.B4) ^ m_x.X.X3;
            m_x.X.X4 = (~m_b.B.B4 & m_x.X.X3) | (~m_b.B.B4 & rhs.m_b.B.B4) | (rhs.m_b.B.B4 & m_x.X.X3);

            Out.m_b.B.B5 = (m_b.B.B5 ^ rhs.m_b.B.B5) ^ m_x.X.X4;
            m_x.X.X5 = (~m_b.B.B5 & m_x.X.X4) | (~m_b.B.B5 & rhs.m_b.B.B5) | (rhs.m_b.B.B5 & m_x.X.X4);

            Out.m_b.B.B6 = (m_b.B.B6 ^ rhs.m_b.B.B6) ^ m_x.X.X5;
            m_x.X.X6 = (~m_b.B.B6 & m_x.X.X5) | (~m_b.B.B6 & rhs.m_b.B.B6) | (rhs.m_b.B.B6 & m_x.X.X5);

            Out.m_b.B.B7 = (m_b.B.B7 ^ rhs.m_b.B.B7) ^ m_x.X.X6;
            m_x.X.X7 = (~m_b.B.B7 & m_x.X.X6) | (~m_b.B.B7 & rhs.m_b.B.B7) | (rhs.m_b.B.B7 & m_x.X.X6);

            Out.m_b.B.B8 = (m_b.B.B8 ^ rhs.m_b.B.B8) ^ m_x.X.X7;
            Out.m_x.X.X0 = (~m_b.B.B8 & m_x.X.X7) | (~m_b.B.B8 & rhs.m_b.B.B8) | (rhs.m_b.B.B8 & m_x.X.X7);

            *this = Out;
            return *this;
        }

        uint8_t overFlow() const
        {
            return m_x.X.X0; // X0 used to indicate a carry/borrow
        }

        void setValue(const uint8_t rhs)
        {
            m_b.U = rhs;
        }

        void setXtra(const bool rhs)
        {
            m_x.X.X0 = rhs;
        }

    protected:
        BITS m_b;
        XTRA m_x;
    }; 

public:
    Number() : m_size(0), m_Bytes(0) {};

    Number(const std::string& strNumber)
    {
        ToBinary(strNumber);
    }

    Number(size_t size) : m_size(size), m_Bytes(new CByte[size]) {}

    ~Number()
    {
        delete[] m_Bytes;
    }

    // Operator at
    CByte& operator[](size_t index) 
    {
        if (index >= m_size) 
            throw std::out_of_range("Byte index out of range");
        return m_Bytes[index];
    }

    // Return size of the collection
    const size_t size() const 
    {
        return m_size;
    }

    Number& operator = (const Number& rhs)
    {
        if (this != &rhs)
        {
            m_size = rhs.m_size;
            m_Bytes = new CByte[size()];
            for (size_t iByte = 0; iByte < size(); ++iByte)
                m_Bytes[iByte] = rhs.m_Bytes[iByte];
        }
        return *this;
    }

    Number& operator = (const std::string& strNumber)
    {
        ToBinary(strNumber);
        return *this;
    }

    Number operator + (const Number& rhs) const
    {
        size_t l = size(), r = rhs.size();
        size_t stMax = l == r ? l : (l < r ? r : l);
        Number out(stMax + 1);
        CByte Zero(0);
        uint8_t of = 0;
        for (size_t st = 0; st < stMax; ++st)
        {
            CByte lb = st < l ? m_Bytes[st] : Zero;
            CByte rb = st < r ? rhs.m_Bytes[st] : Zero;
            CByte& ob = out.m_Bytes[st];
            if (of)
            {
                lb.setXtra(of);
                ob = lb + rb;
                lb.setXtra(0);
            }
            else
                ob = lb + rb;
            of = ob.overFlow();
            if (of)
                ob.setXtra(0);
        }

        if (of)
            out.m_Bytes[stMax].setValue(1);
        else
            out.m_size--;

        return out;
    }

    Number operator - (const Number& rhs) const
    {
        size_t l = size(), r = rhs.size();
        size_t stMax = l == r ? l : (l < r ? r : l);
        Number out(stMax + 1);
        CByte Zero(0);
        uint8_t of = 0;
        for (size_t st = 0; st < stMax; ++st)
        {
            CByte lb = st < l ? m_Bytes[st] : Zero;
            CByte rb = st < r ? rhs.m_Bytes[st] : Zero;
            CByte& ob = out.m_Bytes[st];
            if (of)
            {
                lb.setXtra(of);
                ob = lb - rb;
                lb.setXtra(0);
            }
            else
                ob = lb - rb;
            of = ob.overFlow();
            if (of)
                ob.setXtra(0);
        }

        if (of)
            out.m_Bytes[stMax].setValue(255);
        else
            out.m_size--;

        return out;
    }

    // Conversion functions

    void ToBinary(const std::string strNumber)
    {
        m_Bytes = 0;
        uint8_t pow[] = { 1,2,4,8,16,32,64,128 };

        std::string strInput = strNumber;
        if (strInput.empty())
            throw("Invalid number");

        std::string strOut;
        uint8_t idnm = 0;
        std::deque<char> binary;

        uint8_t bVal = 0;
        uint8_t bPos = 0;
        uint8_t bSiz = 0;
        std::vector<uint8_t> vbytes;

        std::string::const_iterator cit = strInput.begin();
        for (;;)
        {
            // Compute the denominator of the division
            idnm = idnm * 10 + *cit - '0';
            if (idnm < 2 && cit + 1 != strInput.end())
            {
                // Carry a 0
                if (!strOut.empty())
                    strOut += '0';

                // The denominator has to be greater than 2 now
                idnm = idnm * 10 + (*(cit + 1) - '0');

                // Move to the next character
                cit += 2;
            }
            else
            {
                // Check for completion the conversion
                if (strInput.length() == 1 && idnm < 2)
                {
                    /////////////////////////////////////
                    // Binary stream 0s and 1s

                    binary.push_front('0' + idnm);

                    /////////////////////////////////////
                    // Byte stream 0-255

                    bSiz++;
                    if (idnm)
                        bVal += pow[bPos];
                    bPos++;
                    if (bPos > 7)
                    {
                        vbytes.push_back(bVal);
                        bVal = 0;
                        bPos = 0;
                    }

                    /////////////////////////////////////

                    break;
                }

                // Move to the next character
                cit++;
            }

            // Append the digit to the output that becomes the new input from integer division by 2
            strOut += '0' + idnm / 2;
            idnm = idnm % 2;

            // Has the input been processed
            if (cit == strInput.end())
            {
                // Add the remainder of 0 or 1 to the binary string
                binary.push_front('0' + idnm);

                /////////////////////////////////////

                bSiz++;
                if (idnm)
                    bVal += pow[bPos];
                bPos++;
                if (bPos > 7)
                {
                    vbytes.push_back(bVal);
                    bVal = 0;
                    bPos = 0;
                }

                /////////////////////////////////////

                // Reset and restart (but not the incremental bytes, they carry over)
                strInput = strOut;
                strOut.clear();
                idnm = 0;
                cit = strInput.begin();
            }
        }
        if (bVal)
            vbytes.push_back(bVal);

        size_t size = uint8_t(vbytes.size());
        m_Bytes = new CByte[size];
        for (size_t iByte = 0; iByte < size; ++iByte)
            m_Bytes[iByte].setValue(vbytes[iByte]);
        m_size = size;
    }

    std::string ToDisplay()
    {
        std::string strResult = "0";
        if (size() == 0)
            return strResult;

        std::string strInput;
        for (size_t iByte = 0; iByte < size(); ++iByte)
            strInput += m_Bytes[size() - iByte - 1];

        const uint8_t cZero = '0', cOne = '1', cDec = '.';
        std::string strNum = "1";
        std::string::const_reverse_iterator crit = strInput.rbegin();
        std::string::const_reverse_iterator crend = strInput.rend();
        do
        {
            uint8_t iProd;
            std::deque<char> mout;
            bool bCarry = false;
            for (std::string::const_reverse_iterator crit2 = strNum.rbegin(); crit2 != strNum.rend(); )
            {
                uint8_t iMP = *crit2++ - cZero;
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
                mout.push_front(cZero + iProd);
            }

            if (bCarry)
                mout.push_front(cOne);

            if (*crit++ == cOne)
            {
                const std::string& strS1 = strNum;
                const std::string& strS2 = strResult;

                uint8_t iSum;
                std::deque<char> Sum;
                bool bCarry = false;

                std::string::const_reverse_iterator S1_crend = strS1.rend();
                std::string::const_reverse_iterator S2_crend = strS2.rend();

                for (std::string::const_reverse_iterator S1_crit = strS1.rbegin(), S2_crit = strS2.rbegin();
                    S1_crit != S1_crend || S2_crit != S2_crend;)
                {
                    uint8_t S1 = S1_crit != S1_crend ? *S1_crit++ : cZero;
                    uint8_t S2 = S2_crit != S2_crend ? *S2_crit++ : cZero;

                    if (S1 == cDec || S2 == cDec)
                    {
                        Sum.push_front(cDec);
                        continue;
                    }

                    uint8_t N1 = S1 - cZero;
                    uint8_t N2 = S2 - cZero;

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

                    Sum.push_front(cZero + iSum);
                }

                if (bCarry)
                    Sum.push_front(cOne);

                if (*Sum.begin() == cDec)
                    Sum.push_front(cZero);

                strResult = std::string(Sum.begin(), Sum.end());
            }
            strNum = std::string(mout.begin(), mout.end());
        } while (crit != crend);
        return strResult;
    }

private:
    size_t m_size;
    CByte* m_Bytes;
};
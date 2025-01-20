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

class CBytes 
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

        struct _Carry
        {
            unsigned C0 : 1;
            unsigned C1 : 1;
            unsigned C2 : 1;
            unsigned C3 : 1;
            unsigned C4 : 1;
            unsigned C5 : 1;
            unsigned C6 : 1;
            unsigned C7 : 1;
        };

        union BITS
        {
            struct _Bits B;
            uint8_t U;
        };

        union CARRY
        {
            struct _Carry C;
            uint8_t U;
        };

        CByte()
        {
            m_b.U = 0;
            m_c.U = 0;
        }

        CByte(uint8_t byte)
        {
            m_b.U = byte;
            m_c.U = 0;
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
                m_c = rhs.m_c;
            }
            return *this;
        }

        CByte& operator + (const CByte& rhs)
        {
            CByte Out;

            Out.m_b.B.B1 = m_c.C.C0 ^ (m_b.B.B1 ^ rhs.m_b.B.B1);
            m_c.C.C1 = (m_b.B.B1 & rhs.m_b.B.B1) | (rhs.m_b.B.B1 & m_c.C.C0) | (m_b.B.B1 & m_c.C.C0);

            Out.m_b.B.B2 = m_c.C.C1 ^ (m_b.B.B2 ^ rhs.m_b.B.B2);
            m_c.C.C2 = (m_b.B.B2 & rhs.m_b.B.B2) | (rhs.m_b.B.B2 & m_c.C.C1) | (m_b.B.B2 & m_c.C.C1);

            Out.m_b.B.B3 = m_c.C.C2 ^ (m_b.B.B3 ^ rhs.m_b.B.B3);
            m_c.C.C3 = (m_b.B.B3 & rhs.m_b.B.B3) | (rhs.m_b.B.B3 & m_c.C.C2) | (m_b.B.B3 & m_c.C.C2);

            Out.m_b.B.B4 = m_c.C.C3 ^ (m_b.B.B4 ^ rhs.m_b.B.B4);
            m_c.C.C4 = (m_b.B.B4 & rhs.m_b.B.B4) | (rhs.m_b.B.B4 & m_c.C.C3) | (m_b.B.B4 & m_c.C.C3);

            Out.m_b.B.B5 = m_c.C.C4 ^ (m_b.B.B5 ^ rhs.m_b.B.B5);
            m_c.C.C5 = (m_b.B.B5 & rhs.m_b.B.B5) | (rhs.m_b.B.B5 & m_c.C.C4) | (m_b.B.B5 & m_c.C.C4);

            Out.m_b.B.B6 = m_c.C.C5 ^ (m_b.B.B6 ^ rhs.m_b.B.B6);
            m_c.C.C6 = (m_b.B.B6 & rhs.m_b.B.B6) | (rhs.m_b.B.B6 & m_c.C.C5) | (m_b.B.B6 & m_c.C.C5);

            Out.m_b.B.B7 = m_c.C.C6 ^ (m_b.B.B7 ^ rhs.m_b.B.B7);
            m_c.C.C7 = (m_b.B.B7 & rhs.m_b.B.B7) | (rhs.m_b.B.B7 & m_c.C.C6) | (m_b.B.B7 & m_c.C.C6);

            Out.m_b.B.B8 = m_c.C.C7 ^ (m_b.B.B8 ^ rhs.m_b.B.B8);
            Out.m_c.C.C0 = (m_b.B.B8 & rhs.m_b.B.B8) | (rhs.m_b.B.B8 & m_c.C.C7) | (m_b.B.B8 & m_c.C.C7);

            *this = Out;
            return *this;
        }

        uint8_t overFlow() const
        {
            return (*this).m_c.C.C0; // Re-use C0 to indicate a carry, it can't ever start as 1
        }

        void setValue(const uint8_t rhs)
        {
            m_b.U = rhs;
        }

    protected:
        BITS m_b;
        CARRY m_c;
    }; 

public:
    CBytes() : m_size(0), m_Bytes(0) {};
    CBytes(const std::string& strNumber)
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

    CBytes(size_t size) : m_size(size), m_Bytes(new CByte[size]) {}

    ~CBytes() 
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

    CBytes& operator = (const CBytes& rhs)
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

    CBytes operator + (const CBytes& rhs) const
    {
        size_t l = size(), r = rhs.size();
        size_t stMax = l == r ? l : (l < r ? r : l);
        CBytes out(stMax);

        CByte Zero(0);
        for (size_t st = 0; st < stMax; ++st)
        {
            CByte lb = st < l ? m_Bytes[st] : Zero;
            CByte rb = st < r ? rhs.m_Bytes[st] : Zero;
            CByte& ob =  out.m_Bytes[st];
            ob = lb + rb;
        }
        return out;
    }

private:
    size_t m_size;
    CByte* m_Bytes;
};
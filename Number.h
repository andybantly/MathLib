#pragma once
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <stack>
#include <ctime>
#include <thread>
#include <mutex>
#include <functional>

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

bool Equal(const std::string& strLHS, const std::string& strRHS);

class CByte
{
    struct _Byte
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

    union BYTE
    {
        struct _Byte B;
        uint8_t U;
    };

    union CARRY
    {
        struct _Carry C;
        uint8_t U;
    };

public:
    friend class CNumber;

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

protected:
    BYTE m_b;
    CARRY m_c;
};

class CNumber
{
public:
    CNumber();
    CNumber(const std::string& strInput);
    CNumber(const CNumber& rhs);
    ~CNumber();

public:
    CNumber& operator = (const CNumber& rhs);
    CNumber& operator = (const std::string& rhs);
    CNumber operator + (const CNumber& rhs);
    CNumber operator - (const CNumber& rhs);
    CNumber operator * (const CNumber& rhs);
    operator const char * () { return m_strNumber.c_str(); }

public:
    void SetNumber(const std::string& strInput);
    int Contract(const std::string& strInput, std::string& strResult);
	int Expand(const std::string& strInput, std::string& strResult);
    void ToBase2(const std::string& strInput, std::string& strResult);
    void ToBase10(const std::string& strInput, std::string& strResult);
    static std::string WB();
    const std::string& GetNumber();
    const std::string& GetPhrase();
    const std::string& GetBinary();

protected:
    void Init();
    int Convert();
    void Split(const std::string& strInput, std::vector<std::string>& vstrTokens);
    void Add(const CNumber& Num1, const CNumber& Num2, bool bNeg, CNumber& Out);
    void Sub(const CNumber& Num1, const CNumber& Num2, bool bNeg, CNumber& Out);
    void Mul(const CNumber& Num1, const CNumber& Num2, bool bNeg, CNumber& Out);
    int BinarySearch(const std::string& strSearch, const std::vector<std::string> & vec, int nSize);
    std::pair<int, int> Greater(const CNumber& LHS, const CNumber& RHS);

    bool m_bNegative;
    std::string m_strNumber;
    std::string m_strPhrase;
    std::string m_strBinary;
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

class CRndPair
{
public:
    CRndPair()
    {
        m_iOp = rand() > RAND_MAX / 2 ? 1 : -1;
        m_iNum1 = (rand() * rand() * (rand() > RAND_MAX / 2 ? 1 : -1));
        m_iNum2 = (rand() * rand() * (rand() > RAND_MAX / 2 ? 1 : -1));
        m_strNum1 = std::to_string(m_iNum1);
        m_strNum2 = std::to_string(m_iNum2);

        if (m_iOp == 1)
            m_iSum = m_iNum1 + m_iNum2;
        else
            m_iSum = m_iNum1 - m_iNum2;
        m_strSum = std::to_string(m_iSum);
    }
    const int& OP() const { return m_iOp; }
    const std::string& Num1() { return m_strNum1; }
    const std::string& Num2() { return m_strNum2; }
    const std::string& Sum() { return m_strSum; }

protected:
    int m_iOp; // 1 = addition, -1 = subtraction
    int m_iNum1;
    int m_iNum2;
    int m_iSum;
    std::string m_strNum1;
    std::string m_strNum2;
    std::string m_strSum;
};
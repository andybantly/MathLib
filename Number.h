#pragma once
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <stack>
#include <ctime>
#include <thread>
#include <functional>

/*
Notes:
Arranges elements of a given type in a linear arrangement and enables fast random access to any element, 
and efficient insertion and deletion at the back of the container and also the front of the container.
TODO: Find best arrangement of different containers when converting
*/
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

class CBytes {
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

        bool hasOverFlow()
        {
            return (*this).m_c.C.C0;
        }

    protected:
        BYTE m_b;
        CARRY m_c;
    }; 

public:
    class Iterator {
    public:
        Iterator(CByte* ptr) : m_ptr(ptr) {}

        // Dereference operator
        CByte& operator*() 
        {
            return *m_ptr;
        }

        // Arrow operator
        CByte* operator->() 
        {
            return m_ptr;
        }

        // Pre-increment
        Iterator& operator++() 
        {
            ++m_ptr;
            return *this;
        }

        // Post-increment
        Iterator operator++(int) 
        {
            Iterator temp = *this;
            ++m_ptr;
            return temp;
        }

        // Pre-decrement
        Iterator& operator--() 
        {
            m_ptr--;
            return *this;
        }

        // Post-decrement
        Iterator operator--(int) 
        {
            Iterator temp = *this;
            m_ptr--;
            return temp;
        }

        // Addition assignment
        Iterator& operator+=(std::ptrdiff_t n) 
        {
            m_ptr += n;
            return *this;
        }

        // Subtraction assignment
        Iterator& operator-=(std::ptrdiff_t n) 
        {
            m_ptr -= n;
            return *this;
        }

        // Subscript operator
        CByte& operator[](std::ptrdiff_t n) 
        {
            return *(m_ptr + n);
        }

        // Comparison operators
        bool operator==(const Iterator& other) const 
        {
            return m_ptr == other.m_ptr;
        }

        bool operator!=(const Iterator& other) const 
        {
            return m_ptr != other.m_ptr;
        }

        // Random access operations
        Iterator operator+(std::ptrdiff_t n) const 
        {
            return Iterator(m_ptr + n);
        }

        Iterator operator-(std::ptrdiff_t n) const 
        {
            return Iterator(m_ptr - n);
        }

        std::ptrdiff_t operator-(const Iterator& other) const 
        {
            return m_ptr - other.m_ptr;
        }

    private:
        CByte* m_ptr;
    };

    CBytes(size_t size) : m_size(size), m_capacity(size), m_Bytes(new CByte[size]) {}

    ~CBytes() 
    {
        delete[] m_Bytes;
    }

    // Access element at index
    CByte& operator[](size_t index) 
    {
        if (index >= m_size) 
            throw std::out_of_range("Index out of range");
        return m_Bytes[index];
    }

    // Return size of the vector
    size_t size() const {
        return m_size;
    }

    // Return iterator to the beginning
    Iterator begin() {
        return Iterator(m_Bytes);
    }

    // Return iterator to the end
    Iterator end() {
        return Iterator(m_Bytes + m_size);
    }

private:
    size_t m_size;
    size_t m_capacity;
    CByte* m_Bytes;
};



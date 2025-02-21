#pragma once
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <stack>
#include <ctime>
#include <thread>
#include <functional>

class CNumber
{
public:
    CNumber();
    CNumber(const std::string& strInput, bool bNum = true);

    ~CNumber() {};

public:
    void SetNumber(const std::string& strInput);

    std::string Contract(const std::string& strInput);
    std::string Expand(const std::string& strInput);

    static std::string WB();
    const std::string& GetNumber() const;
    const std::string& GetPhrase() const;

    static void Init();
    static bool TextEqual(const std::string& strLHS, const std::string& strRHS);
    friend std::ostream& operator<<(std::ostream& out, const CNumber& Number);

    // error C2338 : static_assert failed : 'Test writer must define specialization of ToString<const Q& q> 
    // for your class class std::basic_string<wchar_t,struct std::char_traits<wchar_t>,class std::allocator<wchar_t> > 
    // __cdecl Microsoft::VisualStudio::CppUnitTestFramework::ToString<class CNumber>(const class CNumber &).
    static std::wstring ToString(const CNumber& Number);

protected:
    void Convert();
    void Split(const std::string& strInput, std::vector<std::string>& vstrTokens, const char cFind = ' ');

    bool m_bNegative;

    std::string m_strNumber;
    std::string m_strPhrase;
};

static uint8_t g_pow[8] = { 1,2,4,8,16,32,64,128 };

class Number
{
protected:
    class CByte
    {
    public:
        CByte()
        {
            m_b.U = 0;
            m_x.X0 = 0;
        }

        CByte(int32_t byte)
        {
            m_b.U = byte;
            m_x.X0 = 0;
        };

        CByte(const CByte& rhs)
        {
            *this = rhs;
        }

        CByte& operator = (const CByte& rhs)
        {
            if (this != &rhs)
            {
                m_b.U = rhs.m_b.U;
                m_x.X0 = rhs.m_x.X0;
            }
            return *this;
        }

        CByte operator + (const CByte& rhs) const // Full-Adder
        {
            CByte Out;
            Out.m_x.X0 = m_x.X0; // Is there a better way to handle Carry?

            Out.m_b.B.B1 = Out.m_x.X0 ^ (m_b.B.B1 ^ rhs.m_b.B.B1);  // SUM: Carry-in XOR (A XOR B)
            Out.m_x.X0 = (m_b.B.B1 & rhs.m_b.B.B1) | (rhs.m_b.B.B1 & Out.m_x.X0) | (m_b.B.B1 & Out.m_x.X0); // CARRY: Carry-out AB OR BC OR ACin

            Out.m_b.B.B2 = Out.m_x.X0 ^ (m_b.B.B2 ^ rhs.m_b.B.B2);
            Out.m_x.X0 = (m_b.B.B2 & rhs.m_b.B.B2) | (rhs.m_b.B.B2 & Out.m_x.X0) | (m_b.B.B2 & Out.m_x.X0);

            Out.m_b.B.B3 = Out.m_x.X0 ^ (m_b.B.B3 ^ rhs.m_b.B.B3);
            Out.m_x.X0 = (m_b.B.B3 & rhs.m_b.B.B3) | (rhs.m_b.B.B3 & Out.m_x.X0) | (m_b.B.B3 & Out.m_x.X0);

            Out.m_b.B.B4 = Out.m_x.X0 ^ (m_b.B.B4 ^ rhs.m_b.B.B4);
            Out.m_x.X0 = (m_b.B.B4 & rhs.m_b.B.B4) | (rhs.m_b.B.B4 & Out.m_x.X0) | (m_b.B.B4 & Out.m_x.X0);

            Out.m_b.B.B5 = Out.m_x.X0 ^ (m_b.B.B5 ^ rhs.m_b.B.B5);
            Out.m_x.X0 = (m_b.B.B5 & rhs.m_b.B.B5) | (rhs.m_b.B.B5 & Out.m_x.X0) | (m_b.B.B5 & Out.m_x.X0);

            Out.m_b.B.B6 = Out.m_x.X0 ^ (m_b.B.B6 ^ rhs.m_b.B.B6);
            Out.m_x.X0 = (m_b.B.B6 & rhs.m_b.B.B6) | (rhs.m_b.B.B6 & Out.m_x.X0) | (m_b.B.B6 & Out.m_x.X0);

            Out.m_b.B.B7 = Out.m_x.X0 ^ (m_b.B.B7 ^ rhs.m_b.B.B7);
            Out.m_x.X0 = (m_b.B.B7 & rhs.m_b.B.B7) | (rhs.m_b.B.B7 & Out.m_x.X0) | (m_b.B.B7 & Out.m_x.X0);

            Out.m_b.B.B8 = Out.m_x.X0 ^ (m_b.B.B8 ^ rhs.m_b.B.B8);
            Out.m_x.X0 = (m_b.B.B8 & rhs.m_b.B.B8) | (rhs.m_b.B.B8 & Out.m_x.X0) | (m_b.B.B8 & Out.m_x.X0);

            return Out;
        }

        CByte operator - (const CByte& rhs) const // Full-Subtractor
        {
            CByte Out;
            Out.m_x.X0 = m_x.X0; // Is there a better way to handle borrowing?

            Out.m_b.B.B1 = (m_b.B.B1 ^ rhs.m_b.B.B1) ^ Out.m_x.X0; // DIFFERENCE: (A XOR B) XOR Borrow-in
            Out.m_x.X0 = (~m_b.B.B1 & Out.m_x.X0) | (~m_b.B.B1 & rhs.m_b.B.B1) | (rhs.m_b.B.B1 & Out.m_x.X0); // BORROW: A'Borrow-in OR A'B OR AB (' = 2's complement)

            Out.m_b.B.B2 = (m_b.B.B2 ^ rhs.m_b.B.B2) ^ Out.m_x.X0;
            Out.m_x.X0 = (~m_b.B.B2 & Out.m_x.X0) | (~m_b.B.B2 & rhs.m_b.B.B2) | (rhs.m_b.B.B2 & Out.m_x.X0);

            Out.m_b.B.B3 = (m_b.B.B3 ^ rhs.m_b.B.B3) ^ Out.m_x.X0;
            Out.m_x.X0 = (~m_b.B.B3 & Out.m_x.X0) | (~m_b.B.B3 & rhs.m_b.B.B3) | (rhs.m_b.B.B3 & Out.m_x.X0);

            Out.m_b.B.B4 = (m_b.B.B4 ^ rhs.m_b.B.B4) ^ Out.m_x.X0;
            Out.m_x.X0 = (~m_b.B.B4 & Out.m_x.X0) | (~m_b.B.B4 & rhs.m_b.B.B4) | (rhs.m_b.B.B4 & Out.m_x.X0);

            Out.m_b.B.B5 = (m_b.B.B5 ^ rhs.m_b.B.B5) ^ Out.m_x.X0;
            Out.m_x.X0 = (~m_b.B.B5 & Out.m_x.X0) | (~m_b.B.B5 & rhs.m_b.B.B5) | (rhs.m_b.B.B5 & Out.m_x.X0);

            Out.m_b.B.B6 = (m_b.B.B6 ^ rhs.m_b.B.B6) ^ Out.m_x.X0;
            Out.m_x.X0 = (~m_b.B.B6 & Out.m_x.X0) | (~m_b.B.B6 & rhs.m_b.B.B6) | (rhs.m_b.B.B6 & Out.m_x.X0);

            Out.m_b.B.B7 = (m_b.B.B7 ^ rhs.m_b.B.B7) ^ Out.m_x.X0;
            Out.m_x.X0 = (~m_b.B.B7 & Out.m_x.X0) | (~m_b.B.B7 & rhs.m_b.B.B7) | (rhs.m_b.B.B7 & Out.m_x.X0);

            Out.m_b.B.B8 = (m_b.B.B8 ^ rhs.m_b.B.B8) ^ Out.m_x.X0;
            Out.m_x.X0 = (~m_b.B.B8 & Out.m_x.X0) | (~m_b.B.B8 & rhs.m_b.B.B8) | (rhs.m_b.B.B8 & Out.m_x.X0);

            return Out;
        }

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

        struct XTRA
        {
            unsigned X0 : 1;
        };

        union BITS
        {
            struct _Bits B;
            uint8_t U;
        };

        BITS m_b;
        XTRA m_x;
    };

    // Helper to convert to the internal format
    void Convert(const int32_t iNumber)
    {
        static CByte _0(0), _255(255);

        m_bNeg = iNumber < 0;
        m_Bytes.resize(4, m_bNeg ? _255 : _0);

        m_Bytes[0] = (uint32_t)(iNumber) & 0xFF;
        m_Bytes[1] = ((uint32_t)(iNumber) >> 8) & 0xFF;
        m_Bytes[2] = ((uint32_t)(iNumber) >> 16) & 0xFF;
        m_Bytes[3] = (uint32_t)(iNumber) >> 24;

        m_bNAN = false;
    }

public:

    Number() : m_bNeg(false), m_bNAN(true) {};

    Number(const char* pstrNumber)
    {
        ToBinary(pstrNumber);
    }

    Number(const std::string& strNumber)
    {
        ToBinary(strNumber);
    }

    Number(const int32_t iNumber)
    {
        Convert(iNumber);
    }

    Number(CByte ch, size_t size)
    {
        static CByte _0(0), _255(255);

        m_bNeg = ch.m_b.B.B8;
        m_Bytes.resize(size, m_bNeg ? _255 : _0);
        m_Bytes[0] = ch;
        m_bNAN = false;
    }

    Number(const CNumber rhs)
    {
        ToBinary(rhs.GetNumber());
    }

    ~Number()
    {
    }

    Number& operator = (const Number& rhs)
    {
        if (this != &rhs)
        {
            m_Bytes = rhs.m_Bytes;
            m_bNeg = rhs.m_bNeg;
            m_bNAN = rhs.m_bNAN;
        }
        return *this;
    }

    Number& operator = (const int32_t iNumber)
    {
        Convert(iNumber);
        return *this;
    }

    Number& operator = (const std::string& strNumber)
    {
        ToBinary(strNumber);
        return *this;
    }

    Number& operator = (const char* pstrNumber)
    {
        ToBinary(pstrNumber);
        return *this;
    }

    bool operator == (const Number& rhs) const
    {
        if (this == &rhs) // I AM ALWAYS EQUAL TOO MYSELF!
            return true;

        if (m_bNAN || rhs.m_bNAN)
            return false;

        if (m_bNeg != rhs.m_bNeg)
            return false;

        if (m_Bytes.size() != rhs.m_Bytes.size())
            return false;

        size_t l = m_Bytes.size(), r = rhs.m_Bytes.size();
        size_t stMax = l == r ? l : (l < r ? r : l);
        CByte Zero(0), Neg1(255);
        for (size_t st = stMax - 1; st != size_t(-1); --st)
        {
            CByte lb = st < l ? m_Bytes[st] : (m_bNeg ? Neg1 : Zero);
            CByte rb = st < r ? rhs.m_Bytes[st] : (rhs.m_bNeg ? Neg1 : Zero);
            if (lb.m_b.U != rb.m_b.U)
                return false;
        }

        return true;
    }

    bool operator != (const Number& rhs) const
    {
        return !(operator == (rhs));
    }

    bool operator < (const Number& rhs) const
    {
        if (this == &rhs)
            return false; // I CANT BE LESS THAN MYSELF!

        if (m_bNAN || rhs.m_bNAN)
            return false;

        if (m_bNeg != rhs.m_bNeg)
            return m_bNeg;

        size_t l = m_Bytes.size(), r = rhs.m_Bytes.size();
        size_t stMax = l == r ? l : (l < r ? r : l);
        CByte Zero(0), Neg1(255);
        for (size_t st = stMax - 1; st != size_t(-1); --st)
        {
            CByte lb = st < l ? m_Bytes[st] : (m_bNeg ? Neg1 : Zero);
            CByte rb = st < r ? rhs.m_Bytes[st] : (rhs.m_bNeg ? Neg1 : Zero);
            if (lb.m_b.U != rb.m_b.U)
                return m_bNeg ? lb.m_b.U < rb.m_b.U : lb.m_b.U < rb.m_b.U;
        }

        return false;
    }

    bool operator <= (const Number& rhs) const
    {
        return (operator < (rhs) || operator == (rhs));
    }

    bool operator > (const Number& rhs) const
    {
        return !(operator <= (rhs));
    }

    bool operator >= (const Number& rhs) const
    {
        return !(operator < (rhs));
    }

    // pre/post increment/decrement
    /*
    The prefix increment/decrement operator (++/--) adds/subs one to its operand and this incremented value is the result of the expression.
    The postfix increment/decrement operator (++/--)(int) adds/subs one to its operand and the previous value is the result of the expression
    */
    
    Number operator ++ ()
    {
        const static Number _1(1, 1);

        if (m_bNAN)
            throw("Invalid number");

        *this += _1;
        return *this;
    }

    Number operator -- ()
    {
        const static Number _1(1, 1);

        if (m_bNAN)
            throw("Invalid number");

        *this -= 1;
        return *this;
    }

    Number operator ++ (int)
    {
        const static Number _1(1, 1);

        if (m_bNAN)
            throw("Invalid number");

        Number rhs = *this;
        *this += _1;
        return rhs;
    }

    Number operator -- (int)
    {
        const static Number _1(1, 1);

        if (m_bNAN)
            throw("Invalid number");

        Number rhs = *this;
        *this += _1;
        return rhs;
    }

//////////////////////////////////////////////////////////
//     +=, -=, *=, /=, %=
//////////////////////////////////////////////////////////

    Number operator += (const Number& rhs)
    {
        *this = *this + rhs;
        return *this;
    }

    Number operator -= (const Number& rhs)
    {
        *this = *this - rhs;
        return *this;
    }

    Number operator *= (const Number& rhs)
    {
        *this = *this * rhs;
        return *this;
    }

    Number operator /= (const Number& rhs)
    {
        *this = *this / rhs;
        return *this;
    }

    Number operator %= (const Number& rhs)
    {
        *this = *this % rhs;
        return *this;
    }

    Number operator + (const Number& rhs) const
    {
        if (m_bNAN || rhs.m_bNAN)
            throw("Invalid number");

        size_t l = m_Bytes.size(), r = rhs.m_Bytes.size();
        size_t stMin = l == r ? l : (l < r ? l : r);
        size_t stMax = l == r ? l : (l < r ? r : l);
        CByte Zero(0);
        Number out(Zero, stMax);
        unsigned of = 0;

        CByte lb, rb;
        size_t st = 0;

        for (; st < stMin; ++st)
        {
            lb = m_Bytes[st];
            rb = rhs.m_Bytes[st];
            CByte& ob = out.m_Bytes[st];
            lb.m_x.X0 = of;
            ob = lb + rb;
            of = ob.m_x.X0;
            ob.m_x.X0 = 0;
        }

        if (st < stMax)
        {
            CByte Neg1(255);
            for (; st < stMax; ++st)
            {
                lb = st < l ? m_Bytes[st] : (m_bNeg ? Neg1 : Zero);
                rb = st < r ? rhs.m_Bytes[st] : (rhs.m_bNeg ? Neg1 : Zero);
                CByte& ob = out.m_Bytes[st];
                lb.m_x.X0 = of;
                ob = lb + rb;
                of = ob.m_x.X0;
                ob.m_x.X0 = 0;
            }
        }

        out.m_bNeg = out.m_Bytes[out.GetSize() - 1].m_b.B.B8;

        return out;
    }

    Number operator - (const Number& rhs) const
    {
        if (m_bNAN || rhs.m_bNAN)
            throw("Invalid number");

        size_t l = m_Bytes.size(), r = rhs.m_Bytes.size();
        size_t stMin = l == r ? l : (l < r ? l : r);
        size_t stMax = l == r ? l : (l < r ? r : l);
        CByte Zero(0);
        Number out(Zero, stMax);
        unsigned of = 0;

        CByte lb, rb;
        size_t st;
        for (st = 0; st < stMin; ++st)
        {
            lb = m_Bytes[st];
            rb = rhs.m_Bytes[st];
            CByte& ob = out.m_Bytes[st];
            lb.m_x.X0 = of;
            ob = lb - rb;
            of = ob.m_x.X0;
            ob.m_x.X0 = 0;
        }

        if (st < stMax)
        {
            CByte Neg1(255);
            for (; st < stMax; ++st)
            {
                lb = st < l ? m_Bytes[st] : (m_bNeg ? Neg1 : Zero);
                rb = st < r ? rhs.m_Bytes[st] : (rhs.m_bNeg ? Neg1 : Zero);
                CByte& ob = out.m_Bytes[st];
                lb.m_x.X0 = of;
                ob = lb - rb;
                of = ob.m_x.X0;
                ob.m_x.X0 = 0;
            }
        }

        out.m_bNeg = out.m_Bytes[out.GetSize() - 1].m_b.B.B8;

        return out;
    }

    Number operator * (const Number& rhs) const
    {
        if (m_bNAN || rhs.m_bNAN)
            throw("Invalid number");

        size_t stMB = m_Bytes.size() > rhs.m_Bytes.size() ? m_Bytes.size() : rhs.m_Bytes.size();
        Number out(CByte(0), stMB);
        Number lhs = *this;
        lhs.SetSize(stMB);

        for (size_t iByte = 0, nBytes = rhs.m_Bytes.size(); iByte < nBytes; ++iByte)
        {
            for (size_t iBit = 0; iBit < 8; ++iBit)
            {
                if (g_pow[iBit] & rhs.m_Bytes[iByte].m_b.U)
                    out = out + lhs;
                lhs.Shl();
            }
        }

        return out;
    }

    Number operator / (const Number& rhs) const
    {
        if (m_bNAN || rhs.m_bNAN)
            throw("Invalid number");

        size_t stMB = m_Bytes.size() > rhs.m_Bytes.size() ? m_Bytes.size() : rhs.m_Bytes.size();
        Number quot, zero(CByte(0), 1);
        if (rhs == zero)
            return quot;

        Number rem = *this;
        Number rhsin = rhs;
        rem.SetSize(stMB);
        rhsin.SetSize(stMB);

        if (m_bNeg != rhs.m_bNeg)
        {
            rhsin = rhsin.TwosComplement();
            rhsin.m_bNeg = m_bNeg;
        }

        Number dbl = rhsin;
        Number pow(m_bNeg == rhs.m_bNeg ? CByte(1) : CByte(-1), stMB);
        size_t stn = 1;

        if (!m_bNeg)
        {
            while (dbl < rem)
            {
                dbl.Shl();
                if (dbl.m_bNeg)
                    return quot;
                pow.Shl();
                ++stn;
            }

            quot = zero;
            for (size_t ndbl = stn; ndbl > 0; --ndbl)
            {
                if (dbl > rem)
                {
                    dbl.Shr();
                    pow.Shr();
                    continue;
                }
                quot += pow;
                rem -= dbl;
                dbl.Shr();
                pow.Shr();
            }
        }
        else
        {
            while (dbl > rem)
            {
                dbl.Shl();
                if (!dbl.m_bNeg)
                    return quot;
                pow.Shl();
                ++stn;
            }

            quot = zero;
            for (size_t ndbl = stn; ndbl > 0; --ndbl)
            {
                if (dbl < rem)
                {
                    dbl.Shr();
                    pow.Shr();
                    continue;
                }
                quot += pow;
                rem -= dbl;
                dbl.Shr();
                pow.Shr();
            }
        }

        return quot;
    }

    Number operator % (const Number& rhs) const
    {
        if (m_bNAN || rhs.m_bNAN)
            throw("Invalid number");

        size_t stMB = m_Bytes.size() > rhs.m_Bytes.size() ? m_Bytes.size() : rhs.m_Bytes.size();
        Number quot, zero(CByte(0), 1);
        if (rhs == zero)
            return quot;

        Number rem = *this;
        Number rhsin = rhs;
        rem.SetSize(stMB);
        rhsin.SetSize(stMB);

        if (m_bNeg != rhs.m_bNeg)
        {
            rhsin = rhsin.TwosComplement();
            rhsin.m_bNeg = m_bNeg;
        }

        Number dbl = rhsin;
        size_t stn = 1;

        if (!m_bNeg)
        {
            while (dbl < rem)
            {
                dbl.Shl();
                if (dbl.m_bNeg)
                    return quot;
                ++stn;
            }

            quot = zero;
            for (size_t ndbl = stn; ndbl > 0; --ndbl)
            {
                if (dbl > rem)
                {
                    dbl.Shr();
                    continue;
                }
                rem -= dbl;
                dbl.Shr();
            }
        }
        else
        {
            while (dbl > rem)
            {
                dbl.Shl();
                if (!dbl.m_bNeg)
                    return quot;
                ++stn;
            }

            quot = zero;
            for (size_t ndbl = stn; ndbl > 0; --ndbl)
            {
                if (dbl < rem)
                {
                    dbl.Shr();
                    continue;
                }
                rem -= dbl;
                dbl.Shr();
            }
        }

        return rem;
    }

    Number operator , (const Number& rhs) const
    {
        return rhs;
    }

    void SetSize(size_t size)
    {
        if (size != m_Bytes.size())
            m_Bytes.resize(size, m_bNeg ? 255 : 0);
    }

    size_t GetSize()
    {
        return m_Bytes.size();
    }

    void Shl() // Shift Left (double)
    {
        size_t iByte = m_Bytes.size() - 1;
        for (; iByte != 0; iByte--)
        {
            m_Bytes[iByte].m_b.B.B8 = m_Bytes[iByte].m_b.B.B7;
            m_Bytes[iByte].m_b.B.B7 = m_Bytes[iByte].m_b.B.B6;
            m_Bytes[iByte].m_b.B.B6 = m_Bytes[iByte].m_b.B.B5;
            m_Bytes[iByte].m_b.B.B5 = m_Bytes[iByte].m_b.B.B4;
            m_Bytes[iByte].m_b.B.B4 = m_Bytes[iByte].m_b.B.B3;
            m_Bytes[iByte].m_b.B.B3 = m_Bytes[iByte].m_b.B.B2;
            m_Bytes[iByte].m_b.B.B2 = m_Bytes[iByte].m_b.B.B1;
            m_Bytes[iByte].m_b.B.B1 = m_Bytes[iByte - 1].m_b.B.B8;
        }

        m_Bytes[iByte].m_b.B.B8 = m_Bytes[iByte].m_b.B.B7;
        m_Bytes[iByte].m_b.B.B7 = m_Bytes[iByte].m_b.B.B6;
        m_Bytes[iByte].m_b.B.B6 = m_Bytes[iByte].m_b.B.B5;
        m_Bytes[iByte].m_b.B.B5 = m_Bytes[iByte].m_b.B.B4;
        m_Bytes[iByte].m_b.B.B4 = m_Bytes[iByte].m_b.B.B3;
        m_Bytes[iByte].m_b.B.B3 = m_Bytes[iByte].m_b.B.B2;
        m_Bytes[iByte].m_b.B.B2 = m_Bytes[iByte].m_b.B.B1;
        m_Bytes[iByte].m_b.B.B1 = 0;

        m_bNeg = m_Bytes[m_Bytes.size() - 1].m_b.B.B8;
    }

    void Shr() // Shift Right (halve)
    {
        size_t iByte = 0;;
        for (; iByte != m_Bytes.size() - 1; iByte++)
        {
            m_Bytes[iByte].m_b.B.B1 = m_Bytes[iByte].m_b.B.B2;
            m_Bytes[iByte].m_b.B.B2 = m_Bytes[iByte].m_b.B.B3;
            m_Bytes[iByte].m_b.B.B3 = m_Bytes[iByte].m_b.B.B4;
            m_Bytes[iByte].m_b.B.B4 = m_Bytes[iByte].m_b.B.B5;
            m_Bytes[iByte].m_b.B.B5 = m_Bytes[iByte].m_b.B.B6;
            m_Bytes[iByte].m_b.B.B6 = m_Bytes[iByte].m_b.B.B7;
            m_Bytes[iByte].m_b.B.B7 = m_Bytes[iByte].m_b.B.B8;
            m_Bytes[iByte].m_b.B.B8 = m_Bytes[iByte + 1].m_b.B.B1;
        }

        m_Bytes[iByte].m_b.B.B1 = m_Bytes[iByte].m_b.B.B2;
        m_Bytes[iByte].m_b.B.B2 = m_Bytes[iByte].m_b.B.B3;
        m_Bytes[iByte].m_b.B.B3 = m_Bytes[iByte].m_b.B.B4;
        m_Bytes[iByte].m_b.B.B4 = m_Bytes[iByte].m_b.B.B5;
        m_Bytes[iByte].m_b.B.B5 = m_Bytes[iByte].m_b.B.B6;
        m_Bytes[iByte].m_b.B.B6 = m_Bytes[iByte].m_b.B.B7;
        m_Bytes[iByte].m_b.B.B7 = m_Bytes[iByte].m_b.B.B8;
        m_Bytes[iByte].m_b.B.B8 = m_bNeg;

        m_bNeg = m_Bytes[iByte].m_b.B.B8;
    }
    
    // Conversion functions
    Number TwosComplement() const
    {
        if (m_bNAN)
            throw("Invalid number");

        size_t size = m_Bytes.size();
        Number Out(CByte(0), size), One(CByte(1), size);

        uint8_t iByte = 0;
        do
        {
            Out.m_Bytes[iByte].m_b.U = ~m_Bytes[iByte].m_b.U;
            iByte++;
        } while (iByte != size);

        size_t sz = Out.m_Bytes.size();
        Out = Out + One;
        Out.m_Bytes.resize(sz);
        Out.m_bNeg = m_bNeg;

        return Out;
    }

    std::string ToDisplay() const
    {
        if (m_bNAN)
            return "NAN";

        if (m_bNeg)
        {
            Number Disp = TwosComplement();
            Disp.m_bNeg = false;
            return "-" + Disp.ToDisplay();
        }

        size_t size = m_Bytes.size();
        std::string strResult = "0";

        const uint8_t cZero = '0', cOne = '1', cDec = '.';
        std::string strNum = "1";

        uint8_t iByte = 0;
        uint8_t iBit = 0;

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

            if (m_Bytes[iByte].m_b.U & g_pow[iBit++]) // Evaluates to False=0 or True=one of 1,2,4,8,16,32,66,128
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

            if (iBit == 8)
            {
                iByte++;
                iBit = 0;
            }

        } while (iByte != size);

        return strResult;
    }

    std::string ToBinary() const
    {
        size_t nBin = m_Bytes.size() * size_t(8);
        std::string strBin(nBin, '0');

        for (size_t iByte = 0, nBytes = m_Bytes.size(); iByte < nBytes; ++iByte, nBin -= 8)
        {
            for (size_t iBit = 0; iBit < 8; ++iBit)
            {
                if (g_pow[iBit] & m_Bytes[iByte].m_b.U)
                    strBin[nBin - iBit - 1] = '1';
            }
        }

        return strBin;
    }

    std::string ToPhrase() const;

    friend std::ostream& operator << (std::ostream& out, Number& rhs)
    {
        out << rhs.ToDisplay();
        return out;
    }

protected:

    void ToBinary(const std::string strNumber)
    {
        if (strNumber.empty())
            throw("Invalid number");
        
        if (strNumber[0] == '-')
        {
            if (strNumber.length() < 2)
                throw("Invalid number");
            m_bNeg = true;
        }
        else
            m_bNeg = false;

        std::string strInput = strNumber.substr(m_bNeg ? 1 : 0);
        if (strInput.empty())
            throw("Invalid number");

        m_bNAN = false;

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
                        bVal += g_pow[bPos];
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
                    bVal += g_pow[bPos];
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
        if (size)
        {
            m_Bytes.resize(size);
            for (size_t iByte = 0; iByte < size; ++iByte)
                m_Bytes[iByte].m_b.U = vbytes[iByte];
        }
        else
        {
            m_Bytes.resize(1);
            m_Bytes[0].m_b.U = 0;
        }

        if (m_bNeg)
            *this = TwosComplement();

        SetSize(std::max(GetSize(), size_t(4)));
    }
    
    protected:
        std::vector<CByte> m_Bytes;
        bool m_bNeg;
        bool m_bNAN;
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
    CDuration(std::string str) : m_str(str), start(clock()), finish(start) {}

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

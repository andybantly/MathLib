#pragma once
#include "Constants.h"
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <stack>
#include <ctime>
#include <thread>
#include <functional>

/*
* CONSTANT/TYPEDEF MEANINGS
* SHFT - Number of bits to left shift. BITWIDTH - 1 in value.
* SHFM - Number of bits for multiplication. (3=8 bits, 4=16 bits, etc)
* AND  - Number of bits for masking in shifting
* ALL  - Maximum value of the internal type
* UNUM - The mapping to the actual type used (change one place, changes many)
*/
#define SHFT            31
#define SHFM            5
#define AND             0x80000000
#define ALL             0xFFFFFFFF
#define BITWIDTH        32

typedef uint32_t UNUM;  // The internal type is a 'unsigned number'

// Power of 2 map with BITWIDTH entries
static const UNUM g_pow[BITWIDTH] = { 1, 2, 4, 8, 16, 32, 64, 128,  // 0-7
                                      256, 512, 1024, 2048, 4096, 8192, 16384, 32768,  // 8-15
                                      65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, // 16-24
                                      16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824 }; // 24-31

class DescNumber
{
public:
    DescNumber();
    DescNumber(const std::string& strInput, bool bNum = true);

    ~DescNumber() {};

public:
    void SetNumber(const std::string& strInput);

    std::string Contract(const std::string& strInput);
    std::string Expand(const std::string& strInput);

    static std::string WB();
    const std::string& GetNumber() const;
    const std::string& GetPhrase() const;

    static void Init();
    static bool TextEqual(const std::string& strLHS, const std::string& strRHS);
    friend std::ostream& operator<<(std::ostream& out, const DescNumber& Number);

    // error C2338 : static_assert failed : 'Test writer must define specialization of ToString<const Q& q> 
    // for your class class std::basic_string<wchar_t,struct std::char_traits<wchar_t>,class std::allocator<wchar_t> > 
    // __cdecl Microsoft::VisualStudio::CppUnitTestFramework::ToString<class CNumber>(const class CNumber &).
    static std::wstring ToString(const DescNumber& Number);

protected:
    void Convert();
    void Split(const std::string& strInput, std::vector<std::string>& vstrTokens, const char cFind = ' ');

    bool m_bNegative;

    std::string m_strNumber;
    std::string m_strPhrase;
};

class Number
{
protected:
    class DATA
    {
    public:
        DATA(UNUM byte = 0) : U(byte), OF(0) { };

        DATA(const DATA& rhs) { *this = rhs; }

        DATA& operator = (const DATA& rhs)
        {
            if (this != &rhs)
            {
                U = rhs.U;
                OF = rhs.OF;
            }
            return *this;
        }

        DATA operator + (const DATA& rhs) const // Full-Adder
        {
            DATA Out;
            Out.OF = OF; // Kerry-In
            for (UNUM ui = 1, uj = 0; ui != 0; ui <<= 1, ++uj)
            {
                Out.U |= (Out.OF ^ (((U & ui) >> uj) ^ ((rhs.U & ui) >> uj))) << uj;                                                // SUM:   Kerry-in XOR (A XOR B)
                Out.OF = (((U & ui) >> uj) & Out.OF) | (((U & ui) >> uj) & ((rhs.U & ui) >> uj)) | (((rhs.U & ui) >> uj) & Out.OF); // CARRY: Kerry-out AB OR BC OR ACin
            }
            return Out;
        }
        
        DATA operator - (const DATA& rhs) const // Full-Subtractor
        {
            DATA Out;
            Out.OF = OF; // Borrow-In
            for (UNUM ui = 1, uj = 0; ui != 0; ui <<= 1, ++uj)
            {
                Out.U |= (Out.OF ^ (((U & ui) >> uj) ^ ((rhs.U & ui) >> uj))) << uj;                                                  // DIFFERENCE: (A XOR B) XOR Borrow-in
                Out.OF = (~((U & ui) >> uj) & Out.OF) | (~((U & ui) >> uj) & ((rhs.U & ui) >> uj)) | (((rhs.U & ui) >> uj) & Out.OF); // BORROW: A'Borrow-in OR A'B OR AB (' = 2s complement)
            }
            return Out;
        }

        UNUM U;
        UNUM OF;
    };

    bool ispow2(const int32_t n) const
    {
        // The bitwise AND of n and n - 1 will be 0 for powers of 2
        return (n > 0) && (n & (n - 1)) == 0;
    }
     
    // Helper to convert to the internal format
    void Convert(const int32_t iNumber)
    {
        m_bNAN = false;

        m_Bytes.resize(2);
        m_Bytes[0] = (uint32_t)(iNumber); // 32

        m_bNeg = iNumber < 0;
        m_Bytes[1] = m_bNeg ? ALL : 0;
    }

    /* -- For 16 and 8 bit widths
    void Convert(const int32_t iNumber)
    {
        m_bNAN = false;

        m_Bytes.resize(5);
        m_Bytes[0] = (uint32_t)(iNumber) & 0xFF;
        m_Bytes[1] = ((uint32_t)(iNumber) >> 0x08) & 0xFF;
        m_Bytes[2] = ((uint32_t)(iNumber) >> 0x10) & 0xFF;
        m_Bytes[3] = (uint32_t)(iNumber) >> 0x18;

        m_Bytes[4] = (m_bNeg = iNumber < 0) ? 255 : 0;
    }

    
    void Convert(const int32_t iNumber)
    {
        m_bNAN = false;

        m_Bytes.resize(3);
        m_Bytes[0] = ((uint32_t)(iNumber)) & 0x0000FFFF; // 16
        m_Bytes[1] = ((uint32_t)(iNumber) >> 0x10); // 32

        m_bNeg = iNumber < 0;
        m_Bytes[2] = m_bNeg ? ALL : 0;
    }
    */

public:
    // Left Bit Shift <- double value
    void Shl(size_t stbit = size_t(-1))
    {
        size_t stn = 0;
        size_t iByte = m_Bytes.size() - 1;
        if (stbit != size_t(-1))
        {
            iByte = (stbit >> SHFM) + 1;
            if (iByte)
                stn = iByte - 1;
        }
        for (; iByte != stn; --iByte)
        {
            m_Bytes[iByte].U <<= 1;
            m_Bytes[iByte].U |= m_Bytes[iByte - 1].U & AND ? 1 : 0;
        }
        m_Bytes[iByte].U <<= 1;
        m_bNeg = (m_Bytes[m_Bytes.size() - 1].U & AND) >> SHFT ? true : false;
    }

    // Right Bit Shift -> halve value
    void Shr(size_t stbit = size_t(-1))
    {
        size_t stn = m_Bytes.size() - 1;
        size_t iByte = 0;
        if (stbit != size_t(-1))
        {
            stn = stbit >> SHFM;
            iByte = stn;
            if (iByte)
                --iByte;
        }
        for (; iByte != stn; ++iByte)
        {
            m_Bytes[iByte].U >>= 1;
            if (m_Bytes[iByte + 1].U & 1)
                m_Bytes[iByte].U |= AND;
        }
        m_Bytes[iByte].U >>= 1;
        if (m_bNeg)
            m_Bytes[iByte].U |= AND;
    }

    Number Add(const Number& rhs, size_t st = 0) const
    {
        if (m_bNAN || rhs.m_bNAN)
            throw("Invalid number");

        size_t l = m_Bytes.size(), r = rhs.m_Bytes.size();
        size_t stMin = l == r ? l : (l < r ? l : r);
        size_t stMax = l == r ? l : (l < r ? r : l);
        const static DATA Zero(0), Neg1(ALL);
        Number out(Zero, stMax);
        UNUM of = 0;

        DATA lb, rb;
        for (; st < stMin; ++st)
        {
            lb = m_Bytes[st];
            rb = rhs.m_Bytes[st];
            if (of == 0 && lb.U == 0 && rb.U == 0) continue;
            of = (lb.OF = of, out.m_Bytes[st] = lb + rb, out.m_Bytes[st].OF);
        }

        for (; st < stMax; ++st)
        {
            lb = st < l ? m_Bytes[st] : (m_bNeg ? Neg1 : Zero);
            rb = st < r ? rhs.m_Bytes[st] : (rhs.m_bNeg ? Neg1 : Zero);
            if (of == 0 && lb.U == 0 && rb.U == 0) continue;
            of = (lb.OF = of, out.m_Bytes[st] = lb + rb, out.m_Bytes[st].OF);
        }

        out.m_bNeg = (out.m_Bytes[out.GetSize() - 1].U & AND) >> SHFT ? true : false; // Shift nbits - 1  to match size of data

        return out;
    }

    Number Sub(const Number& rhs, size_t st = 0) const
    {
        if (m_bNAN || rhs.m_bNAN)
            throw("Invalid number");

        size_t l = m_Bytes.size(), r = rhs.m_Bytes.size();
        size_t stMin = l == r ? l : (l < r ? l : r);
        size_t stMax = l == r ? l : (l < r ? r : l);
        const static DATA Zero(0), Neg1(ALL);
        Number out(Zero, stMax);
        UNUM of = 0;

        DATA lb, rb;
        for (; st < stMin; ++st)
        {
            lb = m_Bytes[st];
            rb = rhs.m_Bytes[st];
            if (of == 0 && lb.U == 0 && rb.U == 0) continue;
            of = (lb.OF = of, out.m_Bytes[st] = lb - rb, out.m_Bytes[st].OF);
        }

        for (; st < stMax; ++st)
        {
            lb = st < l ? m_Bytes[st] : (m_bNeg ? Neg1 : Zero);
            rb = st < r ? rhs.m_Bytes[st] : (rhs.m_bNeg ? Neg1 : Zero);
            if (of == 0 && lb.U == 0 && rb.U == 0) continue;
            of = (lb.OF = of, out.m_Bytes[st] = lb - rb, out.m_Bytes[st].OF);
        }

        out.m_bNeg = (out.m_Bytes[out.GetSize() - 1].U & AND) >> SHFT ? true : false;

        return out;
    }

    Number Mul(const Number& rhs) const
    {
        if (m_bNAN || rhs.m_bNAN)
            throw("Invalid number");

        bool bND = m_Bytes.size() >= rhs.m_Bytes.size();

        size_t stMB = bND ? m_Bytes.size() : rhs.m_Bytes.size();
        Number prod(DATA(0), stMB);
        Number mulp = *this;
        Number mulc = rhs;

        if (bND) // N =>= D
        {
            for (size_t iByte = 0, nBytes = mulc.m_Bytes.size(); iByte < nBytes; ++iByte)
            {
                for (UNUM ui = 1; ui != 0; ui <<= 1)
                {
                    if (ui & mulc.m_Bytes[iByte].U)
                        prod += mulp;
                    mulp.Shl();
                }
            }
        }
        else // D > N
        {
            for (size_t iByte = 0, nBytes = mulp.m_Bytes.size(); iByte < nBytes; ++iByte)
            {
                for (UNUM ui = 1; ui != 0; ui <<= 1)
                {
                    if (ui & mulp.m_Bytes[iByte].U)
                        prod += mulc;
                    mulc.Shl();
                }
            }
        }

        return prod;
    }

    Number Div(const Number& rhs) const
    {
        if (m_bNAN || rhs.m_bNAN)
            throw("Invalid number");

        const static Number _0(DATA(0), 1);
        Number quot;
        if (rhs == _0)
            return quot;

        size_t stMB = m_Bytes.size() > rhs.m_Bytes.size() ? m_Bytes.size() : rhs.m_Bytes.size();

        Number rem = *this;
        rem.SetSize(stMB);

        Number rhsin = rhs;
        if (m_bNeg != rhs.m_bNeg)
            rhsin = rhsin.TwosComplement();

        Number dbl = rhsin;
        dbl.SetSize(stMB);

        Number pow(m_bNeg == rhs.m_bNeg ? DATA(1) : DATA(-1), stMB);
        size_t stn = 0;

        if (!m_bNeg)
        {
            while (dbl < rem)
            {
                dbl.Shl();
                if (dbl.m_bNeg)
                    return quot;
                pow.Shl(stn++);
            }

            quot = _0;
            for (size_t ndbl = stn + 1; ndbl > 0; --ndbl)
            {
                if (dbl > rem)
                {
                    dbl.Shr();
                    pow.Shr(stn--);
                    continue;
                }

                quot = quot.Add(pow, stn >> SHFM);
                rem -= dbl;

                dbl.Shr();
                pow.Shr(stn--);
            }
        }
        else
        {
            while (dbl > rem)
            {
                dbl.Shl();
                if (!dbl.m_bNeg)
                    return quot;
                pow.Shl(stn++);
            }

            quot = _0;
            for (size_t ndbl = stn + 1; ndbl > 0; --ndbl)
            {
                if (dbl < rem)
                {
                    dbl.Shr();
                    pow.Shr(stn--);
                    continue;
                }

                quot = quot.Add(pow, stn >> SHFM);
                rem -= dbl;

                dbl.Shr();
                pow.Shr(stn--);
            }
        }

        return quot;
    }

    Number Mod(const Number& rhs) const
    {
        if (m_bNAN || rhs.m_bNAN)
            throw("Invalid number");

        const static Number _0(DATA(0), 1);
        Number rem;
        if (rhs == _0)
            return rem;

        size_t stMB = m_Bytes.size() > rhs.m_Bytes.size() ? m_Bytes.size() : rhs.m_Bytes.size();

        rem = *this;
        rem.SetSize(stMB);

        Number rhsin = rhs;
        if (m_bNeg != rhs.m_bNeg)
            rhsin = rhsin.TwosComplement();

        Number dbl = rhsin;
        dbl.SetSize(stMB);

        size_t stn = 1;

        if (!m_bNeg)
        {
            while (dbl < rem)
            {
                dbl.Shl();
                if (dbl.m_bNeg)
                    return Number();
                ++stn;
            }

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
                    return Number();
                ++stn;
            }

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

    bool Equals(const Number& rhs) const
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
        const static DATA Zero(0), Neg1(ALL);
        for (size_t st = stMax - 1; st != size_t(-1); --st)
        {
            DATA lb = st < l ? m_Bytes[st] : (m_bNeg ? Neg1 : Zero);
            DATA rb = st < r ? rhs.m_Bytes[st] : (rhs.m_bNeg ? Neg1 : Zero);
            if (lb.U != rb.U)
                return false;
        }

        return true;
    }

    bool LessThan(const Number& rhs) const
    {
        if (this == &rhs)
            return false; // I CANT BE LESS THAN MYSELF!

        if (m_bNAN || rhs.m_bNAN)
            return false;

        if (m_bNeg != rhs.m_bNeg)
            return m_bNeg;

        size_t l = m_Bytes.size(), r = rhs.m_Bytes.size();
        size_t stMax = l == r ? l : (l < r ? r : l);
        const static DATA Zero(0), Neg1(ALL);
        for (size_t st = stMax - 1; st != size_t(-1); --st)
        {
            DATA lb = st < l ? m_Bytes[st] : (m_bNeg ? Neg1 : Zero);
            DATA rb = st < r ? rhs.m_Bytes[st] : (rhs.m_bNeg ? Neg1 : Zero);
            if (lb.U != rb.U)
                return m_bNeg ? lb.U < rb.U : lb.U < rb.U;
        }

        return false;
    }

    Number TwosComplement() const
    {
        if (m_bNAN)
            throw("Invalid number");

        size_t size = m_Bytes.size();
        Number Out(DATA(0), size);
        const static Number _1(DATA(1), 1);

        UNUM iByte = 0;
        do
        {
            Out.m_Bytes[iByte].U = ~m_Bytes[iByte].U;
            iByte++;
        } while (iByte != size);

        Out = Out + _1;
        Out.m_bNeg = !m_bNeg;

        return Out;
    }
    
    // Binary to text based base10 conversion 
    std::string ToDisplay() const
    {
        const static std::string strNAN = "NAN";
        if (m_bNAN)
            return strNAN;

        if (m_bNeg)
        {
            Number TC = TwosComplement();
            return "-" + TC.ToDisplay();
        }

        std::string Num1(1, '1');
        std::string Num2(1, '0');
        std::string Disp(1, '0');

        UNUM iByte = 0;
        UNUM pow = 1;
        do
        {
            UNUM iProd;
            UNUM iCarry;

            if (m_Bytes[iByte].U & pow) // Evaluates to False=0 or True=one of 1,2,4,8,16,32,64,128
            {
                Disp.clear();
                iCarry = 0;

                std::string::const_iterator D1_cend = Num1.end();
                std::string::const_iterator D2_cend = Num2.end();

                for (std::string::const_iterator D1_crit = Num1.begin(), D2_crit = Num2.begin(); D1_crit != D1_cend || D2_crit != D2_cend;)
                {
                    UNUM N1 = (D1_crit != D1_cend ? *D1_crit++ : g_cZero) - g_cZero;
                    UNUM N2 = (D2_crit != D2_cend ? *D2_crit++ : g_cZero) - g_cZero;

                    UNUM iSum = N1 + N2 + iCarry; // adding with carry
                    iCarry = iSum >= 10;
                    if (iCarry)
                        iSum -= 10;

                    Disp.push_back(g_cZero + iSum);
                }
                
                if (iCarry)
                    Disp.push_back(g_cOne);

                Num2 = Disp;
            }

            iCarry = 0;
            std::string Prod;
            for (std::string::const_iterator dit2 = Num1.begin(); dit2 != Num1.end(); )
            {
                UNUM N1 = *dit2++ - g_cZero;

                iProd = 2 * N1 + iCarry; // doubling with carry
                iCarry = iProd >= 10;
                if (iCarry)
                    iProd -= 10;

                Prod.push_back(g_cZero + iProd); // double value
            }

            if (iCarry)
                Prod.push_back(g_cOne);

            Num1 = Prod;

            if (!(pow <<= 1)) // When doubling overflows to 0
            {
                iByte++;
                pow = 1;
            }
        } while (iByte != m_Bytes.size());

        return std::string(Disp.rbegin(), Disp.rend());
    }

    std::string ToBinary() const
    {
        size_t nBin = m_Bytes.size() * size_t(BITWIDTH);
        std::string strBin(nBin, '0');

        for (size_t iByte = 0, nBytes = m_Bytes.size(); iByte < nBytes; ++iByte, nBin -= BITWIDTH)
        {
            for (size_t iBit = 0; iBit < BITWIDTH; ++iBit)
            {
                if (g_pow[iBit] & m_Bytes[iByte].U)
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

    Number(DATA ch, size_t size)
    {
        const static DATA _0(0), _255(ALL);

        m_bNeg = (ch.U & AND) >> SHFT ? true : false;
        m_Bytes.resize(size, m_bNeg ? _255 : _0);
        m_Bytes[0] = ch;
        m_bNAN = false;
    }

    Number(const DescNumber rhs)
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
        return Equals(rhs);
    }

    bool operator != (const Number& rhs) const
    {
        return !(operator == (rhs));
    }

    bool operator < (const Number& rhs) const
    {
        return LessThan(rhs);
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

    Number operator + (const Number& rhs) const
    {
        return Add(rhs);
    }

    Number operator - (const Number& rhs) const
    {
        return Sub(rhs);
    }

    Number operator * (const Number& rhs) const
    {
        return Mul(rhs);
    }

    Number operator / (const Number& rhs) const
    {
        return Div(rhs);
    }

    Number operator % (const Number& rhs) const
    {
        return Mod(rhs);
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

    Number operator , (const Number& rhs) const
    {
        return rhs;
    }

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

    void SetSize(size_t size)
    {
        if (size != m_Bytes.size())
            m_Bytes.resize(size, m_bNeg ? ALL : 0);
    }

    size_t GetSize() const
    {
        return m_Bytes.size();
    }

protected:

    void ToBinary(const std::string strNumber)
    {
        if (strNumber.empty())
            throw("Invalid number");
        
        m_bNeg = false;
        m_bNAN = false;

        bool bNeg = false;
        if (strNumber[0] == '-')
        {
            if (strNumber.length() < 2)
                throw("Invalid number");
            bNeg = true;
        }

        std::string strInput = strNumber.substr(bNeg ? 1 : 0);
        if (strInput.empty())
            throw("Invalid number");

        std::string strOut;
        UNUM idnm = 0;
        UNUM val = 0;
        UNUM pow = 1;
        std::vector<UNUM> vbytes;

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
                    // Byte stream 0-255

                    if (idnm)
                        val += pow;
                    pow <<= 1;
                    if (!pow)
                    {
                        vbytes.push_back(val);
                        val = 0;
                        pow = 1;
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
                /////////////////////////////////////
                // Byte stream 0-255

                if (idnm)
                    val += pow;
                pow <<= 1;
                if (!pow)
                {
                    vbytes.push_back(val);
                    val = 0;
                    pow = 1;
                }

                /////////////////////////////////////

                // Reset and restart (but not the incremental bytes, they carry over)
                strInput = strOut;
                strOut.clear();
                idnm = 0;
                cit = strInput.begin();
            }
        }

        if (val)
            vbytes.push_back(val);

        size_t size = UNUM(vbytes.size());
        if (size)
        {
            m_Bytes.resize(size);
            for (size_t iByte = 0; iByte < size; ++iByte)
                m_Bytes[iByte].U = vbytes[iByte];
        }
        else
        {
            m_Bytes.resize(1);
            m_Bytes[0].U = 0;
        }

        if (bNeg)
            *this = TwosComplement();

        SetSize(GetSize() + 1);
    }
    
    protected:
        std::vector<DATA> m_Bytes;
        bool m_bNeg;
        bool m_bNAN;
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

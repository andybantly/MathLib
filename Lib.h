#pragma once
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <stack>
#include <ctime>
#include <thread>
#include <mutex>

class CLib
{
public:
    enum Type : int { NotSet = 0, Number = 1, Word = 2 };
    
    CLib();
    CLib(std::string strToken);
    CLib(const CLib& rhs);
    ~CLib();

public:
    CLib& operator = (const CLib& rhs);

public:
	int Contract(std::string strInput, std::string& strResult);
	int Expand(std::string strInput, std::string& strResult);
	std::string WB();

protected:
	int ContractLHS(std::string strInput, std::string& strResult);
	int ContractRHS(std::string strInput, std::string& strResult);
	int ExpandLHS(std::string strInput, std::string& strResult);
	int ExpandRHS(std::string strInput, std::string& strResult);

private:
    void Init();
	void Split(std::string strInput, std::vector<std::string>& vstrTokens);
    void SetType();
    int  BinarySearch(std::string& strSearch, const std::vector<std::string> & vec, int nSize);

protected:
    // These work and am leaving them in as a slower way to lookup, in case needed later
	//std::vector<std::string> m_vstrHuns;
	//std::vector <std::pair<std::string, std::string> > m_vstr21to99;
    std::map<std::string, std::string> m_mapWordTo99;
    std::map<std::string, std::string> m_mapWordTo100;

    Type m_Type;
    std::string m_strToken;
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
    bool rem(unsigned long iwght, long double dval, unsigned long nobs)
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

    void add(unsigned long iwght, double dv)
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
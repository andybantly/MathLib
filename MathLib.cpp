// MathLib.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "MathLib.h"
#include "Lib.h"
#pragma warning(disable:6385)

using namespace std;

mutex g_io_mutex;

static void ttest(unsigned long long ullb, unsigned long long ulle)
{
	CMathLib MathLib;

	string s, sr, sv;
	unsigned long long ull = ullb;
	double dp = 0.0, dt = double(ulle - ullb);
	clock_t start, finish;

	start = clock();

	{
		lock_guard<mutex> guard(g_io_mutex);
		cout << "thread from: " << ullb << " to " << ulle << endl;
	}

	do
	{
		s = to_string(ull++);
		if (MathLib.Expand(s, sr) != 0)
		{
			lock_guard<mutex> guard(g_io_mutex);
			cout << s << " did not expand" << endl;
			break;
		}
		else
		{
			if (MathLib.Contract(sr, sv) != 0)
			{
				lock_guard<mutex> guard(g_io_mutex);
				cout << sr << " did not contract" << endl;
				break;
			}
			else
			{
				if (sv != s)
				{
					lock_guard<mutex> guard(g_io_mutex);
					cout << s << " did not expand and contract" << endl;
					break;
				}
			}
		}

		if (ull % 100000 == 0)
		{
			lock_guard<mutex> guard(g_io_mutex);
			finish = clock();
			double d = (double)(finish - start) / CLOCKS_PER_SEC;
			if (d > 60.0)
			{
				dp = (double(ull - ullb) / dt) * 100.0;
				cout << "Expanded/Contracted " << (ull - ullb) << " out of " << (ulle - ullb) << ", value " << s << " at " << dp << "%" << endl;
				start = clock();
			}
		}
	} while (ull <= ulle && ull != 0);

	lock_guard<mutex> guard(g_io_mutex);
	cout << "thread finished" << endl;
}

static void test()
{
	CDuration Duration("Test Expansion/Contraction:");

	vector<pair<unsigned long long, unsigned long long> > vtp;
	unsigned long long numt = thread::hardware_concurrency() * 4;
	unsigned long long dtpt = unsigned long long(-1) / numt;

	vector<thread*> vptp;
	unsigned long long ullb, ulle;
	for (unsigned long long it = 0; it < numt; it++)
	{
		ullb = it * dtpt;
		if (it + 1 != numt)
			ulle = ullb + dtpt - 1;
		else
			ulle = unsigned long long(-1);

		thread* ptp = new thread(ttest, ullb, ulle);
		vptp.push_back(ptp);
	}

	for (vector<thread*>::iterator it = vptp.begin(); it != vptp.end(); ++it)
		(*it)->join();
}

string Base10toBase2(string strin)
{
	string strout;
	string strbin;
	uint8_t idnm = 0;
	string::iterator it = strin.begin();
	do
	{
		idnm = idnm * 10 + *it - '0';
		if (idnm < 2 && it + 1 != strin.end())
		{
			if (!strout.empty())
				strout += '0';
			idnm = idnm * 10 + (*(it + 1) - '0');
			it += 2;
		}
		else
		{
			if (strin.length() == 1 && idnm < 2)
			{
				strbin += '0' + idnm;
				break;
			}
			it++;
		}

		uint8_t inum = idnm / 2;
		idnm = idnm % 2;
		strout += '0' + inum;

		if (it == strin.end())
		{
			strbin += '0' + idnm;
			strin = strout;
			strout.clear();
			idnm = 0;
			it = strin.begin();
		}
	} while (it != strin.end());
//	for (std::string::reverse_iterator rit = strbin.rbegin(); rit != strbin.rend(); ++rit)
//		cout << *rit;
//	cout << endl;
	std::reverse(strbin.begin(), strbin.end());
//	cout << strbin << endl;
	return strbin;
}

int main()
{
	CByte B1(49);
	CByte B2(200);
	CByte B3 = B1 + B2;
	CByte B4 = B3 + CByte(6);
	B4 = B4 + CByte(1); // Overflows, B4.U = 0, B4.C = 1;

	int iResult;
	string strInput, strResult;
	bool bAgain = true;
	do
	{
		cout << "Enter a number or 'test' for verification or 'quit' to exit: ";

		strInput.clear();
		char c;
		while ((c = getchar()) != '\n')
			strInput += c;
		if (strInput != "quit" && strInput != "test")
		{
			CMathLib MathLib(strInput);
			if (MathLib.GetType() == CMathLib::Type::Number)
			{
				iResult = MathLib.Expand(strResult);
				cout << Base10toBase2(strInput) << endl;
			}
			else
				iResult = MathLib.Contract(strResult);
			if (iResult == 0)
			{
				string strVerify;
				CMathLib MathLib2(strResult);
				if (MathLib2.GetType() == CMathLib::Type::Word)
					iResult = MathLib2.Contract(strVerify);
				else
					iResult = MathLib2.Expand(strVerify);

				if (iResult == 0)
					cout << strResult << " = " << strVerify << endl;
				else if (iResult == -1)
					cout << "Invalid Number!" << endl;
				else if (iResult == -2)
					cout << "The number is out of range. The number must not surpass the +/-" << MathLib.WB() << " range" << endl;
				else if (iResult == -3)
					cout << "Wrong number type" << endl;

				MathLib2 = MathLib;
			}
			else
			{
				if (iResult == -1)
					cout << "Invalid Number!" << endl;
				else if (iResult == -2)
					cout << "The number is out of range. The number must not surpass the +/-" << MathLib.WB() << " range" << endl;
				else if (iResult == -3)
					cout << "Wrong number type" << endl;
			}
		}
		else
		{
			if (strInput == "quit")
				bAgain = false;
			else
				test(); // Manual testing, automatic testing in TestMathLib project
		}
	} while (bAgain);
	return 0;
}
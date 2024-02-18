// MathLib.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "MathLib.h"
#include "Lib.h"
#pragma warning(disable:6385)

using namespace std;

mutex g_io_mutex;

static void ttest(unsigned long long ullb, unsigned long long ulle)
{
	CLib MathLib;

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
	unsigned long long numt = thread::hardware_concurrency();
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

int main()
{
	CLib MathLib;
	cout << "This program will need user to input a number." << endl << "Then it will read it out and convert it back to the number." << endl;

	string strInput;
	bool bAgain = true;
	do
	{
		cout << "Enter a number or 'test' for verification or 'quit' to exit: ";
		cin >> strInput;
		if (strInput != "quit" && strInput != "test")
		{
			string strResult;
			int iResult = MathLib.Expand(strInput, strResult);
			if (iResult == 0)
			{
				cout << strResult << endl;
				string strVerify;
				iResult = MathLib.Contract(strResult, strVerify);
				if (iResult == 0)
					cout << strVerify << endl;
				else
					cout << "Invalid Number!" << endl;
			}
			else
			{
				if (iResult == -1)
					cout << "Invalid Number!" << endl;
				else if (iResult == -2)
					cout << "The number is out of range. The number must not surpass the +/-" << MathLib.WB() << " range" << endl;
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
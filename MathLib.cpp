// MathLib.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "MathLib.h"
#include "Number.h"
#pragma warning(disable:6385)

using namespace std;

mutex g_io_mutex;

static void ttest(unsigned long long ullb, unsigned long long ulle)
{
	CNumber Number;

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
		if (Number.Expand(s, sr) != 0)
		{
			lock_guard<mutex> guard(g_io_mutex);
			cout << s << " did not expand" << endl;
			break;
		}
		else
		{
			if (Number.Contract(sr, sv) != 0)
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

	unsigned long long numt = thread::hardware_concurrency();
	unsigned long long dtpt = INT_MAX / numt;

	vector<thread*> vptp;
	unsigned long long ullb, ulle;
	for (unsigned long long it = 0; it < numt; it++)
	{
		ullb = it * dtpt;
		if (it + 1 != numt)
			ulle = ullb + dtpt - 1;
		else
			ulle = INT_MAX;

		thread* ptp = new thread(ttest, ullb, ulle);
		vptp.push_back(ptp);
	}

	for (vector<thread*>::iterator it = vptp.begin(); it != vptp.end(); ++it)
		(*it)->join();

	for (vector<thread*>::iterator it = vptp.begin(); it != vptp.end(); ++it)
		delete* it;
}

void Split(const string& strInput, vector<string>& vstrTokens, const char cFind)
{
	if (strInput.empty())
		return;

	std::string strToken;
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

int main()
{
	string strInput, strResult;
	bool bAgain = true;
	do
	{
		cout << "Enter a number, set of numbers separated by arithmetic, or 'test' for verification or 'quit' to exit. " << endl << "Input: ";

		strInput.clear();
		char c;
		while ((c = getchar()) != '\n')
			strInput += c;
		if (strInput != "quit" && strInput != "test")
		{
			try
			{
				vector<string> vNumbers;
				Split(strInput, vNumbers, ' ');
				if (vNumbers.size() == 1)
				{
					CNumber Number(strInput);
					const string& strNumber = Number.GetNumber();
					const string& strPhrase = Number.GetPhrase();
					const string& strBinary = Number.GetBinary();
					string strBase10;
					Number.ToBase10(strBinary, strBase10);
					cout << strNumber << " = " << strPhrase << " = " << strBinary << " = " << strBase10 << endl;
				}
				else if (vNumbers.size() == 3)
				{
					CNumber Number(vNumbers[0]);
					CNumber Number2(vNumbers[2]);

					string strBase10;
					Number.ToBase10(Number.GetBinary(), strBase10);
					cout << Number.GetNumber() << " = " << Number.GetPhrase() << " = " << Number.GetBinary() << " = " << strBase10 << endl;
					cout << vNumbers[1] << endl;
					Number2.ToBase10(Number2.GetBinary(), strBase10);
					cout << Number2.GetNumber() << " = " << Number2.GetPhrase() << " = " << Number2.GetBinary() << " = " << strBase10 << endl;
					CNumber Sum;
					if (vNumbers[1] == "+")
						Sum = Number + Number2;
					else if (vNumbers[1] == "-")
						Sum = Number - Number2;
					else if (vNumbers[1] == "*")
						Sum = Number * Number2;
					else if (vNumbers[1] == "/")
						Sum = Number / Number2;
					else if (vNumbers[1] == "%")
						Sum = Number % Number2;
					Sum.ToBase10(Sum.GetBinary(), strBase10);
					cout << Sum.GetNumber() << " = " << Sum.GetPhrase() << " = " << Sum.GetBinary() << " = " << strBase10 << endl;
				}
				else
					cout << "Invalid input." << endl;
			}
			catch (std::exception& e)
			{
				cout << e.what() << endl;
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
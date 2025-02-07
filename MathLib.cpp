// MathLib.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "MathLib.h"
#include "Number.h"

#pragma warning(disable:6385)

using namespace std;

int main()
{
	CNumber::Init();
	string strInput, strResult;
	bool bAgain = true;
	do
	{
		std::cout << "Enter a number, set of numbers separated by arithmetic or comparison operations (+,-,*,/,%, <, >, <=, >=, =)" << endl << "Enter 'test' for verification or 'quit' to exit." << endl << "Examples: 12 * 11 + 12, three + 4 - two, 9 / 3 + 7 * 10, 10 % 3, 2 < 3" << endl << "Input: ";

		strInput.clear();
		char c;
		while ((c = getchar()) != '\n')
			strInput += c;
		if (!TextEqual(strInput, "quit") && !TextEqual(strInput, "test"))
		{
			try
			{
				vector<string> vNumbers;
				vector<string> vNumbers2;
				Split(strInput, vNumbers, ' ');
				if (vNumbers.size() > 3)
				{
					string strConcatNumber;
					for (vector<string>::iterator it = vNumbers.begin(); it != vNumbers.end(); ++it)
					{
						if (*it == "+" || *it == "-" || *it == "*" || *it == "/" || *it == "%")
						{
							vNumbers2.push_back(strConcatNumber);
							vNumbers2.push_back(*it);
							strConcatNumber = "";
						}
						else if (*it == "<" || *it == ">" || *it == "=" || *it == "<=" || *it == ">=")
						{
							vNumbers2.push_back(strConcatNumber);
							vNumbers2.push_back(*it);
							strConcatNumber = "";
						}
						else
						{
							if (strConcatNumber.length() > 0)
								strConcatNumber += " ";
							strConcatNumber += *it;
						}
					}
					vNumbers2.push_back(strConcatNumber);
					vNumbers = vNumbers2;
				}

				if (vNumbers.size() == 1)
				{
					CNumber Number1(strInput);
					Number N(strInput);
					const string& strPhrase = Number1.GetPhrase();
					const string& strBinary = Number1.GetBinary();
					string strBase10;
					Number1.ToBase10(strBinary, strBase10);
					std::cout << Number1 << " " << strBinary << endl;
					std::cout << N.ToDisplay() << " " << N.ToBinary() << endl;
					std::cout << endl;
				}
				else if (vNumbers.size() >= 3)
				{
					do
					{
						CNumber Number1(vNumbers[0]);
						CNumber Number2(vNumbers[2]);
						CNumber Sum;

						Number N1(vNumbers[0]);
						Number N2(vNumbers[2]);
						Number S;

						string strBase10;
						Number1.ToBase10(Number1.GetBinary(), strBase10);
						std::cout << Number1 << " " << Number1.GetBinary() << endl;

						std::cout << vNumbers[1] << endl;

						Number2.ToBase10(Number2.GetBinary(), strBase10);
						std::cout << Number2 << " " << Number2.GetBinary() << endl;

						bool bCMP = false, bCMP2 = false;
						if (vNumbers[1] == "+")
						{
							Sum = Number1 + Number2;
							S = N1 + N2;
						}
						else if (vNumbers[1] == "-")
						{
							Sum = Number1 - Number2;
							S = N1 - N2;
						}
						else if (vNumbers[1] == "*")
						{
							Sum = Number1 * Number2;
							S = N1 * N2;
						}
						else if (vNumbers[1] == "/")
						{
							Sum = Number1 / Number2;
							S = N1 / N2;
						}
						else if (vNumbers[1] == "%")
						{
							Sum = Number1 % Number2;
							S = N1 % N2;
						}
						else if (vNumbers[1] == "<")
						{
							bCMP = Number1 < Number2;
							bCMP2 = N1 < N2;
						}
						else if (vNumbers[1] == ">")
						{
							bCMP = Number1 > Number2;
							bCMP2 = N1 > N2;
						}
						else if (vNumbers[1] == "=")
						{
							bCMP = Number1 == Number2;
							bCMP2 = N1 == N2;
						}
						else if (vNumbers[1] == "<=")
						{
							bCMP = Number1 <= Number2;
							bCMP2 = N1 <= N2;
						}
						else if (vNumbers[1] == ">=")
						{
							bCMP = Number1 >= Number2;
							bCMP2 = N1 >= N2;
						}

						if (vNumbers[1] == "+" || vNumbers[1] == "-" || vNumbers[1] == "*" || vNumbers[1] == "/" || vNumbers[1] == "%")
						{
							Sum.ToBase10(Sum.GetBinary(), strBase10);
							std::cout << Sum.GetNumber() << " = " << Sum.GetBinary() << endl;
							std::cout << S.ToDisplay() << " = " << S.ToBinary() << endl;
						}
						else
						{
							Sum = bCMP ? "1" : "0";
							std::cout << Number1.GetNumber() << " " + vNumbers[1] + " " << Number2.GetNumber() << " = " << (bCMP ? "TRUE" : "FALSE") << endl;

							S = bCMP2 ? "1" : "0";
							std::cout << N1.ToDisplay() << " " + vNumbers[1] + " " << N2.ToDisplay() << " = " << (bCMP2 ? "TRUE" : "FALSE") << endl;
						}

						vNumbers2.clear();
						vNumbers2.push_back(Sum.GetNumber());
						for (std::vector<string>::iterator vit = vNumbers.begin() + 3; vit != vNumbers.end(); ++vit)
							vNumbers2.push_back(*vit);
						vNumbers = vNumbers2;
						std::cout << endl;
					} while (vNumbers.size() > 1);
				}
				else
					std::cout << "Invalid input." << endl;
			}
			catch (std::exception& e)
			{
				std::cout << e.what() << endl;
			}
		}
		else
		{
			if (TextEqual(strInput, "quit"))
				bAgain = false;
			else
				test(); // Manual testing, automatic testing in TestMathLib project
		}
	} while (bAgain);
	return 0;
}

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
		std::cout << "thread from: " << ullb << " to " << ulle << endl;
	}

	do
	{
		s = to_string(ull++);
		if (Number.Expand(s, sr) != 0)
		{
			lock_guard<mutex> guard(g_io_mutex);
			std::cout << s << " did not expand" << endl;
			break;
		}
		else
		{
			if (Number.Contract(sr, sv) != 0)
			{
				lock_guard<mutex> guard(g_io_mutex);
				std::cout << sr << " did not contract" << endl;
				break;
			}
			else
			{
				if (sv != s)
				{
					lock_guard<mutex> guard(g_io_mutex);
					std::cout << s << " did not expand and contract" << endl;
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
				std::cout << "Expanded/Contracted " << (ull - ullb) << " out of " << (ulle - ullb) << ", value " << s << " at " << dp << "%" << endl;
				start = clock();
			}
		}
	} while (ull <= ulle && ull != 0);

	lock_guard<mutex> guard(g_io_mutex);
	std::cout << "thread finished" << endl;
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
		delete *it;
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


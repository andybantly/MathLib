// MathLib.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "MathLib.h"
#include "Number.h"

#pragma warning(disable:6385)

int main()
{
	std::string strInput, strResult;
	bool bAgain = true;
	do
	{
		std::cout << "Enter a number, set of numbers separated by arithmetic or comparison operations (+,-,*,/,%, <, >, <=, >=, =)" << std::endl << "Enter 'test' for verification or 'quit' to exit." << std::endl << "Examples: 2147483647, 12 * 11 + 12, three + 4 - two, 9 / 3 + 7 * 10, 10 % 3, 2 < 3" << std::endl << "Input: ";

		strInput.clear();
		char c;
		while ((c = getchar()) != '\n')
			strInput.append(1, c);
		if (!TextEqual(strInput, "quit") && !TextEqual(strInput, "test"))
		{
			try
			{
				std::vector<std::string> vNumbers;
				std::vector<std::string> vNumbers2;
				Split(strInput, vNumbers, ' ');
				if (vNumbers.size() > 3)
				{
					std::string strConcatNumber;
					for (std::vector<std::string>::iterator it = vNumbers.begin(); it != vNumbers.end(); ++it)
					{
						if (*it == "+" || *it == "-" || *it == "*" || *it == "/" || *it == "%" || *it == ",")
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
					Number N(strInput);
					std::cout << N << " " << N.ToBinary() << std::endl;
				}
				else if (vNumbers.size() >= 3)
				{
					do
					{
						Number N1(vNumbers[0]);
						Number N2(vNumbers[2]);

						size_t mb = N1.GetSize() > N2.GetSize() ? N1.GetSize() : N2.GetSize();
						N1.SetSize(mb + 1);
						N2.SetSize(mb + 1);
						Number S;

						bool bCMP = false;
						if (vNumbers[1] == "+")
						{
							S = N1 + N2;
						}
						else if (vNumbers[1] == "-")
						{
							S = N1 - N2;
						}
						else if (vNumbers[1] == "*")
						{
							S = N1 * N2;
						}
						else if (vNumbers[1] == "/")
						{
							S = N1 / N2;
						}
						else if (vNumbers[1] == "%")
						{
							S = N1 % N2;
						}
						else if (vNumbers[1] == ",")
						{
							S = (N1, N2);
						}
						else if (vNumbers[1] == "<")
						{
							bCMP = N1 < N2;
						}
						else if (vNumbers[1] == ">")
						{
							bCMP = N1 > N2;
						}
						else if (vNumbers[1] == "=")
						{
							bCMP = N1 == N2;
						}
						else if (vNumbers[1] == "<=")
						{
							bCMP = N1 <= N2;
						}
						else if (vNumbers[1] == ">=")
						{
							bCMP = N1 >= N2;
						}

						if (vNumbers[1] == "+" || vNumbers[1] == "-" || vNumbers[1] == "*" || vNumbers[1] == "/" || vNumbers[1] == "%" || vNumbers[1] == ",")
						{
							std::cout << N1 << " " << vNumbers[1] << " " << N2 << " = " << std::endl << S.ToDisplay() << std::endl;
						}
						else
						{
							S = bCMP ? "1" : "0";
							std::cout << N1 << " " + vNumbers[1] + " " << N2 << " = " << (bCMP ? "TRUE" : "FALSE") << std::endl;
						}

						vNumbers2.clear();
						vNumbers2.push_back(S.ToDisplay());
						for (std::vector<std::string>::iterator vit = vNumbers.begin() + 3; vit != vNumbers.end(); ++vit)
							vNumbers2.push_back(*vit);
						vNumbers = vNumbers2;
						std::cout << std::endl;
					} while (vNumbers.size() > 1);
				}
				else
					std::cout << "Invalid input." << std::endl;
			}
			catch (std::exception& e)
			{
				std::cout << e.what() << std::endl;
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

	std::string s, sr, sv;
	unsigned long long ull = ullb;
	double dp = 0.0, dt = double(ulle - ullb);
	clock_t start, finish;

	start = clock();

	{
		std::lock_guard<std::mutex> guard(g_io_mutex);
		std::cout << "thread from: " << ullb << " to " << ulle << std::endl;
	}

	do
	{
		s = std::to_string(ull++);
		if (Number.Expand(s, sr) != 0)
		{
			std::lock_guard<std::mutex> guard(g_io_mutex);
			std::cout << s << " did not expand" << std::endl;
			break;
		}
		else
		{
			if (Number.Contract(sr, sv) != 0)
			{
				std::lock_guard<std::mutex> guard(g_io_mutex);
				std::cout << sr << " did not contract" << std::endl;
				break;
			}
			else
			{
				if (sv != s)
				{
					std::lock_guard<std::mutex> guard(g_io_mutex);
					std::cout << s << " did not expand and contract" << std::endl;
					break;
				}
			}
		}

		if (ull % 100000 == 0)
		{
			std::lock_guard<std::mutex> guard(g_io_mutex);
			finish = clock();
			double d = (double)(finish - start) / CLOCKS_PER_SEC;
			if (d > 60.0)
			{
				dp = (double(ull - ullb) / dt) * 100.0;
				std::cout << "Expanded/Contracted " << (ull - ullb) << " out of " << (ulle - ullb) << ", value " << s << " at " << dp << "%" << std::endl;
				start = clock();
			}
		}
	} while (ull <= ulle && ull != 0);

	std::lock_guard<std::mutex> guard(g_io_mutex);
	std::cout << "thread finished" << std::endl;
}

static void test()
{
	CDuration Duration("Test Expansion/Contraction:");

	unsigned long long numt = std::thread::hardware_concurrency();
	unsigned long long dtpt = INT_MAX / numt;

	std::vector<std::thread*> vptp;
	unsigned long long ullb, ulle;
	for (unsigned long long it = 0; it < numt; it++)
	{
		ullb = it * dtpt;
		if (it + 1 != numt)
			ulle = ullb + dtpt - 1;
		else
			ulle = INT_MAX;

		std::thread* ptp = new std::thread(ttest, ullb, ulle);
		vptp.push_back(ptp);
	}

	for (std::vector<std::thread*>::iterator it = vptp.begin(); it != vptp.end(); ++it)
		(*it)->join();

	for (std::vector<std::thread*>::iterator it = vptp.begin(); it != vptp.end(); ++it)
		delete *it;
}

void Split(const std::string& strInput, std::vector<std::string>& vstrTokens, const char cFind)
{
	if (strInput.empty())
		return;

	std::string strToken;
	size_t istart = 0, ipos;
	do
	{
		ipos = strInput.find(cFind, istart);
		if (ipos == std::string::npos)
			vstrTokens.push_back(strInput.substr(istart));
		else
		{
			strToken = strInput.substr(istart, ipos - istart);
			vstrTokens.push_back(strToken);
			istart = ipos + 1;
		}
	} while (ipos != std::string::npos);
}

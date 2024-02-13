// MathLib.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <ctime>
#include <thread>
#include <mutex>
#include "MathLib.h"
#pragma warning(disable:6385)

using namespace std;

static void split(string strInput, vector<string>& vstrTokens)
{
	string strToken;
	size_t ipos;

	do
	{
		ipos = strInput.find(' ');
		if (ipos == string::npos)
			vstrTokens.push_back(strInput);
		else
		{
			strToken = strInput.substr(0, ipos);
			vstrTokens.push_back(strToken);
			ipos = strInput.find(' ');
			if (ipos != string::npos)
				strInput.erase(0, ipos + 1);
		}
	} while (ipos != string::npos);
}

extern "C"
static int contract(string strInput, string& strResult)
{
	strResult = "";
	int iResult = 0;
	bool bNegative = false;
	string strNumber;

	vector<string> vstrTokens;
	split(strInput, vstrTokens);

	bool bFound = false;
	vector<string> vstrNumbers;
	vector<vector<string> > vvstrNumbers;
	for (vector<string>::iterator it = vstrTokens.begin(); it != vstrTokens.end(); ++it)
	{
		bFound = false;
		string strToken = *it;

		// Look from 0-19
		for (int iPos = 0; !bFound && iPos < g_nOnes; ++iPos)
		{
			bFound = strToken == g_ones[iPos];
			if (bFound)
				vstrNumbers.push_back(g_nones[iPos]);
		}

		// Next look in 20-90 in increments of 10
		for (int iPos = 2; !bFound && iPos < g_nTens; ++iPos)
		{
			bFound = strToken == g_tens[iPos];
			if (bFound)
				vstrNumbers.push_back(g_ntens[iPos]);
		}

		// Next look at 21-99 skipping increments of 1 skipping the tens
		for (vector<pair<string, string> >::iterator it = m_vstr21to99.begin(); !bFound && it != m_vstr21to99.end(); ++it)
		{
			bFound = strToken == (*it).first;
			if (bFound)
				vstrNumbers.push_back((*it).second);
		}

		// Look at the big numbers that increase in magnitude. 
		// i.e. Thousand, Million, Billion, etc.
		// Number groups terminate on these
		for (int iPos = 0; !bFound && iPos < g_nHuns; ++iPos)
		{
			bFound = strToken == g_huns[iPos];
			if (bFound)
			{
				vstrNumbers.push_back(*(g_vstrHuns.begin() + iPos));
				vvstrNumbers.push_back(vstrNumbers);
				vstrNumbers.clear();
			}
		}

		if (!bFound)
		{
			if (strToken == "Negative")
				bNegative = true;
			else
			{
				iResult = -1;
				break;
			}
		}
	}

	if (bFound && !vstrNumbers.empty())
		vvstrNumbers.push_back(vstrNumbers);

	if (iResult == -1)
	{
		cout << "NaN" << endl;
		return iResult;
	}

	// Process the number groups
	vector<vector<string> >::iterator vit;
	vector<string>::iterator it;
	for (vit = vvstrNumbers.begin(); vit != vvstrNumbers.end(); ++vit)
	{
		string strGroupNumber = *((*vit).begin());
		for (it = (*vit).begin() + 1; it != (*vit).end(); ++it)
		{
			strNumber = *it;
			if (strNumber.length() > 2 &&
				*(strNumber.end() - 1) == '0')
				strGroupNumber += strNumber.substr(1);
			else
				strGroupNumber.replace(strGroupNumber.end() - strNumber.length(), strGroupNumber.end(), strNumber);
		}

		if (!strResult.empty())
			strResult.replace(strResult.end() - strGroupNumber.length(), strResult.end(), strGroupNumber);
		else
			strResult = strGroupNumber;
	}

	if (bNegative)
		strResult = "-" + strResult;
	return iResult;
}

extern "C"
static int expand(string sInput, string& strResult)
{
	int iResult = 0;
	bool bNegative = false;
	int digs, ld, nd, idx;

	strResult.clear();

	if (sInput.substr(0, 1) == "-")
	{
		bNegative = true;
		sInput = sInput.substr(1);
	}

start:
	digs = (int)sInput.length() - 1;
	idx = (digs / 3) - 1;
	if (idx < g_nHuns)
	{
		ld = digs % 3;
		switch (ld)
		{
		case 1:
			nd = 2;
			break;
		case 2:
			nd = 3;
			break;
		default:
			nd = 1;
		}

		string sInput2 = sInput.substr(0, nd);
		int input2, digs2, div, l;
		try
		{
			input2 = stoi(sInput2);
		}
		catch (invalid_argument)
		{
			iResult = -1;
		}

		if (iResult == 0)
		{
			bool b10 = false;
		start2:
			digs2 = 0;
			if (input2 > 0)
				digs2 = (int)(floor(log10((double)input2)));
			div = 1;
			for (l = 0; l < digs2; l++)
				div *= 10;

			if (input2 < 20)
			{
				if (!strResult.empty())
					strResult += (b10 ? "-" : " ");
				strResult += g_ones[input2];
				b10 = false;
			}
			else if (input2 < 100)
			{
				if (!strResult.empty())
					strResult += " ";
				strResult += g_tens[input2 / div];
				b10 = true;
				if ((input2 % div) != 0)
				{
					input2 = input2 % div;
					goto start2;
				}
			}
			else if (input2 < 1000)
			{
				if (!strResult.empty())
					strResult += " ";
				strResult += g_ones[input2 / div] + " " + g_tens[g_nTens - 1];
				if ((input2 % div) != 0)
				{
					input2 = input2 % div;
					goto start2;
				}
			}

			if (sInput.length() > 3)
			{
				if (!strResult.empty())
					strResult += " ";
				strResult += g_huns[idx];
			}

			sInput = sInput.substr(nd);
			sInput.erase(0, sInput.find_first_not_of('0'));
			if (sInput.length())
				goto start;
		}
		else
			iResult = -2;
	}

	if (bNegative && iResult == 0)
		strResult = "Negative " + strResult;
	return iResult;
}

static void ttest(unsigned long long ullb, unsigned long long ulle)
{
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
		if (expand(s, sr) != 0)
		{
			lock_guard<mutex> guard(g_io_mutex);
			cout << s << " did not expand" << endl;
			break;
		}
		else
		{
			if (contract(sr, sv) != 0)
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

extern "C" static void test()
{
	CDuration Duration("Test Expansion/Contraction:");

	vector<pair<unsigned long long, unsigned long long> > vtp;
	unsigned long long numt = thread::hardware_concurrency() * 2;
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

/*
.123456 is one hundred twenty-three thousand four hundred fifty-six millionths.
 .100456 is one hundred thousand four hundred fifty-six millionths.
 001456 is one thousand four hundred fifty-six millionths.
  .123456789 one hundred twenty-three million, four hundred fifty-six thousand, seven hundred eighty-nine billionth
 12.3456. It is pronounced “twelve and three thousand, four hundred fifty-six ten-thousandths.”
 */

int main()
{
	// Build 21 to 99
	for (int iTen = 2; iTen < g_nTens - 1; ++iTen)
		for (int iOne = 1; iOne < 10; ++iOne)
			m_vstr21to99.push_back(pair<string, string>(g_tens[iTen] + "-" + g_ones[iOne], to_string(iTen * 10 + iOne)));

	// Build the big numbers
	for (int iHun = 0, nZero = 3; iHun < g_nHuns; iHun++, nZero += 3)
	{
		string strZero(nZero, '0');
		strZero = "1" + strZero; // Is a leading 1 necessary? I don't think so
		g_vstrHuns.push_back(strZero);
	}

	cout << "This program will need user to input a number." << endl << "Then it will read it out and convert it back to the number." << endl;

	string strInput;
	bool bAgain = true;
	do
	{
	input:
		cout << "Enter a number or 'test' for verification or 'quit' to exit: ";
		cin >> strInput;
		if (strInput != "quit" && strInput != "test")
		{
			size_t stP1 = strInput.find_first_of('.');
			size_t stP2 = string::npos;
			if (stP1 != string::npos)
				stP2 = strInput.find_first_of('.', stP1 + 1);
			if (stP1 != string::npos && stP2 != string::npos)
				cout << "Invalid Number!" << endl;
			else
			{
				vector<string> vstrInput, vstrOutput;
				if (stP1 != string::npos)
				{
					string strLhs = strInput.substr(0, stP1);
					string strRhs = strInput.substr(stP1 + 1);
					vstrInput.push_back(strLhs);
					vstrInput.push_back(strRhs);
					vstrInput.push_back("1" + string(strRhs.length(), '0'));
				}
				else
					vstrInput.push_back(strInput);

				int iResult;
				vector<string>::iterator vit;
				for (vit = vstrInput.begin(), iResult = 0; iResult == 0 && vit != vstrInput.end(); ++vit)
				{
					string strResult;
					iResult = expand(*vit, strResult);
					if (iResult < 0)
					{
						if (iResult == -1)
							cout << "Invalid Number!" << endl;
						else if (iResult == -2)
							cout << "The number is out of range. The number must not surpass the +/-" << g_huns[g_nHuns - 1] << " range" << endl;
					}
					else
						vstrOutput.push_back(strResult);
				}

				for (vit = vstrOutput.begin(); iResult == 0 && vit != vstrOutput.end(); ++vit)
				{
					if (vstrOutput.size() == 1)
						cout << *vit;
					else
					{
						if (vit + 1 == vstrOutput.end())
						{
							vector<string> vstrTokens;
							split(*vit, vstrTokens);
							if (*(vstrTokens.begin()) != "One")
								cout << *(vstrTokens.begin()) << "-" << *(vstrTokens.begin() + 1);
							else
								cout << *(vstrTokens.begin() + 1);
						}
						else
							cout << *vit;
						if (vstrOutput.size() > 1 && vit == vstrOutput.begin())
							cout << " and ";
						else
						{
							if (vit + 1 == vstrOutput.end())
								cout << "th";
							else
								cout << " ";
						}
					}
				}
				cout << endl;

				for (vit = vstrOutput.begin(); iResult == 0 && vit != vstrOutput.end(); ++vit)
				{
					string strVerify;
					iResult = contract(*vit, strVerify);
					if (iResult < 0)
						cout << "Invalid Number!" << endl;
					else
					{
						if (vstrOutput.size() > 1 && vit + 1 != vstrOutput.end())
							cout << strVerify;
					}
					if (vstrOutput.size() > 1 && vit == vstrOutput.begin())
						cout << ".";

				}
				cout << endl;
			}
		}
		else
		{
			if (strInput == "quit")
				bAgain = false;
			else
				test();
		}
	} while (bAgain);
	return 0;
}
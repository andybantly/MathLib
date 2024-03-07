#include "pch.h"
#include "CppUnitTest.h"
#include "..\Number.h"

using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestMathLib
{
	TEST_CLASS(TestMathLib)
	{
		static void Test(unsigned long long ullb, unsigned long long ulle)
		{
			CNumber MathLib;

			int iResult;
			string s, sr, sv;
			unsigned long long ull = ullb;
			double dp = 0.0, dt = double(ulle - ullb);

			do
			{
				s = to_string(ull++);
				iResult = MathLib.Expand(s, sr);
				Assert::AreEqual(iResult, 0);

				iResult = MathLib.Contract(sr, sv);
				Assert::AreEqual(iResult, 0);

				Assert::AreEqual(sv, s);
			} while (ull <= ulle && ull != 0);
		}

	public:
		TEST_METHOD(Addition)
		{
			CNumber N1, N2, N3;

			// 10 + 15 = 25
			N1 = "10"; N2 = "15";
			N3 = N1 + N2;
			Assert::AreEqual("25", N3);

			// 10 + -15 = -5
			N1 = "10"; N2 = "-15";
			N3 = N1 + N2;
			Assert::AreEqual("-5", N3);

			// -10 + 15 = 5
			N1 = "-10"; N2 = "15";
			N3 = N1 + N2;
			Assert::AreEqual("5", N3);

			// -10 + -15 = -25
			N1 = "-10"; N2 = "-15";
			N3 = N1 + N2;
			Assert::AreEqual("-25", N3);

			// 15 + 10 = 25
			N1 = "15"; N2 = "10";
			N3 = N1 + N2;
			Assert::AreEqual("25", N3);

			// 15 + -10 = 5
			N1 = "15"; N2 = "-10";
			N3 = N1 + N2;
			Assert::AreEqual("5", N3);

			// -15 + 10 = -5
			N1 = "-15"; N2 = "10";
			N3 = N1 + N2;
			Assert::AreEqual("-5", N3);

			// -15 + -10 = -25
			N1 = "-15"; N2 = "-10";
			N3 = N1 + N2;
			Assert::AreEqual("-25", N3);

			// 10 + 10 = 20
			N1 = "10"; N2 = "10";
			N3 = N1 + N2;
			Assert::AreEqual("20", N3);

			// 10 + -10 = 0
			N1 = "10"; N2 = "-10";
			N3 = N1 + N2;
			Assert::AreEqual("0", N3);

			// -10 + 10 = 0
			N1 = "-10"; N2 = "10";
			N3 = N1 + N2;
			Assert::AreEqual("0", N3);

			// -10 + -10 = -20
			N1 = "-10"; N2 = "-10";
			N3 = N1 + N2;
			Assert::AreEqual("-20", N3);

			// -2005 + -1004 = -3009
			N1 = "-2005"; N2 = "-1004";
			N3 = N1 + N2;
			Assert::AreEqual("-3009", N3);

			// Corner case 25466 + -24367 = 1099
			N1 = "25466"; N2 = "-24367";
			N3 = N1 + N2;
			Assert::AreEqual("1099", N3);

			// Corner case 21902 + -4703
			N1 = "21902"; N2 = "-4703";
			N3 = N1 + N2;
			Assert::AreEqual("17199", N3);
		}

		TEST_METHOD(Subtraction)
		{
			CNumber N1, N2, N3;

			// 10 - 15 = -5
			N1 = "10"; N2 = "15";
			N3 = N1 - N2;
			Assert::AreEqual("-5", N3);

			// 10 - -15 = 25
			N1 = "10"; N2 = "-15";
			N3 = N1 - N2;
			Assert::AreEqual("25", N3);

			// -10 - 15 = -25
			N1 = "-10"; N2 = "15";
			N3 = N1 - N2;
			Assert::AreEqual("-25", N3);

			// -10 - -15 = 5
			N1 = "-10"; N2 = "-15";
			N3 = N1 - N2;
			Assert::AreEqual("5", N3);

			// 15 - 10 = 5
			N1 = "15"; N2 = "10";
			N3 = N1 - N2;
			Assert::AreEqual("5", N3);

			// 15 - -10 = 25
			N1 = "15"; N2 = "-10";
			N3 = N1 - N2;
			Assert::AreEqual("25", N3);

			// -15 - 10 = -25
			N1 = "-15"; N2 = "10";
			N3 = N1 - N2;
			Assert::AreEqual("-25", N3);

			// -15 - -10 = -5
			N1 = "-15"; N2 = "-10";
			N3 = N1 - N2;
			Assert::AreEqual("-5", N3);

			// 10 - 10 = 0
			N1 = "10"; N2 = "10";
			N3 = N1 - N2;
			Assert::AreEqual("0", N3);

			// 10 - -10 = 20
			N1 = "10"; N2 = "-10";
			N3 = N1 - N2;
			Assert::AreEqual("20", N3);

			// -10 - 10 = -20
			N1 = "-10"; N2 = "10";
			N3 = N1 - N2;
			Assert::AreEqual("-20", N3);

			// -10 - -10 = 0
			N1 = "-10"; N2 = "-10";
			N3 = N1 - N2;
			Assert::AreEqual("0", N3);

			// -2005 - -1004 = -1001
			N1 = "-2005"; N2 = "-1004";
			N3 = N1 - N2;
			Assert::AreEqual("-1001", N3);
		}

		TEST_METHOD(RandomMath)
		{
			srand((unsigned)time(NULL));
			for (int i = 0; i < RAND_MAX; ++i)
			{
				CRndPair Rnd;
				CNumber N1(Rnd.Num1());
				CNumber N2(Rnd.Num2());
				CNumber N3;
				if (Rnd.OP() == -1)
					N3 = N1 - N2;
				else
					N3 = N1 + N2;
				const std::string& strSUM = Rnd.Sum();
				Assert::AreEqual(strSUM.c_str(), N3);
			}
		}

		TEST_METHOD(TestLib)
		{
			vector<pair<unsigned long long, unsigned long long> > vtp;
			unsigned long long numt = thread::hardware_concurrency();
//			unsigned long long dtpt = unsigned long long(-1) / numt;
			unsigned long long dtpt = INT_MAX / numt;

			vector<thread*> vptp;
			unsigned long long ullb, ulle;
			for (unsigned long long it = 0; it < numt; it++)
			{
				ullb = it * dtpt;
				if (it + 1 != numt)
					ulle = ullb + dtpt - 1;
				else
					ulle = INT_MAX; // unsigned long long(-1);

				thread* ptp = new thread(Test, ullb, ulle);
				vptp.push_back(ptp);
			}

			for (vector<thread*>::iterator it = vptp.begin(); it != vptp.end(); ++it)
				(*it)->join();

			for (vector<thread*>::iterator it = vptp.begin(); it != vptp.end(); ++it)
				delete* it;
		}
	};
}

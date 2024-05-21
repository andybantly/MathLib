#include "pch.h"
#include "CppUnitTest.h"
#include "..\Number.h"

using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestMathLib
{
	static mutex g_test_mutex;

	TEST_CLASS(TestMathLib)
	{
		static bool Init()
		{
			static atomic<bool> bInit(false);
			static lock_guard<mutex> guard(g_test_mutex);
			if (!bInit)
			{
				CNumber::Init();
				bInit = true;
			}
			return bInit;
		}
		
		static void Test(long long ullb, long long ulle)
		{
			CNumber MathLib;

			int iResult;
			string s, sr, sv, sb2, sb10;
			long long ull = ullb;

			do
			{
				s = to_string(ull++);
				iResult = MathLib.Expand(s, sr);
				Assert::AreEqual(iResult, 0);

				iResult = MathLib.Contract(sr, sv);
				Assert::AreEqual(iResult, 0);

				Assert::AreEqual(sv, s);

				iResult = MathLib.ToBase2(sv, sb2);
				Assert::AreEqual(iResult, 0);

				iResult = MathLib.ToBase10(sb2, sb10);
				Assert::AreEqual(iResult, 0);

				Assert::AreEqual(sv, sb10);
			} while (ull <= ulle && ull != 0);
		}

	public:
		TEST_METHOD(Addition)
		{
			Init();
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
			Init();
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

		TEST_METHOD(Multiplication)
		{
			Init();
			CNumber N1, N2, N3;

			// 10 * 15 = 150
			N1 = "10"; N2 = "15";
			N3 = N1 * N2;
			Assert::AreEqual("150", N3);

			// 10 * -15 = -150
			N1 = "10"; N2 = "-15";
			N3 = N1 * N2;
			Assert::AreEqual("-150", N3);

			// -10 * 15 = -150
			N1 = "-10"; N2 = "15";
			N3 = N1 * N2;
			Assert::AreEqual("-150", N3);

			// -10 * -15 = 150
			N1 = "-10"; N2 = "-15";
			N3 = N1 * N2;
			Assert::AreEqual("150", N3);

			// 15 * 10 = 150
			N1 = "15"; N2 = "10";
			N3 = N1 * N2;
			Assert::AreEqual("150", N3);

			// 15 * -10 = -150
			N1 = "15"; N2 = "-10";
			N3 = N1 * N2;
			Assert::AreEqual("-150", N3);

			// -15 * 10 = -150
			N1 = "-15"; N2 = "10";
			N3 = N1 * N2;
			Assert::AreEqual("-150", N3);

			// -15 * -10 = 150
			N1 = "-15"; N2 = "-10";
			N3 = N1 * N2;
			Assert::AreEqual("150", N3);

			// 10 * 0 = 0
			N1 = "10"; N2 = "0";
			N3 = N1 * N2;
			Assert::AreEqual("0", N3);

			// -10 * 0 = 0
			N1 = "-10"; N2 = "0";
			N3 = N1 * N2;
			Assert::AreEqual("0", N3);

			// 0 * 10 = 0
			N1 = "0"; N2 = "10";
			N3 = N1 * N2;
			Assert::AreEqual("0", N3);

			// 0 * -10 = 0
			N1 = "0"; N2 = "-10";
			N3 = N1 * N2;
			Assert::AreEqual("0", N3);
		}

		TEST_METHOD(Division)
		{
			Init();
			CNumber N1, N2, N3;

			// 150 / 10 = 15
			N1 = "150"; N2 = "10";
			N3 = N1 / N2;
			Assert::AreEqual("15", N3);

			// -150 / 10 = -15
			N1 = "-150"; N2 = "10";
			N3 = N1 / N2;
			Assert::AreEqual("-15", N3);

			// -150 / -10 = 15
			N1 = "-150"; N2 = "-10";
			N3 = N1 / N2;
			Assert::AreEqual("15", N3);

			// 150 / -10 = -15
			N1 = "150"; N2 = "-10";
			N3 = N1 / N2;
			Assert::AreEqual("-15", N3);

			// 150 / 15 = 10
			N1 = "150"; N2 = "15";
			N3 = N1 / N2;
			Assert::AreEqual("10", N3);

			// -150 / 15 = -10
			N1 = "-150"; N2 = "15";
			N3 = N1 / N2;
			Assert::AreEqual("-10", N3);

			// -150 / -15 = 10
			N1 = "-150"; N2 = "-15";
			N3 = N1 / N2;
			Assert::AreEqual("10", N3);

			// 150 / -15 = -10
			N1 = "150"; N2 = "-15";
			N3 = N1 / N2;
			Assert::AreEqual("-10", N3);

			// 0 / 10 = 0
			N1 = "0"; N2 = "10";
			N3 = N1 / N2;
			Assert::AreEqual("0", N3);

			// 0 / -10 = 0
			N1 = "0"; N2 = "-10";
			N3 = N1 / N2;
			Assert::AreEqual("0", N3);

			// 0 / 0 = Division by Zero
			N1 = "0"; N2 = "0";
			N3 = N1 / N2;
			Assert::AreEqual("", N3);

			// -10 / 0 = Division by Zero
			N1 = "-10"; N2 = "0";
			N3 = N1 / N2;
			N3 = N1 / N2;
			Assert::AreEqual("", N3);
		}

		TEST_METHOD(RandomMath)
		{
			Init();
			srand((unsigned)time(NULL));
			int nRM = RAND_MAX * 5;
			CNumber N1, N2, N3;
			for (int i = 0; i < nRM; ++i)
			{
				CRndPair Rnd;
				N1 = Rnd.Num1();
				N2 = Rnd.Num2();

				switch (Rnd.OP())
				{
				case 1:
					N3 = N1 + N2;
					break;
				case 2:
					N3 = N1 - N2;
					break;
				case 3:
					N3 = N1 * N2;
					break;
				case 4:
					N3 = N1 / N2;
					break;
				default:
					N3 = N1 % N2;
				}

				const std::string& strSUM = Rnd.Sum();
				Assert::AreEqual(strSUM, N3.GetNumber());
			}
		}

		TEST_METHOD(RandomAdd)
		{
			Init();
			srand((unsigned)time(NULL));
			int nRM = RAND_MAX;
			CNumber N1, N2, N3;
			for (int i = 0; i < nRM; ++i)
			{
				CRndPair Rnd(1);
				N1 = Rnd.Num1();
				N2 = Rnd.Num2();
				N3 = N1 + N2;

				const std::string& strSUM = Rnd.Sum();
				Assert::AreEqual(strSUM, N3.GetNumber());
			}
		}

		TEST_METHOD(RandomSub)
		{
			Init();
			srand((unsigned)time(NULL));
			int nRM = RAND_MAX;
			CNumber N1, N2, N3;
			for (int i = 0; i < nRM; ++i)
			{
				CRndPair Rnd(2);
				N1 = Rnd.Num1();
				N2 = Rnd.Num2();
				N3 = N1 - N2;

				const std::string& strSUM = Rnd.Sum();
				Assert::AreEqual(strSUM, N3.GetNumber());
			}
		}

		TEST_METHOD(RandomMul)
		{
			srand((unsigned)time(NULL));
			int nRM = RAND_MAX;
			CNumber N1, N2, N3;
			for (int i = 0; i < nRM; ++i)
			{
				CRndPair Rnd(3);
				N1 = Rnd.Num1();
				N2 = Rnd.Num2();
				N3 = N1 * N2;

				const std::string& strSUM = Rnd.Sum();
				Assert::AreEqual(strSUM, N3.GetNumber());
			}
		}

		TEST_METHOD(RandomDiv)
		{
			Init();
			srand((unsigned)time(NULL));
			int nRM = RAND_MAX;
			CNumber N1, N2, N3;
			for (int i = 0; i < nRM; ++i)
			{
				CRndPair Rnd(4);
				N1 = Rnd.Num1();
				N2 = Rnd.Num2();
				N3 = N1 / N2;

				const std::string& strSUM = Rnd.Sum();
				if (strSUM != N3.GetNumber())
					Assert::AreEqual(strSUM, N3.GetNumber());
			}
		}

		TEST_METHOD(RandomMod)
		{
			Init();
			srand((unsigned)time(NULL));
			int nRM = RAND_MAX;
			CNumber N1, N2, N3;
			for (int i = 0; i < nRM; ++i)
			{
				CRndPair Rnd(5);
				N1 = Rnd.Num1();
				N2 = Rnd.Num2();
				N3 = N1 % N2;

				const std::string& strSUM = Rnd.Sum();
				if (strSUM != N3.GetNumber())
					Assert::AreEqual(strSUM, N3.GetNumber());
			}
		}

		TEST_METHOD(TestLib)
		{
			Init();
			long long numt = thread::hardware_concurrency();
			long long dtpt = (RAND_MAX * 4) / numt;

			vector<thread*> vptp;
			long long ullb, ulle;
			for (long long it = 0; it < numt; it++)
			{
				ullb = it * dtpt;
				if (it + 1 != numt)
					ulle = ullb + dtpt - 1;
				else
					ulle = (RAND_MAX * 4);

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

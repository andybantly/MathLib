#include "pch.h"
#include "CppUnitTest.h"
#include "..\Number.h"

using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestMathLib
{
	class CRndPair
	{
	public:
		CRndPair()
		{
			m_iOp = rand() % 5 + 1;
			Calc();
		}

		CRndPair(int iOp) : m_iOp(iOp)
		{
			Calc();
		}
	protected:

		int Random()
		{
			int iLO = 1;
			int iHI = RAND_MAX;
			int iNum = iLO + static_cast<int>(rand()) / (static_cast<int>(RAND_MAX) / (iHI - iLO));
			if (rand() > (RAND_MAX / 2))
				iNum = -iNum;
			return iNum;
		}

		void Calc()
		{
			m_iNum1 = Random();
			m_iNum2 = Random();
			m_strNum1 = to_string(m_iNum1);
			m_strNum2 = to_string(m_iNum2);

			switch (m_iOp)
			{
			case 1:
				m_iSum = m_iNum1 + m_iNum2;
				break;
			case 2:
				m_iSum = m_iNum1 - m_iNum2;
				break;
			case 3:
				m_iSum = m_iNum1 * m_iNum2;
				break;
			case 4:
				m_iSum = m_iNum1 / m_iNum2;
				break;
			default:
				m_iSum = m_iNum1 % m_iNum2;
			}

			m_strSum = to_string(m_iSum);
		}

	public:
		const int& OP() const { return m_iOp; }
		const string& Num1() { return m_strNum1; }
		const string& Num2() { return m_strNum2; }
		const string& Sum() { return m_strSum; }

	private:
		int m_iOp;
		int m_iNum1;
		int m_iNum2;
		int m_iSum;
		string m_strNum1;
		string m_strNum2;
		string m_strSum;
	};

	class CRndPairFP
	{
	public:
		CRndPairFP()
		{
			m_iOp = rand() % 3 + 1;
			Calc();
		}

		CRndPairFP(int iOp) : m_iOp(iOp)
		{
			Calc();
		}
	protected:

		double Random()
		{
			double dLO = 1;
			double dHI = RAND_MAX;
			double dNum = dLO + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX) / (dHI - dLO));
			if (rand() > (RAND_MAX / 2))
				dNum = -dNum;
			return dNum;
		}

		void Calc()
		{
			m_dNum1 = Random();
			m_dNum2 = Random();
			char buf[80];
			sprintf_s(buf, "%.2Lf", m_dNum1);
			m_strNum1 = buf;
			sprintf_s(buf, "%.2Lf", m_dNum2);
			m_strNum2 = buf;
			m_dNum1 = stod(m_strNum1);
			m_dNum2 = stod(m_strNum2);

			switch (m_iOp)
			{
			case 1:
				m_dSum = m_dNum1 + m_dNum2;
				break;
			case 2:
				m_dSum = m_dNum1 - m_dNum2;
				break;
			case 3:
				m_dSum = m_dNum1 * m_dNum2;
				break;
			case 4:
				m_dSum = m_dNum1 / m_dNum2;
				break;
			default:
				// No modulus
				break;
			}

			m_strSum = to_string(m_dSum);
		}

	public:
		const int& OP() const { return m_iOp; }
		const string& Num1() { return m_strNum1; }
		const string& Num2() { return m_strNum2; }
		const string& Sum() { return m_strSum; }

	private:
		int m_iOp;
		long double m_dNum1;
		long double m_dNum2;
		long double m_dSum;
		string m_strNum1;
		string m_strNum2;
		string m_strSum;
	};

	class CRndPairCMP
	{
	public:
		CRndPairCMP()
		{
			m_iOp = rand() % 5 + 1;
			Calc();
		}

		CRndPairCMP(int iOp) : m_iOp(iOp)
		{
			Calc();
		}
	protected:

		double Random()
		{
			double dLO = 1;
			double dHI = RAND_MAX;
			double dNum = dLO + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX) / (dHI - dLO));
			if (rand() > (RAND_MAX / 2))
				dNum = -dNum;
			return dNum;
		}

		void Calc()
		{
			m_dNum1 = Random();
			m_dNum2 = Random();
			char buf[80];
			sprintf_s(buf, "%.4Lf", m_dNum1);
			m_strNum1 = buf;
			sprintf_s(buf, "%.4Lf", m_dNum2);
			m_strNum2 = buf;
			m_dNum1 = stod(m_strNum1);
			m_dNum2 = stod(m_strNum2);

			switch (m_iOp)
			{
			case 1: // LT
				m_bResult = m_dNum1 < m_dNum2;
				break;
			case 2: // LTE
				m_bResult = m_dNum1 <= m_dNum2;
				break;
			case 3: // GT
				m_bResult = m_dNum1 > m_dNum2;
				break;
			case 4: // GTE
				m_bResult = m_dNum1 >= m_dNum2;
				break;
			case 5: // EQ
			default:
				m_bResult = m_dNum1 == m_dNum2;
				break;
			}

		}

	public:
		const int& OP() const { return m_iOp; }
		const string& Num1() { return m_strNum1; }
		const string& Num2() { return m_strNum2; }
		const bool Result() { return m_bResult; }

	private:
		int m_iOp;
		long double m_dNum1;
		long double m_dNum2;
		bool m_bResult;
		string m_strNum1;
		string m_strNum2;
	};

	TEST_CLASS(TestMathLib)
	{
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
				if (iResult != 0)
					Assert::AreEqual(iResult, 0);

				iResult = MathLib.Contract(sr, sv);
				if (iResult != 0)
					Assert::AreEqual(iResult, 0);

				Assert::AreEqual(sv, s);

				iResult = MathLib.ToBase2(sv, sb2);
				if (iResult != 0)
					Assert::AreEqual(iResult, 0);

				iResult = MathLib.ToBase10(sb2, sb10);
				if (iResult != 0)
					Assert::AreEqual(iResult, 0);

				Assert::AreEqual(sv, sb10);

				s = to_string(-ull - 1);
				iResult = MathLib.Expand(s, sr);
				if (iResult != 0)
					Assert::AreEqual(iResult, 0);

				iResult = MathLib.Contract(sr, sv);
				if (iResult != 0)
					Assert::AreEqual(iResult, 0);

				Assert::AreEqual(sv, s);

				iResult = MathLib.ToBase2(sv, sb2);
				if (iResult != 0)
					Assert::AreEqual(iResult, 0);

				iResult = MathLib.ToBase10(sb2, sb10);
				if (iResult != 0)
					Assert::AreEqual(iResult, 0);

				Assert::AreEqual(sv, sb10);
			} while (ull <= ulle && ull != 0);
		}

	public:

		TEST_CLASS_INITIALIZE(TestInitialize)
		{
			srand((unsigned)time(nullptr));
			CNumber::Init();
		}

		TEST_METHOD(Addition)
		{
			CNumber N1, N2, N3;

			// 10 + 15 = 25
			N1 = "10"; N2 = "15";
			N3 = N1 + N2;
			Assert::AreEqual(CNumber("25"), N3);

			// 10 + -15 = -5
			N1 = "10"; N2 = "-15";
			N3 = N1 + N2;
			Assert::AreEqual(CNumber("-5"), N3);

			// -10 + 15 = 5
			N1 = "-10"; N2 = "15";
			N3 = N1 + N2;
			Assert::AreEqual(CNumber("5"), N3);

			// -10 + -15 = -25
			N1 = "-10"; N2 = "-15";
			N3 = N1 + N2;
			Assert::AreEqual(CNumber("-25"), N3);

			// 15 + 10 = 25
			N1 = "15"; N2 = "10";
			N3 = N1 + N2;
			Assert::AreEqual(CNumber("25"), N3);

			// 15 + -10 = 5
			N1 = "15"; N2 = "-10";
			N3 = N1 + N2;
			Assert::AreEqual(CNumber("5"), N3);

			// -15 + 10 = -5
			N1 = "-15"; N2 = "10";
			N3 = N1 + N2;
			Assert::AreEqual(CNumber("-5"), N3);

			// -15 + -10 = -25
			N1 = "-15"; N2 = "-10";
			N3 = N1 + N2;
			Assert::AreEqual(CNumber("-25"), N3);

			// 10 + 10 = 20
			N1 = "10"; N2 = "10";
			N3 = N1 + N2;
			Assert::AreEqual(CNumber("20"), N3);

			// 10 + -10 = 0
			N1 = "10"; N2 = "-10";
			N3 = N1 + N2;
			Assert::AreEqual(CNumber("0"), N3);

			// -10 + 10 = 0
			N1 = "-10"; N2 = "10";
			N3 = N1 + N2;
			Assert::AreEqual(CNumber("0"), N3);

			// -10 + -10 = -20
			N1 = "-10"; N2 = "-10";
			N3 = N1 + N2;
			Assert::AreEqual(CNumber("-20"), N3);

			// -10.025 + -10.0025 = 
			N1 = "-10.025"; N2 = "-10.0025";
			N3 = N1 + N2;
			Assert::AreEqual(CNumber("-20.0275"), N3);

			// -10.025 + 10.0025 = -0.0225
			N1 = "-10.025"; N2 = "10.0025";
			N3 = N1 + N2;
			Assert::AreEqual(CNumber("-0.0225"), N3);

			// 10.025 + -10.0025 = 0.0225
			N1 = "10.025"; N2 = "-10.0025";
			N3 = N1 + N2;
			Assert::AreEqual(CNumber("0.0225"), N3);

			// 10.025 + 10.0025 = 20.0275
			N1 = "10.025"; N2 = "10.0025";
			N3 = N1 + N2;
			Assert::AreEqual(CNumber("20.0275"), N3);

			// -10.025 + -10.000025 = -20.025025
			N1 = "-10.025"; N2 = "-10.000025";
			N3 = N1 + N2;
			Assert::AreEqual(CNumber("-20.025025"), N3);

			// -10.025 + 10.000025 = -0.024975
			N1 = "-10.025"; N2 = "10.000025";
			N3 = N1 + N2;
			Assert::AreEqual(CNumber("-0.024975"), N3);

			// 10.025 + -10.000025 = 0.024975
			N1 = "10.025"; N2 = "-10.000025";
			N3 = N1 + N2;
			Assert::AreEqual(CNumber("0.024975"), N3);

			// 10.025 + 10.000025 = 20.025025
			N1 = "10.025"; N2 = "10.000025";
			N3 = N1 + N2;
			Assert::AreEqual(CNumber("20.025025"), N3);

			// -2005 + -1004 = -3009
			N1 = "-2005"; N2 = "-1004";
			N3 = N1 + N2;
			Assert::AreEqual(CNumber("-3009"), N3);

			// Corner case 25466 + -24367 = 1099
			N1 = "25466"; N2 = "-24367";
			N3 = N1 + N2;
			Assert::AreEqual(CNumber("1099"), N3);

			// Corner case 21902 + -4703
			N1 = "00021902.2500"; N2 = "-4703.1";
			N3 = N1 + N2;
			Assert::AreEqual(CNumber("17199.15"), N3);
		}

		TEST_METHOD(Subtraction)
		{
			CNumber N1, N2, N3;

			// 10 - 15 = -5
			N1 = "10"; N2 = "15";
			N3 = N1 - N2;
			Assert::AreEqual(CNumber("-5"), N3);

			// 10 - -15 = 25
			N1 = "10"; N2 = "-15";
			N3 = N1 - N2;
			Assert::AreEqual(CNumber("25"), N3);

			// -10 - 15 = -25
			N1 = "-10"; N2 = "15";
			N3 = N1 - N2;
			Assert::AreEqual(CNumber("-25"), N3);

			// -10 - -15 = 5
			N1 = "-10"; N2 = "-15";
			N3 = N1 - N2;
			Assert::AreEqual(CNumber("5"), N3);

			// 15 - 10 = 5
			N1 = "15"; N2 = "10";
			N3 = N1 - N2;
			Assert::AreEqual(CNumber("5"), N3);

			// 15 - -10 = 25
			N1 = "15"; N2 = "-10";
			N3 = N1 - N2;
			Assert::AreEqual(CNumber("25"), N3);

			// -15 - 10 = -25
			N1 = "-15"; N2 = "10";
			N3 = N1 - N2;
			Assert::AreEqual(CNumber("-25"), N3);

			// -15 - -10 = -5
			N1 = "-15"; N2 = "-10";
			N3 = N1 - N2;
			Assert::AreEqual(CNumber("-5"), N3);

			// 10 - 10 = 0
			N1 = "10"; N2 = "10";
			N3 = N1 - N2;
			Assert::AreEqual(CNumber("0"), N3);

			// 10 - -10 = 20
			N1 = "10"; N2 = "-10";
			N3 = N1 - N2;
			Assert::AreEqual(CNumber("20"), N3);

			// -10 - 10 = -20
			N1 = "-10"; N2 = "10";
			N3 = N1 - N2;
			Assert::AreEqual(CNumber("-20"), N3);

			// -10 - -10 = 0
			N1 = "-10"; N2 = "-10";
			N3 = N1 - N2;
			Assert::AreEqual(CNumber("0"), N3);

			// -10.025 - -10.0025 = -0.0225
			N1 = "-10.025"; N2 = "-10.0025";
			N3 = N1 - N2;
			Assert::AreEqual(CNumber("-0.0225"), N3);

			// -10.025 - 10.0025 = -20.0275
			N1 = "-10.025"; N2 = "10.0025";
			N3 = N1 - N2;
			Assert::AreEqual(CNumber("-20.0275"), N3);

			// 10.025 - -10.0025 = 20.0275
			N1 = "10.025"; N2 = "-10.0025";
			N3 = N1 - N2;
			Assert::AreEqual(CNumber("20.0275"), N3);

			// 10.025 - 10.0025 = 20.0275
			N1 = "10.025"; N2 = "10.0025";
			N3 = N1 - N2;
			Assert::AreEqual(CNumber("0.0225"), N3);

			// -10.025 - -10.000025 = -0.024975
			N1 = "-10.025"; N2 = "-10.000025";
			N3 = N1 - N2;
			Assert::AreEqual(CNumber("-0.024975"), N3);

			// -10.025 - 10.000025 = -20.025025
			N1 = "-10.025"; N2 = "10.000025";
			N3 = N1 - N2;
			Assert::AreEqual(CNumber("-20.025025"), N3);

			// 10.025 - -10.000025 = 20.025025
			N1 = "10.025"; N2 = "-10.000025";
			N3 = N1 - N2;
			Assert::AreEqual(CNumber("20.025025"), N3);

			// 10.025 - 10.000025 = 0.024975
			N1 = "10.025"; N2 = "10.000025";
			N3 = N1 - N2;
			Assert::AreEqual(CNumber("0.024975"), N3);

			// -2005 - -1004 = -1001
			N1 = "-2005"; N2 = "-1004";
			N3 = N1 - N2;
			Assert::AreEqual(CNumber("-1001"), N3);
		}

		TEST_METHOD(Multiplication)
		{
			CNumber N1, N2, N3;

			// 10 * 15 = 150
			N1 = "10"; N2 = "15";
			N3 = N1 * N2;
			Assert::AreEqual(CNumber("150"), N3);

			// 10 * -15 = -150
			N1 = "10"; N2 = "-15";
			N3 = N1 * N2;
			Assert::AreEqual(CNumber("-150"), N3);

			// -10 * 15 = -150
			N1 = "-10"; N2 = "15";
			N3 = N1 * N2;
			Assert::AreEqual(CNumber("-150"), N3);

			// -10 * -15 = 150
			N1 = "-10"; N2 = "-15";
			N3 = N1 * N2;
			Assert::AreEqual(CNumber("150"), N3);

			// 15 * 10 = 150
			N1 = "15"; N2 = "10";
			N3 = N1 * N2;
			Assert::AreEqual(CNumber("150"), N3);

			// 15 * -10 = -150
			N1 = "15"; N2 = "-10";
			N3 = N1 * N2;
			Assert::AreEqual(CNumber("-150"), N3);

			// -15 * 10 = -150
			N1 = "-15"; N2 = "10";
			N3 = N1 * N2;
			Assert::AreEqual(CNumber("-150"), N3);

			// -15 * -10 = 150
			N1 = "-15"; N2 = "-10";
			N3 = N1 * N2;
			Assert::AreEqual(CNumber("150"), N3);

			// 10 * 0 = 0
			N1 = "10"; N2 = "0";
			N3 = N1 * N2;
			Assert::AreEqual(CNumber("0"), N3);

			// -10 * 0 = 0
			N1 = "-10"; N2 = "0";
			N3 = N1 * N2;
			Assert::AreEqual(CNumber("0"), N3);

			// 0 * 10 = 0
			N1 = "0"; N2 = "10";
			N3 = N1 * N2;
			Assert::AreEqual(CNumber("0"), N3);

			// 0 * -10 = 0
			N1 = "0"; N2 = "-10";
			N3 = N1 * N2;
			Assert::AreEqual(CNumber("0"), N3);

			// 2.5 * 2.5 = 6.25
			N1 = "2.5";
			N1 = N1 * N1;
			Assert::AreEqual(CNumber("6.25"), N1);
		}

		TEST_METHOD(Division)
		{
			CNumber N1, N2, N3;

			// 150 / 10 = 15
			N1 = "150"; N2 = "10";
			N3 = N1 / N2;
			Assert::AreEqual(CNumber("15"), N3);

			// -150 / 10 = -15
			N1 = "-150"; N2 = "10";
			N3 = N1 / N2;
			Assert::AreEqual(CNumber("-15"), N3);

			// -150 / -10 = 15
			N1 = "-150"; N2 = "-10";
			N3 = N1 / N2;
			Assert::AreEqual(CNumber("15"), N3);

			// 150 / -10 = -15
			N1 = "150"; N2 = "-10";
			N3 = N1 / N2;
			Assert::AreEqual(CNumber("-15"), N3);

			// 150 / 15 = 10
			N1 = "150"; N2 = "15";
			N3 = N1 / N2;
			Assert::AreEqual(CNumber("10"), N3);

			// -150 / 15 = -10
			N1 = "-150"; N2 = "15";
			N3 = N1 / N2;
			Assert::AreEqual(CNumber("-10"), N3);

			// -150 / -15 = 10
			N1 = "-150"; N2 = "-15";
			N3 = N1 / N2;
			Assert::AreEqual(CNumber("10"), N3);

			// 150 / -15 = -10
			N1 = "150"; N2 = "-15";
			N3 = N1 / N2;
			Assert::AreEqual(CNumber("-10"), N3);

			// 0 / 10 = 0
			N1 = "0"; N2 = "10";
			N3 = N1 / N2;
			Assert::AreEqual(CNumber("0"), N3);

			// 0 / -10 = 0
			N1 = "0"; N2 = "-10";
			N3 = N1 / N2;
			Assert::AreEqual(CNumber("0"), N3);

			// 0 / 0 = Division by Zero
			N1 = "0"; N2 = "0";
			N3 = N1 / N2;
			Assert::AreEqual(CNumber(""), N3);

			// -10 / 0 = Division by Zero
			N1 = "-10"; N2 = "0";
			N3 = N1 / N2;
			Assert::AreEqual(CNumber(""), N3);
		}

		TEST_METHOD(Modulus)
		{
			CNumber N1, N2, N3;

			// 150 % 10 = 0
			N1 = "150"; N2 = "10";
			N3 = N1 % N2;
			Assert::AreEqual(CNumber("0"), N3);

			// -150 % 10 = 0
			N1 = "-150"; N2 = "10";
			N3 = N1 % N2;
			Assert::AreEqual(CNumber("0"), N3);

			// -150 % -10 = 0
			N1 = "-150"; N2 = "-10";
			N3 = N1 % N2;
			Assert::AreEqual(CNumber("0"), N3);

			// 150 % -10 = 0
			N1 = "150"; N2 = "-10";
			N3 = N1 % N2;
			Assert::AreEqual(CNumber("0"), N3);

			// 150 % 14 = 10
			N1 = "150"; N2 = "14";
			N3 = N1 % N2;
			Assert::AreEqual(CNumber("10"), N3);

			// -150 % 14 = -10
			N1 = "-150"; N2 = "14";
			N3 = N1 % N2;
			Assert::AreEqual(CNumber("-10"), N3);

			// -150 % -14 = -10
			N1 = "-150"; N2 = "-14";
			N3 = N1 % N2;
			Assert::AreEqual(CNumber("-10"), N3);

			// 150 % -14 = 10
			N1 = "150"; N2 = "-14";
			N3 = N1 % N2;
			Assert::AreEqual(CNumber("10"), N3);

			// 0 % 10 = 0
			N1 = "0"; N2 = "10";
			N3 = N1 % N2;
			Assert::AreEqual(CNumber("0"), N3);

			// 0 % -10 = 0
			N1 = "0"; N2 = "-10";
			N3 = N1 % N2;
			Assert::AreEqual(CNumber("0"), N3);

			// 0 % 0 = 0
			N1 = "0"; N2 = "0";
			N3 = N1 % N2;
			Assert::AreEqual(CNumber("0"), N3);

			// -10 % 0 = Division by Zero
			N1 = "-10"; N2 = "0";
			N3 = N1 % N2;
			Assert::AreEqual(CNumber("-10"), N3);
		}

		TEST_METHOD(RandomMath)
		{
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

				CNumber SUM(Rnd.Sum());
				Assert::AreEqual(SUM, N3);
			}
		}

		TEST_METHOD(RandomMathFP)
		{
			int nRM = RAND_MAX * 5;
			CNumber N1, N2, N3;
			for (int i = 0; i < nRM; ++i)
			{
				CRndPairFP Rnd;
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

				CNumber N4(Rnd.Sum());
				Assert::AreEqual(N3, N4);
			}
		}

		TEST_METHOD(RandomCMP)
		{
			int nRM = RAND_MAX * 5;
			bool bCMP;
			CNumber N1, N2;
			for (int i = 0; i < nRM; ++i)
			{
				CRndPairCMP Rnd;
				N1 = Rnd.Num1();
				N2 = Rnd.Num2();

				switch (Rnd.OP())
				{
				case 1:
					bCMP = N1 < N2;
					break;
				case 2:
					bCMP = N1 <= N2;
					break;
				case 3:
					bCMP = N1 > N2;
					break;
				case 4:
					bCMP = N1 >= N2;
					break;
				case 5:
				default:
					bCMP = N1 == N2;
				}

				bool bRes = Rnd.Result();
				Assert::AreEqual(bRes, bCMP);
			}
		}

		TEST_METHOD(RandomAdd)
		{
			int nRM = RAND_MAX;
			CNumber N1, N2, N3;
			for (int i = 0; i < nRM; ++i)
			{
				CRndPair Rnd(1);
				N1 = Rnd.Num1();
				N2 = Rnd.Num2();
				N3 = N1 + N2;

				CNumber SUM(Rnd.Sum());
				Assert::AreEqual(SUM, N3);
			}
		}

		TEST_METHOD(RandomSub)
		{
			int nRM = RAND_MAX;
			CNumber N1, N2, N3;
			for (int i = 0; i < nRM; ++i)
			{
				CRndPair Rnd(2);
				N1 = Rnd.Num1();
				N2 = Rnd.Num2();
				N3 = N1 - N2;

				CNumber SUM(Rnd.Sum());
				Assert::AreEqual(SUM, N3);
			}
		}

		TEST_METHOD(RandomMul)
		{
			int nRM = RAND_MAX;
			CNumber N1, N2, N3;
			for (int i = 0; i < nRM; ++i)
			{
				CRndPair Rnd(3);
				N1 = Rnd.Num1();
				N2 = Rnd.Num2();
				N3 = N1 * N2;

				CNumber SUM(Rnd.Sum());
				Assert::AreEqual(SUM, N3);
			}
		}

		TEST_METHOD(RandomDiv)
		{
			int nRM = RAND_MAX;
			CNumber N1, N2, N3;
			for (int i = 0; i < nRM; ++i)
			{
				CRndPair Rnd(4);
				N1 = Rnd.Num1();
				N2 = Rnd.Num2();
				N3 = N1 / N2;

				CNumber SUM(Rnd.Sum());
				Assert::AreEqual(SUM, N3);
			}
		}

		TEST_METHOD(RandomMod)
		{
			int nRM = RAND_MAX;
			CNumber N1, N2, N3;
			for (int i = 0; i < nRM; ++i)
			{
				CRndPair Rnd(5);
				N1 = Rnd.Num1();
				N2 = Rnd.Num2();
				N3 = N1 % N2;

				CNumber SUM(Rnd.Sum());
				Assert::AreEqual(SUM, N3);
			}
		}

		TEST_METHOD(LessThan)
		{
			CNumber N1, N2;
			bool b;

			double d1 = -5, d2 = -5.2;
			b = d1 < d2;
			
			N1 = "-0005"; N2 = "-5.2";
			b = N1 < N2;
			Assert::AreEqual(false, b);

			d1 = -5.01, d2 = -5.2;
			b = d1 < d2;

			N1 = "-0005.01"; N2 = "-5.2";
			b = N1 < N2;
			Assert::AreEqual(false, b);

			N1 = "4"; N2 = "5";
			b = N1 < N2;
			Assert::AreEqual(true, b);

			N1 = "6"; N2 = "5";
			b = N1 < N2;
			Assert::AreEqual(false, b);

			N1 = "5.5"; N2 = "5.5";
			b = N1 < N2;
			Assert::AreEqual(false, b);

			N1 = "4.5"; N2 = "5";
			b = N1 < N2;
			Assert::AreEqual(true, b);

			N1 = "6.5"; N2 = "5";
			b = N1 < N2;
			Assert::AreEqual(false, b);
		}

		TEST_METHOD(LessThanEqual)
		{
			CNumber N1, N2;
			bool b;

			N1 = "5"; N2 = "5";
			b = N1 <= N2;
			Assert::AreEqual(true, b);

			N1 = "4"; N2 = "5";
			b = N1 <= N2;
			Assert::AreEqual(true, b);

			N1 = "6"; N2 = "5";
			b = N1 <= N2;
			Assert::AreEqual(false, b);

			N1 = "5.5"; N2 = "5.5";
			b = N1 <= N2;
			Assert::AreEqual(true, b);

			N1 = "4.5"; N2 = "5";
			b = N1 <= N2;
			Assert::AreEqual(true, b);

			N1 = "6.5"; N2 = "5";
			b = N1 <= N2;
			Assert::AreEqual(false, b);
		}

		TEST_METHOD(GreaterThan)
		{
			CNumber N1, N2;
			bool b;

			N1 = "5"; N2 = "5";
			b = N1 > N2;
			Assert::AreEqual(false, b);

			N1 = "4"; N2 = "5";
			b = N1 > N2;
			Assert::AreEqual(false, b);

			N1 = "6"; N2 = "5";
			b = N1 > N2;
			Assert::AreEqual(true, b);

			N1 = "5.5"; N2 = "5.5";
			b = N1 > N2;
			Assert::AreEqual(false, b);

			N1 = "4.5"; N2 = "5";
			b = N1 > N2;
			Assert::AreEqual(false, b);

			N1 = "6.5"; N2 = "5";
			b = N1 > N2;
			Assert::AreEqual(true, b);
		}

		TEST_METHOD(GreaterThanEqual)
		{
			CNumber N1, N2;
			bool b;

			N1 = "5"; N2 = "5";
			b = N1 >= N2;
			Assert::AreEqual(true, b);

			N1 = "4"; N2 = "5";
			b = N1 >= N2;
			Assert::AreEqual(false, b);

			N1 = "6"; N2 = "5";
			b = N1 >= N2;
			Assert::AreEqual(true, b);

			N1 = "5.5"; N2 = "5.5";
			b = N1 >= N2;
			Assert::AreEqual(true, b);

			N1 = "4.5"; N2 = "5";
			b = N1 >= N2;
			Assert::AreEqual(false, b);

			N1 = "6.5"; N2 = "5";
			b = N1 >= N2;
			Assert::AreEqual(true, b);
		}

		TEST_METHOD(Equal)
		{
			CNumber N1, N2;
			bool b;

			N1 = "5"; N2 = "5";
			b = N1 == N2;
			Assert::AreEqual(true, b);

			N1 = "4"; N2 = "5";
			b = N1 == N2;
			Assert::AreEqual(false, b);

			N1 = "6"; N2 = "5";
			b = N1 == N2;
			Assert::AreEqual(false, b);

			N1 = "5.5"; N2 = "5.5";
			b = N1 == N2;
			Assert::AreEqual(true, b);

			N1 = "4.5"; N2 = "5";
			b = N1 == N2;
			Assert::AreEqual(false, b);

			N1 = "6.5"; N2 = "5";
			b = N1 == N2;
			Assert::AreEqual(false, b);

			N1 = "-5"; N2 = "5";
			b = N1 == N2;
			Assert::AreEqual(false, b);

			N1 = "-4"; N2 = "5";
			b = N1 == N2;
			Assert::AreEqual(false, b);

			N1 = "-6"; N2 = "5";
			b = N1 == N2;
			Assert::AreEqual(false, b);

			N1 = "-5.5"; N2 = "-5.5";
			b = N1 == N2;
			Assert::AreEqual(true, b);

			N1 = "-4.5"; N2 = "5.005";
			b = N1 == N2;
			Assert::AreEqual(false, b);

			N1 = "-6.005"; N2 = "-6.0050";
			b = N1 == N2;
			Assert::AreEqual(true, b);

			N1 = "-6.3450"; N2 = "-6.345";
			b = N1 == N2;
			Assert::AreEqual(true, b);
		}

		TEST_METHOD(RandomAddDouble)
		{
			CNumber N1, N2, N3, N4;
			N4 = "6.28318";
			for (int i = 0; i < 100000; ++i)
			{
				N1 = "3.14159";
				N2 = "3.14159";
				N3 = N1 + N2;
				Assert::AreEqual(N4, N3);
			}
		}

		TEST_METHOD(RandomMulDouble)
		{
			CNumber N1, N2, N3, N4;
			N4 = "6.28318";
			for (int i = 0; i < 100000; ++i)
			{
				N1 = "3.14159";
				N2 = "2";
				N3 = N1 * N2;
				Assert::AreEqual(N4, N3);
			}
		}

		TEST_METHOD(TestLib)
		{
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

// error C2338 : static_assert failed : 'Test writer must define specialization of ToString<const Q& q> 
// for your class class std::basic_string<wchar_t,struct std::char_traits<wchar_t>,class std::allocator<wchar_t> > 
// __cdecl Microsoft::VisualStudio::CppUnitTestFramework::ToString<class CNumber>(const class CNumber &).
namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			template<> wstring static ToString<CNumber>(const CNumber& Number)
			{
				return CNumber::ToString(Number);
			}
		}
	}
}
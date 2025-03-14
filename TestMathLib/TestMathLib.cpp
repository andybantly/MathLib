#include "pch.h"
#include "CppUnitTest.h"
#include "..\Number.h"

#pragma warning(disable:4552)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestMathLib
{
	const int iBeg = -128/* 10*/, iEnd = 127/* 10*/;
	const int jBeg = iBeg, jEnd = iEnd;

	TEST_CLASS(TestMathLib)
	{
		static void Test(long long ullb, long long ulle)
		{
			NumberTranscriber& MathLib = NumberTranscriber::getInstance();
			std::string s, sr, sv;
			long long ull = ullb;

			do
			{
				s = std::to_string(ull++);
				sr = MathLib.ToPhrase(s);
				sv = MathLib.ToNumber(sr);
				if (sv != s)
					Assert::AreEqual(sv, s);
			} while (ull <= ulle && ull != 0);
		}

	public:

		TEST_CLASS_INITIALIZE(TestInitialize)
		{
			srand((unsigned)time(nullptr));
			NumberTranscriber& instance = NumberTranscriber::getInstance();
		}

		TEST_METHOD(TestLib)
		{
			long long numt = std::thread::hardware_concurrency();
			long long dtpt = RAND_MAX / numt;

			std::vector<std::thread*> vptp;
			long long ullb, ulle;
			for (long long it = 0; it < numt; it++)
			{
				ullb = it * dtpt;
				if (it + 1 != numt)
					ulle = ullb + dtpt - 1;
				else
					ulle = RAND_MAX;

				std::thread* ptp = new std::thread(Test, ullb, ulle);
				vptp.push_back(ptp);
			}

			for (std::vector<std::thread*>::iterator it = vptp.begin(); it != vptp.end(); ++it)
				(*it)->join();

			for (std::vector<std::thread*>::iterator it = vptp.begin(); it != vptp.end(); ++it)
				delete* it;
		}

		TEST_METHOD(FibComma)
		{
			Number Fn = 0, NI = 1, NJ = 1, NZ = 0;

			Fn.SetSize(96);
			NI.SetSize(96);
			NJ.SetSize(96);
			NZ.SetSize(1);

			while (!NJ.IsOverFlow()) { NJ = (/*std::cout << Fn << std::endl,*/ Fn = NI, NI = NJ, Fn + NI); }
		}

		TEST_METHOD(FibObj)
		{
			// Traditional Swap
			Number NJ = 1, NI = 0, NZ = 0;
			Number Fib1 = 0, Fib2 = 1, Fib3 = 1;

			Fib1.SetSize(96);
			Fib2.SetSize(96);
			Fib3.SetSize(96);
			NZ.SetSize(1);

			while (!Fib3.IsOverFlow())
			{
				Fib1 = Fib2;
				Fib2 = Fib3;
				Fib3 = Fib1 + Fib2;
			}
		}

		TEST_METHOD(FibArr)
		{
			// Traditional Arrays Swap
			Number NJ = 1, NI = 0, NZ = 0;
			Number Fib[3] = { 0, 1, 1 };

			Fib[0].SetSize(96);
			Fib[1].SetSize(96);
			Fib[2].SetSize(96);
			NZ.SetSize(1);

			while (!Fib[2].IsOverFlow())
			{
				Fib[0] = Fib[1];
				Fib[1] = Fib[2];
				Fib[2] = Fib[0] + Fib[1];
			}
		}

		TEST_METHOD(ByteSingleTest)
		{
			//int a, b, c;
			Number A,B,C;
			std::string s;

			//A = 2147483647; A.SetSize(1); B = A;
			/*
			a = -19;
			b = -21;

			A = a; A.SetSize(1);
			B = b; B.SetSize(1);

			c = a + b;
			C = A + B;

			s = C.ToDisplay();
			if (std::to_string(c) != s)
				Assert::AreEqual(std::to_string(c), s);*/
		}

		TEST_METHOD(ByteMixSize)
		{
			Number A, B, C;
			int a, b, c;
			std::string s;

			A = 999999;
			a = 999999;
			B = b = 180;
			C = A / B;
			c = a / b;
			s = C.ToDisplay();
			if (std::to_string(c) != s)
				Assert::AreEqual(std::to_string(c), s);

			B = b = 256;
			b >> 1;
			B >> 1;
			s = B.ToDisplay();
			if (std::to_string(b) != s)
				Assert::AreEqual(std::to_string(b), s);

			B = b = -2;
			b << 1;
			B << 1;
			s = B.ToDisplay();
			if (std::to_string(b) != s)
				Assert::AreEqual(std::to_string(b), s);

			b >> 1;
			B >> 1;
			s = B.ToDisplay();
			if (std::to_string(b) != s)
				Assert::AreEqual(std::to_string(b), s);

			////// TEST CASE //////
			A = a = 1, B = b = 255;
			A.SetSize(1);
			C = A + B;
			c = a + b;

			s = C.ToDisplay();
			if (std::to_string(c) != s)
				Assert::AreEqual(std::to_string(c), s);

			C = B + A;
			c = b + a;

			s = C.ToDisplay();
			if (std::to_string(c) != s)
				Assert::AreEqual(std::to_string(c), s);

			Number X = "13107200000000";
			X >>= 40; 
			Assert::AreEqual(std::string("11"), X.ToDisplay());

			b = 25;
			A = -20000000000000000;
			if (A.ToDisplay() != "-20000000000000000")
				Assert::AreEqual(A.ToDisplay(), std::string("-20000000000000000"));

			b = (int)sqrt(b);
			s = std::to_string(b);

			B = 25;
			C = B.Sqrt();

			if (C.ToDisplay() != s)
				Assert::AreEqual(C.ToDisplay(), s);

			B = b = 26;
			b = (int)sqrt(b);
			C = B.Sqrt();

			if (C.ToDisplay() != s)
				Assert::AreEqual(C.ToDisplay(), s);

			Number D = 50;
			Number E = D >> 2; // D can't change
			E = D >>= 2; // D changes
			if (D.ToDisplay() == E.ToDisplay())
				Assert::AreEqual(D.ToDisplay(), E.ToDisplay());
		}

		TEST_METHOD(BytePI)
		{
			std::string s = "3141592653589793";
			Number PI = s;
//			s = PI.ToBinary();
//			s = PI.ToDisplay();
		}

		TEST_METHOD(BytePrime)
		{
			Number B = 25, N25p = "15511210043330985984000000";
			B = B.Prime();
			if (B.ToDisplay() != N25p.ToDisplay())
				Assert::AreEqual(N25p.ToDisplay(), B.ToDisplay());
		}

		TEST_METHOD(ByteTestInit)
		{
			std::string s,s1;
			Number A;

			A = 1326124800;
			s = A.ToDisplay();
			A = "1326124800";
			s1 = A.ToDisplay();
			if (s1 != s)
				Assert::AreEqual(s, s1);
		}

		TEST_METHOD(ByteShift)
		{
			std::string s, e;
			int64_t a;
			Number A;

			A = a = -31;
			a = a << 1;
			A <<= 1;
			s = std::to_string(a);
			if (s != A.ToDisplay())
				Assert::AreEqual(s, A.ToDisplay());

			e = "2652249600";
			A = 1326124800;
			A <<= 1;
			s = A.ToDisplay();
			if (e != s)
				Assert::AreEqual(e, s);

			A = a = 0x40000000;
			a <<= 8;
			A <<= 8;
			e = std::to_string(a);
			s = A.ToDisplay();
			if (e != s)
				Assert::AreEqual(e, s);

			for (UNUM ipow = 0; ipow < BITWIDTH - 1; ++ipow)
			{
				UNUM pow = _pow[ipow];
				for (int nb = 1; nb <= BITWIDTH; ++nb)
				{
					A = a = pow;
					a <<= nb;
					A <<= nb;
					e = std::to_string(a);
					s = A.ToDisplay();
					if (e != s)
						Assert::AreEqual(e, s);

					a >>= nb;
					A >>= nb;
					e = std::to_string(a);
					s = A.ToDisplay();
					if (e != s)
						Assert::AreEqual(e, s);
				}
			}
		}

		TEST_METHOD(ByteCornerCases)
		{
			Number A, B, C;
			int a, b, c;
			std::string s;

			////// TEST CASE //////

			A = a = 127;
			B = b = 25;

			c = a / b;
			C = A / B;

			s = C.ToDisplay();
			if (std::to_string(c) != s)
				Assert::AreEqual(std::to_string(c), s);

			////// TEST CASE //////

			B = b = 5;
			
			b *= b;
			B *= B;

			s = B.ToDisplay();
			if (std::to_string(b) != s)
				Assert::AreEqual(std::to_string(b), s);

			b /= b;
			B /= B;

			s = B.ToDisplay();
			if (std::to_string(b) != s)
				Assert::AreEqual(std::to_string(b), s);

			b %= b;
			B %= B;

			s = B.ToDisplay();
			if (std::to_string(b) != s)
				Assert::AreEqual(std::to_string(b), s);

			b += b;
			B += B;

			s = B.ToDisplay();
			if (std::to_string(b) != s)
				Assert::AreEqual(std::to_string(b), s);

			b -= b;
			B -= B;

			s = B.ToDisplay();
			if (std::to_string(b) != s)
				Assert::AreEqual(std::to_string(b), s);

			////// TEST CASE //////

			////// TEST CASE //////

			A = a = 127;
			B = b = 25;

			c = a / b;
			C = A / B;

			s = C.ToDisplay();
			if (std::to_string(c) != s)
				Assert::AreEqual(std::to_string(c), s);

			c = a % b;
			C = A % B;

			s = C.ToDisplay();
			if (std::to_string(c) != s)
				Assert::AreEqual(std::to_string(c), s);

			A = a = 125;
			B = b = 25;

			c = a / b;
			C = A / B;

			s = C.ToDisplay();
			if (std::to_string(c) != s)
				Assert::AreEqual(std::to_string(c), s);

			A = a = -361;
			B = b = 53;

			c = a / b;
			C = A / B;

			s = C.ToDisplay();
			if (std::to_string(c) != s)
				Assert::AreEqual(std::to_string(c), s);

			A = a = 361;
			B = b = -53;

			c = a / b;
			C = A / B;

			s = C.ToDisplay();
			if (std::to_string(c) != s)
				Assert::AreEqual(std::to_string(c), s);

			A = a = -361;
			B = b = -53;

			c = a / b;
			C = A / B;

			s = C.ToDisplay();
			if (std::to_string(c) != s)
				Assert::AreEqual(std::to_string(c), s);

			///////////////////////////////////////////////////////////////////////////////////////////////

			////// TEST CASE //////
			B = b = 1;
			B << 1;
			b << 1;

			s = B.ToDisplay();
			if (std::to_string(b) != s)
				Assert::AreEqual(std::to_string(b), s);

			B <<= 1;
			b <<= 1;

			s = B.ToDisplay();
			if (std::to_string(b) != s)
				Assert::AreEqual(std::to_string(b), s);

			B = B << 2;
			b = b << 2;

			s = B.ToDisplay();
			if (std::to_string(b) != s)
				Assert::AreEqual(std::to_string(b), s);

			A = 56;
			B = 7;
			C = A / B;

			A = -98765;
			s = A.ToBinary();
			std::cout << s << std::endl;

			/// Notes - Shifting is not safe yet for doubling or halving

			////// TEST CASE //////

			A = a = 7;
			B = b = 65535;

			c = a * b;
			C = A * B;

			if (std::to_string(c) != C.ToDisplay())
				Assert::AreEqual(std::to_string(c), C.ToDisplay());

			A = a = 7;
			B = b = -8;

			c = a * b;
			C = A * B;

			if (std::to_string(c) != C.ToDisplay())
				Assert::AreEqual(std::to_string(c), C.ToDisplay());

			A = a = -7;
			B = b = 8;

			c = a * b;
			C = A * B;

			if (std::to_string(c) != C.ToDisplay())
				Assert::AreEqual(std::to_string(c), C.ToDisplay());

			A = a = -7;
			B = b = -8;

			c = a * b;
			C = A * B;

			if (std::to_string(c) != C.ToDisplay())
				Assert::AreEqual(std::to_string(c), C.ToDisplay());

			A = a = -127;
			B = b = -127;
			A.SetSize(8);

			++a;
			++b;
			++A;
			++B;

			if (std::to_string(a) != A.ToDisplay())
				Assert::AreEqual(std::to_string(a), A.ToDisplay());
			if (std::to_string(b) != B.ToDisplay())
				Assert::AreEqual(std::to_string(b), B.ToDisplay());

			C = A / B;
			C = A % B;

			A = a = 0;
			B = b = 1;

			c = a / b;
			C = A / B;

			if (std::to_string(c) != C.ToDisplay())
				Assert::AreEqual(std::to_string(c), C.ToDisplay());

			c = a % b;
			C = A % B;

			if (std::to_string(c) != C.ToDisplay())
				Assert::AreEqual(std::to_string(c), C.ToDisplay());

			A = a = 127;
			B = b = 126;

			if (std::to_string(c) != C.ToDisplay())
				Assert::AreEqual(std::to_string(c), C.ToDisplay());

			c = a / b;
			C = A / B;

			if (std::to_string(c) != C.ToDisplay())
				Assert::AreEqual(std::to_string(c), C.ToDisplay());

			c = a % b;
			C = A % B;

			if (std::to_string(c) != C.ToDisplay())
				Assert::AreEqual(std::to_string(c), C.ToDisplay());

			A = a = 127;
			B = b = -126;

			c = a / b;
			C = A / B;

			if (std::to_string(c) != C.ToDisplay())
				Assert::AreEqual(std::to_string(c), C.ToDisplay());

			c = a % b;
			C = A % B;

			if (std::to_string(c) != C.ToDisplay())
				Assert::AreEqual(std::to_string(c), C.ToDisplay());

			A = a = -127;
			B = b = 126;

			c = a / b;
			C = A / B;

			if (std::to_string(c) != C.ToDisplay())
				Assert::AreEqual(std::to_string(c), C.ToDisplay());

			c = a % b;
			C = A % B;

			if (std::to_string(c) != C.ToDisplay())
				Assert::AreEqual(std::to_string(c), C.ToDisplay());

			A = a = -127;
			B = b = -126;

			c = a / b;
			C = A / B;

			if (std::to_string(c) != C.ToDisplay())
				Assert::AreEqual(std::to_string(c), C.ToDisplay());

			c = a % b;
			C = A % B;

			if (std::to_string(c) != C.ToDisplay())
				Assert::AreEqual(std::to_string(c), C.ToDisplay());

			A = a = 126;
			B = b = 127;

			c = a / b;
			C = A / B;

			if (std::to_string(c) != C.ToDisplay())
				Assert::AreEqual(std::to_string(c), C.ToDisplay());

			c = a % b;
			C = A % B;

			if (std::to_string(c) != C.ToDisplay())
				Assert::AreEqual(std::to_string(c), C.ToDisplay());

			c = a / b;
			C = A / B;

			if (std::to_string(c) != C.ToDisplay())
				Assert::AreEqual(std::to_string(c), C.ToDisplay());

			c = a % b;
			C = A % B;

			if (std::to_string(c) != C.ToDisplay())
				Assert::AreEqual(std::to_string(c), C.ToDisplay());

			A = a = 126;
			B = b = -127;

			c = a / b;
			C = A / B;

			if (std::to_string(c) != C.ToDisplay())
				Assert::AreEqual(std::to_string(c), C.ToDisplay());

			c = a % b;
			C = A % B;

			if (std::to_string(c) != C.ToDisplay())
				Assert::AreEqual(std::to_string(c), C.ToDisplay());

			A = a = -126;
			B = b = 127;

			c = a / b;
			C = A / B;

			if (std::to_string(c) != C.ToDisplay())
				Assert::AreEqual(std::to_string(c), C.ToDisplay());

			c = a % b;
			C = A % B;

			if (std::to_string(c) != C.ToDisplay())
				Assert::AreEqual(std::to_string(c), C.ToDisplay());

			A = a = -126;
			B = b = -127;
			c = a / b;
			C = A / B;

			if (std::to_string(c) != C.ToDisplay())
				Assert::AreEqual(std::to_string(c), C.ToDisplay());

			c = a % b;
			C = A % B;

			if (std::to_string(c) != C.ToDisplay())
				Assert::AreEqual(std::to_string(c), C.ToDisplay());

			///////////////////////

			////// TEST CASE //////

			A = a = 1;
			B = b = 2;

			C = B + A;
			c = b + a;

			if (std::to_string(c) != C.ToDisplay())
				Assert::AreEqual(std::to_string(c), C.ToDisplay());

			///////////////////////

			////// TEST CASE //////

			A = a = -1;
			B = b = 2;

			C = A + B;
			c = a + b;

			if (std::to_string(c) != C.ToDisplay())
				Assert::AreEqual(std::to_string(c), C.ToDisplay());

			///////////////////////

			////// TEST CASE //////

			A = a = -1;
			B = b = 2;

			C = B + A;
			c = b + a;

			if (std::to_string(c) != C.ToDisplay())
				Assert::AreEqual(std::to_string(c), C.ToDisplay());

			///////////////////////

			////// TEST CASE //////

			A = a = 1;
			B = b = -2;

			C = A + B;
			c = a + b;

			if (std::to_string(c) != C.ToDisplay())
				Assert::AreEqual(std::to_string(c), C.ToDisplay());

			///////////////////////

			////// TEST CASE //////

			A = a = 1;
			B = b = -2;

			C = B + A;
			c = b + a;

			if (std::to_string(c) != C.ToDisplay())
				Assert::AreEqual(std::to_string(c), C.ToDisplay());

			///////////////////////

			////// TEST CASE //////

			A = a = -1;
			B = b = -2;

			C = A + B;
			c = a + b;

			if (std::to_string(c) != C.ToDisplay())
				Assert::AreEqual(std::to_string(c), C.ToDisplay());

			///////////////////////

			////// TEST CASE //////

			A = a = -1;
			B = b = -2;

			C = B + A;
			c = b + a;

			if (std::to_string(c) != C.ToDisplay())
				Assert::AreEqual(std::to_string(c), C.ToDisplay());

			///////////////////////
			////// TEST CASE //////

			A = a = 1;
			B = b = 2;

			C = A - B;
			c = a - b;

			if (std::to_string(c) != C.ToDisplay())
				Assert::AreEqual(std::to_string(c), C.ToDisplay());

			///////////////////////

			////// TEST CASE //////

			A = a = 1;
			B = b = 2;

			C = B - A;
			c = b - a;

			if (std::to_string(c) != C.ToDisplay())
				Assert::AreEqual(std::to_string(c), C.ToDisplay());

			///////////////////////

			////// TEST CASE //////

			A = a = -1;
			B = b = 2;

			C = A - B;
			c = a - b;

			if (std::to_string(c) != C.ToDisplay())
				Assert::AreEqual(std::to_string(c), C.ToDisplay());

			///////////////////////

			////// TEST CASE //////

			A = a = -1;
			B = b = 2;

			C = B - A;
			c = b - a;

			if (std::to_string(c) != C.ToDisplay())
				Assert::AreEqual(std::to_string(c), C.ToDisplay());

			///////////////////////

			////// TEST CASE //////

			A = a = 1;
			B = b = -2;

			C = A - B;
			c = a - b;

			if (std::to_string(c) != C.ToDisplay())
				Assert::AreEqual(std::to_string(c), C.ToDisplay());

			///////////////////////

			////// TEST CASE //////

			A = a = 1;
			B = b = -2;

			C = B - A;
			c = b - a;

			if (std::to_string(c) != C.ToDisplay())
				Assert::AreEqual(std::to_string(c), C.ToDisplay());

			///////////////////////

			////// TEST CASE //////

			A = a = -1;
			B = b = -2;

			C = A - B;
			c = a - b;

			if (std::to_string(c) != C.ToDisplay())
				Assert::AreEqual(std::to_string(c), C.ToDisplay());

			///////////////////////

			////// TEST CASE //////

			A = a = -1;
			B = b = -2;

			C = B - A;
			c = b - a;

			if (std::to_string(c) != C.ToDisplay())
				Assert::AreEqual(std::to_string(c), C.ToDisplay());

			///////////////////////

			////// TEST CASE //////

			A = a = -1;
			B = b = -2;

			// Is A > B?
			C = A - B;

			///////////////////////
		}

		TEST_METHOD(ByteAddition)
		{
			int ni, nj, nk;
			Number NI, NJ, NK;

			for (ni = iBeg; ni < iEnd; ++ni)
			{
				for (nj = jBeg; nj < jEnd; ++nj)
				{
					nk = ni + nj;

					NI = ni;
					NJ = nj;
					NK = NI + NJ;

					std::string strNK = NK.ToDisplay();
					if (std::to_string(nk) != strNK)
						Assert::AreEqual(std::to_string(nk), strNK);
				}
			}
		}

		TEST_METHOD(ByteSubtraction)
		{
			int ni, nj, nk;
			Number NI, NJ, NK;

			for (ni = iBeg; ni < iEnd; ++ni)
			{
				for (nj = jBeg; nj < jEnd; ++nj)
				{
					nk = ni - nj;

					NI = ni;
					NJ = nj;
					NK = NI - NJ;

					std::string strNK = NK.ToDisplay();
					if (std::to_string(nk) != strNK)
						Assert::AreEqual(std::to_string(nk), strNK);
				}
			}
		}

		TEST_METHOD(ByteMultiplication)
		{
			int ni, nj, nk;
			Number NI, NJ, NK;

			for (ni = iBeg; ni < iEnd; ++ni)
			{
				for (nj = jBeg; nj < jEnd; ++nj)
				{
					nk = ni * nj;

					NI = ni;
					NJ = nj;
					NK = NI * NJ;

					std::string strNK = NK.ToDisplay();
					if (std::to_string(nk) != strNK)
						Assert::AreEqual(std::to_string(nk), strNK);
				}
			}
		}

		TEST_METHOD(ByteDivision)
		{
			int ni, nj, nk;
			Number NI, NJ, NK;

			for (ni = iBeg; ni < iEnd; ++ni)
			{
				for (nj = jBeg; nj < jEnd; ++nj)
				{
					if (nj == 0)
						continue;

					nk = ni / nj;

					NI = ni;
					NJ = nj;
					NK = NI / NJ;

					std::string strNK = NK.ToDisplay();
					if (std::to_string(nk) != strNK)
						Assert::AreEqual(std::to_string(nk), strNK);
				}
			}
		}

		TEST_METHOD(ByteModulus)
		{
			int ni, nj, nk;
			Number NI, NJ, NK;

			for (ni = iBeg; ni < iEnd; ++ni)
			{
				for (nj = jBeg; nj < jEnd; ++nj)
				{
					if (nj == 0)
						continue;

					nk = ni % nj;

					NI = ni;
					NJ = nj;
					NK = NI % NJ;

					std::string strNK = NK.ToDisplay();
					if (std::to_string(nk) != strNK)
						Assert::AreEqual(std::to_string(nk), strNK);
				}
			}
		}

		TEST_METHOD(ByteLT)
		{
			int ni, nj;
			Number NI, NJ;
			bool b, B;

			for (ni = iBeg; ni < iEnd; ++ni)
			{
				for (nj = jBeg; nj < jEnd; ++nj)
				{
					b = ni < nj;

					NI = ni;
					NJ = nj;
					B = NI < NJ;

					if (b != B)
						Assert::AreEqual(b, B);
				}
			}
		}

		TEST_METHOD(ByteGT)
		{
			int ni, nj;
			Number NI, NJ;
			bool b, B;

			for (ni = iBeg; ni < iEnd; ++ni)
			{
				for (nj = jBeg; nj < jEnd; ++nj)
				{
					b = ni > nj;

					NI = ni;
					NJ = nj;
					B = NI > NJ;

					if (b != B)
						Assert::AreEqual(b, B);
				}
			}
		}

		TEST_METHOD(ByteLE)
		{
			int ni, nj;
			Number NI, NJ;
			bool b, B;

			for (ni = iBeg; ni < iEnd; ++ni)
			{
				for (nj = jBeg; nj < jEnd; ++nj)
				{
					b = ni <= nj;

					NI = ni;
					NJ = nj;
					B = NI <= NJ;

					if (b != B)
						Assert::AreEqual(b, B);
				}
			}
		}

		TEST_METHOD(ByteGE)
		{
			int ni, nj;
			Number NI, NJ;
			bool b, B;

			for (ni = iBeg; ni < iEnd; ++ni)
			{
				for (nj = jBeg; nj < jEnd; ++nj)
				{
					b = ni >= nj;

					NI = ni;
					NJ = nj;
					B = NI >= NJ;

					if (b != B)
						Assert::AreEqual(b, B);
				}
			}
		}

		TEST_METHOD(ByteEQ)
		{
			int ni, nj;
			Number NI, NJ;
			bool b, B;

			for (ni = iBeg; ni < iEnd; ++ni)
			{
				for (nj = jBeg; nj < jEnd; ++nj)
				{
					b = ni == nj;

					NI = ni;
					NJ = nj;
					B = NI == NJ;

					if (b != B)
						Assert::AreEqual(b, B);
				}
			}
		}

		TEST_METHOD(ByteNE)
		{
			int ni, nj;
			Number NI, NJ;
			bool b, B;

			for (ni = iBeg; ni < iEnd; ++ni)
			{
				for (nj = jBeg; nj < jEnd; ++nj)
				{
					b = ni != nj;

					NI = ni;
					NJ = nj;
					B = NI != NJ;

					if (b != B)
						Assert::AreEqual(b, B);
				}
			}
		}

		TEST_METHOD(BytePre)
		{
			int ni, nj;
			Number NI, NJ;
			std::string si, sj;

			ni = iBeg;
			for (NI = iBeg; NI < iEnd; ++NI)
			{
				nj = jBeg;
				for (NJ = jBeg; NJ < jEnd; ++NJ)
				{
					sj = NJ.ToDisplay();
					if (std::to_string(nj) != sj)
						Assert::AreEqual(std::to_string(nj), sj);

					++nj;
				}

				si = NI.ToDisplay();
				if (std::to_string(ni) != si)
					Assert::AreEqual(std::to_string(ni), si);

				++ni;
			}
		}

		TEST_METHOD(BytePost)
		{
			int ni, nj;
			Number NI, NJ;
			std::string si, sj;

			ni = iBeg;
			for (NI = iBeg; NI < iEnd; NI++)
			{
				nj = jBeg;
				for (NJ = jBeg; NJ < jEnd; NJ++)
				{
					sj = NJ.ToDisplay();
					if (std::to_string(nj) != sj)
						Assert::AreEqual(std::to_string(nj), sj);

					++nj;
				}

				si = NI.ToDisplay();
				if (std::to_string(ni) != si)
					Assert::AreEqual(std::to_string(ni), si);

				++ni;
			}
		}

		TEST_METHOD(ByteBigDiv)
		{
			Number N = "9999999999999999";
			Number D = 180;
			Number Q;

			std::string s = "55555555555555";
			for (unsigned int i = 0; i < 65536; ++i)
				Q = N / D;
			Assert::AreEqual(s, Q.ToDisplay());
		}

		TEST_METHOD(ByteBigMul)
		{
			Number N = "9999999999999999";
			Number D = 180;
			Number Q;

			std::string s = "1799999999999999820";
			for (unsigned int i = 0; i < 65536; ++i)
				Q = N * D;
			Assert::AreEqual(s, Q.ToDisplay());
		}

		TEST_METHOD(ByteBigMul2)
		{
			Number N = "9999999999999999";
			Number D = 180;
			Number Q;

			std::string s = "1799999999999999820";
			for (unsigned int i = 0; i < 65536; ++i)
				Q = D * N;
			Assert::AreEqual(s, Q.ToDisplay());
		}
	};
}

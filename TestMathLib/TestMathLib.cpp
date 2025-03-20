/*
Andrew Scott Bantly's Software License Agreement
Version 1.0

Copyright(C) 2012 Andrew Scott Bantly

1. Permission and Restrictions:
   - This software is proprietary and is provided "as is."
   - No individual or organization may copy, modify, distribute, or use this software or its derivatives without prior written consent from Andrew Scott Bantly.
   - Usage in commercial, educational, or personal projects is strictly prohibited without explicit permission from Andrew Scott Bantly

2. Limited Access :
   - Access to the source code is granted for reference purposes only.
   - Redistribution of the source code or its compiled binaries, whether modified or unmodified, is expressly forbidden.

3. Liability Disclaimer :
   - This software is provided without warranty of any kind, either express or implied, including but not limited to the warranties of merchantability, fitness for a particular purpose, or noninfringement.
   - Under no circumstances shall Andrew Scott Bantly be liable for any damages, including incidental, special, or consequential damages arising out of or in connection with the use of this software.

4. Violation of Terms :
   - Any unauthorized use, modification, or distribution of this software will result in immediate revocation of any implied permissions and may lead to legal action.

5. Jurisdiction :
   - This license shall be governed by the laws of The United States of America.
*/

#include "pch.h"
#include <iostream>
#include "CppUnitTest.h"
#include "..\Number.h"

#pragma warning(disable:4552)

#if defined(__x86_64__) || defined(__ppc64__) || defined(_WIN64)
#define IS_64BIT 1
#else
#define IS_32BIT 1
#endif

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestMathLib
{
	const SNUM iBeg = NTH - 64, iEnd = NTH + 63;
	const SNUM jBeg = -64, jEnd = 63;

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
			Number A,B,C,D,E,F,EX;
			std::string s,e;

			EX = "8589934588";
			e = EX.ToDisplay();

			A = 4294967294;
			B = 2;
			C = A * B;
			s = C.ToDisplay();
			if (e != s)
				Assert::AreEqual(e, s);

			D = "4294967294";
			E = 2;
			F = D * E;
			s = F.ToDisplay();
			if (e != s)
				Assert::AreEqual(e, s);
		}

		TEST_METHOD(ByteMixSize)
		{
			Number A, B, C;
			SNUM a, b, c;
			std::string s;

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

			b = (SNUM)sqrt(b);
			s = std::to_string(b);

			B = 25;
			C = B.Sqrt();

			if (C.ToDisplay() != s)
				Assert::AreEqual(C.ToDisplay(), s);

			B = b = 26;
			b = (SNUM)sqrt(b);
			C = B.Sqrt();

			if (C.ToDisplay() != s)
				Assert::AreEqual(C.ToDisplay(), s);

			Number D = 50;
			Number E = D >> 2; // D can't change
			E = D >>= 2; // D changes
			if (D.ToDisplay() == E.ToDisplay())
				Assert::AreEqual(D.ToDisplay(), E.ToDisplay());
		}

		TEST_METHOD(ByteFactorial)
		{
			Number B = 25, N25p = "15511210043330985984000000";
			B = B.Factorial();
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
			SNUM a;
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

			A = a = 0x4000;
			a <<= 4;
			A <<= 4;
			e = std::to_string(a);
			s = A.ToDisplay();
			if (e != s)
				Assert::AreEqual(e, s);

			e = "2147483648";
			A = 1;
			A <<= 31;
			s = A.ToDisplay();
			if (e != s)
				Assert::AreEqual(e, s);

			// asserts because the size allocated is less than the starting element in the backing
			e = "4294967296";
			A = 1;
			A <<= 32;
			s = A.ToDisplay();
			if (e != s)
				Assert::AreEqual(e, s);
			BNUM bw = (BITWIDTH / 2) - 1;
			for (BNUM ipow = 0; ipow < size_t(bw - 1); ++ipow)
			{
				UNUM pow = _pow[ipow];
				for (size_t nb = 1; nb < size_t(bw - 1); ++nb)
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
			SNUM a, b, c;
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
			B = b = 32767;

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
			SNUM ni, nj, nk;
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
			SNUM ni, nj, nk;
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
			SNUM ni, nj, nk;
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
			SNUM ni, nj, nk;
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
			SNUM ni, nj, nk;
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
			SNUM ni, nj;
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
			SNUM ni, nj;
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
			SNUM ni, nj;
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
			SNUM ni, nj;
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
			SNUM ni, nj;
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
			SNUM ni, nj;
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
			SNUM ni, nj;
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
			SNUM ni, nj;
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
			Number N = "99999999999999999999999999999999";
			Number D = 180;
			Number Q;

			std::string s = "555555555555555555555555555555";
			for (unsigned int i = 0; i < 65536; ++i)
				Q = N / D;
			Assert::AreEqual(s, Q.ToDisplay());
		}

		TEST_METHOD(ByteBigMul)
		{
			Number N = "99999999999999999999999999999999";
			Number D = 180;
			Number Q;

			std::string s = "17999999999999999999999999999999820";
			for (unsigned int i = 0; i < 65536; ++i)
				Q = N * D;
			Assert::AreEqual(s, Q.ToDisplay());
		}

		TEST_METHOD(ByteBigMul2)
		{
			Number N = "99999999999999999999999999999999";
			Number D = 180;
			Number Q;

			std::string s = "17999999999999999999999999999999820";
			for (unsigned int i = 0; i < 65536; ++i)
				Q = D * N;
			Assert::AreEqual(s, Q.ToDisplay());
		}
	};
}

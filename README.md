# MathLib
Made public on 3/25/2024

MathLib provides a new class, CNumber, to do operations on very large or small numbers.

Numbers in the form of strings are used.  Additionally the class can convert the number to descriptive text and back.  Example 1234 -> One Thousand Two Hundred and Thirty Four -> 1234

CNumber also has logical operators for comparison functions

usage:

	CNumber::Init(); // Call this once at startup

	CNumber N1, N2("3"), N3("4");
	N1 = N2 * N3;
	if (N1 > N2)
		std::cout << N1 << " Greater than " << N2 << " * " << N3;

  Output:
  12 Greater than 3 * 4

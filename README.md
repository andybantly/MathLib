# MathLib

C++ class for very large integer arithmetic

Source Code

The include file is Number.h 

In C++ code, use the Number object.

It can be constructed or assigned with a string representation of a signed integer, 

a signed integer, or a byte value and capacity.

It has the following logical operators and usage for Number objects N1 and N2

==					: 	N1 == N2	boolean
!=					:	N1 != N2	boolean
<=					:	N1 <= N2	boolean
>=					:	N1 >= N2	boolean
<					:	N1 < N2		boolean
>					:	N1 > N2		boolean

It has the following assignment operators

=					:	N1 = N2, N1 = 1, N1 = “1”

It has the following arithmetic operators

++ and ++ (int)		:	Pre and Post increment – returns reference to this
-- and – (int)		:	Pre and Post decrement – returns reference to this
+ : addition		:	returns new number
- : subtraction		:	returns new number
* : multiplication	:	returns new number
/ : division		:	returns new number
% : modulus			:	returns new number

It has the following properties

ToDispay()			:	returns std::string representation of base 10 number
ToBinary()			:	returns std::string representation of base 2 number
TwosComplement()	:	returns Number representation of the 2s complement
Shr()				:	Shift Right - returns right shifted by 1 bit Number
Shl()				:	Shift-Left - returns left shifted by 1 bit Number
Ror()				:	Roll-Right – returns right rolled by 1 bit Number
Rol()				:	Roll-Left – Returns left rolled by 1 bit Number


#include <iostream>
#include <bitset>

#define Log(arg1, arg2) std::cout << arg1 << arg2 << std::endl
#define Log2(arg1, arg2) std::cout << arg1 << std::bitset<9>(arg2) << std::endl

int main()
{
	// USING <<, >>, &, |, ^, ~
	// << = shifts the bits to Left
	// >> = shifts the bits to Right
	//  & = (AND) can be used to halve the digit (SUBTRACT)
	//  | =  (OR) can be used to double the digit (COMBINE)
	//  ^ = (XOR) both the bits has to be of different value 
	//  ~ =  (!=) inverter
	unsigned int value = 0b101100101;
	unsigned int a = 0b101;
	unsigned int b = 0b10110;
	unsigned int c = 0b00000111;

	Log("Value: ", value);
	Log("a: ", a);
	Log("b: ", b);
	Log("c: ", c);

	b <<= 4;
	unsigned int d = a | b;

	Log("d: ", d);
	Log2("D: ", d);

	unsigned int e = d & c;

	Log("e: ", e);
	Log2("E: ", e);

	unsigned int f = a ^ a;

	Log("f: ", f);
	Log2("F: ", f);


	std::cin.get();
}


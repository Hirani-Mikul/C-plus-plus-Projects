// Pointers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

//int main()
//{
//	int a = 10;
//	int* p = &a;
//
//	std::cout << "Start A: " << a << std::endl;
//	std::cout << "Start A Address" << p << std::endl;
//
//	// Add 1 to pointer address
//	*p = 20;
//	std::cout << "A: " << a << std::endl;
//	p += 1;
//	std::cout << "After 1+ P address: " << p << std::endl;
//	*p = 100;
//
//	std::cout << "End A: " << a << std::endl;
//	std::cout << "Value at p+1: " << * p << std::endl;
//	system("pause>0");
//	return 0;
//}

//int main() {
//	int a = 10;
//	int* p = &a;
//	int** q = &p;
//	int*** r = &q;
//
//	std::cout << "Value of A: " << a << std::endl;
//
//	*p = 20;
//
//	std::cout << "Value of pA: " << a << std::endl;
//
//	**q = *p + 10;
//	std::cout << "Value of qA: " << a << std::endl;
//	***r = *p + 20;
//	std::cout << "Value of rA: " << a << std::endl;
//
//	system("pause>0");
//	return 0;
//}
int main() {

	int nums[2][3] = {
		{1, 2, 3},
		{4, 5, 6}
	};
	// same 
	std::cout << "nums: " << nums << std::endl;
	std::cout << "nums[0]: " << nums[0] << std::endl;
	std::cout << "&nums[0]: " << &nums[0] << std::endl;
	std::cout << "&nums[0][0]: " << &nums[0][0] << std::endl;
	std::cout << "*nums: " << *nums << std::endl;

	std::cout << std::endl << std::endl;
	
	// same
	std::cout << "nums + 1: " << nums + 1 << std::endl;
	std::cout << "nums[1]:  " << nums[1] << std::endl;

	std::cout << std::endl << std::endl;
	
	// print value
	std::cout << "*(*nums + 1): " << *(*nums + 1) << std::endl;
	std::cout << "*(*nums): " << **nums << std::endl;

	system("pause>0");
	return 0;
}

//int nothing[1][8][7][6][5][4][3][2][1] =
//{
//	{
//		{
//
//},
//	{
//
//},
//	{
//
//},
//	{
//
//}
//	},
//};
// Function Pointer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int compare(int a, int b, int flag) {
	if (flag == 1) {
		if (a > b) return 1;
		else return -1;
	}
	else if (flag == -1) {
		if (a < b) return 1;
		else return -1;
	}
	else {
		return -1;
	}
}

void sort(int *Nums, int aSize, int (*compare)(int, int, int), int flag) {
	int temp;
	for (int i = 0; i < aSize; i++)
		for (int j = 0; j < aSize - 1; j++) {
			if (compare(Nums[j], Nums[j + 1], flag) > 0) {
				temp = Nums[j];
				Nums[j] = Nums[j + 1];
				Nums[j + 1] = temp;
			}
		}

}

int main()
{
	//int length = 10;
	int nums[10] = { 1, 5, 3, 6, 22, -64, 0, 10, -100, 1000 };
	int length = sizeof(nums) / sizeof(int);
	
	//sort by either asce or desc ::: 1 = asce and -1 = desc

	std::cout << "ORIGINAL ORDER: " << std::endl;
	for (int i = 0; i < length; i++)
		std::cout << nums[i] << "\t";

	sort(nums, length, compare, 1); // ASCENDING ORDER
	
	std::cout << std::endl << std::endl << "ASCENDING ORDER: " << std::endl;
	for (int i = 0; i < length; i++)
		std::cout << nums[i] << "\t";

	sort(nums, length, compare, -1); // DESCENDING ORDER

	std::cout << std::endl << std::endl << "DESCENDING ORDER: " << std::endl;
	for (int i = 0; i < length; i++)
		std::cout << nums[i] << "\t";

	system("pause>0");
}


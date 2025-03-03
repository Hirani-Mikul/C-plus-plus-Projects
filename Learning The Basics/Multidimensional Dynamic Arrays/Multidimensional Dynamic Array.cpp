// Multidimensional Dynamic Array.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

int main()
{
	int rows, cols;

	// ASK THE USER TO SPECIFY THE NUMBER OF ROWS AND COLUMNS AND THEN STORE THEM IN THE VARIABLES

	// PUT NUMBERS GREATER THAN 3
	cout << "Specify the number of rows and cols: ";
	cin >> rows >> cols;

	// CREATE AND ALLOCATE POINTER TO POINTER REFERENCE AND NAME IT TABLE.
	// TWO DIMENSIONAL
	int** table = new int*[rows];

	// ALLOCATE NEW POINTER TO EACH MEMORY IN THE TABLE

	for (int i = 0; i < rows; i++) {
		table[i] = new int[cols];
	}

	table[1][2] = 100;

	cout << "Number at " << &(table[1][2]) << " memory is: " << table[1][2] << endl;

	// DELETE AND DEALLOCATE THE MEMORY AFTER USED

	for (int i = 0; i < rows; i++) {
		delete[] table[i];
	}

	delete[] table;
	// DECLARE THE TABLE AS NULL TO REMOVE THE MEMORY REFERENCE
	// TO FREE THE MEMORY SO IT CAN BE USED BY OTHER 
	// OR TO AVOID REFERECING THE WRONG VALUE
	table = NULL;
	
	system("pause>0");
}


#include <iostream>
using namespace std;

int main() {

	int size;
	cout << "Please specify size: ";
	cin >> size;
	cout << endl;

	int* arr = new int[size];

	for (int i = 0; i < size; i++) {
		cout << "Array [" << i << "]: ";
		cin >> arr[i];
	}

	for (int i = 0; i < size; i++) {
		if (i == 0) cout << "Method 1 of Dereferencing: " << endl;
		cout << arr[i] << ", ";
	}
	for (int i = 0; i < size; i++) {
		if (i == 0) cout << endl << "Method 2 of Dereferencing: " << endl;
		cout << *(arr + i) << ", ";
	}
	cout << endl << endl;
	// DEALOCATE THE ARRAY FROM THE MEMORY BY DELETING

	delete[] arr;
	arr = NULL;

	cout << arr << endl;

	system("pause>0");
}
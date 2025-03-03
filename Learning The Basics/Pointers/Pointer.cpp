#include <iostream>

using namespace std;

void print(void* ptr, char type) {
	switch (type)
	{
	case 'i':
		cout << "Your Number Is: " << *((int*)ptr) << endl; 
		break;
	case 'c':
		cout << "Your Letter Is: " << *((char*)ptr) << endl; break;
	case 's':
		cout << "Your Name Is: " << *((string*)ptr) << endl; break;
	case 'd':
		cout << "Your Average Is: " << *((double*)ptr) << endl; break;
	case 'f':
		cout << "Your Balance Is: " << *((float*)ptr) << endl; break;

	default:
		cout << "Please provide value." << endl;
		break;
	}
}

int main() {

	int number = 10;
	char letter = 'D';
	string name = "Mikul Hirani";
	double average = 123.23;
	float balance = 100.98f;

	int otherNumbers[5];

	cout << endl << "********** DIFFERENT WAYS OF ENTERING  **********" << endl;
	cout << "**********  VALUE IN THE ARRAY **********" << endl << endl;

	cout << "Method 1" << endl << endl;
	for (int i = 0; i <= 4; i++) {
		cout << "Enter number: ";
		cin >> otherNumbers[i];
	}
	cout << endl;
	for (int i = 0; i <= 4; i++) {
		if (i == 0) cout << "All numbers: ( ";
		cout << otherNumbers[i] << ", ";
		if (i == 4) cout << " )";
	}
	cout << endl << endl;


	cout << "Method 2" << endl << endl;

	for (int i = 0; i <= 4; i++) {
		if (i == 0) cout << "All numbers: ( ";
		cout << *(otherNumbers + i) << ", ";
		if (i == 4) cout << " )";
	}

	cout << endl << endl;

	int luckyNumbers[5] = {2, 4, 6, 8, 10};

	cout << endl << "********** POINTERS AND ARRAY EXAMPLE **********" << endl << endl;


	cout << luckyNumbers << " === ";
	cout << &(luckyNumbers[0]) << endl;

	//

	cout << (luckyNumbers[2]) << " === ";
	cout << *(luckyNumbers + 2) << endl;

	cout << endl << endl << endl << "********** VOID POINTERS EXAMPLE **********" << endl;

	print(&number, 'i');
	print(&letter, 'c');
	print(&name, 's');
	print(&average, 'd');
	print(&balance, 'f');


	system("pause>0");
}
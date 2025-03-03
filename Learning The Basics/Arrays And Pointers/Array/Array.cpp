#include <iostream>
using namespace std;

int getMax(int arr[], int size) {
	int max = arr[0];

	for (int i = 0; i < size; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}
	return max;
}
int getMin(int arr[], int size) {
	int min = arr[0];

	for (int i = 0; i < size; i++) {
		if (arr[i] < min) {
			min = arr[i];
		}
	}

	return min;
}

void getMinAndMax(int arr[], int size, int* min, int* max) {
	for (int i = 0; i < size; i++) {
		if (arr[i] > *max) *max = arr[i];
		if (arr[i] < *min) *min = arr[i];
	}
}

int getLength(int numbers[]) {
	
	int index = 0;

	while (numbers[index] != NULL) {
		index++;
	}
	return index;

}

int main() {

	int numbers[8] = { 100, -58, 432, 23, 1, 15, 19, 99 };

	// FINDING THE MIN AND MAX NUMBER IN THE ARRAY

	int max = getMax(numbers, 8);
	int min = getMin(numbers, 8);

	int maximumNum = numbers[0];
	int minimumNum = numbers[0];

	cout << "***** RETURNING VALUE *****" << endl << endl;


	cout << "Max Number is: " << max << endl;
	cout << "Min Number is: " << min << endl;

	cout << endl << endl;

	getMinAndMax(numbers, 8, &minimumNum, &maximumNum);

	cout << "***** USING REFERENCE *****" << endl << endl;

	cout << "Maximum Number is: " << maximumNum << endl;
	cout << "Minimum Number is: " << minimumNum << endl;

	// FINDING THE LENGTH OR SIZE OF THE ARRAY

	/*int length = getLength(numbers);
	int size = sizeof(numbers) / sizeof(int);
	int length = *(&numbers + 1) - numbers;
	cout << length << endl;
	cout << "Size:" << size << endl;*/




	system("pause>0");
}
// Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>

using namespace std;

void promptMessage(float arr[]) {

	float height, weight;

	cout << "Your Height in meters: ";
	cin >> height;

	cout << "Your Weight in kg: ";
	cin >> weight;

	arr[0] = height;
	arr[1] = weight;
}

float calculateBMI() {

	float BMI;
	float values[2];

	promptMessage(values);

	// values[0] = height &&
	// values[1] = weight;

	BMI = values[1] / (values[0] * values[0]);

	return BMI;
}

void displayResults(int width, int height) {

	//int width = 50, height = 20;

	//float BMI = calculateBMI();
	int frameWidth = 60;
	int factor = 4;

	string displayText = "You Are UNDERWEIGHT";

	/*
		width = 400;
		framewidth = frameWidth; == 60
		textlength = displayText.length(); == 20;
		middle = framewidth / 2; == 30
	*/

	for (int i = 0; i < width ; i++)
		if (i > width / factor && i < (width / factor) + frameWidth + 1)
			cout << "*";
		else cout << " ";
	
	cout << endl;

	for (int i = 0; i < height / 2; i++) {
		for (int j = 0; j < width; j++) {

			if (j > (width / factor) && j < (width / factor) + 2) cout << "*";
			else if (j == (width / factor) + frameWidth) cout << "*";
			else {
			if (j == (width / factor) + 10 && j <= (width / factor) + 10 + displayText.length() && i == 4) cout << displayText;
			else
				cout << " ";
			}


		}
		cout << endl;
	}

	for (int i = 0; i < width; i++)
		if (i > width / factor && i < (width / factor) + frameWidth + 1)
			cout << "*";
		else cout << " ";
	
	cout << endl;
	
	//if (BMI < 18.5) cout << "BMI: " << BMI << "\n" << "You are UNDERWEIGHT!";
	//else if (BMI < 24.9) cout << "BMI: " << BMI << "\n" << "Normal Weight";
	//else cout << "BMI: " << BMI << "\n" << "You are OVERWEIGHT";
}

int main()
{
	//displayResults();

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	//cout << "Columns: " << columns << endl;
	//cout << "Rows: " << rows << endl;

	displayResults(columns, rows);

	

	system("pause>0");
	//return 0;
}


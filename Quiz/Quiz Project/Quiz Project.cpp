// Quiz Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// SCORE FUNCTIONALITY NOT WORKING

#include <Windows.h>
#include "load.h"


int score = 0;

void displayResults() {
	// 0 = UNGRADED, 10 = AVERAGE, 20 = GOOD, 30 = EXCELLENT, 40 = EXCEPTIONAL
	string marks = score >= 40 ? "Exceptional" : score >= 30 ? "Excellent" : score >= 20 ? "Good" : score >= 10 ? "Average" : "Ungraded";

	cout << "************************************" << endl;
	cout << "              QUIZ OVER             " << endl << endl;
	cout << "           CONGRATULATIONS           " << endl << endl;
	cout << "             Your Score:            " << endl << endl;
	cout << "                  " << score << "          " << endl << endl;
	cout << "               " << marks << "              " << endl;
	cout << "************************************" << endl;

}

void Quiz(Question Questions[], int length) {
	int currentQuestion = 0;


	do
	{
		cout << "                                               " << "Score: " << score << endl;
		diplayQuestions(Questions, currentQuestion, score);
		//if (currentQuestion % 2 == 1) {
		
		Sleep(1000);
		system("cls");

		//}

		currentQuestion++;
	} while (currentQuestion != length);

	displayResults();

}

int main()
{
	//int length = sizeof(Questions) / sizeof(int);
	int length = 6;
	Question* Questions = new Question[length];
	Option* Options = new Option[length];

	int Answers[6] = {2, 3, 3, 1, 2, 1};

	loadQuestions(Questions);
	loadOptions(Options);
	resolveOptions(Options, length);
	

	updateQuestions(Questions, length, Options, Answers);

	Quiz(Questions, length);
	//printQuestions(Questionz, length);

	

	system("pause>0");
}



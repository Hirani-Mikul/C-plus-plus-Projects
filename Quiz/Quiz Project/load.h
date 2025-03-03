#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

struct Option {
	string Choices[3];
};

struct Question {
	string question;
	int answer;
	Option options;
};

void loadQuestions(Question Question[]);
void loadOptions(Option Choice[]);
void resolveOptions(Option opts[], int length);
void updateQuestions(Question ques[], int length, Option opts[], int ans[]);
void validateAnswer(Question que, int chosen, int score);
void printQuestions(Question que[], int length);
void printResolvedOptions(Option opts[], int length);
void diplayQuestions(Question ques[], int currentQue, int score);




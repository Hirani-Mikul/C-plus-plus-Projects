#include "load.h"

void resolveOptions(Option opts[], int length) {
	for (int i = 0; i < length; i++) {
		Option current = opts[i];
		for (int j = 0; j < 3; j++) {
			string text = current.Choices[j];
			replace(text.begin(), text.end(), '_', ' ');
			opts[i].Choices[j] = text;
		}
	}
}

void updateQuestions(Question ques[], int length, Option opts[], int ans[]) {
	for (int i = 0; i < length; i++) {
		ques[i].options = opts[i];
		ques[i].answer = ans[i];
	}
}

void validateAnswer(Question que, int chosen, int score) {
	string output = chosen == que.answer ? "Correct" : "Incorrect";
	if (output == "Correct") {
		score += 10;
	}

	cout << "********************" << endl;
	cout << "    " << output << "    " << endl;
	cout << "********************" << endl;
}

void diplayQuestions(Question ques[], int currentQue, int score) {
	int chosen;
	int optsSize = 3;

	cout << "1." << ques[currentQue].question << endl << endl;
	cout << "Choose one." << endl << endl;

	for (int i = 0; i < 3; i++) {
		cout << i + 1 << ". " << ques[currentQue].options.Choices[i] << endl;
	}
	cout << endl;
	do
	{
		cout << "Your choice: ";
		cin >> chosen;
		if (chosen <= 0 || chosen > 3) {
			cout << "Please choose a valid option.." << endl;
		}
	} while (chosen <= 0 || chosen > 3);

	validateAnswer(ques[currentQue], chosen, score);

}
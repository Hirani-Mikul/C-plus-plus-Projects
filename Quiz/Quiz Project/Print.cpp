#include "load.h"

void printQuestions(Question que[], int length) {
	for (int i = 0; i < length; i++) {
		cout << i + 1 << ". " << que[i].question << endl;
	}
}

void printResolvedOptions(Option opts[], int length) {
	int count = 0;
	for (int i = 0; i < length; i++) {
		Option current = opts[i];
		for (int j = 0; j < 3; j++) {
			count++;
			cout << count << ". " << current.Choices[j] << endl;
		}
	}
}
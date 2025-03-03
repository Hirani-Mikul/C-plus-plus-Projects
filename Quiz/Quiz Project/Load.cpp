#include "load.h"


void loadQuestions(Question Questions[]) {
	ifstream QuestionFile("Questions.txt");

	string text;
	int index = 0;

	while (getline(QuestionFile, text)) {
		Questions[index].question = text;
		index++;
	}
}
void loadOptions(Option Choice[]) {
	ifstream OptionsFile("Options.txt");
	string text;

	int oIndex = 0;
	int cIndex = 0;

	while (OptionsFile >> text)
	{
		Choice[oIndex].Choices[cIndex] = text;

		cIndex++;
		if (cIndex % 3 == 0) {
			oIndex++;
			cIndex = 0;
		}
	}

}
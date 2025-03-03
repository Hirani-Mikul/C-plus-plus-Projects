#include <iostream>
#include <iomanip>
using namespace std;

bool isLooping = true;
int x = 0, y = 0;



int width = 30;
int height = 30;
int r = 5;

void Start() {
	bool isLooping = true;
}

void update () {
	system("cls");


	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {

			if (j == x && i == y) {
				for (int k = 0; k < r; k++) {
					for (int l = 0; l < r; l++) {
						cout << '*';
					}
					cout << endl;
				}
				//cout << '*';
			}
			else cout << " ";

		}
	}
	if (x >= width) x = 0;
	x++;

	

	
	
	//angle++;
}

void frame() {

	for (int i = 0; i < width; i++) cout << "*";

	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0) cout << "*";

			else cout << " ";

			if (j == width - 2) cout << "*";
		}
		cout << endl;
	}

	for (int i = 0; i < width; i++) cout << "*";
}

int main()
{
	Start();

	while (isLooping) {
		//frame();
		update();
	}

	system("pause>0");
	return 0;
}

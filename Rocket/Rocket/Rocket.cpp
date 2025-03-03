// Rocket.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include "Ship.h"

const int width = 30;
const int height = 20;

void createSetup(Ship s) {
    //Sleep(33);
    system("cls");

    for (int i = 1; i <= width; i++) cout << "#";
    cout << endl;

    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= width; j++) {
            if (j == 1) cout << "#";
            else {
                if (j == s.pos.x && i == s.pos.y) {
                    s.display();
                }
                else cout << " ";
            }
            if (j == width) cout << "#";
        }
        cout << endl;
    }

    for (int i = 1; i <= width; i++) cout << "#";

    cout << endl << endl;

    cout << "x: " << s.vel.x << endl;
    cout << "y: " << s.vel.y << endl;
}

int main()
{
    int x = 5; int y = 5;
    Ship s(x, y, width, height);

    while (true) {
        createSetup(s);
        s.checkEdges();
        s.update();
    }

    system("pause>0");
}

// Everything.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

int width = 40;
int height = 20;
bool gameOver;
int score;

int foodX = rand() % width;
int foodY = rand() % height;

class Particle {
private:
    int posX;
    int posY;
    int dx;
    int dy;
    int tailX[100];
    int tailY[100];
    int nTail;

public:
    Particle(int x, int y) {
        posX = x;
        posY = y;
        dx = 1;
        dy = 0;
        nTail = 0;
    }

    void addTail() {
        int length = sizeof(tailX) / sizeof(int);

        int index = 1;
        for (int i = 0; i < length; i++) {
            tailX[i] = posX - index;
            tailY[i] = posY;
            index++;
        }
    }

    void move() {
        int prevX = tailX[0];
        int prevY = tailY[0];
        int prev2X, prev2Y;
        tailX[0] = posX;
        tailY[0] = posY;
        posX += dx; // 2, 3, 4, 5, 6
        posY += dy; // 2, 3, 4, 5, 6
                    // 1, 2, 3, 4, 5
                    // 1, 2, 3, 4, 5
        for (int i = 1; i < nTail; i++) {
            prev2X = tailX[i];
            prev2Y = tailY[i];
            tailX[i] = prevX;
            tailY[i] = prevY;

            prevX = prev2X;
            prevY = prev2Y;
        }
        //posY += dy;
    }

    void update() {
        if (_kbhit()) {
            switch (_getch())
            {
            case 'a': 
                if (dx == 1) {
                    dx = 1;
                    break;
                }
                dx = -1;
                dy = 0;
                break;
            case 'd':
                if (dx == -1) {
                    dx = -1;
                    break;
                }
                dx = 1;
                dy = 0;
                break;
            case 'w':
                if (dy == 1) {
                    dy = 1;
                    break;
                }
                dy = -1;
                dx = 0;
                break;
            case 's':
                if (dy == -1) {
                    dy = -1;
                    break;
                }
                dy = 1;
                dx = 0;
                break;
            case 'x': 
                gameOver = true;
                break;
            default:
                break;
            }
        }
    }

    void eatFood() {

        for (int i = 0; i < nTail; i++) {
            if (tailX[i] == posX && tailY[i] == posY)
                gameOver = true;
        }

        if (posX == foodX && posY == foodY) {
            foodX = rand() % width;
            foodY = rand() % height;
            score += 10;
            nTail++;
        }
    }

    void checkEdges() {
        if (posX > width - 2) posX = 0;
        else if (posX < 0) posX = width - 2;
        if (posY > height) posY = 0;
        else if (posY < 0) posY = height;
    }

    void display() {
        for (int i = 0; i <= width; i++) cout << "*";
        cout << endl;

        for (int i = 0; i <= height; i++) {
            for (int j = 0; j <= width; j++) {
                if (j == 0) cout << "*";
                if (j == posX && i == posY) cout << "O";
                else if (j == foodX && i == foodY) cout << "F";
                else
                {
                        bool print = false;
                    for (int k = 0; k < nTail; k++) {
                        if (j == tailX[k] && i == tailY[k])
                        {
                            cout << "o";
                            print = true;
                        }
                    }
                    if (!print) 
                    cout << " ";
                }
               
                if (j == width - 2) cout << "*";
            }
            cout << endl;
        }

        for (int i = 0; i <= width; i++) cout << "*";

        cout << endl << endl;
        cout << "Tail = " << nTail << endl;
        cout << "Score: " << score;
    }
};

int main()
{
    gameOver = false;
    score = 0;
    Particle p1(2, 4);
    //p1.addTail();

    while (!gameOver) {
        system("cls");
        p1.move();
        p1.update();
        p1.eatFood();
        p1.checkEdges();
        p1.display();

    }

    system("cls");

    cout << "********** GAME OVER **********" << endl;
    cout << endl << endl;
    cout << "         Your Score is:         " << endl << endl << endl;
    cout << "                " << score << "        " << endl;
    cout << endl << endl;
    cout << "   PRESS ENTER ENTER TO EXIT   " << endl;

    Sleep(100);
    system("pause>0");
}

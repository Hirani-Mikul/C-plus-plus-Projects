#pragma once

#include <iostream>
using namespace std;
#include "MyVector.h"

class Ship
{
public:
	MyVector pos;
	MyVector vel;
	MyVector acc;
	int cWidth;
	int cHeight;

	enum Direction {STOP = 0, LEFT, RIGHT, UP, DOWN};

	Direction currentDir = RIGHT;
	string prevDir;

	Ship(int, int, int, int);
	void update();
	void move();
	void display();
	void checkEdges();
	void applyForce(int, int);
};


//MyVector* pos;
//MyVector* vel;
//MyVector* acc;
#pragma once
#include "MyVector.h"
#include <iostream>

class Particle
{
public:
	MyVector pos;
	MyVector vel;
	MyVector acc;
	int timeTolive = 100;

	Particle();
	Particle(int, int);

	void run();
	void update();
	void kill();
	void display();
	bool isDead();
};

class Particle1 : public Particle {

public:
	Particle1();
	Particle1(int, int);

	void display();

};

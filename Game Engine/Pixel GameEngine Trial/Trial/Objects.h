#pragma once
#include "olcPixelGameEngine.h"

class Ball
{
public:
	olc::vd2d pos;
	olc::vd2d vel;
	float r;
	bool isSelected;
	Ball();
	Ball(float, float, float);
	void display(olc::PixelGameEngine*);
	void update(olc::vd2d, float, float, float);
	void checkEdges();
	void dragMe(float, float);
	void Zoom(float);
};

class Paddle {
public:
	olc::vd2d pos;
	float pWidth;
	float pHeight;
	int sWidth; // Screen Width
	int sHeight; // Screen Height
	Paddle();
	Paddle(float, float, int, int);
	void display(olc::PixelGameEngine*);
	void update(double, float);
};
class Brick {};


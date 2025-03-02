#pragma once
#include "olcPixelGameEngine.h"

class Vehicle
{
	olc::vf2d position;
	olc::vf2d velocity;
	olc::vf2d acceleration;
	olc::vf2d vehiclePath;

	float radius;
	float size;
	float maxSpeed;
	float maxForce;
	float d;
public:
	Vehicle();
	Vehicle(float x, float y, float width, float height);
	void update();
	void applyForce(olc::vf2d force);
	void checkEdges(olc::PixelGameEngine& pge);
	void display(olc::PixelGameEngine& pge, olc::vf2d& futureLocation);
};


#pragma once
#include "olcPixelGameEngine.h"

class Agent
{
public:
	Agent();
	Agent(std::vector<olc::vf2d> &vecModel, olc::vf2d position, float dir);

private:

	std::vector<olc::vf2d> vecModel;
	std::vector<olc::vf2d> vecPathModel;
	std::vector<olc::vf2d> vecLineModel;

	olc::vf2d position;
	olc::vf2d velocity;
	olc::vf2d acceleration;
	
	float maxForce;
	float maxSpeed;
	float angle;
	float fSize;

public:
	void update(float fElapsedTime);
	void display(olc::PixelGameEngine &pge);
	void applyForce(olc::vf2d f);
	void checkEdges(olc::vf2d &path, olc::PixelGameEngine &pge);
};


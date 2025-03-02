#pragma once
#include "olcPixelGameEngine.h"

class cShapes
{
public:
	cShapes();
	cShapes(olc::vf2d pos, float radius, float mass);

public:
	std::vector<olc::vf2d> vecModel;

	olc::vf2d position;
	olc::vf2d velocity;
	olc::vf2d acceleration;
	
	float fAngle;
	float radius;
	float mass;
	float maxForce;
	float fFriction;

public:

	void display(olc::PixelGameEngine* pge);
	void update(float fElapsedTime);
	void checkEdges(std::pair<olc::vf2d, olc::vf2d> &vGround, olc::vf2d &vGravity);
	void applyForce(olc::vf2d f);
	void createModel();
};


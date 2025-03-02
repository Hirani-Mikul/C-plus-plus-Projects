#pragma once
#include "olcPixelGameEngine.h"

class Platform
{
public:
	Platform();
	Platform(olc::vf2d pos, float width, float height);

public:
	void display(olc::PixelGameEngine &pge);
	void createModel();

public:
	std::vector<olc::vf2d> vecModel;
	std::vector<olc::vf2d> vecCenterLineModel;
	olc::vf2d position;
	float fP_width;
	float fP_height;
	float fAngle;
};

class Ball {
public:
	Ball();
	Ball(olc::vf2d pos, float r, int id);

public:
	void display(olc::PixelGameEngine &pge);
	void createModel();
	void update(float fElapsedTime);
	void checkWalls(std::vector<Platform> &walls);
	void checkPlatforms(std::vector<Platform> &platforms);
	void applyForce(olc::vf2d f);
	void bounce(Ball &other);
	bool intersects(Ball &other);

public:
	olc::vf2d position;
	olc::vf2d velocity;
	olc::vf2d acceleration;
	olc::vf2d gravity;

	std::vector<olc::vf2d> vecModel;
	std::vector<olc::vf2d> vecCenterLineModel;

	float radius;
	float fAngle;
	float maxSpeed;
	float friction = 0.995f;
	float maxForce;
	olc::Pixel col;
	int bId;
};


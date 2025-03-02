#pragma once
#include "olcPixelGameEngine.h"

class Player
{
private:
	olc::vf2d position;
	olc::vf2d velocity;
	olc::vf2d acceleration;
	std::vector<olc::vf2d> vecModel;
	std::vector<olc::vf2d> vecLineModel;
	float friction;
	float angle;
	float radius;
	float fSpeed;
	float jumpForce;
	bool isGrounded = false;

public:

	Player();
	Player( std::vector<olc::vf2d> &model, float x, float y, float r, float s);

public:
	void display(olc::PixelGameEngine& pge);
	void update(float fElapsedTime);
	void applyForce(olc::vf2d force);
	void move(olc::PixelGameEngine &pge);
	void checkEdges(const std::vector<std::pair<olc::vf2d, olc::vf2d>> &surfaces);
};


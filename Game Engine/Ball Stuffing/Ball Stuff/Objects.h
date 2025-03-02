#pragma once
#include "Controller.h"

float extern fWidth, fHeight;


class Entity {

public:
	Entity(olc::vf2d pos, float width, float height, olc::Pixel col);

	void SetPos(olc::vf2d pos_in);
	olc::vf2d GetPos() const;
	

	std::pair<float, float> GetSize() const;
	void display(CoordinateTransformer *ct);
	virtual void createModel();

protected:
	std::vector<olc::vf2d> vecModel;
	olc::vf2d position;
	float eWidth;
	float eHeight;
	olc::Pixel col;

public:
	float radius;
};

class Plank : public Entity
{
public:

	Plank( olc::vf2d pos, float width, float height, olc::Pixel col);

	void MovePlank(float fElapsedTime, float dir);

	void createModel();

	olc::vf2d GetPlankSurface();

	std::pair<olc::vf2d, olc::vf2d> GetPoints() const;

	olc::vf2d dist;
	olc::vf2d offset;
};

class Ball : public Entity{
public:
	Ball(olc::vf2d pos, float wRadius, float hRadius, olc::Pixel col);
	void createModel();
	void update(float fElapsedTime);

	olc::vf2d GetVel() const;
	void SetVel( olc::vf2d vel_in );

	float randVx[4] = { -120.0f, 100.0f, -100.0f, 120.0f };

	olc::vf2d velocity;
};


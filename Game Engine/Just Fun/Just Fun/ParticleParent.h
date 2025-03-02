#pragma once
#include "olcPixelGameEngine.h"

class ParticleParent
{
protected:
	olc::vd2d pos;
	olc::vd2d vel;
	olc::vd2d acc;

	float speed;
	float size;


public:
	float timeTolive;
	ParticleParent();

	ParticleParent(olc::vd2d, float);

	void run(float, olc::PixelGameEngine*);
	virtual void display(olc::PixelGameEngine*);
	//virtual void display(olc::PixelGameEngine*) = 0;
	void update(float);
	bool isDead();
};

// First Particle
class Particle1 : public ParticleParent {
public:
	Particle1();
	Particle1(olc::vd2d, float);
public:
	void display(olc::PixelGameEngine*);
};

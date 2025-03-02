//#pragma once
#include "ParticleParent.h"
#include <vector>

class ParticleSystem
{
private:
	olc::vd2d origin;
	std::vector<ParticleParent*> Particles;

public:
	ParticleSystem();
	ParticleSystem(olc::vd2d);
	void addParticles();
	void update(float, olc::PixelGameEngine*);
};


#pragma once
#include <vector>
#include "Particle.h"
#include "MyVector.h"
class ParticleSystem
{
public:
	MyVector Origin;
	int size;
	std::vector<Particle1> particles;

	ParticleSystem(int, int);
	void initializeParticles();
	void addParticles();
	void update();
};


// Particle System.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ParticleSystem.h"
#include "Particle.h"
int main()
{
    ParticleSystem ps = ParticleSystem(10, 5);
	while (true)
	{
		system("cls");
		ps.addParticles();
		ps.update();
		std::cout << std::endl;
		std::cout << ps.particles.size() << std::endl;
		std::cout << ps.particles[0].timeTolive << std::endl;
	}
    system("pause>0");
}

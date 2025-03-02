#include "ParticleSystem.h"

ParticleSystem::ParticleSystem() {}

ParticleSystem::ParticleSystem(olc::vd2d origin) {
	this->origin = origin;
}
void ParticleSystem::addParticles() {
	int randNum = int(rand() % 2);

	if (randNum < 1) {
		Particles.push_back(new Particle1(origin, 10.0f));
	}
	else {
		Particles.push_back(new ParticleParent(origin, 10.0f));
	}
}
void ParticleSystem::update(float fElapsedTime, olc::PixelGameEngine* pge) {

	std::cout << "No: " << Particles.size() << std::endl;

	for (auto& p : Particles)
		p->run(fElapsedTime, pge);

	Particles.erase(
		std::remove_if(
			Particles.begin(), Particles.end(), [](const ParticleParent* p) {return p->timeTolive < 1.1; }
		), Particles.end()
	);

	for (auto& p : Particles) {
		if (p->isDead()) {
			delete p;
		}
	}

	//Particles.clear();

}

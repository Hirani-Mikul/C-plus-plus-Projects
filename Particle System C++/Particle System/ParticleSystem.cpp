#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(int x, int y) {
	this->Origin = MyVector(x, y);
	this->size = 100;
	//this->initializeParticles();
}
void ParticleSystem::initializeParticles() {}
//void ParticleSystem::initializeParticles() {
//	for (int i = 0; i < size; i++) {
//		this->particles[i] = Particle1(this->Origin.x, this->Origin.y);
//	}
//}
void ParticleSystem::addParticles() {
	int randNum = rand() % 5;

	if (randNum == 1) {

	this->particles.push_back(Particle1(this->Origin.x, this->Origin.y));
	}
}
void ParticleSystem::update() {
	for (Particle p : this->particles) {
		p.run();
	}
	for (int i = 0; i < this->particles.size(); i++) {
		if (this->particles[i].isDead()) {
			std::cout << std::endl << i << ": is DEAD!" << std::endl;
			//this->particles.erase(this->particles.begin() + i);
		}
	}

}

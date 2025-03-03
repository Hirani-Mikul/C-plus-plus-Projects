#include "Particle.h"
#include <cstdlib>

Particle::Particle() {}
Particle::Particle(int x, int y) {
	this->pos = MyVector(x, y);
	int randX = -1 + (rand() % 2);
	int randY = -1 + (rand() % 1);
	this->vel = MyVector(randX, randY);
	this->acc = MyVector(0, 1);
	//this->timeTolive = 100;
}
void Particle::run() {
	this->update();
	this->display();
}
void Particle::update() {
	this->vel.add(this->acc);
	this->pos.add(this->vel);
	this->timeTolive -= 10;
}
void Particle::kill() {
	this->timeTolive--;
}
void Particle::display() {
	std::cout << "O";
}
bool Particle::isDead() {
	return this->timeTolive < 0;
}
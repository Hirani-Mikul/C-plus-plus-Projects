#include "ParticleParent.h"

float generateRand(int min, int max) {
	return float(rand() % (max - min + 1) + min);
}

ParticleParent::ParticleParent() {}

ParticleParent::ParticleParent(olc::vd2d position, float size = 5.0f) {

	pos.x = position.x;
	pos.y = position.y;
	//pos = position;
	vel = { generateRand(-1, 1), generateRand(-1, 0) };
	acc = { 0, 10.0f };
	this->size = size;
	speed = 100.0f;
	timeTolive = 2.0f;
}
void ParticleParent::run(float fElapsedTime, olc::PixelGameEngine* pge) {
	update(fElapsedTime);
	display(pge);
}
void ParticleParent::update(float fElapsedTime) {
	//int randNum = rand() % (max - min + 1) + min;
	vel += acc * fElapsedTime;
	pos += vel * fElapsedTime * speed;
	timeTolive -= fElapsedTime;
}
void ParticleParent::display(olc::PixelGameEngine* pge) {
	//pge->FillCircle(olc::vi2d{100.0f, 100.0f}, 5.0f, olc::GREEN);
	pge->FillCircle(pos, 5.0f, olc::GREEN);
}
bool ParticleParent::isDead() {
	return timeTolive < 0;
}

Particle1::Particle1() {}
Particle1::Particle1(olc::vd2d position, float size) 
	: ParticleParent(position, size) 
{
		
}
void Particle1::display(olc::PixelGameEngine* pge) {
	pge->FillRect(int(pos.x), int(pos.y), size, size, olc::RED);
}



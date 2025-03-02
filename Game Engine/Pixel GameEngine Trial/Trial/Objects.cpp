#include "Objects.h"

// DEFINING PADDLE CLASS METHODS
Paddle::Paddle() {}
Paddle::Paddle(float x, float y, int w, int h) {
	//this->pos = olc::vd2d();
	this->pos = {x, y};
	this->pWidth = 80.0f;
	this->pHeight = 10.0f;
	this->sWidth = w;
	this->sHeight = h;
}
void Paddle::display(olc::PixelGameEngine* pge) {
	pge->FillRect(int(this->pos.x), int(this->pos.y), int(this->pWidth), int(this->pHeight), olc::GREEN);
	//pge->FillCircle(this->pos, 2, olc::RED);
}
void Paddle::update(double dir, float fElapsedTime) {
	// speed = distance / time
	// speed = ScreenWidth() / 2second 
	//this->pos.x += float(this->sWidth / 2) * dir * fElapsedTime;
	this->pos.x += float(this->sWidth) * dir * fElapsedTime;

	if (this->pos.x < 11.0f) this->pos.x = 11.0f;
	if (this->pos.x + this->pWidth > float(this->sWidth) - 10.0f) this->pos.x = float(this->sWidth) - 10.0f - this->pWidth;
}
// DEFINING BALL CLASS METHODS

Ball::Ball() {}

Ball::Ball(float x, float y, float r) {
	this->pos = { x, y };
	this->r = r;
	this->vel = { 200.0f, -100.0f };
	this->isSelected = false;
}
void Ball::display(olc::PixelGameEngine* pge) {
	pge->FillCircle(this->pos, int(this->r), olc::CYAN);
	//pge->FillCircle(this->pos, 2, olc::RED);
};
void Ball::update(olc::vd2d p, float pW, float pH, float fElapsedTime) {
	olc::vf2d vPotentialBallPos = this->pos + this->vel * 2.0f * fElapsedTime;

	this->pos += this->vel * fElapsedTime * 2.0f;

	// check if the ball hits the paddle

	if (this->pos.x > p.x && this->pos.x < p.x + pW && this->pos.y + this->r > p.y)
		this->vel.y *= -1.0f;
	
}
void Ball::checkEdges() {
	if (this->pos.x + this->r >= 590.0f || this->pos.x - this->r <= 10.0f) {
		this->vel.x *= -1.0f;
	}
	if (this->pos.y - this->r <= 10.0f) {
		this->vel.y *= -1.0f;
	}
	if (this->pos.y > 600) {
		this->pos = { 200.0f, 200.0f };
		//float fAngle = (float(rand()) / float(RAND_MAX)) * 2.0f * 3.14159f;
		//this->vel = {300.0f * cos(fAngle), 300.0f * sin(fAngle)};
	}
		
}


void Ball::dragMe(float mX, float mY) {
	float posX = this->pos.x - mX;
	float posY = this->pos.y - mY;
	float dist = (posX * posX) + (posY * posY);

	if (dist <= this->r * this->r) {
		//this->pos = { mX, mY };
		this->isSelected = true;
	}
	else this->isSelected = false;

	if (this->isSelected) this->pos = { mX, mY };
}
void Ball::Zoom(float s) {
	// s is scale value
	this->r += s;

	if (this->r < 8.0f) this->r = 8.0f;
}
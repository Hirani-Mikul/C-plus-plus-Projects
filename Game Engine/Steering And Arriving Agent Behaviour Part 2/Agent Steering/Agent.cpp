#include "Agent.h"

void extern limit(olc::vf2d &v, float max);

void extern DrawWireFrameModel(olc::PixelGameEngine &pge, std::vector<olc::vf2d> &vecModel, olc::vf2d pos, float angle = 0.04f, float scale = 1.0f, olc::Pixel col = olc::WHITE);

Agent::Agent() : position({ 0.0f, 0.0f }), velocity({ 30.0f, -20.0f }), acceleration({ 0.0f, 0.0f }), maxForce(0.15f), maxSpeed(2.0f), fSize(4.0f) {}

Agent::Agent(std::vector<olc::vf2d> &vecModel, olc::vf2d position, float dir) : position({ 0.0f, 0.0f }), velocity({ 3.0f, -2.0f }), acceleration({ 0.0f, 0.0f }), maxForce(0.15f), maxSpeed(2.0f), fSize(4.0f) {
	this->position = position;
	this->velocity = { 3.0f * dir, -2.0f * dir};
	this->angle = 0.04f;
	this->vecModel = vecModel;
	this->maxForce = 0.15f;
	this->maxSpeed = 2.0f;

	this->vecLineModel = { { 0.0f, -5.0f },
			{ 0.0f, +0.5f } };

	
}

void Agent::update(float fElapsedTime) {

	angle = atan2f(velocity.y, velocity.x) + 1.5708f; // + 90 degrees

	velocity += acceleration;
	limit(velocity, maxSpeed);
	position += velocity;
	acceleration *= 0;
}
void Agent::applyForce(olc::vf2d f)
{
	//std::cout << f.x << ", " << f.y << std::endl;
	acceleration += f;
}
void Agent::checkEdges(olc::vf2d &path, olc::PixelGameEngine &pge)
{
	olc::vf2d desired = { 0.0f, 0.0f };
	olc::vf2d predict = velocity;
	predict *= 50.0f;
	bool bSteer = false;

	olc::vf2d futureLocation = position + predict;
	float distance = (futureLocation - path).mag();


	if (distance > 200.0f)
	{
		olc::vf2d toCenter = path - position;
		toCenter = toCenter.norm();
		toCenter *= velocity.mag();
		desired = (velocity + toCenter);
     	desired = desired.norm();
		desired *= maxSpeed;
		bSteer = true;


	}
	if (bSteer)
	{
		olc::vf2d steer = desired - velocity;

		limit(steer, maxForce);
		//std::cout << steer.x << ", " << steer.y << std::endl;
		applyForce(steer);
		bSteer = false;
	}
	pge.FillCircle(futureLocation, 2.0f, olc::GREEN);
}


void Agent::display(olc::PixelGameEngine &pge) {
	DrawWireFrameModel(pge, vecModel, position, angle, fSize, olc::RED);
	DrawWireFrameModel(pge, vecLineModel, position, angle, fSize, olc::WHITE);
	//pge.Draw(position, olc::YELLOW);
	//olc::vf2d newPos = velocity;
	/*olc::vf2d mousePos = { (float)pge.GetMouseX(), (float)pge.GetMouseY() };
	olc::vf2d dir = mousePos - position;
	dir = dir.norm();
	dir *= 40.0f;*/
	
	//newPos = newPos.norm();
	//newPos *= 30.0f;
	//pge.DrawLine(position, position + dir, olc::GREEN);

}

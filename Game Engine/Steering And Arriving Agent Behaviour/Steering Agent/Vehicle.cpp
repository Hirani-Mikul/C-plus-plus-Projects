#include "Vehicle.h"

void limit(olc::vf2d& vel, float max) {
	const float mSq = vel.mag2();
	if (mSq > max * max) {
		vel /= sqrt(mSq);
		vel *= max;
	}
}
std::vector<std::pair<float, float>> vecShipModel;

void DrawWireFrameModel(olc::PixelGameEngine& pge, std::vector<std::pair<float, float>> &vecModelCoordinate, float x, float y, float r = 0.0f, float s = 1.0f, olc::Pixel col = olc::WHITE) {

	std::vector<std::pair<float, float>> vecTransformedCoordinates;
	int verts = vecModelCoordinate.size();
	vecTransformedCoordinates.resize(verts);

	// Rotate
	for (int i = 0; i < verts; i++)
	{
		vecTransformedCoordinates[i].first = vecModelCoordinate[i].second * cosf(r) - vecModelCoordinate[i].first * sinf(r);
		vecTransformedCoordinates[i].second = vecModelCoordinate[i].first * sinf(r) + vecModelCoordinate[i].second * cosf(r);
	}

	// Scale
	for (int i = 0; i < verts; i++)
	{
		vecTransformedCoordinates[i].first *= s;
		vecTransformedCoordinates[i].second *= s;
	}
	// Translate
	for (int i = 0; i < verts; i++)
	{
		vecTransformedCoordinates[i].first = vecTransformedCoordinates[i].first + x;
		vecTransformedCoordinates[i].second = vecTransformedCoordinates[i].second + y;
	}
	// Draw
	for (int i = 0; i < verts + 1; i++)
	{
		int j = (i + 1);
		pge.DrawLine(vecTransformedCoordinates[i % verts].first, vecTransformedCoordinates[i % verts].second, vecTransformedCoordinates[j % verts].first, vecTransformedCoordinates[j % verts].second, col);
		
	}
}

Vehicle::Vehicle() {}
Vehicle::Vehicle(float _x, float _y, float _w, float _h) {
	position = { _x, _y };
	velocity = { 3.0f, -2.0f };
	acceleration = { 0.0f, 0.0f };
	vehiclePath = { _w / 2.0f, _h / 2.0f };
	radius = 100.0f;
	size = 10.0f;
	maxSpeed = 2.0f;
	maxForce = 0.15f;
	d = 25.0f;
}
void Vehicle::update() {
	velocity += acceleration;
	limit(velocity, maxSpeed);
	//std::cout << "Vel: " << velocity.x << ", " << velocity.y << std::endl;
	position += velocity;
	acceleration *= 0;
}
void Vehicle::applyForce(olc::vf2d force) {
	acceleration += force;
}
void Vehicle::checkEdges(olc::PixelGameEngine& pge) {
	olc::vf2d desired = { 0, 0 };
	olc::vf2d predict = velocity;
	predict *= 25;

	olc::vf2d futureLocation = position + predict;
	float distance = (futureLocation - vehiclePath).mag();

	if (distance > radius * 2.0f) {
		olc::vf2d toCenter = vehiclePath - position;
		toCenter = toCenter.norm();
		toCenter *= velocity.mag();
		desired = velocity + toCenter;

		desired = desired.norm();
		desired *= maxSpeed;
	}
	if (desired.x != 0) {
		olc::vf2d steer = desired - velocity;
		limit(steer, maxForce);
		applyForce(steer);
	}

	display(pge, futureLocation);
}
void Vehicle::display(olc::PixelGameEngine& pge, olc::vf2d& futureLocation) {
	
	pge.DrawCircle(futureLocation, 5, olc::RED);

	olc::vf2d firstPoint = position;
	olc::vf2d secondPoint = { position.x + size * 2, position.y + size / 2 };
	olc::vf2d thirdPoint = { position.x, position.y + size };
	pge.FillTriangle(firstPoint, secondPoint, thirdPoint, olc::WHITE);
	//pge.DrawCircle(position, 5, olc::BLUE);
	//pge.DrawLine(position.x, position.y, position.x, position.y + size, olc::WHITE);
	//pge.DrawLine(position.x, position.y, position.x + size * 2, position.y + size / 2, olc::WHITE);
	//pge.DrawLine(position.x, position.y + size, position.x + size * 2, position.y + size / 2, olc::WHITE);
	/*vecShipModel = {
		{position.x, position.y},
		{position.x + size * 2, position.y + size / 2},
		{position.x , position.y + size}
	};*/
	//DrawWireFrameModel(pge, vecShipModel, position.x, position.y, 0, 1, olc::WHITE);
	pge.DrawCircle(vehiclePath, int(radius) * 2, olc::GREEN);
}

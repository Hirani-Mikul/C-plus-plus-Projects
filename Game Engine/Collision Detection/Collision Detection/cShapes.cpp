#include "cShapes.h"

float extern fWidth;
float extern fHeight;

void DrawShapeObjects(olc::PixelGameEngine* pge, const std::vector<olc::vf2d>& vecModelCoordinates, olc::vf2d pos, float angle = 0.04f, float scale = 1.0f, olc::Pixel col = olc::WHITE);
void limit(olc::vf2d& v, float max);
float dist(float x, float y, float ox, float oy);

cShapes::cShapes() : position({ 0.0f, 0.0f }), velocity({ 0.0f, 0.0f }), acceleration({0.0f, 0.0f}), fAngle(0.0f), radius(5.0f), mass(1.0f), maxForce(0.8f) {}
cShapes::cShapes(olc::vf2d pos, float r, float m) : position({ 0.0f, 0.0f }), velocity({ 0.0f, 0.0f }), acceleration({ 0.0f, 0.0f }), radius(5.0f), mass(1.0f), maxForce(0.8f), fAngle(0.0f)
{
	position = pos;
	radius = r;
	mass = m;
	fFriction = 0.9f;

	createModel();
}

void cShapes::createModel() {
	
	int verts = 20;

	for (int i = 0; i < verts; i++)
	{
		float r = 1.0f;
		float a = ((float)i / (float)verts) * 6.28318f;
		vecModel.push_back({ r * sinf(a), r * cosf(a) });
	}

}
void cShapes::display(olc::PixelGameEngine* pge) {
	
	DrawShapeObjects(pge, vecModel, position, fAngle, radius, olc::YELLOW);
}
void cShapes::update(float fElapsedTime) {
	velocity += acceleration * fElapsedTime;

	position += velocity * fElapsedTime; 

	acceleration *= 0;
}
void cShapes::checkEdges(std::pair<olc::vf2d, olc::vf2d> &vGround, olc::vf2d &vGravity) {

	if (!(position.y + radius >= vGround.first.y))
	{
		applyForce(vGravity);
	}

	if (position.x + radius >= fWidth || position.x - radius <= 0.0f)
		velocity.x *= -1;
	if (position.y - radius <= 0.0f)
		velocity.y *= -1;
	else if (position.y + radius >= vGround.first.y)
	{
		position.y = vGround.first.y - radius;
		olc::vf2d force = { 0.0f, velocity.y * fFriction };
		velocity.y *= 0;
		applyForce({0.0f, -600.0f });
	}

	
}
void cShapes::applyForce(olc::vf2d f) {
	acceleration += f;
}
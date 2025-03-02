#include "Platform.h"

void extern DrawGameObjects(olc::PixelGameEngine &pge, std::vector<olc::vf2d> &vecModelCoordinates, olc::vf2d vecPos, float angle = 0.04f, float scale = 1.0f, olc::Pixel col = olc::WHITE);
void extern DrawGameObjectsRect(olc::PixelGameEngine& pge, std::vector<olc::vf2d>& vecModelCoordinates, olc::vf2d vecPos, float angle = 0.04f, float scaleX = 1.0f, float scaleY = 1.0f, olc::Pixel col = olc::WHITE);

void extern limit(olc::vf2d &v, float max);
float extern dist(float x, float y, float ox, float oy);

Platform::Platform() : position({0.0f, 0.0f}), fP_width(1.0f), fP_height(1.0f), fAngle(0.04f) {}
Platform::Platform(olc::vf2d pos, float width, float height) : position({ 0.0f, 0.0f }), fP_width(1.0f), fP_height(1.0f), fAngle(0.04f) {
	position = pos;
	fP_width = width;
	fP_height = height;
	//fAngle = 0.04f;
	fAngle = 0.0f;

	createModel();
}
void Platform::createModel() {
	vecModel = {
		{0.0f, 0.0f},
		{1.0f, 0.0f},
		{1.0f, 1.0f},
		{0.0f, 1.0f}
	};
	vecCenterLineModel = {
		{0.0f, 0.0f},
		{0.0f, -1.0f}
	};
}
void Platform::display(olc::PixelGameEngine &pge) {
	DrawGameObjectsRect(pge, vecModel, position, fAngle, fP_width, fP_height, olc::RED);
	DrawGameObjects(pge, vecCenterLineModel, position, fAngle, fP_height / 2.0f , olc::GREEN);
}


// Ball Class definition
Ball::Ball() : position({ 0.0f, 0.0f }), velocity({ 1.0f, 2.0f }), acceleration({0.0f, 0.0f}), radius(5.0f), fAngle(0.04f) {}
Ball::Ball(olc::vf2d pos, float r, int id) :
	position({ 0.0f, 0.0f }),
	velocity({ 1.0f, 2.0f }),
	acceleration({ 0.0f, 0.0f }),
	gravity({ 0.0f, 10.0f }),
	radius(5.0f),
	fAngle(0.04f),
	maxSpeed(300.0f),
	maxForce(20.0f),
	col(olc::BLUE),
	bId(0)
{
	position = pos;
	radius = r;
	bId = id;

	createModel();
}
void Ball::createModel() {

	int verts = 20;


	// vecModel
	for (int i = 0; i < verts; i++)
	{
		float r = 1.0f;
		float a = ((float)i / (float)verts) * 6.28318f;
		vecModel.push_back({ r * sinf(a), r * cosf(a) });
	}

	// Center Line
	vecCenterLineModel = {
		{0.0f, 0.0f},
		{0.0f, 1.0f}
	};
}
void Ball::display(olc::PixelGameEngine &pge) {

	//olc::vf2d mpos = { (float)pge.GetMouseX(), (float)pge.GetMouseY() };

	//olc::vf2d dir = mpos - position;

	//fAngle = atan2f(dir.y, dir.x) + 1.5708f;

	DrawGameObjects(pge, vecModel, position, fAngle, radius, col);
	DrawGameObjects(pge, vecCenterLineModel, position, fAngle, -radius, olc::YELLOW);
}
void Ball::update(float fElapsedTime) {


	applyForce(gravity);

	if (velocity.x < 0) {
		fAngle -= 0.006f;
	}
	else if (velocity.x > 0) {
		fAngle += 0.006f;
	}

	velocity += acceleration * fElapsedTime * maxForce;
	limit(velocity, maxSpeed);
	position += velocity * fElapsedTime;
	acceleration *= 0.0f;
}
void Ball::applyForce(olc::vf2d f) {
	acceleration += f;
}

//void Ball:checkBalls() {}

void Ball::checkWalls(std::vector<Platform> &walls) {
	if (position.x - radius <= walls[0].position.x + walls[0].fP_width / 2.0f)
	{
		position.x = (walls[0].position.x + walls[0].fP_width / 2.0f) + radius;
		float mag = velocity.mag() * friction * maxForce;
		applyForce({mag, 0.0f});
		//velocity.x = velocity.x * -1 * friction;
	}
	else if (position.x + radius >= walls[2].position.x - walls[2].fP_width / 2.0f)
	{
		position.x = (walls[2].position.x - walls[2].fP_width / 2.0f) - radius;
		//velocity.x = velocity.x * -1 * friction;
		float mag = velocity.mag() * -friction * maxForce;
		applyForce({ mag, 0.0f });
	}

	if (position.y - radius <= walls[1].position.y + walls[1].fP_height / 2.0f)
	{
		position.y = (walls[1].position.y + walls[1].fP_height / 2.0f) + radius;
		//velocity.y = velocity.y * -1.0f * friction;
		float mag = velocity.mag() * friction * maxForce;
		applyForce({ 0.0f, mag });
	}
	else if (position.y + radius >= walls[3].position.y - walls[3].fP_height / 2.0f)
	{
		position.y = (walls[3].position.y - walls[3].fP_height / 2.0f) - radius;
		if (velocity.y <= 0.0f) return;
		velocity.y *= -0.8f;
	}

}
void Ball::checkPlatforms(std::vector<Platform> &platforms) {
	for (int i = 0; i < platforms.size(); i++)
	{
		if (position.x - radius <= platforms[i].position.x + platforms[i].fP_width / 2.0f && position.x + radius >= platforms[i].position.x - platforms[i].fP_width / 2.0f && position.y - radius <= platforms[i].position.y + platforms[i].fP_height / 2.0f && position.y + radius >= platforms[i].position.y - platforms[i].fP_height / 2.0f)
		{
			//position.x = (platforms[0].position.x + platforms[i].fP_width / 2.0f) + radius;
			//float mag = velocity.mag() * friction * maxForce;
			float vx = velocity.x * friction * maxForce;
			float vy = velocity.y * friction * maxForce;
			applyForce({ -vx, -vy });
		}
		
	}
}
bool Ball::intersects(Ball& o) {
	float d = dist(position.x, position.y, o.position.x, o.position.y);
	return d <= radius * 2;
}
void Ball::bounce(Ball& o) {
	/*olc::vf2d bForce = {velocity.x * friction * maxForce, velocity.y * friction * maxForce };
	olc::vf2d oForce = {o.velocity.x * o.friction * o.maxForce, o.velocity.y * o.friction * o.maxForce };*/

	//applyForce(bForce);
	//o.applyForce(oForce);

	// bx + ox = newbx + newox
	// by + oy = newby + newoy
	// b1 + o2 = newbx + newox

	float bx = velocity.x * friction * maxForce;
	float by = velocity.y * friction * maxForce;
	float ox = o.velocity.x * o.friction * o.maxForce;
	float oy = o.velocity.y * o.friction * o.maxForce;

	if (velocity.x <= 0.0f || velocity.y <= 0.0f)
	{
		position.x = position.x;
		position.y = position.y;
		o.position.x = o.position.x;
		o.position.y = o.position.y;
		return;
	}

	olc::vf2d bForce = { bx, by };
	olc::vf2d oForce = {ox, oy};

	applyForce(-bForce);
	o.applyForce(-oForce);


}


	//else if (position.x + radius >= platforms[i].position.x - platforms[i].fP_width / 2.0f)
	//	{
	//	position.x = (platforms[i].position.x - platforms[i].fP_width / 2.0f) - radius;
	//	float mag = velocity.mag() * -friction * maxForce;
	//	applyForce({ mag, 0.0f });
	//	}

//else if ()
//		{
//		position.y = (platforms[i].position.y - platforms[i].fP_height / 2.0f) - radius;
//		if (velocity.y <= 0.0f) return;
//		velocity.y *= -0.8f;
//		}

//if (position.y - radius <= platforms[i].position.y + platforms[i].fP_height / 2.0f && position.y + radius >= platforms[i].position.y - platforms[i].fP_height / 2.0f)
//{
//	//position.y = (platforms[i].position.y + platforms[i].fP_height / 2.0f) + radius;
//	float mag = velocity.mag() * friction * maxForce;
//	applyForce({ 0.0f, mag });
//}
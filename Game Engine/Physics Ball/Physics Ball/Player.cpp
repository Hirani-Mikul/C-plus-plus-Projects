#include "Player.h"

void limit(olc::vf2d& v, float max) {
	const float mSq = ((v.x * v.x) + (v.y * v.y));

	if (mSq > max * max)
	{
		v.x = (v.x / sqrt(mSq)) * max;
		v.y = (v.y / sqrt(mSq)) * max;
	}
};

void DrawWireFrameModel(olc::PixelGameEngine& pge, const std::vector<olc::vf2d>& vecModelCoordinates, olc::vf2d pos, float angle = 0.04f, float s = 1.0f, olc::Pixel col = olc::WHITE) {

	std::vector<olc::vf2d> vecTransformedCoordinates;
	int verts = vecModelCoordinates.size();
	vecTransformedCoordinates.resize(verts);

	// Rotate
	for (int i = 0; i < verts; i++)
	{
		vecTransformedCoordinates[i].x = vecModelCoordinates[i].x * cosf(angle) - vecModelCoordinates[i].y * sinf(angle);

		vecTransformedCoordinates[i].y = vecModelCoordinates[i].x * sinf(angle) + vecModelCoordinates[i].y * cosf(angle);

	}

	// Scale
	for (int i = 0; i < verts; i++)
	{
		vecTransformedCoordinates[i].x *= s;
		vecTransformedCoordinates[i].y *= s;
	}

	// Translate
	for (int i = 0; i < verts; i++)
	{
		vecTransformedCoordinates[i].x += pos.x;
		vecTransformedCoordinates[i].y += pos.y;
	}

	// Draw
	for (int i = 0; i < verts + 1; i++)
	{
		int j = (i + 1);
		pge.DrawLine(vecTransformedCoordinates[i % verts].x, vecTransformedCoordinates[i % verts].y, vecTransformedCoordinates[j % verts].x, vecTransformedCoordinates[j % verts].y, col);
	}


}

Player::Player() : position({ 100.0f, 100.0f }), velocity({ 0.0f, 0.0f }), acceleration({ 0.0f, 0.0f }), radius(10.0f), fSpeed(20.0f), jumpForce(150.0f), angle(0.0f) {}

Player::Player(std::vector<olc::vf2d>& model, float x, float y, float radius, float speed) : position({ 100.0f, 100.0f }), velocity({ 0.0f, 0.0f }), acceleration({ 0.0f, 0.0f }), radius(10.0f), fSpeed(20.0f), jumpForce(150.0f) {

	this->position = { x, y };
	this->radius = radius;
	this->fSpeed = speed;
	this->vecModel = model;
	this->angle = 0.0f;
	this->vecLineModel = { {0.0f, 0.0f}, {1.0f, 0.0f} };
	this->friction = 0.6f;
}
void Player::display(olc::PixelGameEngine &pge) {
	//pge.FillCircle(position, radius, olc::WHITE);
	//DrawWireFrameModel(vecModel, position, angle, radius, olc::RED);
	DrawWireFrameModel(pge, vecModel, position, angle, radius, olc::RED);
	DrawWireFrameModel(pge, vecLineModel, position, angle, radius, olc::WHITE);

}

void Player::update(float fElapsedTime) {
	limit(velocity, fSpeed * 4);
	position += velocity * fElapsedTime;
	if (velocity.x < 0.0f) angle += -2.8f * fElapsedTime;
	else angle += 2.8f * fElapsedTime;
	velocity += acceleration * fElapsedTime;
	acceleration *= 0;
}
void Player::applyForce(olc::vf2d f) {
	acceleration += f;
}
void Player::move(olc::PixelGameEngine &pge) {
	if (pge.GetKey(olc::Key::RIGHT).bHeld)
	{
		//acceleration.x += 1.0f * fSpeed;
		applyForce({ 500.0f, 0.0f });
		//velocity.x = 1.0f * fSpeed;
	}
	if (pge.GetKey(olc::Key::LEFT).bHeld)
	{
		applyForce({ -500.0f, 0.0f });
		//acceleration.x += -1.0f * fSpeed;
		//velocity.x = -1.0f * fSpeed;

	}
	if (pge.GetKey(olc::Key::SPACE).bPressed)
	{
		if (isGrounded)
			velocity.y = -1.0f * jumpForce;
		else return;
	}
}

void Player::checkEdges(const std::vector<std::pair<olc::vf2d, olc::vf2d>>& surfaces)
{

	// force = vel - prev

	if (position.y + radius >= surfaces[3].first.y - 3.0f) isGrounded = true;
	else isGrounded = false;

	if (position.x - radius <= surfaces[0].first.x + surfaces[0].second.x)
	{
		position.x = surfaces[0].first.x + surfaces[0].second.x + radius;
		velocity.x = velocity.x * -1 * friction;
	}
	else if (position.x + radius >= surfaces[2].first.x)
	{
		position.x = surfaces[2].first.x - radius;
		velocity.x = velocity.x * -1 * friction;
	}

	if (position.y - radius <= surfaces[1].first.y + surfaces[1].second.y)
	{
		position.y = surfaces[1].first.y + surfaces[1].second.y + radius;
		velocity.y = velocity.y * -1.0f * friction;
	}
	else if (position.y + radius >= surfaces[3].first.y)
	{
		position.y = surfaces[3].first.y - radius;
		if (velocity.y <= 0.0f) return;
		velocity.y *= -0.8f;
	}
}

//void Player::checkEdges(const olc::vf2d &ground) {
	/*if (position.x + radius >= fSW)
	{
		velocity.x = 0;
		acceleration.x *= -1;
	}
	else if (position.x - radius <= 0)
	{
		velocity.x = 0;
		acceleration.x *= -1;
	}

	if (position.y + radius + 10.0f >= fSH)
	{
		position.y = fSH - radius - 10.0f;
	}
	else if (position.y - radius <= 0)
	{
		position.y = radius;
	}*/
//}

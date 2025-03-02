#include "Objects.h"


Plank::Plank(olc::vf2d pos, float width, float height, olc::Pixel col) : Entity(pos, width, height, col), offset(0.0f, 40.0f), dist(0.0f, 0.0f)
{
	createModel();
}
void Plank::MovePlank(float fElapsedTime, float dir)
{
	if (vecModel[0].y <= vecModel[1].y - 10.0f)
	{
		vecModel[0].y = vecModel[1].y - 10.0f;
		vecModel[3].y = vecModel[0].y + 1.5f;

	}
	else if (vecModel[3].y >= vecModel[1].y + 10.0f) {
		vecModel[0].y = vecModel[1].y + 8.5f;
		vecModel[3].y = vecModel[1].y + 10.0f;
	}

	vecModel[0] += offset * fElapsedTime * dir;
	vecModel[3] += offset * fElapsedTime * dir;

	//std::cout << vecModel[0].x << ", " << vecModel[0].y << std::endl;

	dist = vecModel[2] - vecModel[3];
	dist.x *= eWidth;
	dist.y *= eHeight;

}
void Plank::createModel()
{
	vecModel = {
		{ 0.0f, 0.0f },
		{ 1.0f, 0.0f },
		{ 1.0f, 1.0f },
		{ 0.0f, 1.0f }
	};
}

olc::vf2d Plank::GetPlankSurface()
{
	return -dist;
}

std::pair<olc::vf2d, olc::vf2d> Plank::GetPoints() const
{
	const olc::vf2d pos = GetPos();

	std::pair<olc::vf2d, olc::vf2d> p = std::make_pair(pos, pos + dist);
	p.first.x = p.first.x + eWidth;
	p.first.y = p.first.y + eHeight;

	//std::cout << "1. ( " << p.first.x << ", " << p.first.y << " ), 2. ( " << p.second.x << ", " << p.second.y << " )" << std::endl;

	return p;
	//return std::make_pair(pos, pos + dist);
}

Entity::Entity(olc::vf2d pos, float width, float height, olc::Pixel col = olc::GREEN) : position(pos), eWidth(width), eHeight(height), col(col), radius(width)
{
	createModel();
}

void Entity::SetPos(olc::vf2d pos_in)
{
	position = pos_in;
}

olc::vf2d Entity::GetPos() const
{
	return position;
}

std::pair<float, float> Entity::GetSize() const
{
	return std::make_pair(eWidth, eHeight);
}

void Entity::display(CoordinateTransformer* ct)
{
	ct->DrawShape(vecModel, position, GetSize(), col);
}

void Entity::createModel()
{
	vecModel = {
		{ 0.0f, 0.0f },
		{ 0.0f, 1.0f },
		{ 1.0f, 0.5f }
	};
}

Ball::Ball(olc::vf2d pos, float wRadius, float hRadius, olc::Pixel col) : Entity(pos, wRadius, hRadius, col), velocity(20.0f, -100.0f)
{
	createModel();
}

void Ball::createModel()
{
	vecModel.clear();
	int verts = 20;
	vecModel.reserve(20);

	for (int i = 0; i < verts; i++)
	{
		float radius = 1.0f;
		float a = ( (float)i / (float)verts ) * 6.28318f;
		olc::vf2d m = { radius * sinf(a), radius * cosf(a) };
		vecModel.emplace_back(m);
	}
}

void Ball::update(float fElapsedTime)
{
	if (position.x <= -fWidth / 2 || position.x >= fWidth / 2)
	{
		 position.x = 0.0f;
		 position.y = 0.0f;


		 if (velocity.y > 0)
			 velocity.y *= -1;

		 int index = rand() % 4;

		 float vx = randVx[index];
		 velocity.x = vx;
	}

	if (position.y <= -fHeight / 2 || position.y >= fHeight)
	{
		position.y = 0.0f;
		position.x = 0.0f;



		if (velocity.y > 0)
			velocity.y *= -1;
		int index = rand() % 4;

		float vx = randVx[index];
		velocity.x = vx;
	}


	position += velocity * fElapsedTime;


}

olc::vf2d Ball::GetVel() const
{
	return velocity;
}

void Ball::SetVel(olc::vf2d vel_in)
{
	velocity = vel_in;
}

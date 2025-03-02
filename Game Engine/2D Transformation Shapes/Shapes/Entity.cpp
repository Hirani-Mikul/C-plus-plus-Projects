#include "Entity.h"


Entity::Entity() : pos({ 0.0f, 0.0f }), fScale(1.0f) {}

Entity::Entity(std::vector<olc::vf2d> vecModel, const olc::vf2d& pos = { 0.0f, 0.0f }) : pos(pos), vecModel(std::move(vecModel)), fScale(1.0f) {}

const olc::vf2d& Entity::GetPos() const
{	
	return pos; 
}

void Entity::SetPos(const olc::vf2d& newPos)
{
	pos = newPos;
}

void Entity::TranslateBy(const olc::vf2d& offset)
{
	pos += offset;
}

void Entity::SetScale(float s)
{
	fScale = s;
}

float Entity::GetScale() const
{
	return fScale;
}

std::vector<olc::vf2d> Entity::GetPolyLine() const
{
	auto poly = vecModel;

	for (auto& v : poly)
	{
		v *= fScale;
		v += pos;
	}

	return poly;
}




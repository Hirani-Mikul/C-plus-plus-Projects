#include "Polygon.h"


cCircle::cCircle(olc::vf2d pos, int verts, float radius, olc::Pixel col) : Entity(Circle::Make(verts), pos, radius, col), m_Radius(radius)
{
}

float cCircle::GetRadius() const
{
	return m_Radius;
}

RectF cCircle::GetBoundingRect() const
{
	return RectF::FromCenter( GetPos(), GetRadius(), GetRadius() );
}


// Plank class

Plank::Plank(olc::vf2d anchor, float freeX, float minY, float maxY, float thickness = 10.0f, olc::Pixel col = olc::BLUE)
	: Entity({}, anchor, 1.0f, col ), 
	m_MinYModel(minY - anchor.y),
	m_MaxYModel(maxY - anchor.y),
	m_FreePtModel( freeX - anchor.x, m_MinYModel),
	m_Thickness(thickness)
{
}

void Plank::MoveFreeY(float dir)
{
	SetFreeY( GetFreePt().y + dir );
}

olc::vf2d Plank::GetFreePt() const
{
	return m_FreePtModel + GetPos();
}

void Plank::SetFreeY(float freeY_in)
{
	m_FreePtModel.y = std::clamp(freeY_in - GetPos().y, m_MinYModel, m_MaxYModel);

}

olc::vf2d Plank::GetPlankSurfaceVector() const
{
	return -m_FreePtModel;
}

std::pair<olc::vf2d, olc::vf2d> Plank::GetPoints() const
{
	const olc::vf2d pos = GetPos();

	return std::make_pair(pos, pos + m_FreePtModel);
}

Drawable Plank::GetDrawable()
{
	std::vector<olc::vf2d> model;
	model.reserve(4);
	model.emplace_back(0.0f, 0.0f);
	model.push_back(m_FreePtModel);
	model.push_back( m_FreePtModel + olc::vf2d(0.0f, m_Thickness) );
	model.emplace_back( 0.0f, m_Thickness );
	SetModel( std::move(model) );
	
	return Entity::GetDrawable();

}


// Ball definitions

Ball::Ball(olc::vf2d pos, float radius, olc::vf2d vel, olc::Pixel col = olc::BLUE) : Entity(Circle::Make(20), pos, radius, col), m_Vel(vel), m_Radius(radius)
{
}

float Ball::GetRadius() const
{
	return m_Radius;
}

olc::vf2d Ball::GetVel() const
{
	return m_Vel;
}

void Ball::SetVel(const olc::vf2d& vel_in)
{
	m_Vel = vel_in;
}

void Ball::update(float fElapsedTime)
{
	TranslateBy( m_Vel * fElapsedTime );
}

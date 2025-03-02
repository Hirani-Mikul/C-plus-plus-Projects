#include "Entity.h"

Entity::Entity(std::vector<olc::vf2d> model, olc::vf2d pos = { 0.0f, 0.0f }, float radius = 5.0f, olc::Pixel col = olc::GREEN)
	: m_Model(std::move(model)), m_Position(pos), m_Radius(radius), m_Scale(1.0f), m_Col(col)
{
}

void Entity::TranslateBy(const olc::vf2d& offset)
{
	m_Position += offset;
}

void Entity::SetPos(const olc::vf2d& pos_in)
{
	m_Position = pos_in;
}
void Entity::SetScale(float scale_in)
{
	m_Scale = scale_in;
}
void Entity::SetColor(const olc::Pixel col)
{
	m_Col = col;
}
void Entity::SetRadius(const float& radius_in)
{
	m_Radius = radius_in;
}
float Entity::GetRadius() const
{
	return m_Radius;
}
float Entity::GetScale() const 
{
	return m_Scale;
}

const olc::vf2d& Entity::GetPos() const
{
	return m_Position;
}
Drawable Entity::GetDrawable() const
{
	Drawable d(m_Model, m_Col);
	d.Scale(m_Radius);
	d.Scale(m_Scale);
	d.Translate(m_Position);

	return d;
}

void Entity::SetModel(std::vector<olc::vf2d> model_in)
{
	m_Model = std::move(model_in);
}

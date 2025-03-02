#include "Camera.h"

Camera::Camera(CoordinateTransformer& ct) : ct(ct), m_Position(0.0f, 0.0f), m_Scale(1.0f)
{
}

olc::vf2d Camera::GetPos() const
{
	return m_Position;
}

void Camera::MoveBy(const olc::vf2d& offset)
{
	m_Position += offset;
}

void Camera::MoveTo(const olc::vf2d& pos_in)
{
	m_Position = pos_in;
}

void Camera::FollowEntity(const olc::vf2d& entity_pos)
{

	m_Position = entity_pos;
}

float Camera::GetScale() const
{
	return m_Scale;
}

void Camera::SetScale(float scale_in)
{
	m_Scale = scale_in;
}

void Camera::DrawShape(Drawable &drawable) const
{
	drawable.Translate(-m_Position);
	drawable.Scale(m_Scale);
	ct.DrawShape(drawable);
}

RectF Camera::GetViewPortRect() const
{
	const float zoom = 1.0f / m_Scale;
	return RectF::FromCenter(
		m_Position,
		(fWidth / 2.0f) * zoom,
		(fHeight / 2.0f) * zoom
	);
}

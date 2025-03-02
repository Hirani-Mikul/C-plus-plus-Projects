#include "Camera.h"

Camera::Camera(CoordinateTransformer& ct) : pos(0.0f, 0.0f), fScale(1.0f), ct(ct) {}

olc::vf2d Camera::GetPos() const
{
	return pos;
}

void Camera::MoveBy(const olc::vf2d& offset)
{
	pos += offset;
}

void Camera::MoveTo(const olc::vf2d& pos_in)
{
	pos = pos_in;
}

void Camera::DrawShape( Drawable &drawable ) const
{
	drawable.Translate(-pos);
	drawable.Scale(fScale);
	ct.DrawShape(drawable);
}

void Camera::SetScale(float s)
{
	fScale = s;
}

float Camera::GetScale() const
{
	return fScale;
}

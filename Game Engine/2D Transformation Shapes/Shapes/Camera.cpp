#include "Camera.h"


Camera::Camera(CoordinateTransformer& ct) : pos(0.0f, 0.0f), ct(ct), fScale(1.0f){}

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

void Camera::DrawClosedPolyLine(std::vector<olc::vf2d> poly, olc::Pixel col)
{
	for (auto& v : poly)
	{
		v -= pos;
		v *= fScale;
	}

	ct.DrawClosedPolyline(std::move(poly), col);
}

void Camera::SetScale(float s)
{
	fScale = s;
}

float Camera::GetScale() const
{
	return fScale;
}

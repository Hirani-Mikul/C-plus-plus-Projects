#pragma once
#include "CoordinateTransformer.h"

class Camera
{
public:
	Camera(CoordinateTransformer& ct) : ct{ ct }, m_Position{ .0f, .0f }, m_Scale{ 1.0f } {}

public:

	void MoveTo(const olc::vf2d& pos_in)
	{
		m_Position = pos_in;
	}

	void MoveBy(const olc::vf2d& pos_in)
	{
		m_Position += pos_in;
	}

	void DrawShape(Drawable& drawable) const
	{
		drawable.Translate(-m_Position);
		drawable.Scale(m_Scale);

		ct.DrawShape(drawable);
	}

	void SetScale(float scale_in) {

		m_Scale = scale_in;
	}
	olc::vf2d GetPos() const
	{
		return m_Position;
	}
	float GetScale() const
	{
		return m_Scale;
	}

private:

	CoordinateTransformer& ct;

	olc::vf2d m_Position;

	float m_Scale;


};
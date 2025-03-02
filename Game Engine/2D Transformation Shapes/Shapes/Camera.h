#pragma once
#include "CoordinateTransformer.h"

class Camera
{
public:
	Camera(CoordinateTransformer &ct);

public:
	olc::vf2d GetPos() const;
	void MoveBy(const olc::vf2d &offset);
	void MoveTo(const olc::vf2d &pos_in);
	void DrawClosedPolyLine(std::vector<olc::vf2d> poly, olc::Pixel col);

	void SetScale(float s);
	float GetScale() const;

private:
	olc::vf2d pos;
	CoordinateTransformer& ct;
	float fScale;
};


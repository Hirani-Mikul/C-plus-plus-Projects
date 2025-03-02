#pragma once
#include "Camera.h"
class Entity
{
public:
	Entity();
	Entity(std::vector<olc::vf2d> vecModel, const olc::vf2d &pos);

public:

	const olc::vf2d& GetPos() const;
	void SetPos(const olc::vf2d &newPos);
	void TranslateBy(const olc::vf2d &offset);
	void SetScale(float s);
	float GetScale() const;

	std::vector<olc::vf2d> GetPolyLine() const;

private:
	olc::vf2d pos;
	std::vector<olc::vf2d> vecModel;
	float fScale;
};


#pragma once
#include "CoordinateTransformer.h"

struct Entity
{
	Entity(std::vector<olc::vf2d> vecModel, const olc::vf2d &pos, olc::Pixel col);

	const olc::vf2d& GetPos() const;
	void SetPos(olc::vf2d& newPos);
	void TranslateBy(const olc::vf2d &offset);
	void SetScale(float s);
	float GetScale() const;

	Drawable GetDrawable() const;

private:
	olc::Pixel col;
	olc::vf2d pos;
	std::vector<olc::vf2d> vecModel;
	float fScale;
};

struct Plank : public Entity {


};
#pragma once
#include "Entity.h"
#include <algorithm>

class cCircle : public Entity
{
public:
	cCircle( olc::vf2d pos, int verts, float radius, olc::Pixel col );
	
public:
	float GetRadius() const;
	RectF GetBoundingRect() const;
	
	
private:
	float m_Radius;

};

class Plank : public Entity {

public:
	Plank(olc::vf2d anchor, float freeX, float minY, float maxY, float thickness, olc::Pixel col);

public:
	void MoveFreeY(float dir);
	olc::vf2d GetFreePt() const;
	void SetFreeY(float freeY_in);

	olc::vf2d GetPlankSurfaceVector() const;

	std::pair<olc::vf2d, olc::vf2d> GetPoints() const;

	Drawable GetDrawable();

private:
	float m_MinYModel;
	float m_MaxYModel;
	olc::vf2d m_FreePtModel;
	float m_Thickness;

};



class Ball : public Entity {
public:
	Ball(olc::vf2d pos, float radius, olc::vf2d vel, olc::Pixel col);

public:
	float GetRadius() const;
	olc::vf2d GetVel() const;
	void SetVel(const olc::vf2d& vel_in);
	void update(float fElapsedTime);

private:
	float m_Radius;
	olc::vf2d m_Vel;
};
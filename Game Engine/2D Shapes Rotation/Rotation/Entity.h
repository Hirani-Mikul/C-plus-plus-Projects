#pragma once
#include "Shape.h"
#include "Drawable.h"
#include "RectF.h"

class Entity
{
public:
	Entity(std::vector<olc::vf2d> model, olc::vf2d pos, float radius, olc::Pixel col);

public:
	void TranslateBy( const olc::vf2d& offset );

	void SetPos(const olc::vf2d &pos_in );
	void SetScale( float scale_in );
	void SetColor( const olc::Pixel col );
	void SetRadius( const float &radius_in );
	float GetRadius() const;

	const olc::vf2d &GetPos() const;
	float GetScale() const;



	Drawable GetDrawable() const;
protected:
	void SetModel( std::vector<olc::vf2d> model_in );

private:
	std::vector<olc::vf2d> m_Model;
	olc::vf2d m_Position;

	olc::Pixel m_Col;
	float m_Scale;
	float m_Radius;
};


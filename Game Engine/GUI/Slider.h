#pragma once
#include "olcPixelGameEngine.h"
#include <cmath>

float constrain( float n, float low, float high ) {

	return std::max( std::min(n, high), low );

}

float mapNum( float n, float s1, float e1, float s2, float e2, bool withinBounds = false ) {

	const float newVal = ((n - s1) / (e1 - s1)) * (e2 - s2) + s2;

	if (!withinBounds)
		return newVal;

	if (s2 < e2)
		return constrain(newVal, s2, e2);
	else
		return constrain(newVal, e2, s2);

}

float dist( const olc::vf2d& cursor, const olc::vf2d& pos ) {
	
	return std::sqrtf( (pos.x - cursor.x) * (pos.x - cursor.x) + (pos.y - cursor.y) * (pos.y - cursor.y) );

}


class Slider {

public:
	Slider(olc::vf2d pos, olc::vf2d size = { 50.0f, 20.0f }, olc::Pixel col = olc::BLACK, float min = 0.0f, float max = 1.0f, float step = 0.1f, float value = 0.0f) : m_Position(pos), m_Size(size), m_Color(col), m_Min(min), m_Max(max), m_Step(step), m_CurrentValue(value), m_IsSelected(false) { 
		
		//m_BallPosition = m_Position;
		Construct();
	}
public:
	void Construct() {
		
		m_BallPosition.y = m_Position.y;

		m_BallPosition.x = mapNum( m_CurrentValue, m_Min, m_Max, m_Position.x - m_Size.x / 2.0f, m_Position.x + m_Size.x / 2.0f );

		m_BallPosition.x = constrain( m_BallPosition.x, m_Position.x - m_Size.x / 2.0f, m_Position.x + m_Size.x / 2.0f );

		//m_Step = m_Step * 100.0f;
		m_Step = m_Step * 100.0f;

	}
	void Display(olc::PixelGameEngine* pge) {
		
		pge->FillRect(m_Position - m_Size / 2.0f, m_Size, olc::WHITE);

		if (!m_IsSelected)
			pge->FillCircle(m_BallPosition, m_Size.y, m_Color);
		else
			pge->FillCircle(m_BallPosition, m_Size.y, olc::GREEN);
	}

	void Select( const olc::vf2d& cursor ) {
		if (dist(cursor, m_BallPosition) <= m_Size.y)
			m_IsSelected = true;
		else m_IsSelected = false;
	}

	void Slide( float dir ) {
		
		if (m_IsSelected)
		{
			m_BallPosition.x += m_Step * dir;
			m_BallPosition.x = constrain(m_BallPosition.x, m_Position.x - m_Size.x / 2.0f, m_Position.x + m_Size.x / 2.0f);

			m_CurrentValue = mapNum( m_BallPosition.x, m_Position.x - m_Size.x / 2.0f, m_Position.x + m_Size.x / 2.0f, m_Min, m_Max );
		}

	}

	float GetValue() const
	{
		return m_CurrentValue;
	}

private:
	olc::vf2d m_Position;
	olc::vf2d m_BallPosition;
	olc::vf2d m_Size;
	olc::Pixel m_Color;

	float m_Min;
	float m_Max;
	float m_Step;

	float m_CurrentValue;

	bool m_IsSelected;

};
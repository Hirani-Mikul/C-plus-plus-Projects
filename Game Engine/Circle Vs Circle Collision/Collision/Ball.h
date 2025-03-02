#pragma once
#include "Polygon.h"

class Ball : public Entity {

public:
	Ball() : m_Velocity(0.0f, 0.0f), m_Acceleration(0.0f, 0.0f), m_Mass(1.0f) {};
	Ball(olc::vf2d position, float radius = 10.0f, olc::Pixel col = olc::BLUE) : Entity(cCircle::Make(20), position, radius, col), m_Velocity(0.0f, 0.0f), m_Acceleration(0.0f, 0.0f) {
		
		m_Mass = radius * 10.0f;
	};

public:
	// Void
	void Update( float fElapsedTime ) {

		m_Acceleration.x = -m_Velocity.x * 0.8f;
		m_Acceleration.y = -m_Velocity.y * 0.8f;

		m_Velocity += m_Acceleration * fElapsedTime;
		m_Position += m_Velocity * fElapsedTime;

		if (fabs(m_Velocity.x * m_Velocity.x + m_Velocity.y * m_Velocity.y) < 0.01f)
		{
			m_Velocity = { 0.0f, 0.0f };
		}
	}


	// Setters
	void SetLastPosition(const olc::vf2d lastpos_in) {
		m_LastPosition = lastpos_in;
	}
	void SetVelocity (const olc::vf2d velocity_in) {
		m_Velocity = velocity_in;
	}

	void SetAcceleration(const olc::vf2d acceleration_in) {
		m_Acceleration = acceleration_in;
	}

	void SetId(const int id_in) {
		m_Id = id_in;
	}

	void SetRadius(const float radius_in)
	{
		m_Radius = radius_in;
	}
	
	void SetMass( const float mass_in )
	{
		m_Mass = mass_in;
	};
	void SetSimTime(float fTimeRemaining) 
	{
		fSimTimeRemaining = fTimeRemaining;
	}

	// Getters
	olc::vf2d GetVelocity() const {
		return m_Velocity;
	}
	olc::vf2d GetAcceleration() const {
		return m_Acceleration;
	}
	olc::vf2d GetLastPosition() const {
		return m_LastPosition;
	}

	float GetMass() const
	{

		return m_Mass;
	}

	int GetId() const {
		return m_Id;
	}

	float GetRadius() const
	{
		return m_Radius;
	}

	float GetSimTime() const
	{
		return fSimTimeRemaining;
	}

public:
	bool bIsStatic = false;

private:
	olc::vf2d m_LastPosition;
	olc::vf2d m_Velocity;
	olc::vf2d m_Acceleration;

	float fSimTimeRemaining;
	float m_Mass;

	int m_Id;
};
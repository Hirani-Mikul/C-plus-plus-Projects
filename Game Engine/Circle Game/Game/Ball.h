#pragma once
#include "Entity.h"
#include "MyMath.h"
#include "Shape.h"

class Ball : public Entity {

public:
	Ball(olc::vf2d position, float radius = 10.0f, olc::Pixel col = olc::BLUE) : Entity(Shape::Circle::Make(20), position, radius, col), m_Velocity(0.0f, 0.0f), m_Acceleration(0.0f, 0.0f), m_Id(1) {
		m_Mass = radius * 10.0f;
	}
public:
	void Update(float fElapsedTime) {
	
		m_Acceleration *= -m_Velocity * 0.8f;

		m_Velocity += m_Acceleration * fElapsedTime;
		m_Position += m_Velocity * fElapsedTime;

		if (fabs(m_Velocity.x * m_Velocity.x + m_Velocity.y * m_Velocity.y) < 0.01f)
		{
			m_Velocity = { 0.0f, 0.0f };
		}
	}

	void ApplyForce(olc::vf2d force) {
		m_Acceleration += force;
	}

	void CheckCollision(Ball &target) {

		auto pt = target.GetPos();
		float rt = target.GetRadius();

		if (Dist(m_Position, pt, m_Radius, rt))
		{
			float fDistance = Dist( m_Position, pt );

			float fOverlap = .5f * ( fDistance - m_Radius - rt );

			olc::vf2d offset = fOverlap * (m_Position - pt) / fDistance;

			// Displace this ball
			SetPos(m_Position -= offset);

			// Displace target ball
			target.SetPos( pt += offset );
		}

	}

	bool isSelected(olc::vf2d cursor) {
		return Dist(m_Position, cursor, m_Radius);
	}

	// Setters
	void SetVelocity(const olc::vf2d velocity_in) {
		m_Velocity = velocity_in;
	}
	void SetAcceleration(const olc::vf2d acceleration_in) {
		m_Acceleration = acceleration_in;
	}
	void SetId(const int id_in)
	{
		m_Id = id_in;
	}
	void SetRadius(const float radius_in)
	{
		m_Radius = radius_in;
	}
	void SetMass(float mass_in)
	{
		m_Mass = mass_in;
	}

	// Getters

	olc::vf2d GetVelocity() const {
		return m_Velocity;
	}
	olc::vf2d GetAcceleration() const {
		return m_Acceleration;
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

private:
	olc::vf2d m_Velocity;
	olc::vf2d m_Acceleration;

	float m_Mass;
	int m_Id;

};
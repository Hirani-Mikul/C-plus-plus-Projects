#pragma once

#include "Drawable.h"


class Entity {
public:

	Entity() : m_Position{ 0.0f, 0.0f }, m_velocity{ 0.0f, 0.0f }, m_acceleration{ 0.0f, 0.0f }, f_angle{ 1.0f }, f_maxSpeed{ 0.0f }, m_Scale{ 1.0f }, m_Color{ olc::BLACK } {
	
		m_id = Entity::p_id;
	}

	Entity(olc::vf2d position, olc::Pixel color = olc::RED) : m_Position{ position }, m_velocity{ 1.0f, 1.0f }, m_acceleration{ 0.0f, 0.0f }, f_angle{ 1.0f }, f_maxSpeed{ 10.0f }, m_Scale { 1.0f }, m_Color{ color } {

		/*
			------------------------------ IMPORTANT ----------------------------
			Debug whether the moving the model is efficient during creation
				
					Entity(std::vector<olc::vf2d> model, ....) : m_Model{std::move(model)}, ..... {}
		*/

		m_id = Entity::p_id;
		Entity::p_id++;
		std::cout << "Entity created from Entity class." << std::endl;

	}

public:
	// Getters
	Drawable getEntityDrawable() {
		Drawable d(m_Model, m_Color);

		//rotate();
		d.rotate(f_angle);
		d.Translate(m_Position);
		d.Scale(m_Scale);

		return d;
	}
	const olc::vf2d getPosition() const { return m_Position; }
	const float getScale() const { return m_Scale; }

	float getAngle() const { return f_angle; }

	// Setters
	void setPosition(const olc::vf2d position_in) { m_Position = position_in; }
	void setScale(const float scale_in) { m_Scale = scale_in; }

	void rotate() {
		
		// Rotate
		/*for (int i = 0; i < verts; i++) {
			vecTransformedCoordinates[i].first = vecModelCoordinates[i].first * cosf(r) - vecModelCoordinates[i].second * sinf(r);
			vecTransformedCoordinates[i].second = vecModelCoordinates[i].first * sinf(r) + vecModelCoordinates[i].second * cosf(r);
		}*/

		for (int i = 0; i < m_Model.size(); i++)
		{
			m_Model[i].x = m_Model[i].x * cosf(f_angle) - m_Model[i].y * sinf(f_angle);
			m_Model[i].y = m_Model[i].x * sinf(f_angle) + m_Model[i].y * cosf(f_angle);
		}
	}

	void setAngle(float angle_in) { f_angle = angle_in; }

	void update() {
		//f_angle = atan2f(m_velocity.y, m_velocity.x) + 1.5708f;
		if (f_angle > 2.0f) f_angle = 0.0f;

		f_angle += 0.005f;
		//rotate();
		//m_velocity += m_acceleration;
		// Limit the velocity to maximum speed

		//m_Position += m_velocity;
		//m_acceleration *= 0;

	}
	void applyForce(olc::vf2d force_in) {
		
		m_acceleration += force_in;
	}

	virtual void createModel() = 0;

protected:
	char m_id;
	std::vector<olc::vf2d> m_Model;
	olc::vf2d m_Position;
	olc::vf2d m_velocity;
	olc::vf2d m_acceleration;

	float f_angle;
	float f_maxSpeed;
	
	olc::Pixel m_Color;
	float m_Scale;



	static char p_id;
};

char Entity::p_id = 0;
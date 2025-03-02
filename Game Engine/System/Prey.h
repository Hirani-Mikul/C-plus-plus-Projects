#pragma once
#include "Entity.h"


class Prey : public Entity {

public:

	Prey(float radius = 10.0f) : Entity{ m_Position, olc::GREEN }, m_radius{ radius } {
		std::cout << "Entity created from Predetor class." << std::endl;


		m_Position.x = rand() % 500;
		m_Position.y = rand() % 500;



		m_Model.reserve(20);
		createModel();
	}

	Prey(olc::vf2d position, float radius = 10.0f) : Entity{ position, olc::GREEN }, m_radius{ radius } {
		std::cout << "Entity created from Predetor class." << std::endl;

		m_Model.reserve(20);
		createModel();
	}


private:
	void createModel() {
		for (int i = 0; i < 20; i++)
		{
			const float angle = ((float)i / (float)20) * 6.28318f;
			m_Model.emplace_back(m_radius * sinf(angle), m_radius * cosf(angle));
		}
	}

private:
	float m_radius;
};
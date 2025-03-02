#pragma once

#include "Entity.h"

class Predetor : public Entity {
public:

    Predetor(float size = 20.0f) : Entity{ m_Position, olc::RED }, m_size{ size } {
		std::cout << "Entity created from Predetor class." << std::endl;


        m_Position.x = rand() % 500;
        m_Position.y = rand() % 500;

        m_Model.reserve(20);
        createModel();
	}

    Predetor(olc::vf2d position, float size = 20.0f) : Entity{ position, olc::BLUE}, m_size{size} {
        std::cout << "Entity created from Predetor class." << std::endl;

        m_Model.reserve(3);
        createModel();
    }



private:
	void createModel() {


        // FIRST CREATE A HEAD TRIANGLE
        // SECOND THE BODY TRIANGLE


        // ============================== HEAD TRIANGLE =================================
        m_Model.emplace_back(olc::vf2d{ +0.75f, -2.75f } * m_size);  // First
        m_Model.emplace_back(olc::vf2d{ -0.75f, -2.75f } * m_size); // Second
        

        // ================================ BODY TRIANGLE =========================

        m_Model.emplace_back(olc::vf2d{ 0.0f, -5.0f } * m_size); // First
        m_Model.emplace_back(olc::vf2d { +2.5f, +2.5f } * m_size ); // Third
        m_Model.emplace_back(olc::vf2d { -2.5f, +2.5f } * m_size ); // Second 

        m_Model.emplace_back(olc::vf2d{ -0.75f, -2.75f } *m_size); // HEAD Second

	}

private:
    float m_size;
};
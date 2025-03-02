#pragma once
#include "olcPixelGameEngine.h"
#include "Entity.h"
#include "Camera.h"

class Map {

public:
	Map(olc::PixelGameEngine& pge, float width, float height) : width{ width }, height{ height }, pge{ &pge } {  }

	const void Render(const Camera& cam) {

		for (const auto& entities : m_entities)
		{
			cam.Draw(entities->getEntityDrawable());
		}
	}

	const void update(float fElapsedTime) {
		
		if (pge->GetKey(olc::Key::LEFT).bHeld)
			m_entities[1]->setAngle(m_entities[1]->getAngle() - (5.0f * fElapsedTime));
		if (pge->GetKey(olc::Key::RIGHT).bHeld)
			m_entities[1]->setAngle(m_entities[1]->getAngle() + (5.0f) * fElapsedTime);

	}

	CoordinateTransformer& getCT() { return ct; }

	void initializeMap() {
		ct = CoordinateTransformer(pge, width, height);
	}

	void addEntity(Entity* ent) {
		m_entities.push_back(ent);
	}

public:
	olc::PixelGameEngine* pge;
	std::vector<Entity*> m_entities;
	CoordinateTransformer ct;
	float width;
	float height;
};

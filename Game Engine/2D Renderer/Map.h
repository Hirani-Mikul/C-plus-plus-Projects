#pragma once
#include "Entity.h"
#include "Camera.h"
#include "Utils.h"

struct sSelectedEntity {
	std::list<Entity*>::iterator entity;
	olc::Pixel color = olc::WHITE;

	sSelectedEntity operator () ( std::list<Entity*>::iterator &e, olc::Pixel c ) {
		this->color = c;
		this->entity = e;

		return *this;
	}


};

class Map
{
public:
	Map(Camera& cam);

public:
	// Void methods
	void Construct();
	void AppendChild(Entity& entity);
	void SelectEntity(const olc::vf2d pos);
	void DeleteChild();
	void MoveSelectedEntity(const olc::vf2d dir);
	void Draw();

	
	// Setters
	// Getters
	float GetWidth() const;
	float GetHeight() const;

private:
	std::list<Entity*> m_Childrens;

	sSelectedEntity m_SelectedEntity;

	Camera& m_MainCamera;
	

	const float m_Width = 5000.0f;
	const float m_Height = 5000.0f;
	
};
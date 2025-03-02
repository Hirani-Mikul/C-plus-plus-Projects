#include "Map.h"

Map::Map(Camera& cam) : m_MainCamera(cam) {};

// Void methods

void Map::Construct () 
{
	std::cout << "Map Ready\n";
	m_SelectedEntity.entity = m_Childrens.end();
}

void Map::AppendChild( Entity& entity ) { m_Childrens.emplace_back(&entity); }

void Map::SelectEntity( const olc::vf2d pos ) 
{
	if (m_SelectedEntity.entity != m_Childrens.end())
	{
		(*m_SelectedEntity.entity)->SetColor(m_SelectedEntity.color);
		m_SelectedEntity.entity = m_Childrens.end();
	}

	for (std::list<Entity*>::iterator i = m_Childrens.begin(); i != m_Childrens.end(); i++)
	{
		if (Dist((*i)->GetPos(), pos) <= (*i)->GetRadius())
		{
			m_SelectedEntity.entity = i;
			m_SelectedEntity.color = (*i)->GetColor();
			(*m_SelectedEntity.entity)->SetColor(olc::CYAN);
			break;
		}
	}
}

void Map::DeleteChild() 
{
	if (m_SelectedEntity.entity == m_Childrens.end())
	{
		std::cout << "No Entity Selected\n";
		return;
	}

	m_Childrens.erase(m_SelectedEntity.entity);
	m_SelectedEntity.entity = m_Childrens.end();
}

void Map::MoveSelectedEntity(const olc::vf2d dir)
{
	if (m_SelectedEntity.entity == m_Childrens.end()) return;

	(*m_SelectedEntity.entity)->SetPos((*m_SelectedEntity.entity)->GetPos() + dir * 500.0f);
}

void Map::Draw()
{
	for (auto& c : m_Childrens)
	{
		auto drawable = c->GetDrawable();
		m_MainCamera.DrawShape(drawable);
	}
}


// Setters


// Getters

float Map::GetWidth() const { return m_Width; }
float Map::GetHeight() const { return m_Height; }

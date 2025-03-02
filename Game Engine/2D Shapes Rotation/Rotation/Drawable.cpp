#include "Drawable.h"

Drawable::Drawable(const std::vector<olc::vf2d> &model, olc::Pixel col) : m_Translation(0.0f, 0.0f), m_Scale_x(1.0f), m_Scale_y(1.0f), m_Col(col), m_Model(&model)
{
}

void Drawable::Translate(const olc::vf2d& translation_in)
{
	m_Translation += translation_in;
}

void Drawable::Scale(float scale_in)
{
	m_Scale_x *= scale_in;
	m_Scale_y *= scale_in;
	m_Translation *= scale_in;
}

void Drawable::ScaleIndependent(float scale_x_in, float scale_y_in)
{
	m_Scale_x *= scale_x_in;
	m_Scale_y *= scale_y_in;
	m_Translation.x *= scale_x_in;
	m_Translation.y *= scale_y_in;
}

void Drawable::Render(olc::PixelGameEngine *pge)
{
	sShape::DrawClosedPolyLine(pge, *m_Model, m_Translation, m_Scale_x, m_Scale_y, m_Col);
}


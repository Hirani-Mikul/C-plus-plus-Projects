#pragma once

#include "CoordinateTransformer.h"

class Camera {

public: 

	Camera(CoordinateTransformer& ct) : ct{ ct }, m_position{ 0.0f, 0.0f }, m_scale{ 1.0f } {  }


	void Draw(Drawable&& d) const {
	
		d.Translate(-m_position);
		d.Scale(m_scale);

		ct.drawEntity(d);
	}

	// Getters
	olc::vf2d getPosition() const { return m_position; }
	float getScale() const { return m_scale; }

	// Setters

	void moveTo(const olc::vf2d& pos_in) { m_position = pos_in; }
	void moveBy(const olc::vf2d& pos_in) { m_position += pos_in; }

	void setScale(float scale_in) { m_scale = scale_in; }

private:
	CoordinateTransformer& ct;

	olc::vf2d m_position;
	float m_scale;
};

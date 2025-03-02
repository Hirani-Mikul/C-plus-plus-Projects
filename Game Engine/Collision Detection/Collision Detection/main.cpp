#include "cShapes.h"

float fWidth = 0.0f;
float fHeight = 0.0f;

class Collision : public olc::PixelGameEngine
{
public: 
	Collision()
	{
		sAppName = "Collision Detection";
	}

private:
	std::list<cShapes* > polygons;

	std::pair<olc::vf2d, olc::vf2d> vGround;

	olc::vf2d vGravity;

public:
	bool OnUserCreate () override {

		// Set global values of screen width and height
		fWidth = (float)ScreenWidth();
		fHeight = (float)ScreenHeight();

		vGround.first = { 0.0f, (float)ScreenHeight() - 10.0f }; // Ground Position
		vGround.second = {(float)ScreenWidth(), 10.0f }; // Ground Dimensions

		// Gravity
		vGravity = { 0.0f, 200.0f };

		return true;
	}

	void addPolygons(olc::vf2d &vMouse) {

		if (GetKey(olc::Key::SPACE).bPressed)
		{
			float r = (float)(5 + rand() % 30);
			float m = (float)(1 + rand() % 3);

			polygons.push_back(new cShapes(vMouse, r, m));
		}
	}

	bool OnUserUpdate(float fElapsedTime) override {

		olc::vf2d vMouse = { (float)GetMouseX(), (float)GetMouseY() };

		addPolygons(vMouse);

		Clear(olc::VERY_DARK_GREY);

		if (polygons.size() > 0)
		{
			for (auto& s : polygons)
			{
				s->checkEdges(vGround, vGravity);
				s->update(fElapsedTime);
				s->display(this);
			}
		}

		// Draw Static Ground
		FillRect(vGround.first, vGround.second, olc::RED);

		return true;
	}
};

int main()
{
	Collision game;
	if (game.Construct(300, 300, 2, 2))
		game.Start();
}

void DrawShapeObjects(olc::PixelGameEngine *pge, const std::vector<olc::vf2d> &vecModelCoordinates, olc::vf2d pos, float angle = 0.04f, float scale = 1.0f, olc::Pixel col = olc::WHITE) {

	std::vector<olc::vf2d> vecTransformedCoordinates;
	int verts = vecModelCoordinates.size();
	vecTransformedCoordinates.resize(verts);

	// Rotate
	for (int i = 0; i < verts; i++)
	{
		// Rotate
		vecTransformedCoordinates[i].x = vecModelCoordinates[i].x * cosf(angle) - vecModelCoordinates[i].y * sinf(angle);
		vecTransformedCoordinates[i].y = vecModelCoordinates[i].x * sinf(angle) + vecModelCoordinates[i].y * cosf(angle);

		// Scale
		vecTransformedCoordinates[i].x *= scale;
		vecTransformedCoordinates[i].y *= scale;

		//Translate
		vecTransformedCoordinates[i].x += pos.x;
		vecTransformedCoordinates[i].y += pos.y;
	}

	// Draw
	for (int i = 0; i <= verts; i++)
	{
		int j = i + 1;
		pge->DrawLine(vecTransformedCoordinates[i % verts].x, vecTransformedCoordinates[i % verts].y, vecTransformedCoordinates[j % verts].x, vecTransformedCoordinates[j % verts].y, col);
	}




}; 

void limit(olc::vf2d &v, float max) {
	const float mSq = v.mag2();

	if (mSq > max * max)
	{
		v /= sqrt(mSq);
		v *= max;
	}
};

float dist(float x, float y, float ox, float oy) {
	return hypotf(ox - x, oy = y);
}
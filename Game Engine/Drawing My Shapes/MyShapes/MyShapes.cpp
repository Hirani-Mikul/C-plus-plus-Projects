/*
	NOT THE BEST METHOD

	BETTER ONES:
				-LINE RASTERIZATION RULES (ALIASED, WITHOUT MULTISAMPLING)
				- BRESENHAM'S LINE ALGORITHM

	
*/

#include "olcPixelGameEngine.h"

struct sShape;

struct sNode {
	sShape* parent;
	olc::vf2d pos;
};
struct sShape {
	std::vector<sNode> vecNodes;
	uint32_t nMaxNodes = 0;
	olc::Pixel col = olc::WHITE;

	virtual void DrawYourSelf(olc::PixelGameEngine* pge) = 0;

	sNode* GetNextNode()
	{

	}
};

struct sLine
{
	olc::vf2d vStart;
	olc::vf2d vEnd;

	void PlaceNextPoint(olc::vf2d vMouse) {
		vStart = vMouse;
	}

	void draw(olc::PixelGameEngine *pge) {

		float m = 0.0f;
		if (vEnd.x != vStart.x)
		{
			m = (vEnd.y - vStart.y) / (vEnd.x - vStart.x);
		}
		if (vEnd.x != vStart.x && std::abs(m) <= 1.0f)
		{
			if (vStart.x > vEnd.x)
			{
				std::swap(vStart, vEnd);
			}
			const float m = (vEnd.y - vStart.y) / (vEnd.x - vStart.x);
			// y = mx + c
			// c = y - mx
			const float c = vStart.y - (m * vStart.x);

			for (int x = (int)vStart.x; x <= (int)vEnd.x; x++)
			{
				const float y = (m * (float)x) + c;
				pge->Draw(x, (int)y, olc::YELLOW);
			}

		}
		else {
			if (vStart.y > vEnd.y)
			{
				std::swap(vStart, vEnd);
			}

			const float m2 = (vEnd.x - vStart.x) / (vEnd.y - vStart.y);
			const float c2 = vStart.x - m2 * vStart.y;

			for (int y = (int)vStart.y; y <= (int)vEnd.y; y++)
			{
				const float x = m2 * (float)y + c2;

				pge->Draw((int)x, y, olc::YELLOW);
			}
		}

		

	}
	void DrawPoint(olc::PixelGameEngine *pge) {
		pge->FillCircle(vStart, 2, olc::RED);
		pge->FillCircle(vEnd, 2, olc::RED);
	}
};

class cMyShape : public olc::PixelGameEngine
{
public:
	cMyShape()
	{
		sAppName = "Creating & Drawing Shapes";
	}

private:
	sLine* tempShape = nullptr;
	std::list<sLine*> listShapes;

public:

	bool OnUserCreate() override {

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {

		olc::vf2d vMouse = { (float)GetMouseX(), (float)GetMouseY() };

		Clear(olc::VERY_DARK_GREY);


		if (GetKey(olc::Key::L).bPressed)
		{
			tempShape = new sLine();

			tempShape->PlaceNextPoint(vMouse);
		}
		if (tempShape) tempShape->vEnd = vMouse;
		if (GetMouse(0).bPressed && tempShape)
		{
			tempShape->vEnd = vMouse;
			listShapes.push_back(tempShape);
			tempShape = nullptr;
		}
		if (tempShape)
		{
			DrawLine(tempShape->vStart, tempShape->vEnd, olc::WHITE);
			tempShape->DrawPoint(this);
		}

		if (listShapes.size() > 0)
		{
			for (auto& s : listShapes)
			{
				s->draw(this);
				s->DrawPoint(this);
			}
		}


		return true;
	}
};

int main()
{
	cMyShape draw;
	if (draw.Construct(600, 600, 1, 1))
		draw.Start();
}


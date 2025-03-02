#include "olcPixelGameEngine.h"


struct sShape;

struct sNode {
	sShape* parent;
	olc::vf2d pos;
};

struct sShape {
	std::vector<sNode> vecNodes;
	uint32_t nMaxNodes = 0;
	olc::Pixel col = olc::GREEN;

	static float fWorldScale;
	static olc::vf2d vWorldOffset;

	void WorldToScreen(const olc::vf2d& v, int& nScreenX, int& nScreenY)
	{
		nScreenX = (int)((v.x - vWorldOffset.x) * fWorldScale);
		nScreenY = (int)((v.y - vWorldOffset.y) * fWorldScale);
	}

	virtual void Draw(olc::PixelGameEngine* pge) = 0;

	sNode* GetNextNode(const olc::vf2d& p)
	{
		if (vecNodes.size() == nMaxNodes)
			return nullptr; // Shape complete 

		// else create new nodes and add to shapes node vector
		sNode n;
		n.parent = this;
		n.pos = p;
		vecNodes.push_back(n);
		return &vecNodes[vecNodes.size() - 1];
	}

	sNode* HitNode(olc::vf2d& p)
	{
		for (auto& n : vecNodes)
		{
			if ((p - n.pos).mag() < 0.01f)
				return &n;
		}

		return nullptr;
	}

	void DrawNodes(olc::PixelGameEngine* pge)
	{
		for (auto& n : vecNodes)
		{
			int sx, sy;
			WorldToScreen(n.pos, sx, sy);
			pge->FillCircle(sx, sy, 2, olc::RED);
		}
	}

};

float sShape::fWorldScale = 1.0f;
olc::vf2d sShape::vWorldOffset = { 0, 0 };

struct sLine : public sShape
{
	sLine()
	{
		nMaxNodes = 2;
		vecNodes.reserve(nMaxNodes);
	}
	void Draw(olc::PixelGameEngine* pge) override {
		int sx, sy, ex, ey;
		WorldToScreen(vecNodes[0].pos, sx, sy);
		WorldToScreen(vecNodes[1].pos, ex, ey);
		pge->DrawLine(sx, sy, ex, ey, col);
	}
};
struct sBox : public sShape
{
	sBox()
	{
		nMaxNodes = 2;
		vecNodes.reserve(nMaxNodes);
	}
	void Draw(olc::PixelGameEngine* pge) override {
		int sx, sy, ex, ey;
		WorldToScreen(vecNodes[0].pos, sx, sy);
		WorldToScreen(vecNodes[1].pos, ex, ey);
		pge->DrawRect(sx, sy, ex - sx, ey - sy, col);
	}
};
struct sCircle : public sShape
{
	sCircle()
	{
		nMaxNodes = 2;
		vecNodes.reserve(nMaxNodes);
	}
	void Draw(olc::PixelGameEngine* pge) override {

		float fRadius = (vecNodes[0].pos - vecNodes[1].pos).mag();
		int sx, sy, ex, ey;
		WorldToScreen(vecNodes[0].pos, sx, sy);
		WorldToScreen(vecNodes[1].pos, ex, ey);
		pge->DrawLine(sx, sy, ex, ey, col, 0xFF00FF00);
		pge->DrawCircle(sx, sy, fRadius * fWorldScale, col);
	}
};
struct sCurve : public sShape
{
	sCurve()
	{
		nMaxNodes = 3;
		vecNodes.reserve(nMaxNodes);
	}
	void Draw(olc::PixelGameEngine* pge) override {
		int sx, sy, ex, ey;

		if (vecNodes.size() < 3)
		{
			// can only draw line from first to second
			WorldToScreen(vecNodes[0].pos, sx, sy);
			WorldToScreen(vecNodes[1].pos, ex, ey);
			pge->DrawLine(sx, sy, ex, ey, col, 0xFF00FF00);
		}

		if (vecNodes.size() == 3)
		{
			// can only draw line from first to second
			WorldToScreen(vecNodes[0].pos, sx, sy);
			WorldToScreen(vecNodes[1].pos, ex, ey);
			pge->DrawLine(sx, sy, ex, ey, col, 0xFF00FF00);

			// CAN DRAW SECOND structural line
			WorldToScreen(vecNodes[1].pos, sx, sy);
			WorldToScreen(vecNodes[2].pos, ex, ey);
			pge->DrawLine(sx, sy, ex, ey, col, 0xFF00FF00);


			// Add bezier curve
			olc::vf2d op = vecNodes[0].pos;
			olc::vf2d np = op;

			for (float t = 0; t < 1.0f; t += 0.01f)
			{
				np = (1 - t) * (1 - t) * vecNodes[0].pos + 2 * (1 - t) * t * vecNodes[1].pos + t * t * vecNodes[2].pos;

				WorldToScreen(op, sx, sy);
				WorldToScreen(np, ex, ey);
				pge->DrawLine(sx, sy, ex, ey, col);
				op = np;
			}
		}
	
	}
};

class All : public olc::PixelGameEngine
{
public:
	All() {
		sAppName = "Shapes Polymorphism";
	}
private:
	olc::vf2d vOffset = { 0.0f, 0.0f };
	olc::vf2d vStartPan = { 0.0f, 0.0f };
	float fScale = 10.0f;
	float fGrid = 1.0f;

	// Shapes
	sShape* tempShape = nullptr;
	std::list<sShape* > listShapes;
	sNode* selectedNode = nullptr;

	int nTotalShapes = 0;

	olc::vf2d vCursor = { 0, 0 };
	
	bool bShowLog = false;

	void WorldToScreen (const olc::vf2d &v, int &nScreenX, int &nScreenY) {
		nScreenX = (int)((v.x - vOffset.x) * fScale);
		nScreenY = (int)((v.y - vOffset.y) * fScale);
	}

	void ScreenToWorld(int nScreenX, int nScreenY, olc::vf2d &v) {
	
		v.x = (float)(nScreenX) / fScale + vOffset.x;
		v.y = (float)(nScreenY) / fScale + vOffset.y;
	}

public:

	bool OnUserCreate() override {

		vOffset = { (float)(-ScreenWidth() / 2) / fScale, (float)(-ScreenHeight() / 2) / fScale };

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {

		olc::vf2d vMouse = { (float)GetMouseX(), (float)GetMouseY() };

		if (GetKey(olc::Key::SPACE).bPressed)
			bShowLog = !bShowLog;

		if (GetMouse(1).bPressed)
		{
			vStartPan = vMouse;
		}
		if (GetMouse(1).bHeld)
		{
			vOffset -= (vMouse - vStartPan) / fScale;

			vStartPan = vMouse;
		}
		if (GetKey(olc::Key::RIGHT).bHeld)
		{
			vOffset.x += 0.5f;
		} 
		if (GetKey(olc::Key::LEFT).bHeld)
		{
			vOffset.x -= 0.5f;
		}		
		if (GetKey(olc::Key::UP).bHeld)
		{
			vOffset.y -= 0.5f;
		}
		if (GetKey(olc::Key::DOWN).bHeld)
		{
			vOffset.y += 0.5f;
		}

		olc::vf2d vMouseBeforeZoom;
		ScreenToWorld((int)vMouse.x, (int)vMouse.y, vMouseBeforeZoom);

		if (GetKey(olc::Key::Z).bHeld || GetMouseWheel() > 0)
		{
			fScale *= 1.1f;
		}
		if (GetKey(olc::Key::X).bHeld || GetMouseWheel() < 0)
		{
			fScale *= 0.9f;
		}
		if (GetKey(olc::Key::NP_ADD).bPressed) fScale += 0.1f;
		if (GetKey(olc::Key::NP_SUB).bPressed) fScale -= 0.1f;
		olc::vf2d vMouseAfterZoom;
		ScreenToWorld((int)vMouse.x, (int)vMouse.y, vMouseAfterZoom);
		vOffset += (vMouseBeforeZoom - vMouseAfterZoom);

		vCursor.x = floorf((vMouseAfterZoom.x + .5f) * fGrid);
		vCursor.y = floorf((vMouseAfterZoom.y + .5f) * fGrid);

		if (GetKey(olc::Key::L).bPressed)
		{
			tempShape = new sLine();

			// Place first node at the location of keypress
			selectedNode = tempShape->GetNextNode(vCursor);

			// get second node
			selectedNode = tempShape->GetNextNode(vCursor);

		}
		if (GetKey(olc::Key::B).bPressed)
		{
			tempShape = new sBox();

			// Place first node at the location of keypress
			selectedNode = tempShape->GetNextNode(vCursor);

			// get second node
			selectedNode = tempShape->GetNextNode(vCursor);

		}
		if (GetKey(olc::Key::C).bPressed)
		{
			tempShape = new sCircle();

			// Place first node at the location of keypress
			selectedNode = tempShape->GetNextNode(vCursor);

			// get second node
			selectedNode = tempShape->GetNextNode(vCursor);

		}
		if (GetKey(olc::Key::S).bPressed)
		{
			tempShape = new sCurve();

			// Place first node at the location of keypress
			selectedNode = tempShape->GetNextNode(vCursor);

			// get second node
			selectedNode = tempShape->GetNextNode(vCursor);

		}

		if (GetKey(olc::Key::M).bPressed)
		{
			selectedNode = nullptr;

			for (auto& shape : listShapes)
			{
				selectedNode = shape->HitNode(vCursor);
				if (selectedNode != nullptr)
					break;
			}
		}

		if (selectedNode != nullptr)
		{
			selectedNode->pos = vCursor;
		}

		if (GetMouse(0).bReleased)
		{
			if (tempShape != nullptr) {
				selectedNode = tempShape->GetNextNode(vCursor);
				if (selectedNode == nullptr)
				{
					tempShape->col = olc::WHITE;
					listShapes.push_back(tempShape);
					nTotalShapes++;
				}
			}
		}

		// Clear screen
		Clear(olc::VERY_DARK_GREY);

		int sx, sy;
		int ex, ey;

		// Get visible world
		olc::vf2d vWorldTopLeft, vWorldBottomRight;
		ScreenToWorld(0, 0, vWorldTopLeft);
		ScreenToWorld(ScreenWidth(), ScreenHeight(), vWorldBottomRight);

		vWorldTopLeft.x = floor(vWorldTopLeft.x);
		vWorldTopLeft.y = floor(vWorldTopLeft.y);
		vWorldBottomRight.x = ceil(vWorldBottomRight.x);
		vWorldBottomRight.y = ceil(vWorldBottomRight.y);

		// Draw cursor
		WorldToScreen(vCursor, sx, sy);
		DrawCircle(sx, sy, 3, olc::YELLOW);

		int nLineDrawn = 0;
		int nLineDrawnX = 0;

		for (float x = vWorldTopLeft.x; x < vWorldBottomRight.x; x += fGrid)
		{
			for (float y = vWorldTopLeft.y; y < vWorldBottomRight.y; y += fGrid)
			{
				WorldToScreen({ x, y }, sx, sy);
				Draw(sx, sy, olc::BLUE);
				nLineDrawn++;
			}
			nLineDrawnX++;
		}
		// Draw World Axis
		// VERTICLE
		WorldToScreen({ 0, vWorldTopLeft.y }, sx, sy);
		WorldToScreen({ 0, vWorldBottomRight.y }, ex, ey);
		DrawLine(sx, sy, ex, ey, olc::GREY, 0xF0F0F0F0);

		// HORIZONTAL
		WorldToScreen({ vWorldTopLeft.x, 0 }, sx, sy);
		WorldToScreen({ vWorldBottomRight.x, 0 }, ex, ey);
		DrawLine(sx, sy, ex, ey, olc::GREY, 0xF0F0F0F0);

		// Update shape translation coefficients
		sShape::fWorldScale = fScale;
		sShape::vWorldOffset = vOffset;

		for (auto& shape : listShapes)
		{
			shape->Draw(this);
			shape->DrawNodes(this);
		}

		if (tempShape != nullptr)
		{
			tempShape->Draw(this);
			tempShape->DrawNodes(this);
		}

		if (bShowLog)
		{;
			DrawString(5, 5, "Line Drawn: (" + std::to_string(nLineDrawnX) + ", " + std::to_string( nLineDrawn / nLineDrawnX) + "): " + std::to_string(nLineDrawn), olc::YELLOW);
			DrawString(5, 20, "Zoom Level: " + std::to_string((int)(fScale * 10)) + "%", olc::YELLOW);

			DrawString(5, 35, "Total Shapes: " + std::to_string(nTotalShapes), olc::YELLOW);

			// Cursor Position
			DrawString(5, 50, "X: " + std::to_string(vCursor.x) + ", Y: " + std::to_string(vCursor.y), olc::YELLOW);
		}

		return true;
	}
};

int main() {

	All draw;
	if (draw.Construct(600, 600, 1, 1))
		draw.Start();
}


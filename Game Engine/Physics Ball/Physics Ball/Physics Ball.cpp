#include "Player.h"

class Game : public olc::PixelGameEngine {

public: 
	Game() {
		sAppName = "Ball Game";
	}

private:
	Player p;
	olc::vf2d Ground;
	std::vector<std::pair<olc::vf2d, olc::vf2d>> Surfaces;
	//std::vector<olc::Pixel> cols = { olc::RED, olc::YELLOW, olc::GREEN, olc::BLUE };
	olc::vf2d gravity = { 0.0f, 200.0f };

	std::vector<olc::vf2d> vecModel;

	float fSurfaceWidth = 10.0f;
public:

	bool OnUserCreate() override {
		olc::vf2d pos = { 0.0f, 0.0f };
		olc::vf2d pSize = { 0.0f, 0.0f };
		// LEFT WALL
		Surfaces.push_back(std::make_pair(olc::vf2d{ 0.0f, 0.0f }, olc::vf2d{ fSurfaceWidth ,(float)ScreenHeight()}));

		// TOP WALL
		Surfaces.push_back(std::make_pair(olc::vf2d{ fSurfaceWidth, 0.0f }, olc::vf2d{ (float)ScreenWidth() - fSurfaceWidth * 2 , fSurfaceWidth }));


		// RIGHT WALL
		Surfaces.push_back(std::make_pair(olc::vf2d{ (float)ScreenWidth() - fSurfaceWidth, 0.0f }, olc::vf2d{ fSurfaceWidth ,(float)ScreenHeight() }));

		// GROUND WALL
		Surfaces.push_back(std::make_pair(olc::vf2d{ fSurfaceWidth, (float)ScreenHeight() - fSurfaceWidth }, olc::vf2d{ (float)ScreenWidth() - fSurfaceWidth * 2 , fSurfaceWidth }));
		Ground = { (float)ScreenWidth() - fSurfaceWidth * 2, fSurfaceWidth };

		int verts = 20;

		for (int i = 0; i < verts; i++)
		{
			float radius = 1.0f;
			float angle = ((float)i / (float)verts) * 6.28318f;
			vecModel.push_back({radius * sinf(angle), radius * cosf(angle)});
		}

		p = Player(vecModel, 100.0f, 100.0f, 10.0f, 150.0f);

		return true;
	}

	void drawSurfaces() {
		for (int i = 0; i < Surfaces.size(); i++)
		{
			FillRect(Surfaces[i].first, Surfaces[i].second, olc::RED);
		}
	}

	bool OnUserUpdate(float fElapsedTime) override {

		Clear(olc::VERY_DARK_GREY);


		// Player
		p.move(*this);
		p.checkEdges(Surfaces);


		p.applyForce(gravity);
		p.update(fElapsedTime);
		p.display(*this);

		// Static Ground
		//FillRect(Ground, olc::vf2d{ (float)ScreenWidth(), 10.0f }, olc::RED);
		drawSurfaces();
		return true;
	}
};

int main() {

	Game demo;
	if (demo.Construct(300, 300, 2, 2))
		demo.Start();
}



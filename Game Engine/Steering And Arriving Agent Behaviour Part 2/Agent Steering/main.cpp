#include "Agent.h"

void DrawWireFrameModel(olc::PixelGameEngine &pge, std::vector<olc::vf2d> &vecModelCoordinates, olc::vf2d pos, float angle = 0.04f, float scale = 1.0f, olc::Pixel col = olc::WHITE) {
	
	std::vector<olc::vf2d> vecTransformedCoordinates;

	int verts = vecModelCoordinates.size();

	vecTransformedCoordinates.resize(verts);

	/*angle = atan2(position.x, position.y);*/


	// Rotate
	for (int i = 0; i < verts; i++)
	{
		vecTransformedCoordinates[i].x = vecModelCoordinates[i].x * cosf(angle) - vecModelCoordinates[i].y * sinf(angle);
		vecTransformedCoordinates[i].y = vecModelCoordinates[i].x * sinf(angle) + vecModelCoordinates[i].y * cosf(angle);
	}

	// Scale

	for (int i = 0; i < verts; i++)
	{
		vecTransformedCoordinates[i].x *= scale;
		vecTransformedCoordinates[i].y *= scale;
	}

	// Translate

	for (int i = 0; i < verts; i++)
	{
		vecTransformedCoordinates[i].x += pos.x;
		vecTransformedCoordinates[i].y += pos.y;
	}

	// Draw

	for (int i = 0; i < verts + 1; i++)
	{
		int j = (i + 1);

		pge.DrawLine(vecTransformedCoordinates[i % verts].x, vecTransformedCoordinates[i % verts].y, vecTransformedCoordinates[j % verts].x, vecTransformedCoordinates[j % verts].y, col);
	}

}


void limit(olc::vf2d& v, float max) {
	//const float mSq = ((v.x * v.x) + (v.y * v.y));
	const float mSq = v.mag2();


	if (mSq > max * max)
	{
		//v.x = (v.x / sqrt(mSq)) * max;
		//v.y = (v.y / sqrt(mSq)) * max;
		v /= sqrt(mSq);
		v *= max;
	}
};

class Game : public olc::PixelGameEngine {

public:
	Game() {
		sAppName = "Steering Agent";
	}

private:
	
	float fRadius = 200.0f;

	Agent player;
	std::vector<Agent> players;

	// Models
	std::vector<olc::vf2d> vecAgentModel;
	std::vector<olc::vf2d> vecCircularPathModel;
	olc::vf2d circularPath;

public:

	bool OnUserCreate() override {
		float sW = (float)ScreenWidth();
		float sH = (float)ScreenHeight();

		players.reserve(5);

		circularPath = { (float)ScreenWidth() / 2.0f, (float)ScreenHeight() / 2.0f };


		// Path Model
		
		int verts = 20;

		for (int i = 0; i < verts; i++)
		{
			float fAngle = ((float)i / (float)verts) * 6.28318f;
			vecCircularPathModel.push_back({fRadius * sinf(fAngle), fRadius * cosf(fAngle)});
		}

		// Agent Model
		vecAgentModel = {
			{ 0.0f, -5.0f },
			{ -2.5f, +2.5f },
			{ +2.5f, +2.5f }
		}; // Isoceles Triangle

		//player = Agent(vecAgentModel, { (float)ScreenWidth() / 2.0f, (float)ScreenHeight() / 2.0f }, 1.0f);


		for (int i = 0; i < 5; i++)
		{
			float dir;
			if (i % 2 == 0)
				dir = -1.0f;
			else dir = 1.0f;
			float x = rand() % 500;
			float y = rand() % 500;
			std::cout << x << ", " << y << std::endl;

			players.emplace_back(Agent(vecAgentModel, { x, y }, dir));
		}

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {

		Clear(olc::VERY_DARK_GREY);

		//player.checkEdges(circularPath, *this);
		//player.update(fElapsedTime);
		//player.display(*this);

		for (auto& p : players)
		{
			p.checkEdges( circularPath, *this);
			p.update(fElapsedTime);
			p.display(*this);
		}

		// Draw Path
		DrawWireFrameModel(*this, vecCircularPathModel, circularPath, 0.04f, 1.0f, olc::BLUE);

		return true;
	}

};

int main()
{
	Game demo;
	if (demo.Construct(600, 600, 1, 1))
		demo.Start();
}
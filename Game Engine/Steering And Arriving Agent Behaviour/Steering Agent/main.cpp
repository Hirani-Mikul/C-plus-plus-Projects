#include "Vehicle.h"

class Agent : public olc::PixelGameEngine {

	Vehicle driver;

public:
	Agent() {
		sAppName = "Autonomous Agent Steering And Arriving";
	}

	bool OnUserCreate() override {

		driver = Vehicle(300.0f, 300.0f, float(ScreenWidth()), float(ScreenHeight()));
		return true;
	}
	bool OnUserUpdate(float fElapsedTime) override {
		
		Clear(olc::VERY_DARK_GREY);

		driver.update();
		driver.checkEdges(*this);
		return true;
	}
};

int main() {
	Agent agent;
	if (agent.Construct(600, 600, 1, 1))
		agent.Start();

}
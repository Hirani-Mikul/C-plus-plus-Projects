#include <iostream>
#include "ParticleSystem.h"
class Everything : public olc::PixelGameEngine {
private:
	ParticleSystem ps;
	//Particle1 p;
public:
	Everything() {

		sAppName = "Particle System";
	}

public:

	bool OnUserCreate() override {

		//p = Particle1(olc::vd2d{floor(ScreenWidth() / 2), 20.0f }, 10.0f);
		ps = ParticleSystem(olc::vd2d{float(ScreenWidth() / 2), 30.0f});
		return true;
	}
	bool OnUserUpdate(float fElapsedTime) override {

		Clear(olc::GREY);
		//p.run(fElapsedTime, this);
		ps.addParticles();
		ps.update(fElapsedTime, this);
		return true;
	}

};

int main() {

	Everything P;
	
	if (P.Construct(600, 600, 1, 1))
		P.Start();


	//system("pause>0");
	return 0;
}
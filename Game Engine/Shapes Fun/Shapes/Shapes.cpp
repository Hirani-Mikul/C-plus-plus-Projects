#include "olcPixelGameEngine.h"

class Circle {
public:
	olc::vf2d position;
	olc::vf2d velocity;
	olc::vf2d acceleration;
	float radius;
	float angle;
	
public:
	Circle() : position{ 0.0f, 0.0f }, velocity{ 100.0f, 0.0f }, acceleration{ 60.0f, 0.0f }, radius(5.0f), angle(0.0f) {};
	Circle(float x, float y, float r) : position(x, y), velocity(100.0f, 0.0f), acceleration(60.0f, 0.0f), radius(r), angle(0.0f) {};

	void display(olc::PixelGameEngine& pge) {
		pge.FillCircle(position, int(radius), olc::GREEN);
	}
	void update(float fElapsedTime) {
		/*velocity += acceleration * fElapsedTime;
		if (velocity.x > 60.0f || velocity.y > 60.0f)
		{
			velocity.x = 60.0f;
			velocity.y = 0.0f;
		}*/
		position += velocity * fElapsedTime;
		//acceleration *= 0;
	}
	void checkEdges() {
		if (position.x <= radius || position.x + radius>= 300.0f)
			velocity.x *= -1;
		if (position.y <= 0 || position.y >= 300.0f)
			velocity.y *= -1;
	}

};

class Shape : public olc::PixelGameEngine {

public: 
	Shape() {
		sAppName = "Shapes";
	}

private:
	Circle c1;

public:
	bool OnUserCreate() override {

		c1 = Circle((float)ScreenWidth() / 2, (float)ScreenHeight() / 2, 20.0f);

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {

		Clear(olc::VERY_DARK_GREY);
		c1.display(*this);
		c1.checkEdges();
		c1.update(fElapsedTime);

		return true;
	}

};

int main() {

	Shape demo;
	if (demo.Construct(300, 300, 2, 2))
		demo.Start();
}
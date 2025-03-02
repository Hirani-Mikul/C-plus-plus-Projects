#include "Objects.h"

float fWidth, fHeight;

template<typename T>
auto sq(T x)
{
	return x * x;
}
template<typename T>
T DistancePointLine(const T& p0, const T& p1, const T& q)
{
	const T a = p0.y - p1.y;
	const T b = p1.x - p0.x;
	const T c = p0.x * p1.y - p1.x * p0.y;

	return std::abs(a * q.x + b * q.y + c) / std::sqrt(sq(a) + sq(b));
}
float DistancePointLine2(const olc::vf2d &p0, const olc::vf2d &p1, const olc::vf2d &q)
{
	float a = p0.y - p1.y;
	float b = p1.x - p0.x;
	float c = p0.x * p1.y - p1.x * p0.y;

	return std::abs(a * q.x + b * q.y + c) / std::sqrtf(sq(a) + sq(b));
}

class Game : public olc::PixelGameEngine {

public:
	Game() {
		sAppName = "Ball Stuff";
	}

private:

	CoordinateTransformer ct = CoordinateTransformer(this);

	Plank p = Plank({-100.0f, -100.0f}, 300.0f, 15.0f, olc::YELLOW);
	Ball b = Ball({0.0f, 0.0f}, 20.0f, 20.0f, olc::MAGENTA);

public:
	
	bool OnUserCreate() override {

		fWidth = (float)ScreenWidth();
		fHeight = (float)ScreenHeight();

		return true;
	}

	void movePlank(float fElapsedTime) {
		if (GetKey(olc::Key::UP).bHeld)
			p.MovePlank(fElapsedTime, -1.0f);
		if (GetKey(olc::Key::DOWN).bHeld)
			p.MovePlank(fElapsedTime, 1.0f);
	}

	bool OnUserUpdate(float fElapsedTime) override {

		Clear(olc::VERY_DARK_GREY);

		//const auto plankPts = p.GetPoints();

		const std::pair<olc::vf2d, olc::vf2d> plan = p.GetPoints();

		//std::cout << "1: ( " << plan.first.x << ", " << plan.first.y << " ), 2: ( " << plan.second.x << ", " << plan.second.y << " )" << std::endl;

		movePlank(fElapsedTime);
		p.display(&ct);
		b.display(&ct);
		b.update(fElapsedTime);

		float d = DistancePointLine2(plan.first, plan.second, b.GetPos());

		//std::cout << d << std::endl;

		if (DistancePointLine2(plan.first, plan.second, b.GetPos()) <= b.radius)
		{
			const olc::vf2d w = p.GetPlankSurface().norm();
			const olc::vf2d v = b.GetVel();

			b.SetVel(w * (v * w) * 2.0f - v);
		}

		return true;
	}

};

int main()
{
	Game app;
	if (app.Construct(600, 600, 1, 1))
		app.Start();
}

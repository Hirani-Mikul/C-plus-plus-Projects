#include "Entity.h"
#include "Ball.h"
#include "Plank.h"
#include "Polygon.h"
#include "CameraControl.h"

float fWidth, fHeight;

class Game : public olc::PixelGameEngine
{

public:
	Game() {
		sAppName = "Circle Collision Detection";
	}

private:
	CoordinateTransformer ct = CoordinateTransformer(this);
	Camera cam = Camera(ct);
	CameraControl camCtrl = CameraControl(*this, cam);

	olc::vf2d cursor = { 0.0f, 0.0f };

	std::vector<Ball> balls;
	Ball* bSelectedBall = nullptr;
	olc::Pixel cols[5] = { olc::RED, olc::CYAN, olc::YELLOW, olc::BLUE, olc::GREEN };

	Plank plank1 = Plank({0.0f, 0.0f}, 20.0f, 200.0f, olc::MAGENTA);



public:

	void AddBall( float x, float y, float r ) {

		int randIndex = rand() % 4;

		Ball b = Ball({x, y}, r, cols[randIndex]);
		b.SetId(balls.size());
		balls.emplace_back(b);
	}

	bool OnUserCreate() override {

		fWidth = (float)ScreenWidth();
		fHeight = (float)ScreenHeight();
		


		//AddBall(0.0f, 0.0f, 30.0f);
		//AddBall(100.0f, 100.0f, 40.0f);
		//AddBall(-100.0f, -100.0f, 20.0f);
		//AddBall(-300.0f, 300.0f, 80.0f);
		//AddBall(-100.0f, 100.0f, 100.0f);

		for (int i = 0; i < 10; i++)
		{
			const float x = (float)(rand() % 1200 - 600);
			const float y = (float)(rand() % 1200 - 600);
			const float r = (float)(rand() % 100 + 50);
			AddBall(x, y, r);
		}
		AddBall( 800.0f, 800.0f, 1000.0f );
		balls[balls.size() - 1].bIsStatic = true;

		return true;
	}

	float Dist(olc::vf2d p1, olc::vf2d p2) {
		return sqrtf( (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) );
	};

	void CheckBallCollision(float fElapsedTime) {

		std::vector<std::pair<Ball*, Ball*>> vecCollidingPairs;

		int nSimulationUpdates = 4;

		float fSimElpasedTime = fElapsedTime / (float)nSimulationUpdates;

		int nMaxSimulationSteps = 15;

		for (int i = 0; i < nSimulationUpdates; i++)
		{

			for (auto& b : balls)
				b.SetSimTime(fSimElpasedTime);

			for (int j = 0; j < nMaxSimulationSteps; j++)
			{


				auto DoCircleOverlaps = [](olc::vf2d c1, olc::vf2d c2, float r1, float r2)
				{
					return fabs((c1.x - c2.x) * (c1.x - c2.x) + (c1.y - c2.y) * (c1.y - c2.y)) <= (r1 + r2) * (r1 + r2);
				};

				for (auto& b : balls)
				{
					if (b.GetSimTime() > 0.0f)
					{
						b.SetLastPosition(b.GetPos());

						b.Update(b.GetSimTime());
					}
					olc::vf2d pb = b.GetPos(); // ball position
					float rb = b.GetRadius(); // ball radius

					for (auto& target : balls)
					{
						olc::vf2d pt = target.GetPos(); // target ball position
						float rt = target.GetRadius(); // target ball radius

						if (b.GetId() != target.GetId())
						{
							if (DoCircleOverlaps(pb, pt, rb, rt))
							{
								vecCollidingPairs.push_back({ &b, &target });

								// Calculate the distance between two balls PYTHAGORUS THEOREM

								float fDistance = Dist(pb, pt);

								float fOverlap = 0.5f * (fDistance - rb - rt);

								// Displace current ball
								olc::vf2d offset = fOverlap * (pb - pt) / fDistance;
								b.SetPos(pb -= offset);

								// Displace target ball
								target.SetPos(pt += offset);
							}

						}
					}

					float fIntendedSpeed = sqrtf(pb.x * pb.x + pb.y * pb.y);
					float fIntendedDistance = fIntendedSpeed * b.GetSimTime();

					olc::vf2d lpb = b.GetLastPosition(); // Old position

					float fActualDistance = sqrtf((pb.x - lpb.x) * (pb.x - lpb.x) + (pb.y - lpb.y) * (pb.y - lpb.y));

					float fActualTime = fActualDistance / fIntendedSpeed;

					b.SetSimTime( b.GetSimTime() - fActualTime );

				}

				// Working out dynamic collisions
				for (auto c : vecCollidingPairs)
				{
					Ball* b1 = c.first;
					Ball* b2 = c.second;

					// Get Position
					olc::vf2d pb1 = b1->GetPos();
					olc::vf2d pb2 = b2->GetPos();

					// Get Velocity
					olc::vf2d vb1 = b1->GetVelocity();
					olc::vf2d vb2 = b2->GetVelocity();

					// Get Masses
					float mb1 = b1->GetMass();
					float mb2 = b2->GetMass();

					// Distance between balls
					float fDistance = Dist(pb1, pb2);

					// Normal
					olc::vf2d normal = (pb2 - pb1) / fDistance;

					// Dot product normal
					float dpNorm1 = vb1.dot(normal);
					float dpNorm2 = vb2.dot(normal);

					// Wikipedia Version - Maths is smarter but same ( CONSERVATION OF MOMENTUM IN 1D)

					// ELASTIC COLLISION

					olc::vf2d k = vb1 - vb2;
					float totalMass = mb1 + mb2;
					float p = 2.0 * (normal.dot(k)) / totalMass;
					olc::vf2d vel1 = vb1 - normal * p * mb2;
					olc::vf2d vel2 = vb2 + normal * p * mb1;

					b1->SetVelocity(vel1);

					if (!b2->bIsStatic)
						b2->SetVelocity(vel2);

					else b2->SetVelocity({ 0.0f, 0.0f });
				}
			}
		}
		// Draw Line between two collided balss

		for (auto c : vecCollidingPairs)
		{
			Entity eLine = Entity(sLine::Make(c.first->GetPos(), c.second->GetPos()), { 0.0f, 0.0f }, 1.0f, olc::RED);
			Drawable ed = eLine.GetDrawable();
			cam.DrawShape(ed);
		}

		for (auto& b : balls)
		{
			Drawable bd = b.GetDrawable();
			cam.DrawShape(bd);
		}
	}

	void SelectBall(olc::vf2d mouse ) {

		cam.TranslateCursorCoordinates( mouse, cursor );

		auto IsPointInCircle = [](olc::vf2d p1, olc::vf2d p2, float r) {
		
			return fabs( (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)) < (r * r);

		};

		if (GetMouse(1).bPressed || GetKey(olc::Key::SPACE).bPressed)
		{
			bSelectedBall = nullptr;
			for (auto& b : balls)
			{
				if (IsPointInCircle(b.GetPos(), cursor, b.GetRadius()))
				{
					if (!b.bIsStatic)
					{
						bSelectedBall = &b;
					}
					break;
				}
			}
		}

		if (GetMouse(1).bHeld)
		{
			if (bSelectedBall)
			{
				bSelectedBall->SetPos(cursor);
			}
		}

		if (GetMouse(1).bReleased) 
		{
			bSelectedBall = nullptr;
		}
		if (GetKey(olc::Key::SPACE).bReleased)
		{
			if (bSelectedBall)
			{
				olc::vf2d newVel = 5.0f * (bSelectedBall->GetPos() - cursor);
				bSelectedBall->SetVelocity( newVel );
			}
			bSelectedBall = nullptr;
		}

	}

	bool OnUserUpdate(float fElapsedTime) override {

		olc::vf2d vMouse = { (float)GetMouseX(), (float)GetMouseY() };

		Clear(olc::VERY_DARK_GREY);

		camCtrl.update();

		SelectBall(vMouse);
		CheckBallCollision(fElapsedTime);

		

		FillCircle(vMouse, 2.0f, olc::RED);

		if (bSelectedBall)
		{
			Entity eLine = Entity(sLine::Make(bSelectedBall->GetPos(), cursor), { 0.0f, 0.0f }, 1.0f, olc::BLUE);
			Drawable ed = eLine.GetDrawable();
			cam.DrawShape(ed);
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



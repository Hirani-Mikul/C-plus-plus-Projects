#include "CoordinateTransformer.h"
#include "CameraController.h"
#include "Polygon.h"
#include "MyMath.h"
float fWidth, fHeight;

class Game : public olc::PixelGameEngine {

public:
    Game() {
        sAppName = "Shape Collision With Dot Product";
    }

private:
    CoordinateTransformer ct = CoordinateTransformer(this);
    Camera cam = Camera(ct);
    CameraController camCtrl = CameraController(*this, cam);


    Entity camCenter = Entity(Rectangle::Make(), { 0.0f, 0.0f }, fWidth, olc::BLUE);
    Entity camCenterDot = Entity(Circle::Make(20), { 0.0f, 0.0f }, 4.0f, olc::YELLOW);

    Plank p1 = Plank({ 100.0f, 200.0f }, -380.0f, -200.0f, 240.0f, 10.0f, olc::RED); // Random

    std::vector<Plank> planks;


    Ball b = Ball({ 0.0f, 0.0f }, 15.0f, {0.0f, 160.0f}, olc::GREEN);


public:

    bool OnUserCreate() override {

        fWidth = (float)ScreenWidth();
        fHeight = (float)ScreenHeight();
        planks.reserve(4);

        planks.emplace_back(Plank({ -300.0f, 300.0f }, 300.0f, 300.0f, -300.0f, 10.0f, olc::RED)); // Top

        planks.push_back(Plank({ 300.0f, -300.0f }, 300.0f, 0.0f, 300.0f, 10.0f, olc::RED)); // Right
        planks.push_back(Plank({ -300.0f, -300.0f }, -300.0f, 0.0f, 300.0f, 10.0f, olc::RED)); // Left

        planks.emplace_back(Plank({ -300.0f, -300.0f }, 300.0f, -300.0f, 300.0f, 10.0f, olc::RED)); // Bottom


        return true;
    }

    void MovePlank() {

        if (GetKey(olc::Key::UP).bHeld)
        {
            //planks[1].MoveFreeY(2.0f);
            //planks[2].MoveFreeY(2.0f);
            p1.MoveFreeY(2.0f);

        }
        if (GetKey(olc::Key::DOWN).bHeld)
        {
            p1.MoveFreeY(-2.0f);
            //planks[1].MoveFreeY(-2.0f);
            //planks[2].MoveFreeY(-2.0f);
        }


        

    }
    void UpdateBall(float fElapsedTime) {

        if (b.GetPos().y > 400.0f || GetKey(olc::Key::SPACE).bPressed)
        {
            b.SetPos({ 0.0f, 0.0f });

            olc::vf2d newVel = { (float)(rand() % 140 + -90), 160.0f  };
            b.SetVel(newVel);
        }

        if (GetKey(olc::Key::SHIFT).bPressed)
            b.SetVel(b.GetVel() * 1.5f);

        b.update(fElapsedTime);
    }
    void BounceBall() {

        const auto plankPts = p1.GetPoints();
        const auto dy = plankPts.second.y - plankPts.first.y;
        const auto dx = plankPts.second.x - plankPts.first.x;
        const auto ballPos = b.GetPos();

        olc::vf2d plankNormal;

        if (dy == 0.0f)
        {
            plankNormal = { 0.0f, ballPos.y > plankPts.first.y ? 1.0f : -1.0f };
        }
        else if (dx == 0.0f)
        {
            plankNormal = { 0.0f, ballPos.x > plankPts.first.x ? 1.0f : -1.0f };
        }
        else {
            const auto m = dy / dx;
            const auto w = -dx / dy;
            /*const auto c = m * plankPts.first.x - plankPts.first.y;*/
            //const auto p = w * ballPos.x - ballPos.y;
            const auto c = plankPts.first.y - m * plankPts.first.x;

            const auto p = ballPos.y - w * ballPos.x;
            const auto x = (p - c) / (m - w);
            const auto y = m * x + c;
            plankNormal = ballPos - olc::vf2d(x, y);
        }
        if (plankNormal.dot(b.GetVel()) < 0.0f)
        {
            if (DistancePointLine(plankPts.first, plankPts.second, b.GetPos()) < b.GetRadius())
            {
                const olc::vf2d w = p1.GetPlankSurfaceVector().norm();
                const olc::vf2d v = b.GetVel();

                const float d1 = v.dot(w);
                const olc::vf2d d2 = w * d1;

                const olc::vf2d newVel = d2 * 2.0f - v;

                b.SetVel(newVel);
            }
        }




    }
    bool OnUserUpdate(float fElapsedTime) override {

        Clear(olc::VERY_DARK_GREY);

        camCtrl.update(); // Controls camera movement and scaling

        UpdateBall(fElapsedTime);

        MovePlank();
        BounceBall();
       /* for (auto& p : planks)
        {
            const auto plankPts = p.GetPoints();
            const auto dy = plankPts.second.y - plankPts.first.y;
            const auto dx = plankPts.second.x - plankPts.first.x;
            const auto ballPos = b.GetPos();

            olc::vf2d plankNormal;

            if (dy == 0.0f)
            {
                plankNormal = { 0.0f, ballPos.y > plankPts.first.y ? 1.0f : -1.0f };
            }
            else if (dx == 0.0f)
            {
                plankNormal = { 0.0f, ballPos.x > plankPts.first.x ? 1.0f : -1.0f };
            }
            else {
                const auto m = dy / dx;
                const auto w = -dx / dy;
                const auto c = m * plankPts.first.x - plankPts.first.y;

                const auto p = w * ballPos.x - ballPos.y;
                const auto x = (p - c) / (m - w);
                const auto y = m * x + c;
                plankNormal = ballPos - olc::vf2d(x, y);
            }

            if (plankNormal.dot(b.GetPos()) < 0.0f)
            {


                if (DistancePointLine(plankPts.first, plankPts.second, b.GetPos()) < b.GetRadius())
                {
                    const olc::vf2d w = p.GetPlankSurfaceVector().norm();
                    const olc::vf2d v = b.GetVel();

                    const float d1 = v.dot(w);
                    const olc::vf2d d2 = w * d1;

                    const olc::vf2d newVel = d2 * 2.0f - v;

                    b.SetVel(newVel);
                }
            }


            Drawable pd = p.GetDrawable();
            cam.DrawShape(pd);
        }*/

        Drawable p1d = p1.GetDrawable();
        cam.DrawShape(p1d);

        Drawable bd = b.GetDrawable();
        cam.DrawShape(bd);

        olc::vf2d camCenterPos = { cam.GetPos().x - camCenter.GetRadius() / 2.0f, cam.GetPos().y - camCenter.GetRadius() / 2.0f };
        camCenter.SetPos(camCenterPos);
        camCenter.SetRadius(fWidth * cam.GetScale());
        Drawable camCenterD = camCenter.GetDrawable();
        cam.DrawShape(camCenterD);

        camCenterDot.SetPos(cam.GetPos());
        Drawable cmdd = camCenterDot.GetDrawable();
        cam.DrawShape(cmdd);


        //cam.FollowEntity(current->GetPos());
        return true;
    }
};



int main()
{
    Game app;
    if (app.Construct(600, 600, 1, 1))
        app.Start();

}

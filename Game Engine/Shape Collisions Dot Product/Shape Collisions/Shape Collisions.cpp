//#include "CoordinateTransformer.h"
//#include "CameraController.h"
//#include "Polygon.h"
//
//float fWidth, fHeight;
//
//class Game : public olc::PixelGameEngine {
//
//public: 
//    Game() {
//        sAppName = "Shape Collision With Dot Product";
//    }
//
//private:
//    CoordinateTransformer ct = CoordinateTransformer(this);
//    Camera cam = Camera(ct);
//    CameraController camCtrl = CameraController(*this, cam);
//
//    int nTotalEntities;
//
//    Entity* current = nullptr;
//    int nCurrentEntityIndex;
//
//    Entity camCenter = Entity(Rectangle::Make(), { 0.0f, 0.0f }, fWidth, olc::RED);
//
//    //std::vector<Entity*> entities;
//    std::vector<cCircle> entities;
//
//
//
//public:
//
//    bool OnUserCreate() override {
//
//        fWidth = (float)ScreenWidth();
//        fHeight = (float)ScreenHeight();
//
//        nTotalEntities = 10;
//        entities.reserve(nTotalEntities);
//
//        nCurrentEntityIndex = 0;
//
//        
//        for (int i = 0; i < nTotalEntities; i++)
//        {
//            int verts = (rand() % 30 + 5);
//            int radius = (rand() % 80 + 20);
//            olc::vf2d pos = { (float)(rand() % (int)fWidth - (int)fWidth / 2), (float)(rand() % (int)fHeight - (int)fHeight / 2) };
//
//            entities.emplace_back(cCircle(pos, 20, (float)radius, olc::YELLOW));
//        }
//
//        current = &entities[nCurrentEntityIndex];
//        current->SetColor(olc::RED);
//
//
//        return true;
//    }
//    void SwitchEntity() {
//        
//        if (GetKey(olc::Key::SPACE).bPressed)
//        {
//            current->SetColor(olc::YELLOW);
//            nCurrentEntityIndex++;
//
//            if (nCurrentEntityIndex >= entities.size())
//                nCurrentEntityIndex = 0;
//
//            current = &entities[nCurrentEntityIndex];
//            current->SetColor(olc::RED);
//        }
//
//    }
//    void MoveEntity(float fElapsedTime)
//    {
//        float fSpeed = 300 * fElapsedTime;
//
//        if (GetKey(olc::Key::A).bHeld)
//        {
//            current->TranslateBy({ -fSpeed, 0.0f });
//        }
//        if (GetKey(olc::Key::W).bHeld)
//        {
//            current->TranslateBy({ 0.0f, fSpeed });
//        }
//        if (GetKey(olc::Key::D).bHeld)
//        {
//            current->TranslateBy({ fSpeed, 0.0f });
//        }
//        if (GetKey(olc::Key::S).bHeld)
//        {
//            current->TranslateBy({ 0.0f, -fSpeed });
//        }
//
//        if (GetKey(olc::Key::Z).bHeld)
//            current->SetScale(current->GetScale() * 1.005);
//        if (GetKey(olc::Key::X).bHeld)
//            current->SetScale(current->GetScale() * 0.995);
//
//    }
//
//    bool OnUserUpdate(float fElapsedTime) override {
//
//        Clear(olc::VERY_DARK_GREY);
//
//        camCtrl.update(); // Controls camera movement and scaling
//        
//        SwitchEntity(); // Switches current entity with other === SPACE BAR
//
//        MoveEntity(fElapsedTime); // MOVES AND ZOOMS ENTITY (A, W, D, S) ( Z, X )
//        
//        const auto vp = cam.GetViewPortRect();
//
//        for (const auto &e : entities)
//        {
//            if (e.GetBoundingRect().IsOverLappingWith(vp))
//            {
//                Drawable d = e.GetDrawable();
//                cam.DrawShape(d);
//            }
//            else continue;
//        }
//
//        olc::vf2d camCenterPos = { cam.GetPos().x - camCenter.GetRadius() / 2.0f, cam.GetPos().y - camCenter.GetRadius() / 2.0f };
//        camCenter.SetPos(camCenterPos);
//        camCenter.SetRadius(fWidth * cam.GetScale());
//        Drawable camCenterD = camCenter.GetDrawable();
//        cam.DrawShape(camCenterD);
//
//        
//        //cam.FollowEntity(current->GetPos());
//
//        return true;
//    }
//};
//
//
//
//int main()
//{
//    Game app;
//    if (app.Construct(600, 600, 1, 1))
//        app.Start();
//
//}

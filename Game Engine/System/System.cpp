#include "CameraController.h"
#include "Predetor.h"
#include "Prey.h"
#include "Map.h"

class System : public olc::PixelGameEngine {

public: 
    System() {
        sAppName = "System";

    }

private:
    Map map = Map(*this, 600.0f, 600.0f);
    Camera cam = Camera(map.getCT());
    CameraController camCtrl = CameraController(*this, cam);


public:

    bool OnUserCreate() override {

        map.initializeMap();

        //map.addEntity(new Predetor(10.0f));
        //map.addEntity(new Predetor(10.0f));
        //map.addEntity(new Predetor(10.0f));
        //map.addEntity(new Predetor(10.0f));

        map.addEntity(new Prey({0.0f, 0.0f}, 6.0f));
        map.addEntity(new Predetor({ 0.0f, 0.0f }, 10.0f));
        //map.addEntity(new Prey({30.0f, 50.0f}, 10.0f));
        //map.addEntity(new Prey({0.0f, 100.0f}, 10.0f));

        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override {
        Clear(olc::VERY_DARK_GREY);


        map.update(fElapsedTime);
        map.Render(cam);

        camCtrl.update();


        return true;
    }
};

int main()
{
    System sys;

    if (sys.Construct(600, 600, 1, 1))
        sys.Start();
}

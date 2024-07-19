#include "GameLib/Framework.h"
#include "GameLib/Math.h"
#include "base/calculate/Matrix44.h"
#include "base/calculate/Matrix34.h"
#include "engine/base/Camera.h"
#include "engine/blueprint/Blueprint.h"
#include "models/Stage.h"
#include "models/Robo.h"
#include "base/xml/Document.h"
#include "base/xml/Element.h"
using namespace models;
using namespace Model;
using namespace engine::blueprint;
using namespace base::engine;

namespace GameLib
{
    Camera* camera;
    Blueprint* gBlueprint;
    Stage* stage;
    Robo* robo1;
    Robo* robo2;
    Vector3 gEyePosition(0.0, 0.0, 1.0);
    Vector3 roboPosition1(0.0, 2.0, 5.0);
    Vector3 roboPosition2(0.0, 0.0, -5.0);
    Vector3 gEyeTarget(0.0, 30.0, 0.0);

    int gCount = 0;
    bool  isInit = false;
    void Framework::update() {
        if (gCount <= 0)
        {
            setFrameRate(60);
            camera = new Camera(1.0, 10000.0, gEyePosition, gEyeTarget);
            stage = new Stage();
            double angle1[3] = { 0.0,180.0,0.0 };
            double angle2[3] = { 0.0,0.0,0.0 };
            gBlueprint = new Blueprint("bullet.txt");
            //const Batch* batch = gBlueprint->batch("robo");
            robo1 = new Robo(roboPosition1, angle1, gBlueprint);
            robo2 = new Robo(roboPosition2, angle2, gBlueprint);
            camera->bind(robo2); // 可以通过切换绑定来设置相机位置
        }

        //const Cuboid& cbRobo1 = *robo1->cuboid(); // 碰撞模型长方体
        //const Cuboid& cbRobo2 = *robo2->cuboid(); // 碰撞模型长方体
        //Vector3 moveDirection;
        //robo1->move(&moveDirection);
        //cbRobo1.restrictMove(&moveDirection, cbRobo2);

        const Sphere& spRobo1 = *robo1->sphere(); // 碰撞模型球体
        const Sphere& spRobo2 = *robo2->sphere(); // 碰撞模型球体

        Vector3 moveDirection;
        stage->restrictMove(&moveDirection, *robo1->position());
        spRobo1.restrictMove(&moveDirection, spRobo2);

        robo1->update(robo2); // 目标机器人  自瞄处理  后面可能会弄一个模型池从里面获取

        camera->update();
        stage->draw(camera->view());
        robo1->draw(camera->view());
        robo2->draw(camera->view());
        gCount = 1;
    }
}


#include <sstream>
#include "GameLib/Framework.h"
#include "GameLib/Input/Manager.h"
#include "GameLib/Input/Keyboard.h"
#include "GameLib/Math.h"
#include "Vector3.h"
#include "Matrix34.h"
#include "Matrix44.h"
#include "GameLib/Math.h"
#include "Robo.h"
#include "Stage.h"
#include "Pad.h"
#include <iostream>
using namespace GameLib;
using namespace std;
// 设置视角  观察点和目标点只是为了设置观察角度
Vector3 eyePoint(0.0, 0.0, 1.0);
Vector3 targetPoint(0.0, 0.0, 0.0);

bool gMultiplyWToZByHand = false;
int gCount;
bool init = false;
namespace GameLib {
	Robo* robo[2];
	Stage* stage;
	void Framework::update() {
		setFrameRate(60);
		Vector3 point[4];
		point[0].set(-50.0, 0.0, -50.0);
		point[1].set(-50.0, 0.0, 50.0);
		point[2].set(50.0, 0.0, -50.0);
		point[3].set(50.0, 0.0, 50.0);
		if (!init)
		{
			Pad::create(); //初始化
			robo[0] = new Robo(0);
			robo[1] = new Robo(1);

			robo[1]->setAngleY(30.0);
			robo[1]->setPosition(Vector3(0.0, 0.0, 50.0));

			robo[0]->setAngleY(30.0);
			robo[0]->setPosition(Vector3(0.0, 0.0, -50.0));

			stage = new Stage();
			init = !init;
		}
		robo[0]->update();
		// 要让观察点与机甲位置对其
		eyePoint = *(robo[0]->position());
		Vector3 dir;
		robo[0]->getDirection(&dir);

		Vector3 v;
		v.setMul(dir, 6.0); // 往机甲的面朝的方向3个单位距离
		eyePoint -= v;
		eyePoint.y += 6.0; // 视角向上移动2个单位距离
		targetPoint = *(robo[0]->position());
		v.setMul(dir, 1.0);
		eyePoint += v;

		Matrix34 matrix34;	// 观察者
		matrix34.setView(eyePoint, targetPoint);


		Matrix44 matrix44;	// 世界变换
		matrix44.setPerspectiveTransform(60, 640.0, 480.0, 1.0, 10000.0);


		matrix44 *= matrix34;

		stage->draw(matrix44);
		for (size_t i = 0; i < 2; i++)
		{
			robo[i]->draw(matrix44);
		}
		

		++gCount;
	}
}
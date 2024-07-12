#include <sstream>
#include "GameLib/Framework.h"
#include "GameLib/Input/Manager.h"
#include "GameLib/Input/Keyboard.h"
#include "Vector3.h"
#include "Matrix34.h"
#include "Matrix44.h"
#include "GameLib/Math.h"
using namespace GameLib;
using namespace std;

bool gMultiplyWToZByHand = false;
int gCount;

namespace GameLib {
	void Framework::update() {
		setFrameRate(60);
		Vector3 p[4];
		unsigned c[4]; //易于识别的颜色

		p[0].set(-1000.0, 0.0, -1000.0);
		p[1].set(-1000.0, 0.0, 1000.0);
		p[2].set(1000.0, 0.0, -1000.0);
		p[3].set(1000.0, 0.0, 1000.0);

		c[0] = 0xffff0000; //红色的
		c[1] = 0xff00ff00; //绿
		c[2] = 0xff0000ff; //蓝色的
		c[3] = 0xffffffff; //白

		Matrix34 wm;
		wm.setRotateZ(gCount * 4.0);

		Vector3 viewPoint;
		viewPoint.set(sin(gCount) * 4000.0, 1000.0, cos(gCount) * 4000.0);
		Vector3 targetPoint(0.0, 0.0, 0.0);

		//设置视角
		Matrix34 matrix34;
		matrix34.setView(viewPoint, targetPoint);

		Matrix44 matrix44;
		matrix44.setPerspectiveTransform(45, 640.0, 480.0, 1.0, 10000.0);

		matrix34 *= wm;

		matrix44 *= matrix34;

		double p4[4][4];

		for (int i = 0; i < 4; i++)
		{
			matrix44.multiply(p4[i], p[i]);
		}

		//画一个矩形。
		drawTriangle3DH(p4[0], p4[1], p4[2], 0, 0, 0, c[0], c[1], c[2]);
		drawTriangle3DH(p4[3], p4[1], p4[2], 0, 0, 0, c[3], c[1], c[2]);

		++gCount;
	}
}

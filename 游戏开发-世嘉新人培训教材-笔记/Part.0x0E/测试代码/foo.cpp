#include "foo.h"
#include "GameLib/Framework.h"
#include "GameLib/Input/Manager.h"
#include "GameLib/Input/Keyboard.h"
#include "Vector3.h"
#include "Matrix34.h"
#include <sstream>
using namespace std;
namespace GameLib
{

	double gX = 0;
	double gZ = 5000;
	double gY = 0;
	double ring = 1.0;
	void Framework::update()
	{
		layour::Vector3 vector[4] = {
			layour::Vector3(-500.0, -300.0, -1000.0),
			layour::Vector3(-500.0, -300.0, 1000.0),
			layour::Vector3(500.0, -300.0, -1000.0),
			layour::Vector3(500.0, -300.0, 1000.0)
		};


		layour::Matrix34 matrix340;
		layour::Matrix34 matrix341;
		layour::Vector3 scar(ring, ring, ring);
		layour::Vector3 trans(gX, gY, gZ);

		matrix340.setTranslation(trans);
		matrix341.setScaling(scar);
		for (int i = 0; i < 4; i++)
		{
			matrix340.multiply(&vector[i], vector[i]);
			matrix341.multiply(&vector[i], vector[i]);
		}

		double vp[4][4];

		for (int i = 0; i < 4; i++)
		{
			vp[i][0] = vector[i].x;
			vp[i][1] = vector[i].y * 640.0 / 480.0;
			vp[i][2] = (1.0 / 9999.0) * vector[i].z - (1.0 / 9999.0);
			vp[i][3] = vector[i].z;
			vp[i][2] *= vp[i][3];
		}

		if (Input::Manager::instance().keyboard().isOn('w')) {
			gZ -= 10;
		}
		else if (Input::Manager::instance().keyboard().isOn('s'))
		{
			gZ += 10;
		}
		else if (Input::Manager::instance().keyboard().isOn('a'))
		{
			gX -= 10;
		}
		else if (Input::Manager::instance().keyboard().isOn('d'))
		{
			gX += 10;
		}
		else if (Input::Manager::instance().keyboard().isOn('q'))
		{
			gY -= 10;
		}
		else if (Input::Manager::instance().keyboard().isOn('e'))
		{
			gY += 10;
		}
		else if (Input::Manager::instance().keyboard().isOn('-'))
		{
			ring += 0.01;
		}
		else if (Input::Manager::instance().keyboard().isOn('+'))
		{
			ring -= 0.01;
		}
		drawTriangle3DH(vp[0], vp[1], vp[2]);
		drawTriangle3DH(vp[3], vp[1], vp[2]);
		ostringstream oss;
		oss << "[w-z] Z MOVEMENT: " << gZ;
		drawDebugString(10, 0, oss.str().c_str());
		oss.str("");
		oss << "[a-s] X MOVEMENT: " << gX;
		drawDebugString(10, 1, oss.str().c_str());
	}
}
#include "Vector3.h"
// ��Ԫ����
namespace layour {
	Vector3::Vector3() {};
	Vector3::Vector3(double ix, double iy, double iz) :x(0), y(0), z(0)
	{
		x = ix, y = iy, z = iz;
	};
	Vector3::~Vector3()
	{

	};
}
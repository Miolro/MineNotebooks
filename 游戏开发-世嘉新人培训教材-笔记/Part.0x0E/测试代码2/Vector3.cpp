#include "Vector3.h"

Vector3::Vector3(double ix, double iy, double iz)
{
	x = ix;
	y = iy;
	z = iz;
}

void Vector3::set(double ix, double iy, double iz)
{
	x = ix;
	y = iy;
	z = iz;
}

void Vector3::setSub(Vector3 v1, Vector3 v2)
{
	x = v1.x - v2.x;
	y = v1.y - v2.y;
	z = v1.z - v2.z;
}

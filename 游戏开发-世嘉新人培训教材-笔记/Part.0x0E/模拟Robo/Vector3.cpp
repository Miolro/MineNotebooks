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

void Vector3::setMul(Vector3 v1, double arg)
{
	x = v1.x * arg;
	y = v1.y * arg;
	z = v1.z * arg;
}

void Vector3::operator-=(Vector3 v)
{
	x = x - v.x;
	y = y - v.y;
	z = z - v.z;
}

void Vector3::operator+=(Vector3 v)
{
	x = x + v.x;
	y = y + v.y;
	z = z + v.z;
}

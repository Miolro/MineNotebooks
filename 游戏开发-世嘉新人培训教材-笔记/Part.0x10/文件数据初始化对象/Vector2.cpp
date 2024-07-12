#include "Vector2.h"
Vector2::Vector2(double ix, double iy)
{
	x = ix;
	y = iy;
}

void Vector2::set(double ix, double iy)
{
	x = ix;
	y = iy;
}

void Vector2::setSub(Vector2 v1, Vector2 v2)
{
	x = v1.x - v2.x;
	y = v1.y - v2.y;
}

void Vector2::setMul(Vector2 v1, double arg)
{
	x = v1.x * arg;
	y = v1.y * arg;
}

void Vector2::operator-=(Vector2 v)
{
	x = x - v.x;
	y = y - v.y;
}

void Vector2::operator+=(Vector2 v)
{
	x = x + v.x;
	y = y + v.y;
}

#include "Vector2.h"


Vector2::Vector2() :x(0), y(0) {}
Vector2::Vector2(int ix, int iy)
{
	x = static_cast<double>(ix);
	y = static_cast<double>(iy);
};
Vector2::Vector2(double ix, double iy) :x(ix), y(iy) {}
Vector2::~Vector2() {}
void Vector2::operator*=(double in)
{
	x *= in;	y *= in;
}
void Vector2::operator+=(const Vector2& thatVector2)
{
	x += thatVector2.x;
	y += thatVector2.y;
}
void Vector2::operator-=(const Vector2& thatVector2)
{
	x -= thatVector2.x;
	y -= thatVector2.y;
}
void Vector2::operator=(const Vector2& thatVector2)
{
	x = thatVector2.x;
	y = thatVector2.y;
}

void Vector2::addVector(Vector2 v0, Vector2 v1)
{
	*this = v0;
	*this += v1;
}

void Vector2::setInterpolation(Vector2& a, const Vector2& ab, double absize, const Vector2& ac, double acsize)
{
	//公式 p向量 = a向量+absize1单位的比例*ab向量+ac向量*acsize1单位比例
	*this += a;
	Vector2 tmp;
	tmp = ab;
	tmp *= absize;
	*this += tmp;
	tmp = ac;
	tmp *= acsize;
	*this += tmp;
};
#include "Matrix32.h"
#include "Vector2.h"

Matrix32::Matrix32()
{
}
// ³õÊ¼»¯¾ØÕó
Matrix32::Matrix32(double im00, double im01, double im02, double im10, double im11, double im12)
	:m00(im00), m01(im01), m02(im02), m10(im10), m11(im11), m12(im12) {}

Matrix32::~Matrix32()
{
}

void Matrix32::multiply(Vector2* out, const Vector2& in) const
{
	double tmpx = in.x;
	double tmpy = in.y;

	out->x = tmpx * m00 + tmpy * m01 + 1 * m02;
	out->y = tmpx * m10 + tmpy * m11 + 1 * m12;
}

void Matrix32::transfromMove(Vector2* out, const Vector2& in)
{
	multiply(out, in);
}

void Matrix32::transfromMove(Vector2* out, const Vector2& in, double x, double y)
{
	m00 = m11 = 1;
	m01 = m10 = 0;
	m02 = x;
	m12 = y;
	multiply(out, in);
}

// 
void Matrix32::transfromRoll(Vector2* out, const Vector2& in, Vector2 offset)
{

	*out = in;
	*out += Vector2(0.5, 0.5);
	*out -= offset;
	multiply(out, *out);
	*out += offset;
}

void Matrix32::transfromScal(Vector2* out, const Vector2& in, const Vector2 offset)
{
	Vector2 tmp;
	tmp = in;
	tmp += offset;
	multiply(out, tmp);

}


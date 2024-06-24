#include "Matrix44.h"
#include "GameLib/Math.h"
#include "Matrix34.h"
#include "Vector3.h"
using namespace GameLib;
void Matrix44::setPerspectiveTransform(double fov, double windowWidth, double windowHeight, double nearClip, double farClip)
{
	double s = 1.0 / tan(fov * 0.5);//缩放比例
	double wh = windowHeight / windowWidth;  // 宽高比
	double a = 1.0 / (nearClip - farClip); //可视范围
	double b = nearClip * a;

	m00 = s * wh;
	m11 = s;
	m22 = a;
	m23 = b;
	m32 = -1.0;
	m01 = m02 = m03 = 0.0;
	m10 = m12 = m13 = 0.0;
	m20 = m21 = 0.0;
	m30 = m31 = m33 = 0.0;
}

void Matrix44::operator*=(const Matrix34 m)
{
	//double x = m00, y = m01, z = m02;
	//m00 = m.m00 * x + m.m10 * y + m.m20 * z;
	//m01 = m.m01 * x + m.m11 * y + m.m21 * z;
	//m02 = m.m02 * x + m.m12 * y + m.m22 * z;
	//m03 = m.m03 * x + m.m13 * y + m.m23 * z + m03;

	//x = m10, y = m11, z = m12;
	//m10 = m.m00 * x + m.m10 * y + m.m20 * z;
	//m11 = m.m01 * x + m.m11 * y + m.m21 * z;
	//m12 = m.m02 * x + m.m12 * y + m.m22 * z;
	//m13 = m.m03 * x + m.m13 * y + m.m23 * z + m13;

	//x = m20, y = m21, z = m22;
	//m20 = m.m00 * x + m.m10 * y + m.m20 * z;
	//m21 = m.m01 * x + m.m11 * y + m.m21 * z;
	//m22 = m.m02 * x + m.m12 * y + m.m22 * z;
	//m23 = m.m03 * x + m.m13 * y + m.m23 * z + m23;

	//x = m30; y = m31; z = m32;
	//m30 = x * m.m00 + y * m.m10 + z * m.m20;
	//m31 = x * m.m01 + y * m.m11 + z * m.m21;
	//m32 = x * m.m02 + y * m.m12 + z * m.m22;
	//m33 = x * m.m03 + y * m.m13 + z * m.m23 + m33;
	setMul(*this, m);
}

void Matrix44::multiply(double* out, Vector3 in) const
{
	out[0] = m00 * in.x + m01 * in.y + m02 * in.z + m03;
	out[1] = m10 * in.x + m11 * in.y + m12 * in.z + m13;
	out[2] = m20 * in.x + m21 * in.y + m22 * in.z + m23;
	out[3] = m30 * in.x + m31 * in.y + m32 * in.z + m33;
}

void Matrix44::setMul(const Matrix44& m44, const Matrix34& m34)
{
	double tx, ty, tz;
	tx = m44.m00; ty = m44.m01; tz = m44.m02;
	m00 = tx * m34.m00 + ty * m34.m10 + tz * m34.m20;
	m01 = tx * m34.m01 + ty * m34.m11 + tz * m34.m21;
	m02 = tx * m34.m02 + ty * m34.m12 + tz * m34.m22;
	m03 = tx * m34.m03 + ty * m34.m13 + tz * m34.m23 + m44.m03;
	tx = m44.m10; ty = m44.m11; tz = m44.m12;
	m10 = tx * m34.m00 + ty * m34.m10 + tz * m34.m20;
	m11 = tx * m34.m01 + ty * m34.m11 + tz * m34.m21;
	m12 = tx * m34.m02 + ty * m34.m12 + tz * m34.m22;
	m13 = tx * m34.m03 + ty * m34.m13 + tz * m34.m23 + m44.m13;
	tx = m44.m20; ty = m44.m21; tz = m44.m22;
	m20 = tx * m34.m00 + ty * m34.m10 + tz * m34.m20;
	m21 = tx * m34.m01 + ty * m34.m11 + tz * m34.m21;
	m22 = tx * m34.m02 + ty * m34.m12 + tz * m34.m22;
	m23 = tx * m34.m03 + ty * m34.m13 + tz * m34.m23 + m44.m23;
	tx = m44.m30; ty = m44.m31; tz = m44.m32;
	m30 = tx * m34.m00 + ty * m34.m10 + tz * m34.m20;
	m31 = tx * m34.m01 + ty * m34.m11 + tz * m34.m21;
	m32 = tx * m34.m02 + ty * m34.m12 + tz * m34.m22;
	m33 = tx * m34.m03 + ty * m34.m13 + tz * m34.m23 + m44.m33;
}



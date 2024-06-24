#include "Matrix34.h"
#include "Vector3.h"
#include "GameLib/Math.h"
#include "Vector3.h"
using namespace GameLib;
void Matrix34::setView(Vector3 view, Vector3 target)
{
	// view视为移动到原点位置
	Vector3 temp;
	temp.setSub(target, view);
	//原点到目标的直线距离
	double line = sqrt(temp.x * temp.x + temp.z * temp.z);
	//然后求出与正常视角相差多少度数  通过atan两条边求出角度
	double rotateUpDown = atan2(temp.y, line);
	double rotateLeftRight = atan2(temp.x, temp.z) + 180.0;
	//视角旋转
	setRotateX(-rotateUpDown);
	rotateY(-rotateLeftRight);
	translate(Vector3(-view.x, -view.y, -view.z)); // 把视角移动回去
}

void Matrix34::setRotateX(double r)
{
	double c = cos(r);
	double s = sin(r);
	m00 = 1.0;
	m01 = 0.0;
	m02 = 0.0;
	m03 = 0.0;

	m10 = 0.0;
	m11 = c;
	m12 = -s;
	m13 = 0.0;

	m20 = 0.0;
	m21 = s;
	m22 = c;
	m23 = 0.0;
}

void Matrix34::setRotateZ(double r)
{
	double c = cos(r);
	double s = sin(r);
	m00 = c;
	m01 = -s;
	m02 = 0.0;
	m03 = 0.0;

	m10 = s;
	m11 = c;
	m12 = 0.0;
	m13 = 0.0;

	m20 = 0.0;
	m21 = 0.0;
	m22 = 1.0;
	m23 = 0.0;
}
/*
cosθ  0  sinθ
0      1     0
−sinθ  0  cosθ
*/
void Matrix34::setRotateY(double r)
{
	double c = cos(r);
	double s = sin(r);
	double t;

	m00 = c;
	m01 = 0.0;
	m02 = s;
	m03 = 0.0;

	m10 = 0.0;
	m11 = 1.0;
	m12 = 0.0;
	m13 = 0.0;

	m20 = -s;
	m21 = 0.0;
	m22 = c;
	m23 = 0.0;

}
// 向量
void Matrix34::rotateY(double r)
{
	double c = cos(r);
	double s = sin(r);
	double t;

	t = m00 * c + m02 * -s;
	//m01 = t * 0 + m01 * 1 + m02 * 0;
	m02 = m00 * s + m02 * c;
	m00 = t;

	t = m10 * c + m12 * -s;
	//m11 = m10 * 0 + m11 * 1 + m12 * 0;
	m12 = m10 * s + m12 * c;
	m10 = t;

	t = m20 * c + m22 * -s;
	//m21 = m20 * 0 + m21 * 1 + m22 * 0;
	m22 = m20 * s + m22 * c;
	m20 = t;

}
void Matrix34::setTranslation(Vector3 v)
{
	m00 = m11 = m22 = 1.0;
	m01 = m02 = 0.0;
	m10 = m12 = 0.0;
	m20 = m21 = 0.0;
	m03 = v.x;
	m13 = v.y;
	m23 = v.z;
}
//与移动矩阵相乘。请自己参考2d时的处理
void Matrix34::translate(const Vector3& a) {
	m03 += m00 * a.x + m01 * a.y + m02 * a.z;
	m13 += m10 * a.x + m11 * a.y + m12 * a.z;
	m23 += m20 * a.x + m21 * a.y + m22 * a.z;
}
void Matrix34::multiply(double& vout, Vector3 v)
{

}
// 向量输入进行矩阵处理
void Matrix34::multiply(Vector3* vout, Vector3 v)
{
	double tx = v.x;
	double ty = v.y;
	vout->x = m00 * tx + m01 * ty + m02 * v.z + m03;
	vout->y = m10 * tx + m11 * ty + m12 * v.z + m13;
	vout->z = m20 * tx + m21 * ty + m22 * v.z + m23;
}

void Matrix34::operator*=(const Matrix34 m)
{
	double x = m00, y = m01, z = m02;
	m00 = m.m00 * x + m.m10 * y + m.m20 * z;
	m01 = m.m01 * x + m.m11 * y + m.m21 * z;
	m02 = m.m02 * x + m.m12 * y + m.m22 * z;
	m03 = m.m03 * x + m.m13 * y + m.m23 * z + m03;

	x = m10, y = m11, z = m12;
	m10 = m.m00 * x + m.m10 * y + m.m20 * z;
	m11 = m.m01 * x + m.m11 * y + m.m21 * z;
	m12 = m.m02 * x + m.m12 * y + m.m22 * z;
	m13 = m.m03 * x + m.m13 * y + m.m23 * z + m13;

	x = m20, y = m21, z = m22;
	m20 = m.m00 * x + m.m10 * y + m.m20 * z;
	m21 = m.m01 * x + m.m11 * y + m.m21 * z;
	m22 = m.m02 * x + m.m12 * y + m.m22 * z;
	m23 = m.m03 * x + m.m13 * y + m.m23 * z + m23;
}

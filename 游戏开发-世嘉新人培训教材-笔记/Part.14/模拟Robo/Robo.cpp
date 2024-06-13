#include "Robo.h"
#include "Pad.h"
#include "Matrix34.h"
#include "Matrix44.h"
#include "GameLib/Math.h"
using namespace GameLib;

Robo::Robo(int id) :mPosition(0.0, 0.0, 0.0), mAngleY(0), mid(id), mTexture(0)
{

}

Robo::~Robo()
{
}

void Robo::draw(Matrix44& pvm)const
{
	Vector3 p[8];
	//上面
	p[0].set(-0.5, 2.0, -0.5);  //左上前		0
	p[1].set(0.5, 2.0, -0.5);	//右上前		1
	p[2].set(-0.5, 2.0, 0.5);	//左上后		2
	p[3].set(0.5, 2.0, 0.5);	//右上后		3

	//下底面	
	p[4].set(-0.5, 0.0, -0.5);	//左下前		4
	p[5].set(0.5, 0.0, -0.5);	//右下前		5
	p[6].set(-0.5, 0.0, 0.5);	//左下后		6
	p[7].set(0.5, 0.0, 0.5);	//右下后		7

	Matrix34 viewTransform;
	viewTransform.setTranslation(mPosition);
	viewTransform.rotateY(mAngleY);

	Matrix44 worldTransform;
	worldTransform.setMul(pvm, viewTransform);

	//三角形信息 6个面 3个点  1个面2个三角形  =36
	const int vIdx[36] = {
		4,5,6,  // 地面三角形组 -y
		7,5,6,

		0,1,2, // 顶部
		3,1,2,

		2,0,6, // 左边
		4,0,6,

		3,1,7, // 右边
		5,1,7,

		2,3,6, // 后边
		7,3,6,

		0,1,4, // 前边
		5,1,4,
	};

	double po[8][4];
	for (int i = 0; i < 8; i++)
	{
		worldTransform.multiply(po[i], p[i]);
	}
	for (size_t i = 0; i < 6; i++)
	{
		int vi0 = vIdx[i * 6 + 0];// 提取每个三角形的三个顶点
		int vi1 = vIdx[i * 6 + 1];// 提取每个三角形的三个顶点
		int vi2 = vIdx[i * 6 + 2];// 提取每个三角形的三个顶点

		int vi4 = vIdx[i * 6 + 3];// 提取每个三角形的三个顶点
		int vi5 = vIdx[i * 6 + 4];// 提取每个三角形的三个顶点
		int vi6 = vIdx[i * 6 + 5];// 提取每个三角形的三个顶点

		GameLib::Framework::instance().drawTriangle3DH(
			po[vi0], po[vi1], po[vi2],
			0, 0, 0, 0xffffffff, 0xffffffff, 0xffffffff);
		GameLib::Framework::instance().drawTriangle3DH(
			po[vi4], po[vi5], po[vi6],
			0, 0, 0, 0xffffffff, 0xffffffff, 0xffffffff);
	}
}

void Robo::update()
{
	Vector3 enemy(0.0, 0.0, 50.0);  // 对方机器人的坐标也可以外部传入
	Pad* pad = Pad::instance();
	Vector3 move;
	if (mPosition.y > 1) {
		move.set(0.0, -1.0, 0.0);
	}
	else
	{
		move.set(0.0, 0.0, 0.0);
	}

	if (pad->isOn(Pad::KEY_FORWARD, 0))
	{
		move.z = 1.0;
	}
	else if (pad->isOn(Pad::KEY_BACK, 0))
	{
		move.z = -1.0;
	}
	if (pad->isOn(Pad::KEY_LEFT, 0))
	{
		move.x = 1.0;
	}
	else if (pad->isOn(Pad::KEY_RIGHT, 0))
	{
		move.x = -1.0;
	}
	if (pad->isOn(Pad::KEY_FLY, 0))
	{
		move.y = 1.0;
		// 修正视角计算偏转角度
		Vector3 t;
		t.setSub(mPosition, enemy);  // 计算坐标差将通过xz获得坐标
		mAngleY = GameLib::atan2(t.x, t.z) + 180.0;
	}
	Matrix34 matrix34; // 修正旋转后的移动方向  旋转后移动的向量应该也跟着一起旋转
	matrix34.translate(move);
	matrix34.setRotateY(mAngleY);

	matrix34.multiply(&move, move);
	mPosition += move;
}

const Vector3* Robo::position() const
{
	return &mPosition;
}

double Robo::angleY() const
{
	return mAngleY;
}

void Robo::getDirection(Vector3* v)
{
	Matrix34 m34;
	m34.setRotateY(mAngleY);
	m34.multiply(v, Vector3(0.0, 0.0, 1.0));
}

void Robo::setPosition(const Vector3& position)
{
	mPosition = position;
}

void Robo::setAngleY(double r)
{
	mAngleY = r;
}

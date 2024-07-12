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
	//����
	p[0].set(-0.5, 2.0, -0.5);  //����ǰ		0
	p[1].set(0.5, 2.0, -0.5);	//����ǰ		1
	p[2].set(-0.5, 2.0, 0.5);	//���Ϻ�		2
	p[3].set(0.5, 2.0, 0.5);	//���Ϻ�		3

	//�µ���	
	p[4].set(-0.5, 0.0, -0.5);	//����ǰ		4
	p[5].set(0.5, 0.0, -0.5);	//����ǰ		5
	p[6].set(-0.5, 0.0, 0.5);	//���º�		6
	p[7].set(0.5, 0.0, 0.5);	//���º�		7

	Matrix34 viewTransform;
	viewTransform.setTranslation(mPosition);
	viewTransform.rotateY(mAngleY);

	Matrix44 worldTransform;
	worldTransform.setMul(pvm, viewTransform);

	//��������Ϣ 6���� 3����  1����2��������  =36
	const int vIdx[36] = {
		4,5,6,  // ������������ -y
		7,5,6,

		0,1,2, // ����
		3,1,2,

		2,0,6, // ���
		4,0,6,

		3,1,7, // �ұ�
		5,1,7,

		2,3,6, // ���
		7,3,6,

		0,1,4, // ǰ��
		5,1,4,
	};

	double po[8][4];
	for (int i = 0; i < 8; i++)
	{
		worldTransform.multiply(po[i], p[i]);
	}
	for (size_t i = 0; i < 6; i++)
	{
		int vi0 = vIdx[i * 6 + 0];// ��ȡÿ�������ε���������
		int vi1 = vIdx[i * 6 + 1];// ��ȡÿ�������ε���������
		int vi2 = vIdx[i * 6 + 2];// ��ȡÿ�������ε���������

		int vi4 = vIdx[i * 6 + 3];// ��ȡÿ�������ε���������
		int vi5 = vIdx[i * 6 + 4];// ��ȡÿ�������ε���������
		int vi6 = vIdx[i * 6 + 5];// ��ȡÿ�������ε���������

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
	Vector3 enemy(0.0, 0.0, 50.0);  // �Է������˵�����Ҳ�����ⲿ����
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
		// �����ӽǼ���ƫת�Ƕ�
		Vector3 t;
		t.setSub(mPosition, enemy);  // ��������ͨ��xz�������
		mAngleY = GameLib::atan2(t.x, t.z) + 180.0;
	}
	Matrix34 matrix34; // ������ת����ƶ�����  ��ת���ƶ�������Ӧ��Ҳ����һ����ת
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

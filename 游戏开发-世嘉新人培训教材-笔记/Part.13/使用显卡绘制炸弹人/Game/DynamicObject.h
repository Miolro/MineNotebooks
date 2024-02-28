#pragma once
#include "../Utils/Image.h"
#include "../Utils/Vector2.h"

namespace Game
{
	class StaticObject;
	class DynamicObject
	{
	public:
		enum Type
		{
			NONE = (0), // ������Ķ���
			PLAYER1 = (1 << 0),
			PLAYER2 = (1 << 1),
			MONSTER = (1 << 2),

		};
		enum DirectionType
		{
			TOP,
			LEFT,
			SELF,
			RIGHT,
			BOTTOM
		};

		void set(double cellx, double celly, Type dyObject);
		void getDirction(int* dx, int* dy);
		void getVelocity(int* dx, int* dy);
		void getCell(int* x, int* y);
		void draw(const Image* image)const;
		void move(const int* wallX, const  int* wallY, const int wallNumber);
		// ��ײ���
		bool collisionDetection(int thisX, int thisY, int thatX, int thatY);
		bool hasBombButtonPressed();
		// ��ײ����
		bool collisionResponseMove(Vector2& imove, const Vector2& itargetLT, const Vector2& itargetLRB);
		Vector2 findInBlock();
		bool isDead()const;  // �������mType�Ƿ�ΪNONE��������������Ƿ���
		void die();
		//���Ǻܶ�ΪʲôҪ��ը�����������̬����  �������Ӧ�ñ����ھ�̬��������ߵ�ͼ��ȽϺ���
		//int mbakudaX[10];
		//int mbakudaY[10];
	private:
		Game::DynamicObject::Type mType;
		int innnerX;
		int innnerY;
		double mSpeed;
		//bool isDead; // ����Ҫ�������
	};
}


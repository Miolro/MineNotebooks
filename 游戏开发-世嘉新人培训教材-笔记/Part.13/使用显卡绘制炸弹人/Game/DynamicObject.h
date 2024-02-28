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
			NONE = (0), // 不定义的对象
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
		// 碰撞检测
		bool collisionDetection(int thisX, int thisY, int thatX, int thatY);
		bool hasBombButtonPressed();
		// 碰撞反馈
		bool collisionResponseMove(Vector2& imove, const Vector2& itargetLT, const Vector2& itargetLRB);
		Vector2 findInBlock();
		bool isDead()const;  // 检查对象的mType是否为NONE来返回这个对象是否存活
		void die();
		//不是很懂为什么要把炸弹数分配给动态对象  这个不是应该保存在静态对象里或者地图里比较好吗
		//int mbakudaX[10];
		//int mbakudaY[10];
	private:
		Game::DynamicObject::Type mType;
		int innnerX;
		int innnerY;
		double mSpeed;
		//bool isDead; // 不需要这个属性
	};
}


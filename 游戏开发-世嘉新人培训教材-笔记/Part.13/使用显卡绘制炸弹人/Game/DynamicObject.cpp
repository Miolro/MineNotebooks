#include "DynamicObject.h"
#include "../Utils/Pad.h"
#include "StaticObject.h"
namespace Game
{
	static const int PLATER_SPEED = 1000;// 玩家速度
	static const int ENEMY_SPEED = 500;  // 敌人速度
	static const int HALF_SIZE = 6000;   // 一半大小
	static const int HALF_CELL = 8000;
	int round(double in)
	{
		double temp = in;
		if (in > 0)
		{
			temp += 0.5;
		}
		else
		{
			temp -= 0.5;
		}
		return static_cast<int>(temp);
	}
	// 内存格子到内部坐标
	int convertCellToInner(int num)
	{
		// 一个像素等于1000的比例 +8000=中心坐标
		return ((2 * num) + 1) * HALF_CELL;
	}
	// 从内部坐标到像素坐标
	int convertInnerToPiexl(int num)
	{
		return (num - HALF_CELL) / 1000;
	}
	bool DynamicObject::hasBombButtonPressed()
	{
		return Pad::isTriggered(Pad::J);
	}

	void DynamicObject::set(double cellx, double celly, Type dyObject)
	{

		innnerX = convertCellToInner(cellx);
		innnerY = convertCellToInner(celly);

		mType = dyObject;
	}
	//得到方向 
	void DynamicObject::getDirction(int* dx, int* dy)
	{
		GameLib::Framework frame = GameLib::Framework::instance();
		*dx = 0;
		*dy = 0;
		if (mType & Type::PLAYER1)
		{
			if (Pad::isOn(Pad::W))
			{
				*dy = -1;
			}
			else if (Pad::isOn(Pad::S)) {
				*dy = 1;
			}
			if (Pad::isOn(Pad::A))
			{
				*dx = -1;
			}
			else if (Pad::isOn(Pad::D)) {
				*dx = 1;
			}
		}
		else if (mType & Type::MONSTER)
		{

		}
	}
	//  计算速度
	void DynamicObject::getVelocity(int* dx, int* dy)
	{
		int speedX = 0;
		int speedY = 0;
		if (mType & Type::PLAYER1)
		{
			speedX = PLATER_SPEED;
			speedY = PLATER_SPEED;
		}
		getDirction(dx, dy);
		*dx = *dx * speedX;
		*dy = *dy * speedY;
	}

	void DynamicObject::getCell(int* x, int* y)
	{
		*x = innnerX / 16000;
		*y = innnerY / 16000;
	}

	void DynamicObject::draw(const Image* image)const
	{

		if (mType & Type::PLAYER1)
		{
			int piexlX = convertInnerToPiexl(innnerX);
			int piexlY = convertInnerToPiexl(innnerY);
			image->drawTexture(piexlX, piexlY, 0, 0, 16, 16);
		}

	}
	void DynamicObject::move(const int* wallX, const  int* wallY, const int wallNumber)
	{
		int dx, dy;
		getVelocity(&dx, &dy);
		bool hitX = false;
		bool hitY = false;
		bool hit = false;
		//  与位置相加得到此时的位置

		for (int i = 0; i < wallNumber; i++)
		{
			// 将墙外部的Cell坐标转为Inner坐标用于检测碰撞  这个是墙的中心坐标
			int innerWallX = convertCellToInner(wallX[i]);
			int innerWallY = convertCellToInner(wallY[i]);
			// 防止结果被覆盖  判断这一组数据里只要碰撞就为真
			if (collisionDetection(innnerX + dx, innnerY, innerWallX, innerWallY))
			{
				hitX = hit = true;
			}
			// 防止结果被覆盖  判断这一组数据里只要碰撞就为真
			if (collisionDetection(innnerX, innnerY + dy, innerWallX, innerWallY))
			{
				hitY = hit = true;
			}
		}
		if (hitX && !hitY)
		{
			innnerY += dy;
		}
		else if (!hitX && hitY)
		{
			innnerX += dx;
		}
		else
		{
			innnerX += dx;
			innnerY += dy;
		}

	}
	// 碰撞检测 传入左上角和右下角坐标 方向
	bool DynamicObject::collisionDetection(int thisX, int thisY, int thatX, int thatY)
	{
		// 先判断左右碰撞
		int thisL = thisX - HALF_SIZE;
		int thisR = thisX + HALF_SIZE;
		int thatL = thatX - HALF_CELL;
		int thatR = thatX + HALF_CELL;
		if ((thisL < thatR) && (thisR > thatL))
		{
			int thisT = thisY - HALF_SIZE;
			int thisB = thisY + HALF_SIZE;
			int thatT = thatY - HALF_CELL;
			int thatB = thatY + HALF_CELL;
			if ((thisT < thatB) && (thisB > thatT))
			{
				return true;
			}
		}
		return false;
	}
	// 碰撞反馈  计算可以移动的距离
	bool DynamicObject::collisionResponseMove(Vector2& imove, const Vector2& itargetLT, const Vector2& itargetLRB)
	{
		return false;
	}

	bool DynamicObject::isDead() const
	{
		return mType == DynamicObject::Type::NONE;
	}

	// 设置None表示对象已经死亡
	void DynamicObject::die()
	{
		mType = DynamicObject::Type::NONE;
	}

	//Vector2 DynamicObject::findInBlock()
	//{
	//	//return null;
	//}

}

#include "DynamicObject.h"
#include "../Utils/Pad.h"
#include "StaticObject.h"
namespace Game
{
	static const int PLATER_SPEED = 1000;// ����ٶ�
	static const int ENEMY_SPEED = 500;  // �����ٶ�
	static const int HALF_SIZE = 6000;   // һ���С
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
	// �ڴ���ӵ��ڲ�����
	int convertCellToInner(int num)
	{
		// һ�����ص���1000�ı��� +8000=��������
		return ((2 * num) + 1) * HALF_CELL;
	}
	// ���ڲ����굽��������
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
	//�õ����� 
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
	//  �����ٶ�
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
		//  ��λ����ӵõ���ʱ��λ��

		for (int i = 0; i < wallNumber; i++)
		{
			// ��ǽ�ⲿ��Cell����תΪInner�������ڼ����ײ  �����ǽ����������
			int innerWallX = convertCellToInner(wallX[i]);
			int innerWallY = convertCellToInner(wallY[i]);
			// ��ֹ���������  �ж���һ��������ֻҪ��ײ��Ϊ��
			if (collisionDetection(innnerX + dx, innnerY, innerWallX, innerWallY))
			{
				hitX = hit = true;
			}
			// ��ֹ���������  �ж���һ��������ֻҪ��ײ��Ϊ��
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
	// ��ײ��� �������ϽǺ����½����� ����
	bool DynamicObject::collisionDetection(int thisX, int thisY, int thatX, int thatY)
	{
		// ���ж�������ײ
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
	// ��ײ����  ��������ƶ��ľ���
	bool DynamicObject::collisionResponseMove(Vector2& imove, const Vector2& itargetLT, const Vector2& itargetLRB)
	{
		return false;
	}

	bool DynamicObject::isDead() const
	{
		return mType == DynamicObject::Type::NONE;
	}

	// ����None��ʾ�����Ѿ�����
	void DynamicObject::die()
	{
		mType = DynamicObject::Type::NONE;
	}

	//Vector2 DynamicObject::findInBlock()
	//{
	//	//return null;
	//}

}

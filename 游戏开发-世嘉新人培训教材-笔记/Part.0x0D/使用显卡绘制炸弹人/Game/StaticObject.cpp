#include "StaticObject.h"
#include "../Utils/Image.h"
namespace Game
{
	StaticObject::StaticObject() :mFlag(0x00000000)
	{
	}
	void StaticObject::draw(const int cellx, const int celly, const Image* image)const
	{
		int srcX = -1;
		int srcY = -1;
		// ������Ⱦ
		checkFlag(FLAG_WALL) ? (srcX = 48, srcY = 16) : (srcX = 16, srcY = 32);
		if (srcX != -1 && srcY != -1)
		{
			image->drawTexture(cellx * 16, celly * 16, srcX, srcY, 16, 16);
		}
		if (checkFlag(FLAG_BRICK))
		{
			image->drawTexture(cellx * 16, celly * 16, 0, 32, 16, 16);
		}
		srcX = -1;
		srcY = -1;


		// �����
		if (mFlag & FLAG_FIRE_ORIGIN)
		{
			srcX = 48, srcY = 32;
		}
		else if (mFlag & FLAG_FIRE_X)
		{
			if (mFlag & FLAG_BRICK)
			{
				srcX = 0, srcY = 48;
			}
			else {
				srcX = 0, srcY = 16;
			}
		}
		else if (mFlag & FLAG_FIRE_Y)
		{
			if (mFlag & FLAG_BRICK)
			{
				srcX = 0, srcY = 48;
			}
			else
			{
				srcX = 16, srcY = 16;
			}
		}

		if (srcX != -1 && srcY != -1)
		{
			image->drawTexture(cellx * 16, celly * 16, srcX, srcY, 16, 16);
		}


		// ը�����������ϲ������Ⱦ
		if (checkFlag(FLAG_BAKUDA))
		{
			image->drawTexture(cellx * 16, celly * 16, 32, 32, 16, 16);
		}
	}
	void StaticObject::setFlag(Flag flag)
	{
		mFlag |= flag;
	}
	bool StaticObject::checkFlag(int flag)
	{
		return flag & mFlag;
	}
	bool StaticObject::checkFlag(int flag) const
	{
		return flag & mFlag;
	}
	void StaticObject::resetFlag(int flag)
	{
		// ������Ҫ����ǽΪ�ذ�  ��Ǵ��� 0000 0001 ��֮�� 1111 1110 ����ԭ��־λ��ô�Ϳ���������������

		mFlag &= ~flag;
	}
	// ��ըʱ����true
	bool StaticObject::updateBakudan()
	{
		//����ʱ����ը��������
		//������Ϊ��ʱ�Ƴ����󲢷��û�
		// ը���������ᱻ����Ϊ180  Ϊ0ʱ����Ϊflaseȡ��������ը
		if (!mBakudaCount)
		{
			// ��ը�Ƴ�ը������
			resetFlag(Flag::FLAG_BAKUDA);
			setFire(60, Flag::FLAG_FIRE_ORIGIN);
			// �����Ŀ�ʼ��������� ����Ϊ����ʱ��power  power�ö�̬��������
			// ��ʱʹ��Flag��ʾһ�³��������
			return true;
		}
		mBakudaCount--;
		return false;
	}
	int StaticObject::getBakudanPower()
	{
		return mBakudaPower;
	}
	bool StaticObject::setBakudan(int count, int power)
	{
		// ��λ������ը��ʱ�򲻷���
		if (!checkFlag(StaticObject::Flag::FLAG_BAKUDA)) {
			setFlag(StaticObject::Flag::FLAG_BAKUDA);
			mBakudaCount = count;
			mBakudaPower = power;
			return true;
		}
		// ������ʧ��ʱ�򷵻�false ���óɹ�ʱ��true
		return false;
	}
	bool StaticObject::setFire(int count, Flag flag)
	{
		mShockWavesCount = count;
		setFlag(flag);
		return true;
	}
	bool StaticObject::updateShockWaves()
	{
		if (mShockWavesCount > 0)
		{
			mShockWavesCount--;
			return false;
		}
		//��ʱ�����Ƴ�����ͳ����
		resetFlag(StaticObject::Flag::FLAG_FIRE_X | StaticObject::Flag::FLAG_FIRE_Y | StaticObject::Flag::FLAG_FIRE_ORIGIN);
		resetFlag(StaticObject::Flag::FLAG_BRICK);
		return true;
	}
}
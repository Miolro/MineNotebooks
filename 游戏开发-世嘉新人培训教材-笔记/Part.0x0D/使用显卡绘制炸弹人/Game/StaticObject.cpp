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
		// 背景渲染
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


		// 冲击波
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


		// 炸弹纹理在最上层最后渲染
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
		// 比如我要设置墙为地板  标记传入 0000 0001 非之后 1111 1110 与上原标志位那么就可以做到批量设置

		mFlag &= ~flag;
	}
	// 爆炸时返回true
	bool StaticObject::updateBakudan()
	{
		//更新时减少炸弹计数器
		//计数器为零时移除对象并放置火花
		// 炸弹计数器会被设置为180  为0时被定为flase取反发生爆炸
		if (!mBakudaCount)
		{
			// 爆炸移除炸弹对象
			resetFlag(Flag::FLAG_BAKUDA);
			setFire(60, Flag::FLAG_FIRE_ORIGIN);
			// 以中心开始发出冲击波 长度为设置时的power  power让动态对象设置
			// 暂时使用Flag表示一下冲击波类型
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
		// 当位置上有炸弹时候不放置
		if (!checkFlag(StaticObject::Flag::FLAG_BAKUDA)) {
			setFlag(StaticObject::Flag::FLAG_BAKUDA);
			mBakudaCount = count;
			mBakudaPower = power;
			return true;
		}
		// 当放置失败时候返回false 放置成功时候true
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
		//计时结束移除方块和冲击波
		resetFlag(StaticObject::Flag::FLAG_FIRE_X | StaticObject::Flag::FLAG_FIRE_Y | StaticObject::Flag::FLAG_FIRE_ORIGIN);
		resetFlag(StaticObject::Flag::FLAG_BRICK);
		return true;
	}
}
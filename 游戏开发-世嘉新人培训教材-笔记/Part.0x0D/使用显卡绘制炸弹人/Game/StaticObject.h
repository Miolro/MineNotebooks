#pragma once
class Image;
namespace Game
{
	class StaticObject
	{
	public:
		StaticObject();
		enum Flag
		{
			FLAG_WALL = (1 << 0),			//0000 0001  //墙
			FLAG_BRICK = (1 << 1),			//0000 0010  //砖
			FLAG_BAKUDA = (1 << 2),			//0000 0100  //炸弹
			FLAG_EXPLODING = (1 << 3),		//0000 1000	 //爆炸原点
			FLAG_FIRE_ORIGIN = (1 << 4),	//0001 0000  //冲击波原点
			FLAG_FIRE_X = (1 << 5),			//0010 0000	 //横向火
			FLAG_FIRE_Y = (1 << 6)			//0100 0000	 //纵向火

		};
		void draw(const int cellx, const int celly, const Image* image)const;

		void setFlag(Flag);
		bool checkFlag(int);
		bool checkFlag(int)const;
		void resetFlag(int);
		bool updateBakudan();
		bool setBakudan(int count, int power); //返回设置成功
		bool setFire(int count, Flag); // 持续时间和类型
		bool updateShockWaves();
		int getBakudanPower();
	private:
		int mFlag;
		// 炸弹属性

		int mBakudaCount;  // 炸弹状态计数
		int mBakudaPower;  // 爆炸威力
		int mShockWavesCount; // 冲击波状态计数器
	};
}


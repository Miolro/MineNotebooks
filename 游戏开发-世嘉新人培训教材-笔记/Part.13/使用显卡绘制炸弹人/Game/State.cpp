#include "State.h"
#include "GameLib/GameLib.h"
#include "../Utils/Pad.h"
namespace Game
{
	State::State(int stateId)
	{
		// 地图生成
		mImage = new Image("data/BakudanBitoImage.dds");
		mStaticObjects.setSize(WIDTH, HEIGHT);
		dyObject = new DynamicObject[1];
		for (int y = 0; y < HEIGHT; y++)
		{
			for (int x = 0; x < WIDTH; x++)
			{
				StaticObject& staObj = mStaticObjects(x, y);
				if (x == 0 || y == 0 || x == WIDTH - 1 || y == HEIGHT - 1) {
					staObj.setFlag(StaticObject::Flag::FLAG_WALL);
					GameLib::cout << "1";
				}
				else if (x % 2 == 0 && y % 2 == 0)
				{
					staObj.setFlag(StaticObject::Flag::FLAG_WALL);
					GameLib::cout << "1";
				}
				else if (GameLib::Framework::instance().getRandom(100) < 70)
				{
					staObj.setFlag(StaticObject::Flag::FLAG_BRICK);
					GameLib::cout << "2";
				}
				else
				{
					GameLib::cout << "0";
				}
			}
			GameLib::cout << "" << GameLib::endl;
		}
		// 放置动态对象
		dyObject[0].set(1, 2, DynamicObject::Type::PLAYER1);
		int x; int y;
		dyObject[0].getCell(&x, &y);

		mStaticObjects(x + 1, y).resetFlag(StaticObject::Flag::FLAG_BRICK);
		mStaticObjects(x - 1, y).resetFlag(StaticObject::Flag::FLAG_BRICK);
		mStaticObjects(x, y + 1).resetFlag(StaticObject::Flag::FLAG_BRICK);
		mStaticObjects(x, y - 1).resetFlag(StaticObject::Flag::FLAG_BRICK);
		// 初始化炸弹池

	}
	State::~State()
	{

	}
	State::Flag State::update()
	{
		// 获取当前在Cell的位置
		int dx, dy;
		// 碰撞检测
		int wallsX[9];
		int wallsY[9];
		dyObject[0].getCell(&dx, &dy);
		//这样判断火焰碰撞似乎不太严格
		if (mStaticObjects(dx, dy).checkFlag(StaticObject::Flag::FLAG_FIRE_Y | StaticObject::Flag::FLAG_FIRE_X | StaticObject::Flag::FLAG_FIRE_ORIGIN))
		{
			dyObject[0].die();
		}
		if (dyObject[0].isDead()) {
			// 玩家已经死亡那么就显示结束页面
			return State::Flag::LOSE;
		}
		// 未死亡就去判断是否在火焰范围中

		int wallNumber = 0;
		// 以动态对象为中心的十字上下左右各一格
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				// *需要计算当前位置的9宫格位置  不能直接以循环的x和y去二维数组里取对象mStaticObjects(x, y);<-像这样
				// *这样取的位置是相对与地图二维素组的  而不是相对于当前玩家的位置

				StaticObject& staObj = mStaticObjects(dx + x - 1, dy + y - 1);
				// 如果是墙体或者可破坏方块那么放入到对象中 | 允许移动但是致密的格子
				if (staObj.checkFlag(StaticObject::Flag::FLAG_WALL | StaticObject::Flag::FLAG_BRICK))
				{
					// 这边主要是获取墙的横向坐标和纵向坐标
					wallsX[wallNumber] = dx + x - 1;
					wallsY[wallNumber] = dy + y - 1;
					wallNumber++;
				}
			}
		}
		dyObject->move(wallsX, wallsY, wallNumber);

		// 设置爆炸信息
		if (dyObject->hasBombButtonPressed())
		{
			// 在地图上的位置D
			StaticObject& staObj = mStaticObjects(dx, dy);
			// 可以设置                 爆炸时间/爆炸威力
			if (staObj.setBakudan(LAST_BOOM_TIME, 3))
			{
				for (int i = 0; i < 15; i++)
				{
					// 检查炸弹位置  并保存炸弹位置
					if (!mBakudanX[i] or !mBakudanY[i])
					{
						mBakudanX[i] = dx;
						mBakudanY[i] = dy;
						GameLib::cout << "炸弹池" << BAKUDANPOOL - i << GameLib::endl;
						break;
					}
				}
			};
		}
		// 炸弹更新  更新全部的炸弹状态  虽然感觉把自己提出来构建一个对象比较好
		// 只需要保存炸弹位置就不用整个地图遍历寻找炸弹位置了  但是炸弹放太快会导致越界
		for (int i = 0; i < BAKUDANPOOL; i++)
		{
			// 这边改为炸弹池存储
			int x = mBakudanX[i];
			int y = mBakudanY[i];
			StaticObject& staObj = mStaticObjects(x, y);
			// 这样写可以减少一层嵌套  不然下面的更新的if要写在检查炸弹的if里
			if (!staObj.checkFlag(StaticObject::Flag::FLAG_BAKUDA))
			{
				continue;
			}
			// 炸弹更新返回爆炸
			if (staObj.updateBakudan())
			{
				// 将爆炸设置为爆炸中心
				staObj.setFlag(StaticObject::FLAG_FIRE_ORIGIN);
				//计算上下左右的距离 以爆炸力量为最大范围
				// i = 0 已经被爆炸原点给占用
				// 代码有点长
				for (int i = 1; i < staObj.getBakudanPower(); i++)
				{
					// 左边火
					StaticObject& temp = mStaticObjects(x - i, y);
					// 是墙直接结束循环  这边可以加上如果是砖头的破坏
					if (temp.checkFlag(StaticObject::Flag::FLAG_WALL)) { break; }
					else if (temp.checkFlag(StaticObject::Flag::FLAG_BRICK))
					{
						temp.setFire(SHOCK_WAVES_TIME, StaticObject::FLAG_FIRE_Y);
						break;
					}
					temp.setFire(SHOCK_WAVES_TIME, StaticObject::FLAG_FIRE_X);
				}
				for (int i = 1; i < staObj.getBakudanPower(); i++)
				{
					// 上边火
					StaticObject& temp = mStaticObjects(x, y - i);
					// 是墙直接结束循环
					if (temp.checkFlag(StaticObject::Flag::FLAG_WALL)) { break; }
					else if (temp.checkFlag(StaticObject::Flag::FLAG_BRICK))
					{
						temp.setFire(SHOCK_WAVES_TIME, StaticObject::FLAG_FIRE_Y);
						break;
					}
					temp.setFire(SHOCK_WAVES_TIME, StaticObject::FLAG_FIRE_Y);
				}
				for (int i = 1; i < staObj.getBakudanPower(); i++)
				{
					// 右边火
					StaticObject& temp = mStaticObjects(x + i, y);
					// 是墙直接结束循环
					if (temp.checkFlag(StaticObject::Flag::FLAG_WALL)) { break; }
					else if (temp.checkFlag(StaticObject::Flag::FLAG_BRICK))
					{
						temp.setFire(SHOCK_WAVES_TIME, StaticObject::FLAG_FIRE_Y);
						break;
					}
					temp.setFire(SHOCK_WAVES_TIME, StaticObject::FLAG_FIRE_X);
				}
				for (int i = 1; i < staObj.getBakudanPower(); i++)
				{
					// 下边火
					StaticObject& temp = mStaticObjects(x, y + 1);
					// 是墙直接结束循环
					if (temp.checkFlag(StaticObject::Flag::FLAG_WALL)) { break; }
					else if (temp.checkFlag(StaticObject::Flag::FLAG_BRICK))
					{
						temp.setFire(SHOCK_WAVES_TIME, StaticObject::FLAG_FIRE_Y);
						break;
					}
					temp.setFire(SHOCK_WAVES_TIME, StaticObject::FLAG_FIRE_Y);
				}

				mBakudanX[i] = 0;
				mBakudanY[i] = 0;
			}
		}
		for (int i = 0; i < WIDTH * HEIGHT; i++)
		{
			// 带有火焰就减少计数器
			StaticObject& temp = mStaticObjects(i, 0);
			if (temp.checkFlag(StaticObject::FLAG_FIRE_X | StaticObject::Flag::FLAG_FIRE_Y | StaticObject::Flag::FLAG_FIRE_ORIGIN))
			{
				temp.updateShockWaves();
			}
		}
	}
	void State::draw()
	{
		// 背景 钢板 石砖 地板
		for (int y = 0; y < HEIGHT; y++)
		{
			for (int x = 0; x < WIDTH; x++)
			{
				mStaticObjects(x, y).draw(x, y, mImage);
			}
		}

		dyObject[0].draw(mImage);
	}
}
#include "State.h"
#include "GameLib/GameLib.h"
#include "../Utils/Pad.h"
namespace Game
{
	State::State(int stateId)
	{
		// ��ͼ����
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
		// ���ö�̬����
		dyObject[0].set(1, 2, DynamicObject::Type::PLAYER1);
		int x; int y;
		dyObject[0].getCell(&x, &y);

		mStaticObjects(x + 1, y).resetFlag(StaticObject::Flag::FLAG_BRICK);
		mStaticObjects(x - 1, y).resetFlag(StaticObject::Flag::FLAG_BRICK);
		mStaticObjects(x, y + 1).resetFlag(StaticObject::Flag::FLAG_BRICK);
		mStaticObjects(x, y - 1).resetFlag(StaticObject::Flag::FLAG_BRICK);
		// ��ʼ��ը����

	}
	State::~State()
	{

	}
	State::Flag State::update()
	{
		// ��ȡ��ǰ��Cell��λ��
		int dx, dy;
		// ��ײ���
		int wallsX[9];
		int wallsY[9];
		dyObject[0].getCell(&dx, &dy);
		//�����жϻ�����ײ�ƺ���̫�ϸ�
		if (mStaticObjects(dx, dy).checkFlag(StaticObject::Flag::FLAG_FIRE_Y | StaticObject::Flag::FLAG_FIRE_X | StaticObject::Flag::FLAG_FIRE_ORIGIN))
		{
			dyObject[0].die();
		}
		if (dyObject[0].isDead()) {
			// ����Ѿ�������ô����ʾ����ҳ��
			return State::Flag::LOSE;
		}
		// δ������ȥ�ж��Ƿ��ڻ��淶Χ��

		int wallNumber = 0;
		// �Զ�̬����Ϊ���ĵ�ʮ���������Ҹ�һ��
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				// *��Ҫ���㵱ǰλ�õ�9����λ��  ����ֱ����ѭ����x��yȥ��ά������ȡ����mStaticObjects(x, y);<-������
				// *����ȡ��λ����������ͼ��ά�����  ����������ڵ�ǰ��ҵ�λ��

				StaticObject& staObj = mStaticObjects(dx + x - 1, dy + y - 1);
				// �����ǽ����߿��ƻ�������ô���뵽������ | �����ƶ��������ܵĸ���
				if (staObj.checkFlag(StaticObject::Flag::FLAG_WALL | StaticObject::Flag::FLAG_BRICK))
				{
					// �����Ҫ�ǻ�ȡǽ�ĺ����������������
					wallsX[wallNumber] = dx + x - 1;
					wallsY[wallNumber] = dy + y - 1;
					wallNumber++;
				}
			}
		}
		dyObject->move(wallsX, wallsY, wallNumber);

		// ���ñ�ը��Ϣ
		if (dyObject->hasBombButtonPressed())
		{
			// �ڵ�ͼ�ϵ�λ��D
			StaticObject& staObj = mStaticObjects(dx, dy);
			// ��������                 ��ըʱ��/��ը����
			if (staObj.setBakudan(LAST_BOOM_TIME, 3))
			{
				for (int i = 0; i < 15; i++)
				{
					// ���ը��λ��  ������ը��λ��
					if (!mBakudanX[i] or !mBakudanY[i])
					{
						mBakudanX[i] = dx;
						mBakudanY[i] = dy;
						GameLib::cout << "ը����" << BAKUDANPOOL - i << GameLib::endl;
						break;
					}
				}
			};
		}
		// ը������  ����ȫ����ը��״̬  ��Ȼ�о����Լ����������һ������ȽϺ�
		// ֻ��Ҫ����ը��λ�þͲ���������ͼ����Ѱ��ը��λ����  ����ը����̫��ᵼ��Խ��
		for (int i = 0; i < BAKUDANPOOL; i++)
		{
			// ��߸�Ϊը���ش洢
			int x = mBakudanX[i];
			int y = mBakudanY[i];
			StaticObject& staObj = mStaticObjects(x, y);
			// ����д���Լ���һ��Ƕ��  ��Ȼ����ĸ��µ�ifҪд�ڼ��ը����if��
			if (!staObj.checkFlag(StaticObject::Flag::FLAG_BAKUDA))
			{
				continue;
			}
			// ը�����·��ر�ը
			if (staObj.updateBakudan())
			{
				// ����ը����Ϊ��ը����
				staObj.setFlag(StaticObject::FLAG_FIRE_ORIGIN);
				//�����������ҵľ��� �Ա�ը����Ϊ���Χ
				// i = 0 �Ѿ�����ըԭ���ռ��
				// �����е㳤
				for (int i = 1; i < staObj.getBakudanPower(); i++)
				{
					// ��߻�
					StaticObject& temp = mStaticObjects(x - i, y);
					// ��ǽֱ�ӽ���ѭ��  ��߿��Լ��������שͷ���ƻ�
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
					// �ϱ߻�
					StaticObject& temp = mStaticObjects(x, y - i);
					// ��ǽֱ�ӽ���ѭ��
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
					// �ұ߻�
					StaticObject& temp = mStaticObjects(x + i, y);
					// ��ǽֱ�ӽ���ѭ��
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
					// �±߻�
					StaticObject& temp = mStaticObjects(x, y + 1);
					// ��ǽֱ�ӽ���ѭ��
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
			// ���л���ͼ��ټ�����
			StaticObject& temp = mStaticObjects(i, 0);
			if (temp.checkFlag(StaticObject::FLAG_FIRE_X | StaticObject::Flag::FLAG_FIRE_Y | StaticObject::Flag::FLAG_FIRE_ORIGIN))
			{
				temp.updateShockWaves();
			}
		}
	}
	void State::draw()
	{
		// ���� �ְ� ʯש �ذ�
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
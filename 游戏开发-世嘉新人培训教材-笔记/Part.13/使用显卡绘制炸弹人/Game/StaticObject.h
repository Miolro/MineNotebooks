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
			FLAG_WALL = (1 << 0),			//0000 0001  //ǽ
			FLAG_BRICK = (1 << 1),			//0000 0010  //ש
			FLAG_BAKUDA = (1 << 2),			//0000 0100  //ը��
			FLAG_EXPLODING = (1 << 3),		//0000 1000	 //��ըԭ��
			FLAG_FIRE_ORIGIN = (1 << 4),	//0001 0000  //�����ԭ��
			FLAG_FIRE_X = (1 << 5),			//0010 0000	 //�����
			FLAG_FIRE_Y = (1 << 6)			//0100 0000	 //�����

		};
		void draw(const int cellx, const int celly, const Image* image)const;

		void setFlag(Flag);
		bool checkFlag(int);
		bool checkFlag(int)const;
		void resetFlag(int);
		bool updateBakudan();
		bool setBakudan(int count, int power); //�������óɹ�
		bool setFire(int count, Flag); // ����ʱ�������
		bool updateShockWaves();
		int getBakudanPower();
	private:
		int mFlag;
		// ը������

		int mBakudaCount;  // ը��״̬����
		int mBakudaPower;  // ��ը����
		int mShockWavesCount; // �����״̬������
	};
}


#include "GameLib/Framework.h"
#include "GameLib/Math.h"
#include "Image.h"
#include "Vector2.h"
#include "Matrix32.h"

namespace GameLib {
	int round(double a)
	{
		a += (a > 0.0) ? 0.5 : -0.5f;
		return static_cast<int>(a);
	}

	bool initFlag = false;
	Image* image = nullptr;
	Vector2 pointO(50.0, 30.0);
	unsigned* vram;
	int ww = 0;
	int gAngle = 0;
	void Framework::update()
	{
		if (!initFlag)
		{
			image = new Image("background.dds");
			ww = width();
			vram = videoMemory();
			initFlag = true;
		}
		Vector2 pointP1, pointP2;
		pointP1.addVector(pointO, Vector2(image->iWidth(), 0));
		pointP2.addVector(pointO, Vector2(0, image->iHeight()));


		vram[round(pointO.y) * ww + round(pointO.x)] = 0xffff0000;
		vram[round(pointP1.y) * ww + round(pointP1.x)] = 0xff00ff00;
		vram[round(pointP2.y) * ww + round(pointP2.x)] = 0xff0000ff;

		Vector2 t1, t2, t3;

		// �ƶ� �������þ���
		//matrix32.transfromMove(&t1, pointO, 2.0, 2.0);
		//matrix32.transfromMove(&t2, pointP1, 2.0, 2.0);
		//matrix32.transfromMove(&t3, pointP2, 2.0, 2.0);

		// �ƶ�  ���þ���
		//Matrix32 matrix32(1, 0, 10, 0, 1, 20.0);
		//matrix32.transfromMove(&t1, pointO);
		//matrix32.transfromMove(&t2, pointP1);
		//matrix32.transfromMove(&t3, pointP2);

		// ��ת
		//double sine = sin(gAngle);
		//double cosine = cos(gAngle)��
		//Matrix32 matrix32(cosine, -sine, 0, sine, cosine, 0);
		//Vector2 originP(image->iWidth() / 2, image->iHeight() / 2);
		//originP += pointO;

		// �ڶ�����������������  ���������������ϽǾ���ͼ������λ�õ�����
		//matrix32.transfromRoll(&t1, pointO, originP);
		//matrix32.transfromRoll(&t2, pointP1, originP);
		//matrix32.transfromRoll(&t3, pointP2, originP);
		// 

		// ����
		//Matrix32 matrix32(0.5, 0, 0, 0, 0.5, 0);
		//matrix32.transfromScal(&t1, pointO, originP);
		//matrix32.transfromScal(&t2, pointP1, originP);
		//matrix32.transfromScal(&t3, pointP2, originP);

		vram[round(t1.y) * ww + round(t1.x)] = 0xffff0000;
		vram[round(t2.y) * ww + round(t2.x)] = 0xff00ff00;
		vram[round(t3.y) * ww + round(t3.x)] = 0xff0000ff;

		gAngle++;
	}
}
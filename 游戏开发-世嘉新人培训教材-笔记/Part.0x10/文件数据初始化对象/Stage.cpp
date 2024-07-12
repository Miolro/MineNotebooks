#include "Stage.h"
#include "Vector3.h"
#include "Matrix44.h"
#include "GameLib/Framework.h"
Stage::Stage()
{
}
Stage::~Stage()
{
}

void Stage::draw(Matrix44 pvm)
{
	Vector3 p[4];
	unsigned c[4];
	p[0].set(-50.0, 0.0, -50.0);
	p[1].set(-50.0, 0.0, 50.0);
	p[2].set(50.0, 0.0, -50.0);
	p[3].set(50.0, 0.0, 50.0);

	c[0] = 0xffff0000;
	c[1] = 0xff00ff00;
	c[2] = 0xff0000ff;
	c[3] = 0xffffffff;

	double p4[4][4];
	for (int i = 0; i < 4; i++)
	{
		pvm.multiply(p4[i], p[i]);
	}
	GameLib::Framework frame = GameLib::Framework::instance();
	frame.drawTriangle3DH(p4[0], p4[1], p4[2], 0, 0, 0, c[0], c[1], c[2]);
	frame.drawTriangle3DH(p4[3], p4[1], p4[2], 0, 0, 0, c[3], c[1], c[2]);
}

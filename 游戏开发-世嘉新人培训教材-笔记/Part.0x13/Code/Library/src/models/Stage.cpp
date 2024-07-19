#include "models/Stage.h"
#include "GameLib/Framework.h"
#include "base/calculate/Matrix44.h"
#include "engine/collision/Triangle.h"
namespace Model
{
    Stage::Stage()
    {
        Vector3 p[4];
        unsigned c[4]; //易于识别的颜色
        mPosition[0].set(-100.0, 0.0, -100.0);
        mPosition[1].set(-100.0, 0.0, 100.0);
        mPosition[2].set(100.0, 0.0, -100.0);
        mPosition[3].set(100.0, 0.0, 100.0);
        mColor[0] = 0xffff0000; //红色的
        mColor[1] = 0xff00ff00; //绿
        mColor[2] = 0xff0000ff; //蓝色的
        mColor[3] = 0xffffffff; //白
        mTriangle = new Triangle * [2];

        mTriangle[0] = new Triangle();
        mTriangle[1] = new Triangle();
        mTriangle[0]->setPosition(mPosition[0], mPosition[1], mPosition[2]);
        mTriangle[1]->setPosition(mPosition[3], mPosition[1], mPosition[2]);

    }

    void Stage::restrictMove(Vector3* v, const Vector3& position) const
    {
        bool hit = false;
        double t = 0.0;
        for (int i = 0; i < 2; i++)
        {
            hit = mTriangle[i]->isIntersectTriangleTest(*v, position);
            if (hit)
            {
                break;
            }
        }
        if (hit)
        {
            Vector3 d, e, n;
            d.setSub(mPosition[1], mPosition[0]);
            e.setSub(mPosition[2], mPosition[0]);
            n.normal(d, e);

            n *= n.dot(*v) / n.squareLength();
            *v -= n;
        }
    }

    void Stage::draw(const Matrix44& matrix)const
    {
        double p4[4][4];
        for (int i = 0; i < 4; i++)
        {
            matrix.mul(p4[i], mPosition[i]);
        }

        GameLib::Framework frame = GameLib::Framework::instance();
        frame.drawTriangle3DH(p4[0], p4[1], p4[2], 0, 0, 0, mColor[0], mColor[1], mColor[2]);
        frame.drawTriangle3DH(p4[3], p4[1], p4[2], 0, 0, 0, mColor[3], mColor[1], mColor[2]);
    }
}
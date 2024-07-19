#include "engine/collision/Triangle.h"
#include <limits>
using namespace std;
namespace engine
{
    namespace collision
    {
        void Triangle::setPosition(const Vector3& mP0, const Vector3& mP1, const Vector3& mP2)
        {
            mPosition[0] = mP0;
            mPosition[1] = mP1;
            mPosition[2] = mP2;
        }
        bool Triangle::isIntersectTriangleTest(const Vector3& line, const Vector3& modelPos) const
        {
            double t = getIntersectionTime(line, modelPos);
            return (t >= 0.0 && t <= 1.0);
        }
        // 移动方向,模型的位置
        double Triangle::getIntersectionTime(const Vector3& line, const Vector3& modelPos) const
        {
            double inf = numeric_limits< double >::max();
            // 首先判断向量是否平行  平行的条件是与面的法向量垂直
            Vector3 lineP;
            Vector3 lineE;
            Vector3 lineD;
            lineP.setSum(line, modelPos);
            lineE.setSub(mPosition[1], mPosition[0]);
            lineD.setSub(mPosition[2], mPosition[0]);
            Vector3 normal;
            normal.normal(lineE, lineD);

            // 计算是否与三角形平行
            // 如果于面平行那么表示法线与交线垂直
            double isParallelWithTriangle = normal.dot(line);
            if (!isParallelWithTriangle) // 0时候表示cos90度  提前退出判断
            {
                return false;
            }
            //现在求线段交点是否在面上  求出uv相加是否在0到1的范围中
            Vector3 lineF;
            lineF.setSub(mPosition[0], modelPos);
            double t = lineF.dot(normal) / isParallelWithTriangle;
            Vector3 pointP;
            pointP.setMul(lineP, t); // 与三角形同面的点
            Vector3 lineCP;
            lineCP.setSub(pointP, mPosition[0]);

            double cpe = lineCP.dot(lineE);
            double cpd = lineCP.dot(lineD);
            double dd = lineD.dot(lineD);
            double de = lineD.dot(lineE);
            double ee = lineE.dot(lineE);

            // 分母
            double denominator = 1.0 / (de * de - ee * dd);

            double u = (cpd * de - cpe * dd) * denominator;
            if (u < 0 || u > 1) {
                return inf;
            }
            double v = (cpe * de - cpd * ee) * denominator;
            if (v < 0 || (u + v > 1)) {
                return inf;
            }
            return t;

        }
        void Triangle::restrictMove(Vector3* v, const Vector3& p)const
        {

            double t = isIntersectTriangleTest(*v, p);
            if (!(t >= 0.0 && t <= 1.0)) {
                return; //它不会碰撞所以就结束了
            }
            Vector3 d, e, n;
            d.setSub(mPosition[1], mPosition[0]);
            e.setSub(mPosition[2], mPosition[0]);
            n.normal(d, e);

            n *= n.dot(*v) / n.squareLength();
            *v -= n;
        }
    }
}
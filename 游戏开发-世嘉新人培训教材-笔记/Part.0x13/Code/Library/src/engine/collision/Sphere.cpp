#include "engine/collision/Sphere.h"
namespace engine
{
    namespace collision

    {
        void Sphere::setPosition(const Vector3& position)
        {
            mPosition = position;
        }
        void Sphere::setRadius(double rad)
        {
            mRadius = rad;
        }
        bool Sphere::isIntersectCircleTest(const Sphere& oth) const
        {
            Vector3 difference;
            difference.setSub(mPosition, oth.mPosition);
            double squareDistance = difference.squareLength();
            double rSum = mRadius + oth.mRadius;
            rSum *= rSum;
            return (squareDistance < rSum);
        }

        void Sphere::restrictMove(Vector3* v, const Sphere& a)const
        {
            const Vector3* vcopy = v;
            Sphere t = *this;
            t.mPosition += *vcopy;
            if (!t.isIntersectCircleTest(a))
            {
                return;
            }

            Vector3 d;
            d.setSub(mPosition, a.mPosition); //c0-c1 = d
            double dotDV = d.dot(*v); //dot(d, v)
            double dLength2 = d.squareLength(); //|d|^2
            d *= (dotDV / dLength2); //dot(b,v) / |d|^2
            //最后减法
            *v -= d;
        }
    }
}

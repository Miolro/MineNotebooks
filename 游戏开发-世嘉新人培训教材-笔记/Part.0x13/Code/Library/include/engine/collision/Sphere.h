#pragma once
#include "base/calculate/Vector3.h"
using namespace base::calculate;
namespace engine
{
    namespace collision
    {
        class Sphere
        {
        public:
            void setPosition(const Vector3& position);
            void setRadius(double rad);
            bool isIntersectCircleTest(const Sphere& b)const;   // 矩形检测
            void restrictMove(Vector3* direction, const Sphere& oth)const;
        private:
            Vector3 mPosition;
            double mRadius;
        };
    }
}



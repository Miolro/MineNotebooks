#pragma once
#include "base/calculate/Vector3.h"
using namespace base::calculate;
namespace engine
{
    namespace collision
    {
        class Triangle
        {
        public:
            void setPosition(const Vector3& mP0, const Vector3& mP1, const Vector3& mP2);
            bool isIntersectTriangleTest(const Vector3& line, const Vector3& modelPos) const;
            double getIntersectionTime(const Vector3& line, const Vector3& modelPos)const;
            void restrictMove(Vector3* v, const Vector3& p)const;
        private:
            Vector3 mPosition[3];
        };

    }
}
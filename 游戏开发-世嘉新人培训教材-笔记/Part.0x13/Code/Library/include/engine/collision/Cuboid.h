#pragma once
#include "base/calculate/Vector3.h"
namespace engine
{
    namespace collision
    {
        using namespace base::calculate;
        class Cuboid
        {
        public:
            Cuboid();
            void setPosition(const Vector3& instancePosition);
            void setHalfSize(const Vector3& instanceHalfSize);
            bool isIntersectRectTest(const Cuboid& b)const;   // 矩形检测
            void restrictMove(Vector3* direction, const Cuboid& oth) const;
        private:
            int mX;
            int mY;
            int mZ;
            int mHalfSizeX;
            int mHalfSizeY;
            int mHalfSizeZ;
        };
    }
}



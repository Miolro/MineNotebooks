#include "engine/collision/Cuboid.h"
#include "GameLib/GameLib.h"
#include "GameLib/Math.h"
namespace {
    const double UNIT = 1000.0;
}
namespace engine
{
    namespace collision
    {
        Cuboid::Cuboid() :
            mX(0),
            mY(0),
            mZ(0),
            mHalfSizeX(0),
            mHalfSizeY(0),
            mHalfSizeZ(0)
        {
        }

        void Cuboid::setPosition(const Vector3& instancePosition)
        {
            mX = static_cast<int>(instancePosition.x * UNIT);
            mY = static_cast<int>(instancePosition.y * UNIT);
            mZ = static_cast<int>(instancePosition.z * UNIT);
        }
        [[decltype]]
        void Cuboid::setHalfSize(const Vector3& instanceHalfSize)
        {
            mHalfSizeX = static_cast<int>(instanceHalfSize.x * UNIT);
            mHalfSizeY = static_cast<int>(instanceHalfSize.y * UNIT);
            mHalfSizeZ = static_cast<int>(instanceHalfSize.z * UNIT);
        }

        // 矩形测试
        bool Cuboid::isIntersectRectTest(const Cuboid& b) const
        {
            int selfLeft = mX - mHalfSizeX; // 左边
            int selfRigh = mX + mHalfSizeX; // 右边
            int othLeft = b.mX - b.mHalfSizeX; // 左边-
            int othRigh = b.mX + b.mHalfSizeX; // 右边+
            if ((selfRigh > othLeft) && (othRigh > selfLeft))
            {
                int selfForw = mZ - mHalfSizeZ; // 前面
                int selfBack = mZ + mHalfSizeZ; // 后面
                int othForw = b.mZ - b.mHalfSizeZ; // 前面-
                int othBack = b.mZ + b.mHalfSizeZ; // 后面+
                if ((selfForw < othBack) && (othForw < selfBack))
                {
                    int selfTop = mY + mHalfSizeY; // 上面
                    int selfBott = mY - mHalfSizeY; // 下面
                    int othTop = b.mY + b.mHalfSizeY; // 上面
                    int othBott = b.mY - b.mHalfSizeY; // 下面
                    if ((selfBott < othTop) && (othBott < selfTop))
                    {
                        return true;
                    }
                }
            }
            return false;
        }
        void Cuboid::restrictMove(Vector3* direction, const Cuboid& oth) const
        {
            int dirX = static_cast<int>(direction->x * UNIT); // 单位距离
            int dirY = static_cast<int>(direction->y * UNIT); // 单位距离
            int dirZ = static_cast<int>(direction->z * UNIT); // 单位距离

            // 测试移动
            Cuboid _this = *this;
            bool r = false;
            _this.mX += dirX;// 测试移动
            _this.mZ += dirZ;// 测试移动
            _this.mY += dirY;// 测试移动

            r = _this.isIntersectRectTest(oth);
            if (!r) {
                int a = 1;
                return; // 没有碰撞
            }
            _this.mZ -= dirZ;// 测试移动
            r = _this.isIntersectRectTest(oth);
            if (!r) {
                direction->z = 0.0;
                return; // 没有碰撞
            }

            _this.mZ += dirZ;// 测试移动
            _this.mX -= dirX;
            r = _this.isIntersectRectTest(oth);
            if (!r) {
                direction->x = 0.0;
                return; // 没有碰撞
            }

            _this.mX += dirX;
            _this.mY -= dirY;
            r = _this.isIntersectRectTest(oth);
            if (!r) {
                direction->y = 0.0;
                return; // 没有碰撞
            }

            _this.mX -= dirX;
            r = _this.isIntersectRectTest(oth);
            if (!r) {
                direction->y = direction->x = 0.0;
                return; // 没有碰撞
            }

            _this.mY += dirY;
            _this.mZ -= dirZ;
            r = _this.isIntersectRectTest(oth);
            if (!r) {
                direction->z = direction->x = 0.0;
                return; // 没有碰撞
            }
            _this.mX += dirX;
            _this.mY -= dirY;
            r = _this.isIntersectRectTest(oth);
            if (!r) {
                direction->z = direction->y = 0.0;
                return; // 没有碰撞
            }
        }
    }
}

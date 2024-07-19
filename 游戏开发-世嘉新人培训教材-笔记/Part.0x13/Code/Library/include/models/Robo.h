#pragma once
#include "base/calculate/Vector3.h"
#include "engine/collision/Cuboid.h"
#include "engine/collision/Sphere.h"
#include <engine/collision/Sphere.h>

namespace base
{
    namespace calculate
    {
        class Vector3;
        class Matrix44;
    }
}

namespace engine
{
    namespace blueprint
    {
        class Batch;
        class Blueprint;
    }
    namespace base
    {
        class Pad;
    }
}

namespace models
{
    using namespace base::calculate;
    using namespace engine::blueprint;
    using namespace engine::collision;
    using namespace engine::base;
    using namespace engine::blueprint;
    class Bullet;
    class Robo
    {
    public:
        Robo(Vector3 position, double* angle, const Blueprint* bluePrint);
        void update(const Robo* robo);          // 主要更新函数
        void draw(const Matrix44& pwm);         // 绘制
        const Vector3* position()const;         // 模型位置
        void direction(Vector3* vector) const;  // 获取朝向
        double angle();                         // 获取模型角度
        const Cuboid* cuboid()const;            // 碰撞对象模型(长方体)
        const Sphere* sphere()const;            // 碰撞对象模型(球体)
    private:
        void move();
        void turn();
        void autoAim();
        void setTatget(const Robo* robo);
        void fire();
        static const double sMoveMaxSpeed;      // 最大移动速度
        static const double sMoveZeroToMaxTime; // 加速时间
        static const double sTrunSpeed;         // 旋转速度
        static const double sTrunCount;         // 最大加速时间
        static const double sFlySpeed;          // 飞行速度
        static const int sBulletNum;             // 弹药数量
        const Robo* aimTarget;                  // 瞄准的目标

        double mAngleVelocityY;                 // 旋转角速度
        Vector3 mMoveVelocity;                  // 移动速度

        Vector3 mPosition;
        Vector3 mPoint[4];
        Cuboid mCuboid;
        Sphere mSphere;
        Bullet* mBulletPool;

        double mAngleXYZ[3];
        const Blueprint* mBlueprint;
        const Batch* mBatch;
        Pad* mPad;
    };
}
#pragma once
#include "base/calculate/Vector3.h"
namespace engine
{
    namespace blueprint
    {
        class Batch;
        class Blueprint;
    }
}
namespace base
{
    namespace calculate
    {
        class Matrix34;
        class Matrix44;
    }
}
namespace models
{
    using namespace engine::blueprint;
    using namespace base::calculate;
    class Bullet
    {
    public:
        Bullet();
        const bool isReady();
        void create(const Blueprint& blueprint, const char* name, const Vector3& setPos, const Vector3& dir);
        void update(const Vector3& enemyPos);
        void draw(const Matrix44& pwm);
    private:
        static const double sSpeed;
        static const int sTime;

        int mTime;      //寿命计数器
        bool mReady;    // 是否就绪  准备发射
        Vector3 mPosition;
        Vector3 mDir;
        const Batch* mBatch;
    };
}

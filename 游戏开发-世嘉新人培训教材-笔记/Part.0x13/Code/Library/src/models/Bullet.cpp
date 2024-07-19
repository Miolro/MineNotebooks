#include "models/Bullet.h"
#include "GameLib/Math.h"
#include "base/calculate/Vector3.h"
#include "base/calculate/Matrix44.h"
#include "base/calculate/Matrix34.h"
#include "engine/blueprint/Blueprint.h"
#include "engine/blueprint/Batch.h"
namespace models
{

    const double Bullet::sSpeed = 0.5;
    const int Bullet::sTime = 120;
    Bullet::Bullet() :mReady(true), mBatch(0)
    {
    }
    const bool Bullet::isReady()
    {
        return mReady;
    }

    void Bullet::create(const Blueprint& blueprint, const char* name, const Vector3& setPos, const Vector3& dir)
    {
        mBatch = blueprint.batch(name);
        mPosition.set(setPos);
        mReady = false;
        mDir.set(dir);
        mTime = 0;
    }
    void Bullet::update(const Vector3& enemyPos)
    {
        if (mTime > sTime)
        {
            mReady = true;
            mTime = 0;
            return;
        }
        Vector3 temp;
        temp.setSub(enemyPos, mPosition);
        //需要确认怎么偏转离敌人最近
        double enemDir = GameLib::atan2(temp.x, temp.z);// 敌人位置
        double xzAngle = GameLib::atan2(mDir.x, mDir.z);// 发射角度

        Matrix34 trans;
        trans.rotationY(&trans, xzAngle);
        Vector3 speed(0.0, 0.0, sSpeed);
        trans.mul(&speed, speed);
        mPosition += speed;
        mTime++;
    }
    void Bullet::draw(const Matrix44& pwm)
    {
        Matrix34 wm;
        wm.translate(mPosition);
        Matrix44 trans;
        trans.setMul(pwm, wm);
        mBatch->draw(trans);
    }
}
#include "models/Robo.h"
#include "models/Bullet.h"
#include "base/calculate/Matrix34.h"
#include "base/calculate/Matrix44.h"
#include "base/calculate/Vector3.h"

#include "GameLib/Framework.h"
#include "GameLib/Math.h"

#include "engine/blueprint/Blueprint.h"
#include "engine/blueprint/Batch.h"
#include "engine/base/Pad.h"
#include "engine/collision/Cuboid.h"

namespace models
{
    const double Robo::sMoveMaxSpeed = 0.5;
    const double Robo::sTrunSpeed = 1.0;
    const double Robo::sMoveZeroToMaxTime = 40; // 40帧达到最高移动速度
    const double Robo::sTrunCount = 10;         // 在第几帧时候转过去
    const double Robo::sFlySpeed = 0.5;
    const int Robo::sBulletNum = 10;


    Robo::Robo(Vector3 position, double* angle, const Blueprint* blueprint) :
        mBlueprint(blueprint),
        mPosition(position),
        mAngleXYZ{ angle[0],angle[1],angle[2] },
        mBatch(0) {
        Vector3 tempPosition;
        mBulletPool = new Bullet[sBulletNum];
        tempPosition.setSum(mPosition, Vector3(0.0, 0.5, 0.0));
        mBatch = blueprint->batch("robo");
        mCuboid.setPosition(tempPosition);
        mCuboid.setHalfSize(Vector3(0.5, 1.0, 0.5));
        mSphere.setPosition(tempPosition);
        mSphere.setRadius(0.5);
        mPad = new Pad();
    }
    void Robo::update(const Robo* robo)
    {
        //Vector3 t = mPosition;
        //t.y += 0.5;
        //// 设置碰撞箱
        //mSphere.setPosition(t);
        //mCuboid.setPosition(t);
        move();
        setTatget(robo);
        autoAim();
        turn();
        fire();
        for (int i = 0; i < sBulletNum; i++)
        {
            if (!mBulletPool[i].isReady())
            {
                mBulletPool[i].update(*robo->position());
            }
        }
        mPosition += mMoveVelocity;
    }
    void Robo::draw(const Matrix44& pwm)
    {
        // 设置角度矩阵变换
        Matrix34 trans;
        trans.translate(mPosition);
        trans.rotation(mAngleXYZ);

        Matrix44 matrix;
        matrix.setMul(pwm, trans);
        mBatch->draw(matrix);
        for (int i = 0; i < sBulletNum; i++)
        {
            if (!mBulletPool[i].isReady())
            {
                mBulletPool[i].draw(pwm);
            }
        }
    }
    //属性
    const Vector3* Robo::position()const
    {
        return &mPosition;
    }
    void Robo::direction(Vector3* vector)const
    {
        Matrix34 matrix;
        matrix.rotationY(&matrix, mAngleXYZ[1]);
        matrix.mul(vector, Vector3(0.0, 0.0, 1.0));
    };
    double Robo::angle()
    {
        return mAngleXYZ[1];
    }
    //碰撞
    const Cuboid* Robo::cuboid() const
    {
        return &mCuboid;
    }
    const Sphere* Robo::sphere()const
    {
        return &mSphere;
    }
    //行为
    void Robo::move()
    {
        Vector3 vector(0.0, 0.0, 0.0);

        if (mPad->keyno(Pad::KEY_FORWARD)) {
            vector += Vector3(0.0, 0.0, -sMoveMaxSpeed);
        }
        else if (mPad->keyno(Pad::KEY_COMEBACK)) {
            vector += Vector3(0.0, 0.0, +sMoveMaxSpeed);
        }
        if (mPad->keyno(Pad::KEY_RIGHT)) {
            vector += Vector3(+sMoveMaxSpeed, 0.0, 0.0);
        }
        else if (mPad->keyno(Pad::KEY_LEFT)) {
            vector += Vector3(-sMoveMaxSpeed, 0.0, 0.0);
        }

        Matrix34 transform;
        transform.rotationY(&transform, mAngleXYZ[1] + 180.0);
        transform.mul(&vector, vector);
        double ratio = sMoveMaxSpeed / static_cast<double>(sMoveZeroToMaxTime); // 加减速系数

        vector.setMul(vector, ratio);
        if (mMoveVelocity.x == 0.0 && mMoveVelocity.z == 0.0) // 需要对robo速度进行初始赋值
        {
            mMoveVelocity.set(vector);
        }
        else // 已经获取到初始速度时候
        {
            if (vector.x == 0.0 && vector.z == 0.0)
            {

                if (mMoveVelocity.lengthXZ() < 0.01)          // 当速度小于多少的时候将速度设置为0
                {
                    mMoveVelocity = Vector3(0.0, 0.0, 0.0);
                }
                else
                {
                    // 速度衰减
                    vector.setMul(mMoveVelocity, ratio * 7);
                    mMoveVelocity -= vector;
                }
            }
            else
            {
                //计算 机甲速度与加速度方向的夹角
                double dp = mMoveVelocity.dot(vector);
                if (dp <= 0.0)
                {
                    mMoveVelocity.set(0.0, 0.0, 0.0);
                }
                else  // 夹角小于90度  向西移动转为西北或者西南移动时候
                {
                    double moveSquare = vector.squarelengthXZ();
                    mMoveVelocity.setMul(vector, dp / moveSquare);
                }
                mMoveVelocity += vector;
            }
            // 会导致达到最高速度后失控  需要设置测试移动
            double speed = mMoveVelocity.length();
            if (speed > sMoveMaxSpeed)
            {
                mMoveVelocity *= sMoveMaxSpeed / speed;
            }
        }

        if (mPad->keyno(Pad::KEY_UP)) {
            if (mPosition.y < 40.0)
            {
                mMoveVelocity += Vector3(0.0, +sFlySpeed, 0.0);
            }
        }
        else if (mPad->keyno(Pad::KEY_DOWN))
        {
            if (mPosition.y > 0.0)
            {
                mMoveVelocity += Vector3(0.0, -sFlySpeed, 0.0);
            }
        }

    }
    void Robo::turn()
    {
        if (mPad->keyno(Pad::KEY_TURNRIGHT)) {
            if (mAngleXYZ[1] > 180.0)
            {
                mAngleXYZ[1] -= 360.0;
            }
            mAngleXYZ[1] += sTrunSpeed;
        }
        if (mPad->keyno(Pad::KEY_TURNLEFT)) {
            if (mAngleXYZ[1] < -180.0)
            {
                mAngleXYZ[1] += 360.0;
            }
            mAngleXYZ[1] -= sTrunSpeed;
        }
    }
    void Robo::autoAim()
    {
        if (aimTarget != nullptr)
        {
            Vector3 temp;
            temp.setSub(aimTarget->mPosition, mPosition);
            double angle = GameLib::atan2(temp.x, temp.z);
            double  diff = angle - mAngleXYZ[1]; // 目标角度和当前角度相差
            if (diff > 180.0)
            {
                angle -= 360.0;
            }
            else if (diff < -180.0)
            {
                angle += 360.0;
            }
            diff = angle - mAngleXYZ[1]; // 目标角度和当前角度相差
            mAngleVelocityY = diff / sTrunCount;
            mAngleXYZ[1] += mAngleVelocityY;
            mAngleXYZ[1] = mAngleXYZ[1] > 360.0 ? mAngleXYZ[1] -= 360.0 : mAngleXYZ[1] < 0.0 ? mAngleXYZ[1] += 360.0 : mAngleXYZ[1];

        }
    }
    void Robo::setTatget(const Robo* robo)
    {
        if (mPad->triggered(Pad::KEY_AIM))
        {
            if (aimTarget != nullptr)
            {
                aimTarget = nullptr;
                return;
            }
            aimTarget = robo;
        }
    }
    void Robo::fire()
    {
        if (mPad->triggered(Pad::KEY_FIRE))
        {
            for (int i = 0; i < sBulletNum; i++)
            {
                if (mBulletPool[i].isReady())
                {
                    Vector3 dir;
                    direction(&dir);
                    mBulletPool[i].create(*mBlueprint, "bullet", mPosition, dir);
                    break;
                }
            }
        }
    }
}



#include "engine/base/Camera.h"
#include "base/calculate/Vector3.h"
#include "GameLib/Math.h"
#include "models/Robo.h"
using namespace GameLib;
namespace base
{
    namespace engine
    {
        Camera::Camera(
            double nearCilp,
            double farCilp,
            Vector3& position,
            Vector3& target,
            double fov,
            double windowW,
            double windowH) :
            mFov(fov),
            mNearCilp(nearCilp),
            mFarCilp(farCilp),
            mPosition(position),
            mTarget(target),
            mWindowW(windowW),
            mWindowH(windowH),
            w(-1.0)
        {
            mEyePosition.set(0.0, 10.0, -15.0);
            mTargetPosition.set(0.0, 0.0, 25.0);
        }

        void Camera::setView(const Vector3& position, const Vector3& target)
        {
            Vector3 temp;
            temp.setSub(target, position);
            double dir = sqrt(temp.x * temp.x + temp.z * temp.z);
            // 俯仰角
            double pitchAngle = atan2(temp.y, dir);
            // 偏航角
            double yawAngle = atan2(temp.x, temp.z) + 180.0;

            Matrix34 trans;
            trans.rotation(-pitchAngle, -yawAngle, 0);
            trans.translate(Vector3(-position.x, -position.y, -position.z));
            Matrix44 matrix;
            double s = 1.0 / tan(mFov * 0.5);
            double r = mWindowH / mWindowW;
            double a = 1.0 / (mNearCilp - mFarCilp);
            matrix.setElement(0, 0, s * r);
            matrix.setElement(1, 1, s);
            matrix.setElement(2, 2, a);
            matrix.setElement(2, 3, mNearCilp * a);
            matrix.setElement(3, 2, -1.0);
            matrix *= trans;
            mPwm = matrix;
        }
        void Camera::update()
        {
            mPosition = *(mRobo->position());
            mTarget = *(mRobo->position());
            Vector3 dir;
            mRobo->direction(&dir);
            Vector3 temp;
            temp.setMul(dir, mEyePosition.z);
            temp.y += mEyePosition.y;
            temp.y += mPosition.y * 0.12; // 动态调整相机角度
            mPosition += temp;
            ////世界变换（Z旋转）
            temp.setMul(dir, mTargetPosition.z);
            temp.y -= mPosition.y * 0.12;// 动态调整相机角度
            mTarget += temp;
            setView(mPosition, mTarget);
        }
        void Camera::setEyePosition(const Vector3& position)
        {
            mEyePosition = position;
        }
        void Camera::setTargetPositin(const Vector3& position)
        {
            mTargetPosition = position;
        }
        void Camera::bind(Robo* robo)
        {
            mRobo = robo;
        }
        const Matrix44& Camera::view() const
        {
            // TODO: 在此处插入 return 语句
            return mPwm;
        }
    }
}


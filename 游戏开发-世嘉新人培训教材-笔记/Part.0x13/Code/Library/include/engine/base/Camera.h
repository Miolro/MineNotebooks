#pragma once
#ifndef LIBRARY_INCLUDE_MATH_CAMERA
#define LIBRARY_INCLUDE_MATH_CAMERA
#include "base/calculate/Matrix34.h"
#include "base/calculate/Matrix44.h"
#include "base/calculate/Vector3.h"
namespace models
{
    class Robo;
}
namespace base {
    using namespace base::calculate;
    using namespace models;
    namespace engine {
        class Camera
        {
        public:
            Camera(double nearCilp, double farCilp, Vector3& position, Vector3& target, double fov = 45, double windowW = 640.0, double windowH = 480.0);
            void setView(const Vector3& position, const Vector3& target);
            void bind(Robo* robo);
            const Matrix44& view()const;
            void update();
            void setEyePosition(const Vector3& position);
            void setTargetPositin(const Vector3& position);
        private:
            Matrix44 mPwm;
            Matrix34 mTrans;
            double mFov;
            double mNearCilp;
            double mFarCilp;
            double mWindowH;
            double mWindowW;
            double w;
            double angle = 30;
            Vector3 mEyePosition; // 眼睛位置
            Vector3 mTargetPosition;      // 设置目标向前位置
            Vector3 mPosition;
            Vector3 mTarget;
            Robo* mRobo;
        };
    }
}
#endif //LIBRARY_INCLUDE_MATH_CAMERA
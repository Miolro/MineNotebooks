#pragma once
#ifndef LIBRARY_INCLUDE_MATH_VECTOR3
#define LIBRARY_INCLUDE_MATH_VECTOR3
namespace base
{
    namespace calculate {
        class Vector3
        {
        public:
            Vector3();
            Vector3(double vx, double vy, double vz);
            ~Vector3();
            void set(double x, double y, double z);
            void set(const Vector3& v);
            void setSum(const Vector3& v1, const Vector3& v2);
            void setSub(const Vector3& v1, const Vector3& v2);
            void setMul(const Vector3& v1, const double ratio);
            void setDiv(const Vector3& v1, const double ratio);
            void normal(const Vector3& v1, const Vector3& v2);

            void operator+=(const Vector3& v1);
            void operator-=(const Vector3& v1);
            void operator*=(const double ratio);
            void operator/=(const double ratio);
            bool operator==(const Vector3& v1);

            void dot(double out, const Vector3& v1)const;
            double dot(const Vector3& v1)const;
            double length()const;
            double squareLength()const;
            double squarelengthXZ()const;
            double lengthXY()const;
            double lengthXZ()const;
            double lengthYZ()const;
            double cosValue(const Vector3& v1)const;  // 求角系数
            double x;
            double y;
            double z;
        };
    }
}

#endif // !LIBRARY_INCLUDE_MATH_VECTOR3


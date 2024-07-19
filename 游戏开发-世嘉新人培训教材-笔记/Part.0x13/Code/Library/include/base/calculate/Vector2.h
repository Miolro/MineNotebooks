#pragma once
#ifndef LIBRARY_INCLUDE_MATH_VECTOR2
#define LIBRARY_INCLUDE_MATH_VECTOR2

namespace base
{
    namespace calculate {
        class Vector2
        {
        public:
            Vector2();
            Vector2(double x, double y);
            ~Vector2();
            void set(double x, double y);
            void setSum(const Vector2& v1, const Vector2& v2);
            void setSub(const Vector2& v1, const Vector2& v2);
            void setMul(const Vector2&, const double);
            void operator+=(const Vector2& v1);
            void operator-=(const Vector2& v1);
            void operator*=(const double);
            void dotProduct(double& out, const Vector2& v1)const;
            void modulus(Vector2& out)const;
            void length(double& out)const;
            const double length() const;
            void cosValue(double& out, const Vector2& v1)const;  // 求角系数
            void angle(double& out, const Vector2& v1)const;  // 求角
            double x;
            double y;

        };
    }
}
#endif  //LIBRARY_INCLUDE_MATH_VECTOR2


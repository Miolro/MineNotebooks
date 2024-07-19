#pragma once
#ifndef LIBRARY_INCLUDE_MATH_MATRIX44
#define LIBRARY_INCLUDE_MATH_MATRIX44
namespace base
{
    namespace calculate {
        class Vector3;
        class Matrix34;
        class Matrix44
        {
        public:
            Matrix44();
            Matrix44(const Matrix44& m);
            // 设置元素
            void setElement(const int position, const double value);
            void setElement(const int row, const int col, const double value);
            // 获取元素
            const double getElement(int position)const;
            const double getElement(int row, int col)const;
            // 左乘
            void setMul(const Matrix44& m1, const Matrix44& m2);
            void setMul(const Matrix44& m1, const Matrix34& m2);
            // 左乘
            void operator*=(const Matrix44&);
            void operator*=(const Matrix34&);
            // 矩阵变换
            void const mul(double*, const Vector3& v1)const;
        private:
            double mElement[4][4];
        };
    }
}
#endif // !LIBRARY_INCLUDE_MATH_MATRIX44
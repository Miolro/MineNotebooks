#pragma once
#ifndef LIBRARY_INCLUDE_MATH_MATRIX34
#define LIBRARY_INCLUDE_MATH_MATRIX34
namespace base
{
    namespace calculate {

        class Vector3;
        class Matrix34
        {
        public:
            // 基础方法
            Matrix34();
            Matrix34(const Matrix34& m);
            // 设置节点
            void setElement(const int position, const double value);
            void setElement(const int row, const int col, const double value);
            // 获取节点
            const double getElement(int position)const;
            const double getElement(int col, int row)const;
            // 左乘
            void setMul(const Matrix34& m1, const Matrix34& m2);
            void operator*=(const Matrix34&);
            // 矩阵变换
            void mul(Vector3* out, const Vector3& in)const;
            // 旋转集合
            void rotation(const double x, const double y, const double z);
            void rotation(const double* rXYZ);
            // 俯仰角
            void rotationX(Matrix34* matrix, const double);
            // 偏航角
            void rotationY(Matrix34* matrix, const double);
            // 翻滚角
            void rotationZ(Matrix34* matrix, const double);
            // 平移
            void translate(const Vector3& vetocr);
        private:
            double mElement[3][4];
            bool mInit = false;
        };
    }
}
#endif // !LIBRARY_INCLUDE_MATH_MATRIX34
#include "base/calculate/Matrix34.h"
#include "GameLib/Math.h"
#include "base/calculate/Vector3.h"
namespace base
{
    namespace calculate {
        Matrix34::Matrix34() :mElement{ 0.0 } {}
        Matrix34::Matrix34(const Matrix34& m) {
            for (int c = 0; c < 3; c++)
            {
                mElement[c][0] = m.mElement[c][0];
                mElement[c][1] = m.mElement[c][1];
                mElement[c][2] = m.mElement[c][2];
                mElement[c][3] = m.mElement[c][3];
            }
        }

        void Matrix34::setElement(int position, const double value)
        {
            mElement[position / 4][position % 4] = value;
        }
        void Matrix34::setElement(int col, int row, double value)
        {
            mElement[col][row] = value;
        }

        const double Matrix34::getElement(int position)const
        {
            return mElement[position / 4][position % 4];
        }
        const double Matrix34::getElement(int col, int row)const
        {
            return mElement[col][row];
        }

        void Matrix34::setMul(const Matrix34& m1, const Matrix34& m2)
        {
            double t1, t2, t3, t4;
            double y1, y2, y3, y4;
            double value;
            for (int c = 0; c < 3; c++) // 第一行
            {
                t1 = m1.getElement(c, 0);
                t2 = m1.getElement(c, 1);
                t3 = m1.getElement(c, 2);
                //t4 = m1.getElement(c, 3);
                for (int r = 0; r < 4; r++)
                {
                    y1 = m2.getElement(0, r);
                    y2 = m2.getElement(1, r);
                    y3 = m2.getElement(2, r);
                    //if (r == 3)
                    //{
                    //	// 第三列时候执行
                    //	//value = t1 * y1 + t2 * y2 + t3 * y3 + t4; // 齐次坐标
                    //}
                    //else
                    //{
                    value = t1 * y1 + t2 * y2 + t3 * y3;
                    //}
                    setElement(c, r, value);
                }
            }
        }
        void Matrix34::operator*=(const Matrix34& m)
        {
            setMul(*this, m);
        }
        void Matrix34::rotation(const double* rXYZ)
        {
            rotation(rXYZ[0], rXYZ[1], rXYZ[2]);
        }
        void Matrix34::rotation(const double rx, const double ry, const double rz)
        {
            Matrix34 out = *this;
            Matrix34 temp;
            //if (mInit) //已经初始化和没有初始化的情况
            //{
            //	//已经初始化直接做乘
            //	if (rx)
            //	{
            //		rotationX(&temp, rx); // 设置
            //		out *= temp;
            //	}
            //	if (ry)
            //	{
            //		rotationY(&temp, ry); // 设置
            //		out *= temp;
            //	}
            //	if (rz)
            //	{
            //		rotationZ(&temp, rz); // 设置
            //		out *= temp;
            //	}
            //}
            //else
            //{	// 没做初始化的
                if (rx)
                {
                    rotationX(&out, rx); // 设置
                    mInit = !mInit;
                    if (ry)
                    {
                        rotationY(&temp, ry); // 叠加
                        out *= temp;
                    }
                    if (rz)
                    {
                        rotationZ(&temp, rz); // 叠加
                        out *= temp;
                    }
                }
                else if (ry)
                {
                    rotationY(&out, ry); // 设置
                    mInit = !mInit;
                    if (rz)
                    {
                        rotationZ(&temp, rz); // 叠加
                        out *= temp;
                    }
                }
                else if (rz)
                {
                    rotationZ(&temp, rz); // 设置
                    out *= temp;
                }
            //}
            *this = out;
            mInit = true;  // tmd这个东西找了一一天才找出来
        }
        void Matrix34::rotationX(Matrix34* matrix, const double angle)
        {
            double c = GameLib::cos(angle);
            double s = GameLib::sin(angle);
            matrix->setElement(0, 0, 1.0);
            matrix->setElement(1, 1, c);
            matrix->setElement(1, 2, -s);
            matrix->setElement(2, 1, s);
            matrix->setElement(2, 2, c);

        }
        void Matrix34::rotationY(Matrix34* matrix, const double angle)
        {
            double c = GameLib::cos(angle);
            double s = GameLib::sin(angle);
            matrix->setElement(0, 0, c);
            matrix->setElement(0, 2, s);
            matrix->setElement(1, 1, 1.0);
            matrix->setElement(2, 0, -s);
            matrix->setElement(2, 2, c);
        }
        void Matrix34::rotationZ(Matrix34* matrix, const double angle)
        {
            double c = GameLib::cos(angle);
            double s = GameLib::sin(angle);
            matrix->setElement(0, 0, c);
            matrix->setElement(0, 1, -s);
            matrix->setElement(1, 0, s);
            matrix->setElement(1, 1, c);
            matrix->setElement(2, 2, 1.0);
        }
        void Matrix34::translate(const Vector3& vetocr)
        {
            if (!mInit)
            {
                mInit = !mInit;
                mElement[0][0] = 1;
                mElement[1][1] = 1;
                mElement[2][2] = 1;
                mElement[0][3] += mElement[0][0] * vetocr.x + mElement[0][1] * vetocr.y + mElement[0][2] * vetocr.z;
                mElement[1][3] += mElement[1][0] * vetocr.x + mElement[1][1] * vetocr.y + mElement[1][2] * vetocr.z;
                mElement[2][3] += mElement[2][0] * vetocr.x + mElement[2][1] * vetocr.y + mElement[2][2] * vetocr.z;
            }
            else {
                mElement[0][3] += mElement[0][0] * vetocr.x + mElement[0][1] * vetocr.y + mElement[0][2] * vetocr.z;
                mElement[1][3] += mElement[1][0] * vetocr.x + mElement[1][1] * vetocr.y + mElement[1][2] * vetocr.z;
                mElement[2][3] += mElement[2][0] * vetocr.x + mElement[2][1] * vetocr.y + mElement[2][2] * vetocr.z;
            }
        }
        void Matrix34::mul(Vector3* out, const Vector3& in)const
        {
            Vector3 copy = in;
            out->x = mElement[0][0] * copy.x + mElement[0][1] * copy.y + mElement[0][2] * copy.z + mElement[0][3];
            out->y = mElement[1][0] * copy.x + mElement[1][1] * copy.y + mElement[1][2] * copy.z + mElement[1][3];
            out->z = mElement[2][0] * copy.x + mElement[2][1] * copy.y + mElement[2][2] * copy.z + mElement[2][3];
        }
    }
}
//#include "Math/Matrix34.h"
//
//
//namespace MathOverwritwe
//{
//	Matrix34::Matrix34() :
//		m00(0.0), m01(0.0), m02(0.0), m03(0.0),
//		m10(0.0), m11(0.0), m12(0.0), m13(0.0),
//		m20(0.0), m21(0.0), m22(0.0), m23(0.0)
//	{
//
//	}
//
//	void Matrix34::translate(const MathOverwritwe::Vector3& a)
//	{
//		m03 += m00 * a.x + m01 * a.y + m02 * a.z;
//		m13 += m10 * a.x + m11 * a.y + m12 * a.z;
//		m23 += m20 * a.x + m21 * a.y + m22 * a.z;
//	}
//
//	void Matrix34::operator*=(Matrix34& m2)
//	{
//		double tx, ty, tz, tw;
//		tx = m00; ty = m01; tz = m02, tw = m03;
//
//		m00 = m2.m00 * tx + m2.m10 * ty + m2.m20 * tz;
//		m01 = m2.m01 * tx + m2.m11 * ty + m2.m21 * tz;
//		m02 = m2.m02 * tx + m2.m12 * ty + m2.m22 * tz;
//		m03 = m2.m03 * tx + m2.m13 * ty + m2.m23 * tz + tw;
//
//		tx = m10; ty = m11; tz = m12; tw = m13;
//
//		m10 = m2.m00 * tx + m2.m10 * ty + m2.m20 * tz;
//		m11 = m2.m01 * tx + m2.m11 * ty + m2.m21 * tz;
//		m12 = m2.m02 * tx + m2.m12 * ty + m2.m22 * tz;
//		m13 = m2.m03 * tx + m2.m13 * ty + m2.m23 * tz + tw;
//
//		tx = m20; ty = m21; tz = m22; tw = m23;
//
//		m20 = m2.m00 * tx + m2.m10 * ty + m2.m20 * tz;
//		m21 = m2.m01 * tx + m2.m11 * ty + m2.m21 * tz;
//		m22 = m2.m02 * tx + m2.m12 * ty + m2.m22 * tz;
//		m23 = m2.m03 * tx + m2.m13 * ty + m2.m23 * tz + tw;
//	}
//
//	void Matrix34::mul(Vector3* out,const Vector3& in)
//	{
//		out->x = m00 * in.x + m01 * in.y + m02 * in.z;
//		out->y = m10 * in.x + m11 * in.y + m12 * in.z;
//		out->z = m20 * in.x + m21 * in.y + m22 * in.z;
//	}
//}



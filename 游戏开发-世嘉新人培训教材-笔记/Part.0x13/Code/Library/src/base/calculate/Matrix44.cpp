#include "base/calculate/Matrix44.h"
#include "base/calculate/Matrix34.h"
#include "base/calculate/Vector3.h"
namespace base
{
    namespace calculate
    {
        Matrix44::Matrix44() :mElement{ 0.0 } {}
        Matrix44::Matrix44(const Matrix44& m) {
            for (int c = 0; c < 4; c++)
            {
                mElement[0][c] = m.mElement[0][c];
                mElement[1][c] = m.mElement[1][c];
                mElement[2][c] = m.mElement[2][c];
                mElement[3][c] = m.mElement[3][c];
            }
        }

        void Matrix44::setElement(int position, const double value)
        {
            mElement[position / 4][position % 4] = value;
        }
        void Matrix44::setElement(int col, int row, double value)
        {
            mElement[col][row] = value;
        }

        const double Matrix44::getElement(int position)const
        {
            return mElement[position / 4][position % 4];
        }
        const double Matrix44::getElement(int col, int row)const
        {
            return mElement[col][row];
        }

        void Matrix44::setMul(const Matrix44& m1, const Matrix44& m2)
        {
            double t1, t2, t3, t4;
            double y1, y2, y3, y4;
            for (int c = 0; c < 4; c++) // 第一行
            {
                t1 = m1.getElement(c, 0);
                t2 = m1.getElement(c, 1);
                t3 = m1.getElement(c, 2);
                t4 = m1.getElement(c, 3);
                for (int r = 0; r < 4; r++)
                {
                    y1 = m2.getElement(0, r);
                    y2 = m2.getElement(1, r);
                    y3 = m2.getElement(2, r);
                    y4 = m2.getElement(3, r);
                    double value = t1 * y1 + t2 * y2 + t3 * y3 + t4 * t4;
                    setElement(c, r, value);
                }
            }
        }
        void Matrix44::setMul(const Matrix44& m1, const Matrix34& m2)
        {

            double y1, y2, y3;
            double value;
            for (int c = 0; c < 4; c++) // 第一行
            {
                double t1, t2, t3, t4;
                t1 = m1.getElement(c, 0);
                t2 = m1.getElement(c, 1);
                t3 = m1.getElement(c, 2);

                for (int r = 0; r < 4; r++)
                {
                    y1 = m2.getElement(0, r);
                    y2 = m2.getElement(1, r);
                    y3 = m2.getElement(2, r);
                    if (r == 3)
                    {
                        // 第三列时候执行
                        value = t1 * y1 + t2 * y2 + t3 * y3 + m1.getElement(c, 3); // 齐次坐标
                    }
                    else
                    {
                        value = t1 * y1 + t2 * y2 + t3 * y3;
                    }
                    setElement(c, r, value);
                }
            }
        }

        void Matrix44::operator*=(const Matrix44& m)
        {
            setMul(*this, m);
        }
        void Matrix44::operator*=(const Matrix34& m)
        {
            setMul(*this, m);
        }

        void const Matrix44::mul(double* out, const Vector3& v1)const
        {
            out[0] = v1.x * mElement[0][0] + v1.y * mElement[0][1] + v1.z * mElement[0][2] + mElement[0][3];
            out[1] = v1.x * mElement[1][0] + v1.y * mElement[1][1] + v1.z * mElement[1][2] + mElement[1][3];
            out[2] = v1.x * mElement[2][0] + v1.y * mElement[2][1] + v1.z * mElement[2][2] + mElement[2][3];
            out[3] = v1.x * mElement[3][0] + v1.y * mElement[3][1] + v1.z * mElement[3][2] + mElement[3][3];
        }
    }
}
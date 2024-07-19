#include "base/calculate/Vector3.h"
#include "GameLib/Math.h"
namespace base
{
    namespace calculate
    {
        Vector3::Vector3() :x(0.0), y(0.0), z(0.0) {}
        Vector3::Vector3(double vx, double vy, double vz) :x(vx), y(vy), z(vz) {}
        Vector3::~Vector3() {}

        void Vector3::set(double vx, double vy, double vz)
        {
            x = vx; y = vy; z = vz;
        }

        void Vector3::set(const Vector3& v)
        {
            x = v.x; y = v.y; z = v.z;
        }

        void Vector3::setSum(const Vector3& v1, const Vector3& v2)
        {
            x = v1.x + v2.x;
            y = v1.y + v2.y;
            z = v1.z + v2.z;
        }
        void Vector3::setSub(const Vector3& v1, const Vector3& v2)
        {
            x = v1.x - v2.x;
            y = v1.y - v2.y;
            z = v1.z - v2.z;
        }
        void Vector3::setMul(const Vector3& v1, const double ratio)
        {
            x = v1.x * ratio;
            y = v1.y * ratio;
            z = v1.z * ratio;
        }

        void Vector3::setDiv(const Vector3& v1, const double ratio)
        {
            x = v1.x / ratio;
            y = v1.y / ratio;
            z = v1.z / ratio;
        }

        void Vector3::normal(const Vector3& v1, const Vector3& v2)
        {
            x = v1.y * v2.z - v1.z * v2.y;
            y = -(v1.x * v2.z - v1.z * v2.x);
            z = v1.x * v2.y - v1.y * v2.x;
        }

        void Vector3::operator+=(const Vector3& v1)
        {
            x += v1.x;
            y += v1.y;
            z += v1.z;
        }
        void Vector3::operator-=(const Vector3& v1)
        {
            x -= v1.x;
            y -= v1.y;
            z -= v1.z;
        }
        void Vector3::operator*=(const double ratio)
        {
            x *= ratio;
            y *= ratio;
            z *= ratio;
        }

        void Vector3::operator/=(const double ratio)
        {
            setDiv(*this, ratio);
        }

        bool Vector3::operator==(const Vector3& v1)
        {
            if (x != v1.x)
            {
                return false;
            }
            else if (y != v1.y)
            {
                return false;
            }
            else if (z != v1.z)
            {
                return false;
            }
            return true;
        }

        void Vector3::dot(double out, const Vector3& v1) const
        {
            out = x * v1.x + y * v1.y + z * v1.z; // 点积
        }
        double Vector3::dot(const Vector3& a) const
        {
            return  (x * a.x) + (y * a.y) + (z * a.z);
        }
        double Vector3::length()const
        {
            return GameLib::sqrt(x * x + y * y + z * z);  // 取模
        }
        double Vector3::squareLength() const
        {
            return (x * x) + (y * y) + (z * z);
        }
        double Vector3::lengthXY()const
        {
            return GameLib::sqrt(x * x + y * y);  // 取模;
        }
        double Vector3::lengthXZ()const
        {
            return  GameLib::sqrt(x * x + z * z);  // 取模;
        }
        double Vector3::squarelengthXZ()const
        {
            return  x * x + z * z;  // 取模;
        }
        double Vector3::lengthYZ()const
        {
            return GameLib::sqrt(y * y + z * z);  // 取模;
        }
        double Vector3::cosValue(const Vector3& v1)const
        { // 向量点积/向量的模 = cos
            double tValue = length();
            double tValue1 = v1.length();
            double dotValue = dot(v1);
            tValue *= tValue1;
            return dotValue / tValue;
        }
    }
}



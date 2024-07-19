#include "base/calculate/Vector2.h"
#include "GameLib/Math.h"
const float TO_RAD = 3.1415926535897932384626433832795f / 180.f;
const float TO_DEG = 180.f / 3.1415926535897932384626433832795f;
namespace base
{
    namespace calculate
    {
        Vector2::Vector2() :x(0), y(0) {}
        Vector2::Vector2(double ix, double iy) :x(ix), y(iy)
        {
        }
        Vector2::~Vector2() {}
        void Vector2::set(double ix, double iy)
        {
            x = ix;
            y = iy;
        }
        void Vector2::setSum(const Vector2& v1, const Vector2& v2)
        {
            x = v1.x + v2.x;
            y = v1.y + v2.y;
        }
        void Vector2::setSub(const Vector2& v1, const Vector2& v2)
        {
            x = v1.x - v2.x;
            y = v1.y - v2.y;
        }
        void Vector2::setMul(const Vector2& v1, const double ratio)
        {
            x = v1.x * ratio;
            y = v1.y * ratio;
        }

        void Vector2::operator+=(const Vector2& v)
        {
            x += v.x;
            y += v.y;
        }

        void Vector2::operator-=(const Vector2& v)
        {
            x -= v.x;
            y -= v.y;
        }

        void Vector2::operator*=(const double ratio)
        {
            x *= ratio;
            y *= ratio;
        }

        void Vector2::dotProduct(double& out, const Vector2& v1)const
        {
            out = x * v1.x + y * v1.y; // 点积
        }
        void Vector2::modulus(Vector2& out)const // 取模向量
        {
            out.x = x > 0 ? -x : x;
            out.y = y > 0 ? -y : y;
        }

        void Vector2::length(double& out) const
        {
            out = GameLib::sqrt(x * x + y * y); // 取模
        }
        const double Vector2::length() const
        {
            return GameLib::sqrt(x * x + y * y); // 取模
        }
        // cos
        void Vector2::cosValue(double& out, const Vector2& v1)const
        { // 向量点积/向量的模 = cos
            double dotValue = 0;
            double tValue = 0;
            double tValue1 = 0;
            dotProduct(dotValue, v1);
            length(tValue);
            v1.length(tValue1);
            tValue *= tValue1;
            out = dotValue / tValue;
        }
        // cos
        void Vector2::angle(double& out, const Vector2& v1)const
        {
            cosValue(out, v1);
            out = GameLib::acos(out) * TO_DEG;
        }
    }
}
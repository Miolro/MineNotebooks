#include "base/xml/Attribute.h"
#include <sstream>
namespace base
{
    namespace xml
    {
        Attribute::Attribute(const char* key, const char* value) :mKey(key), mValue(value)
        {

        }
        const std::string* Attribute::key() const
        {
            return &mKey;
        }
        const std::string* Attribute::valueStr() const
        {
            return &mValue;
        }
        const double Attribute::valueDouble() const
        {
            return 0.0;
        }
        const int Attribute::valueDoubles(double* out, int length) const
        {
            int count = 0;
            std::istringstream iss(mValue);
            int size = static_cast<int>(mValue.length());
            for (int i = 0; i < length; i++)
            {
                iss >> out[i];
                if (iss.fail())
                {
                    break;
                }
                iss.ignore(size, ',');
                count++;
            }
            return count;
        }
        const unsigned Attribute::valueUnsigned() const
        {

            return 0;
        }
        const int Attribute::valueUnsigneds(unsigned* out, int length) const
        {
            int count = 0;
            std::istringstream iss(mValue);
            int size = static_cast<int>(mValue.length());
            for (int i = 0; i < length; i++)
            {
                iss >> out[i];
                if (iss.fail())
                {
                    break;
                }
                iss.ignore(size, ',');
                count++;
            }
            return count;
        }
    }
}


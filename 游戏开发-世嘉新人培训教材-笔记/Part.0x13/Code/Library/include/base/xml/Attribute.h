#pragma once
#include <string>
namespace base
{
    namespace xml
    {
        class Attribute
        {
        public:
            Attribute(const char* key, const char* value);
            const std::string* key()const;
            const std::string* valueStr()const;
            const double valueDouble()const;
            const int valueDoubles(double* out, int length)const;
            const unsigned valueUnsigned()const;
            const int valueUnsigneds(unsigned* out, int length)const;
        private:
            std::string mKey;
            std::string mValue;
        };

    }
}


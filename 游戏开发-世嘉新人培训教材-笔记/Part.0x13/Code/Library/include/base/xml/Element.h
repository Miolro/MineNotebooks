#pragma once
#include <vector>
#include <string>
namespace base
{
    namespace xml
    {
        class Attribute;
        class Tag;
        class Element
        {
        public:
            Element(const Tag* rootEle, const char** dataPoint, const char* endPoint);
            const std::string* name()const;
            const Element* children(int index)const;
            const Attribute* attribute(int index)const;
            const int childrenNum()const;
            const int attributesNum()const;
        private:
            std::vector< Attribute* > mAttributes;
            std::vector< Element* > mChildren;
            std::string mName;
        };

    }
}
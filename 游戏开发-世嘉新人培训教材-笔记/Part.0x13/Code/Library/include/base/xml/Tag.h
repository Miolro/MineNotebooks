#pragma once
#include <string>
#include <vector>
namespace base {
    namespace xml
    {
        class Element;
        class Attribute;
        class Tag
        {
        public:
            enum TagType
            {
                CNT, // 继续
                END, // 结束本次添加
            };
            Tag(const char* tagName);
            Tag(const char** dataPoint, const char* endPoint);
            const std::string* name()const;
            const std::vector<Attribute*>* attribute()const;

            TagType type();
        private:
            bool isNormalChar(const char c);
            std::string mName;
            std::vector<Attribute*> mAttribute;
            TagType mType;
        };
    }
}

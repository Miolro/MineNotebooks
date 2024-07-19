#include "base/xml/Tag.h"
#include "base/xml/Attribute.h"
#include <string>
bool base::xml::Tag::isNormalChar(const char c)
{
    char lowerChar = c | 0x20;
    if (lowerChar >= 'a' && lowerChar <= 'z')
    {
        return true;
    }
    else if (c == '_')
    {
        return true;
    }
    else if (c >= '0' && c <= '9') {
        return true;
    }
    return false;
}
base::xml::Tag::Tag(const char* tagName) :mName(tagName)
{

}

base::xml::Tag::Tag(const char** dataPoint, const char* endPoint)
{
    int model = 0;
    bool back = false;
    std::string tName;
    std::string tValue;
    while (*dataPoint < endPoint)
    {
        ++(*dataPoint);
        char c = **dataPoint;
        switch (model)
        {
        case 0:
            if (c == '/') { mType = END; back = true; break; } // 检查</
            if (!isNormalChar(c)) {
                model = 1; break;
            }
            mName += c;
            break;
        case 1:
            if (c == '=') { model = 2; break; }
            if (c == '>') { back = true; break; }
            if (c == '/') { back = true; break; }
            if (isNormalChar(c)) { tName += c; }
            break;
        case 2:
            if (c == '"') { model = 3; break; }
            break;
        case 3:
            if (c == '"') {
                model = 1;
                mAttribute.push_back(new Attribute(tName.c_str(), tValue.c_str()));
                tName.clear(); tValue.clear();
                break;
            }
            tValue += c;
            break;
        }
        if (back)
        {
            break;
        }
    }
}

const std::string* base::xml::Tag::name()const
{
    return &mName;
}

const std::vector<base::xml::Attribute*>* base::xml::Tag::attribute()const
{
    return &mAttribute;
}

base::xml::Tag::TagType base::xml::Tag::type()
{
    return mType;
}

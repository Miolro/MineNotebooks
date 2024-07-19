#include "base/xml/Element.h"
#include "base/xml/Tag.h"

namespace base
{
    namespace xml
    {
        Element::Element(const Tag* rootEle, const char** dataPoint, const char* endPoint)
        {
            mName = *(rootEle->name());
            mAttributes = *rootEle->attribute();
            while (*dataPoint < endPoint)
            {
                if (**dataPoint == '/') { break; }// 检查 />
                if (**dataPoint == '<')
                {
                    Tag tag(dataPoint, endPoint); // 解析标签
                    Tag::TagType type = tag.type();
                    if (type == Tag::TagType::CNT)
                    {
                        mChildren.push_back(new Element(&tag, dataPoint, endPoint)); // 内部子节点碰到/会跳出循环
                    }
                    else if (type == Tag::TagType::END)
                    {
                        break;
                    }
                }
                ++(*dataPoint);
            }
        }
        const std::string* Element::name() const
        {
            return &mName;
        }
        const Element* Element::children(int index)const
        {
            return mChildren[index];
        }
        const Attribute* Element::attribute(int index)const
        {
            return mAttributes[index];
        }
        const int Element::childrenNum()const
        {
            return mChildren.size();
        }
        const int Element::attributesNum()const
        {
            return mAttributes.size();
        }
    }
}

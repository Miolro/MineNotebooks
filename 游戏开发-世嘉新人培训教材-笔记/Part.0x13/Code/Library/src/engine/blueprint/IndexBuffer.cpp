#include "Engine/blueprint/IndexBuffer.h"
#include "base/xml/Element.h"
#include "base/xml/Attribute.h"
namespace engine
{
    namespace blueprint
    {
        IndexBuffer::IndexBuffer()
        {
        }

        IndexBuffer::~IndexBuffer()
        {
        }

        const std::string* IndexBuffer::name() const
        {
            return &mName;
        }

        const unsigned IndexBuffer::index(int index) const
        {
            return mIndices[index];
        }

        IndexBuffer::IndexBuffer(const base::xml::Element& element)
        {
            buildObject(element);
        }

        void IndexBuffer::setName(const std::string& name)
        {
            mName = name;
        }

        void IndexBuffer::buildObject(const base::xml::Element& element)
        {
            int size = element.attributesNum();
            for (int index = 0; index < size; index++)
            {
                const base::xml::Attribute* attr = element.attribute(index);
                const std::string* key = attr->key();
                const std::string* value = attr->valueStr();
                if (*key == "name")
                {
                    setName(*value);
                }
                mSize = element.childrenNum();
                mIndices = new unsigned[mSize * 3];

                for (int childIndex = 0; childIndex < mSize; childIndex++)
                {
                    const base::xml::Element* child = element.children(childIndex);
                    int attributeNum = child->attributesNum();

                    for (int attIndex = 0; attIndex < attributeNum; attIndex++)
                    {
                        const base::xml::Attribute* childAttr = child->attribute(attIndex);
                        const std::string* aKey = childAttr->key();
                        if (*aKey == "indices")
                        {
                            childAttr->valueUnsigneds(&mIndices[childIndex * 3], 3);
                            continue;
                        }
                    }
                }
            }
        }

        const int IndexBuffer::size()const
        {
            return mSize;
        }

    }
}
#include "engine/blueprint/VertexBuffer.h"
#include "base/xml/Element.h"
#include "base/xml/Attribute.h"
#include "base/calculate/Vector3.h"
#include "base/calculate/Vector2.h"
namespace engine
{
    namespace blueprint
    {
        VertexBuffer::VertexBuffer()
        {

        }

        VertexBuffer::VertexBuffer(const Element& element)
        {
            buildObject(element);
        }

        VertexBuffer::~VertexBuffer()
        {
        }

        const std::string* VertexBuffer::name() const
        {
            return &mName;
        }

        void VertexBuffer::setName(const std::string& name)
        {
            mName = name;
        }

        void VertexBuffer::buildObject(const Element& element)
        {
            int size = element.attributesNum();
            for (int index = 0; index < size; index++)
            {
                const Attribute* attr = element.attribute(index);
                const std::string* key = attr->key();
                const std::string* value = attr->valueStr();
                if (*key == "name")
                {
                    setName(*value);
                }
                mSize = element.childrenNum();
                mPosition = new Vector3[mSize];
                mUV = new Vector2[mSize];
                for (int childIndex = 0; childIndex < mSize; childIndex++)
                {
                    const Element* child = element.children(childIndex);
                    int attributeNum = child->attributesNum();

                    for (int attIndex = 0; attIndex < attributeNum; attIndex++)
                    {
                        const Attribute* childAttr = child->attribute(attIndex);
                        const std::string* aKey = childAttr->key();
                        if (*aKey == "position")
                        {
                            childAttr->valueDoubles(&mPosition[childIndex].x, 3);
                            continue;
                        }
                        if (*aKey == "uv")
                        {
                            double uv[2];
                            childAttr->valueDoubles(&mUV[childIndex].x, 2);
                            continue;
                        }
                    }
                }
            }
        }

        void VertexBuffer::setPosition(const double* position)
        {
            mPosition->set(position[0], position[1], position[2]);
        }

        void VertexBuffer::setUV(const double* uv)
        {
            mUV->set(uv[0], uv[1]);
        }

        const Vector3* VertexBuffer::position(int index) const
        {
            return &mPosition[index];
        }

        const Vector2* VertexBuffer::UV(int index) const
        {
            return &mUV[index];
        }

        const int VertexBuffer::size()const
        {
            return mSize;
        }
    }
}



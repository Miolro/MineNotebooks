#include "engine/blueprint/Batch.h"
#include "base/xml/Document.h"
#include "base/xml/Element.h"
#include "base/xml/Attribute.h"

#include "base/calculate/Vector3.h"
#include "base/calculate/Matrix44.h"

#include "engine/blueprint/Texture.h"
#include "engine/blueprint/IndexBuffer.h"
#include "engine/blueprint/VertexBuffer.h"

using namespace base::xml;
using namespace base::calculate;
namespace engine
{
    namespace blueprint
    {

        Batch::Batch(const Element& element, const Blueprint blueprint)
        {
            buildObject(element, blueprint);
        }
        Batch::~Batch()
        {

        }

        const std::string* Batch::name() const
        {
            return &mName;
        }

        const VertexBuffer* Batch::vertexBuffer() const
        {
            return mVertexBuffer;
        }

        const IndexBuffer* Batch::indexBuffer() const
        {
            return mIndexBuffer;
        }

        const Texture* Batch::texture() const
        {
            return mTexture;
        }

        const void Batch::draw(const Matrix44& pwm)const
        {
            Vector3  mPosition[4];
            unsigned mColor[4];
            int bufferSize = mVertexBuffer->size();
            double* p4 = new double[bufferSize * 4];
            GameLib::Framework frame = GameLib::Framework::instance();
            frame.setBlendMode(frame.BLEND_OPAQUE);
            frame.enableDepthWrite(true);
            frame.enableDepthTest(true);
            for (int i = 0; i < bufferSize; i++)
            {
                pwm.mul(&p4[i * 4], *mVertexBuffer->position(i));
            }
            if (mTexture != NULL)
            {
                frame.setTexture(mTexture->texture());
                for (int i = 0; i < mIndexBuffer->size(); i++)
                {
                    unsigned i0 = mIndexBuffer->index(i * 3 + 0);
                    unsigned i1 = mIndexBuffer->index(i * 3 + 1);
                    unsigned i2 = mIndexBuffer->index(i * 3 + 2);

                    frame.drawTriangle3DH(
                        &p4[i0 * 4],
                        &p4[i1 * 4],
                        &p4[i2 * 4],
                        &mVertexBuffer->UV(i0)->x,
                        &mVertexBuffer->UV(i1)->x,
                        &mVertexBuffer->UV(i2)->x

                    );
                }

            }
            else
            {
                unsigned color[4];
                color[0] = 0xffff0000; //红色的
                color[1] = 0xff00ff00; //绿
                color[2] = 0xff0000ff; //蓝色的
                color[3] = 0xffffffff; //白
                for (int i = 0; i < mIndexBuffer->size(); i++)
                {
                    unsigned i0 = mIndexBuffer->index(i * 3 + 0);
                    unsigned i1 = mIndexBuffer->index(i * 3 + 1);
                    unsigned i2 = mIndexBuffer->index(i * 3 + 2);

                    frame.drawTriangle3DH(
                        &p4[i0 * 4],
                        &p4[i1 * 4],
                        &p4[i2 * 4],
                        0, 0, 0,
                        color[i0],
                        color[i1],
                        color[i2]
                    );
                }
            }
            SAFE_DELETE_ARRAY(p4);
        }

        void Batch::buildObject(const Element& element, const Blueprint blueprint)
        {
            int size = element.attributesNum();
            for (int index = 0; index < size; index++)
            {
                const Attribute* attr = element.attribute(index);
                const std::string* key = attr->key();
                const std::string* value = attr->valueStr();
                if (*key == "name")
                {
                    mName = value->c_str();
                }
                if (*key == "vertexBuffer")
                {
                    mVertexBuffer = blueprint.vertexBuffer(value->c_str());
                }
                if (*key == "indexBuffer")
                {
                    mIndexBuffer = blueprint.indexBuffer(value->c_str());
                }
                if (*key == "texture")
                {
                    mTexture = blueprint.texture(value->c_str());
                }
                if (*key == "blend")
                {

                }
            }
        }
    }
}
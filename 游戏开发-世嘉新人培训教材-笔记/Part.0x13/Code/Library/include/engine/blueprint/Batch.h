#pragma once
#include <string>
#include "GameLib/Framework.h"
#include "engine/blueprint/Blueprint.h"
#include "engine/blueprint/VertexBuffer.h"

namespace base
{

    namespace xml
    {
        class Element;
    }
    namespace calculate
    {
        class Matrix44;
        class Matrix44;
    }
}
using namespace base::xml;
using namespace base::calculate;
namespace engine
{
    namespace blueprint
    {
        class Batch
        {
        public:
            Batch(const Element& element, const Blueprint blueprint);
            ~Batch();
            const std::string* name()const;

            const VertexBuffer* vertexBuffer()const;
            const IndexBuffer* indexBuffer()const;
            const Texture* texture()const;

            const void draw(const Matrix44& pwm)const;
            void buildObject(const Element& element, const Blueprint blueprint);
        private:
            std::string mName;
            GameLib::Framework::BlendMode mBlendMode;
            const VertexBuffer* mVertexBuffer;
            const IndexBuffer* mIndexBuffer;
            const Texture* mTexture;
        };
    }
}



#pragma once
#include <string>
#include "base/calculate/Vector2.h"
namespace base
{
    namespace xml
    {
        class Element;
    }
    namespace calculate
    {
        class Vector3;
        class Vector2;
    }
}
using namespace base::xml;
using namespace base::calculate;
namespace engine
{
    namespace blueprint
    {
        class VertexBuffer
        {
        public:
            VertexBuffer();
            VertexBuffer(const Element& element);
            ~VertexBuffer();
            const std::string* name() const;
            void setName(const std::string& name);
            void buildObject(const Element& element);
            void setPosition(const double* position);
            void setUV(const double* uv);
            const Vector3* position(int index)const;
            const Vector2* UV(int index)const;
            const int size()const;
        private:
            std::string mName;
            Vector3* mPosition;
            Vector2* mUV;
            int mSize;
        };
    }
}


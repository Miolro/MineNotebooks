#pragma once
#include <string>

namespace base
{
    namespace xml
    {
        class Element;
    }
}
namespace engine
{
    namespace blueprint
    {
        class IndexBuffer
        {
        public:
            IndexBuffer();
            ~IndexBuffer();
            const std::string* name() const;
            const unsigned index(int index) const;
            IndexBuffer(const base::xml::Element& element);
            void setName(const std::string& name);
            void buildObject(const base::xml::Element& element);
            const int size()const;
        private:
            std::string mName;
            int mSize;
            unsigned* mIndices;
        };
    }
}



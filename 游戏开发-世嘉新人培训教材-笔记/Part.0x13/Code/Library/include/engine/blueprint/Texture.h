#pragma once
#include "GameLib/Framework.h"
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
        class Texture
        {
        public:
            Texture();
            ~Texture();
            const std::string* name()const;
            Texture(const base::xml::Element& element);
            void setName(const std::string& name);
            void buildObject(const base::xml::Element& element);
            const GameLib::Texture* texture()const;
        private:
            GameLib::Texture* mTexture;
            std::string mName;
        };
    }

}

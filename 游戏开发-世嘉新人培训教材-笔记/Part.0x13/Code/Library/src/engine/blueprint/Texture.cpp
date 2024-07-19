#include "Engine/blueprint/Texture.h"
#include "base/xml/Element.h"
#include "base/xml/Attribute.h"
namespace engine
{
    namespace blueprint
    {
        Texture::Texture() :mTexture(0)
        {
        }

        Texture::~Texture()
        {
        }

        const std::string* Texture::name() const
        {
            return &mName;
        }

        Texture::Texture(const base::xml::Element& element)
        {
            buildObject(element);
        }

        void Texture::setName(const std::string& name)
        {
            mName = name;
        }

        void Texture::buildObject(const base::xml::Element& element)
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
                if (*key == "filename")
                {
                    GameLib::Framework::instance().createTexture(&mTexture, value->c_str());
                }
            }
        }

        const GameLib::Texture* Texture::texture()const
        {
            return mTexture;
        }
    }
}


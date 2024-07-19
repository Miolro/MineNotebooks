#include "base/xml/Document.h"
#include "base/xml/Tag.h"
#include "base/file/File.h"
#include "GameLib/GameLib.h"
#include "base/xml/Element.h"
namespace base
{
    namespace xml {
        Document::Document(const char* fileName)
        {
            base::file::File file(fileName);
            int count = 0;
            const char* dataPoint = file.data();
            const char* endPoint = dataPoint + file.size();
            Tag tag("<ROOT>");
            mRoot = new Element(&tag, &dataPoint, endPoint);
        }
        const Element* Document::root()const
        {
            return mRoot;
        }
    }
}
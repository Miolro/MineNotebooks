#pragma once

namespace base
{
    namespace xml
    {
        class Element;
        class Document
        {
        public:
            Document(const char* fileName);
            const Element* root()const;
        private:
            Element* mRoot;
        };
    }
}



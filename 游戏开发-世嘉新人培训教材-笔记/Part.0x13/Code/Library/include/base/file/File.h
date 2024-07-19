#pragma once
namespace base
{
    namespace file {
        class File
        {
        public:
            File(const char* fileName);
            const char* data() const;
            const int size()const;
            ~File();
        private:
            char* mData;
            int mSize;
        };
    }
}



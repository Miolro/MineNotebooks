#include "base/file/File.h"
#include "GameLib/GameLib.h"
#include <fstream>
using namespace std;
using namespace GameLib;
namespace base
{
    namespace file
    {
        File::File(const char* fileName) :mData(0), mSize(-1)
        {
            std::ifstream file(fileName, ios::binary);
            if (file.fail())
            {
                return;
            }
            file.seekg(0, ios::end);
            mSize = static_cast<int>(file.tellg());
            file.seekg(0, ios::beg);
            mData = new char[mSize];
            file.read(mData, mSize);
            cout << mData << endl;
        }

        const char* File::data() const
        {
            // TODO: 在此处插入 return 语句
            return mData;
        }

        const int File::size() const
        {
            return mSize;
        }

        File::~File()
        {
            delete(mData);
            mData = nullptr;
        }
    }
}


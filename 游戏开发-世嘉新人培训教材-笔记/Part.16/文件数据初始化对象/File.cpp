
#include "File.h"
#include "GameLib/GameLib.h"
#include <fstream>
using namespace std;
File::File()
{

}

File::~File()
{
	SAFE_DELETE_ARRAY(mData);
}

File::File(const char* fileName) :mSize(0), mData(nullptr)
{
	ifstream fileData(fileName, ifstream::binary); // 不能使用fstream 
	if (fileData)
	{
		fileData.seekg(0, fstream::end);
		mSize = static_cast<int>(fileData.tellg()); // 文本长度
		fileData.seekg(0, fstream::beg);
		mData = new char[mSize];
		fileData.read(mData, mSize);
	}
	else
	{
		HALT("can not open file");
	}


}

char* File::getData()const
{
	return mData;
}

unsigned File::getSize()const
{
	return mSize;
}

unsigned File::getEndian(unsigned iPosition)
{
	return 0;
}

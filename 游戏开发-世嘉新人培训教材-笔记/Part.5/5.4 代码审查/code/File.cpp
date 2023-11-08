#include "File.h"
File::File(const char* path) :mFileData(0), mFileSize(0)
{
	std::ifstream fileRead(path, std::ifstream::binary);
	if (fileRead.fail())
	{
		HALT("FILE ERROR");
	}
	fileRead.seekg(0, std::ifstream::end); // 把文件指针移动到最后一位
	mFileSize = fileRead.tellg(); // 返回当前指针的位置
	fileRead.seekg(0, std::ifstream::beg);
	mFileData = new char[mFileSize];
	fileRead.read(mFileData, mFileSize);
}

File::File() :mFileData(0), mFileSize(0)
{
}

File::~File()
{
	SAFE_DELETE_ARRAY(mFileData);
}

int File::getSize()
{
	return mFileSize;
}
char* File::getByte()
{
	return mFileData;
}
unsigned File::getBigEndia(int position)
{
	unsigned char* unsignedFileData = reinterpret_cast<unsigned char*> (mFileData);
	unsigned bigEndia = unsignedFileData[position];
	bigEndia |= unsignedFileData[position + 1] << 8;
	bigEndia |= unsignedFileData[position + 2] << 16;
	bigEndia |= unsignedFileData[position + 3] << 24;
	return bigEndia;
}
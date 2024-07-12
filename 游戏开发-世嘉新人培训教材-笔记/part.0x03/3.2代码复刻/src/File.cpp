#include "File.h"

File::File()
{
}
File::File(const char* fileName)
{
	std::ifstream fileReadIn(fileName, std::ifstream::binary);
	if (fileReadIn.fail())
	{
		throw "File 404";
	}
	fileReadIn.seekg(0, std::ifstream::end);
	mFileSize = static_cast<unsigned>(fileReadIn.tellg());
	fileReadIn.seekg(0, std::ifstream::beg);
	mFileData = new char[mFileSize];
	fileReadIn.read(mFileData, mFileSize);
}

char* File::getData()
{
	return mFileData;
}

unsigned File::getSize()
{
	return mFileSize;
}

unsigned File::getEndian(unsigned iPosition)
{
	// char -> unsigned char 去除负数防止初始化返回值时出现FF FF FF ?? 的情况
	// 一个临时变量tFileData
	unsigned char* tFileData = reinterpret_cast<unsigned char*>(mFileData);
	// 这个是小端  需要放到unsigned中 0 0 0 1 (1)标记的位置
	unsigned tRtn = tFileData[iPosition + 0];
	tRtn |= (tFileData[iPosition + 1] << 8);  // 或运算设置0 0 1 0 (1)标记的位置
	tRtn |= (tFileData[iPosition + 2] << 16);
	tRtn |= (tFileData[iPosition + 3] << 24);

	return tRtn;
}

File::~File()
{
	delete[]mFileData;
	mFileData = nullptr;
}
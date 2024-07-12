#include "File.h"

#include <fstream>
#include "GameLib/GameLib.h"

File::File(const char* fileName)
{
	std::ifstream imageFileBuffer(fileName, std::ios::binary);
	imageFileBuffer.seekg(0, std::ios::end);
	int fileSize = imageFileBuffer.tellg();
	imageFileBuffer.seekg(0, std::ios::beg);
	char* originFileByte = new char[fileSize];
	imageFileBuffer.read(originFileByte, fileSize);
	mFileByte = reinterpret_cast<unsigned char*>(originFileByte); // 指针指向originFile 只需要回收一个即可
}
File::~File()
{
	SAFE_DELETE_ARRAY(mFileByte);
}
unsigned File::getEndia(int position)
{
	return mFileByte[position] | mFileByte[position + 1] << 8 | mFileByte[position + 2] << 2 * 8 | mFileByte[position + 3] << 3 * 8;
}
#include "File.h"

#include <fstream>
#include "GameLib/GameLib.h"

File::File(const char* fileName)
{
	std::ifstream imageFileBuffer(fileName, std::ios::binary);
	ASSERT(imageFileBuffer&&"文件未找到");
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
// 最大输出4字节大小的大端无符号unsigned
unsigned File::getEndia(int position, int size)
{
	ASSERT(!(size > 4)&&"单次获取的大端数值不允许超过4字节");
	// 创建一个与阅读尺寸一样大的字节数组
	unsigned resultEndia = 0;
	for (int i = 0; i < size; i++)
	{
		resultEndia |= mFileByte[position + i] << i * 8;
	}
	return resultEndia;
}


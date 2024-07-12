#include "File.h"

#include <fstream>
#include "GameLib/GameLib.h"

File::File(const char* fileName)
{
	std::ifstream imageFileBuffer(fileName, std::ios::binary);
	ASSERT(imageFileBuffer&&"�ļ�δ�ҵ�");
	imageFileBuffer.seekg(0, std::ios::end);
	int fileSize = imageFileBuffer.tellg();
	imageFileBuffer.seekg(0, std::ios::beg);
	char* originFileByte = new char[fileSize];
	imageFileBuffer.read(originFileByte, fileSize);
	mFileByte = reinterpret_cast<unsigned char*>(originFileByte); // ָ��ָ��originFile ֻ��Ҫ����һ������
}
File::~File()
{
	SAFE_DELETE_ARRAY(mFileByte);
}
// ������4�ֽڴ�С�Ĵ���޷���unsigned
unsigned File::getEndia(int position, int size)
{
	ASSERT(!(size > 4)&&"���λ�ȡ�Ĵ����ֵ��������4�ֽ�");
	// ����һ�����Ķ��ߴ�һ������ֽ�����
	unsigned resultEndia = 0;
	for (int i = 0; i < size; i++)
	{
		resultEndia |= mFileByte[position + i] << i * 8;
	}
	return resultEndia;
}


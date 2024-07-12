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
	// char -> unsigned char ȥ��������ֹ��ʼ������ֵʱ����FF FF FF ?? �����
	// һ����ʱ����tFileData
	unsigned char* tFileData = reinterpret_cast<unsigned char*>(mFileData);
	// �����С��  ��Ҫ�ŵ�unsigned�� 0 0 0 1 (1)��ǵ�λ��
	unsigned tRtn = tFileData[iPosition + 0];
	tRtn |= (tFileData[iPosition + 1] << 8);  // ����������0 0 1 0 (1)��ǵ�λ��
	tRtn |= (tFileData[iPosition + 2] << 16);
	tRtn |= (tFileData[iPosition + 3] << 24);

	return tRtn;
}

File::~File()
{
	delete[]mFileData;
	mFileData = nullptr;
}
#include "File.h"
#include<fstream>
using namespace std;
File::File(const char* iFileName)
{
	// binary参数不加在图片读到10行附加时出现0xfbfbfbfb
	ifstream tFileObject(iFileName, ifstream::binary);
	tFileObject.seekg(0, ios::end);
	mFileSize = static_cast<int>(tFileObject.tellg());
	tFileObject.seekg(0, ios::beg);
	mFileByte = new char[mFileSize];
	tFileObject.read(mFileByte, mFileSize);
}

File::~File()
{
	delete[]mFileByte;
	mFileByte = nullptr;
}

int File::getFileSize()
{
	return mFileSize;
}

char* File::getFileByte()
{
	return mFileByte;
}

unsigned File::getEndian(unsigned iFileBytePosition)
{
	char number = mFileByte[iFileBytePosition];
	unsigned char* unsignedCharFileBuffer = reinterpret_cast<unsigned char*> (mFileByte);

	unsigned rtn = 0;
	rtn |= unsignedCharFileBuffer[iFileBytePosition + 0];
	rtn |= unsignedCharFileBuffer[iFileBytePosition + 1] << 8;
	rtn |= unsignedCharFileBuffer[iFileBytePosition + 2] << 16;
	rtn |= unsignedCharFileBuffer[iFileBytePosition + 3] << 24;
	return rtn;
}
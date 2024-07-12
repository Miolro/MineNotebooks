#pragma once
class File
{
public:
	File(const char* iFileName);
	~File();

	unsigned getFileSize();
	char* getFileByte();
	unsigned getEndian(unsigned iFileBytePosition);

	unsigned mFileSize;
	char* mFileByte;
};


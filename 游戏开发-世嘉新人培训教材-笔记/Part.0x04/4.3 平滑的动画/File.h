#pragma once
class File
{
public:
	File(const char* iFileName);
	~File();

	int getFileSize();
	char* getFileByte();
	unsigned getEndian(unsigned iFileBytePosition);

	int mFileSize;
	char* mFileByte;
};


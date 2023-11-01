#pragma once
#include <fstream>
#include"GameLib/GameLib.h"
class File
{
public:
	File(const char* path);
	File();
	~File();
	int getSize();
	char* getByte();
	unsigned getBigEndia(int position);
private:
	char* mFileData;
	int mFileSize;
};


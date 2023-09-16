#ifndef INCLUDE_FILE_HEADER
#define INCLUDE_FILE_HEADER

#include<fstream>

class File
{
public:
	File();
	~File();
	File(const char* fileName);
	char* getData();
	unsigned getSize();
	// 小端转为大端unsigned输出  传入的是这个文件开始读的位置
	unsigned getEndian(unsigned iPosition);

private:
	char* mFileData;
	unsigned mFileSize;
};

#endif INCLUDE_FILE_HEADER


#ifndef INCLUDE_FILE_HEADER
#define INCLUDE_FILE_HEADER

#include<fstream>

class File
{
public:
	File();
	~File();
	File(const char* fileName);
	char* getData() const;
	unsigned getSize() const;
	// 小端转为大端unsigned输出  传入的是这个文件开始读的位置
	unsigned getEndian(unsigned iPosition);

private:
	char* mData;
	int mSize;
};

#endif INCLUDE_FILE_HEADER


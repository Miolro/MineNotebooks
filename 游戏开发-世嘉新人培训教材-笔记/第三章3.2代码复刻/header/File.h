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
	// С��תΪ���unsigned���  �����������ļ���ʼ����λ��
	unsigned getEndian(unsigned iPosition);

private:
	char* mFileData;
	unsigned mFileSize;
};

#endif INCLUDE_FILE_HEADER


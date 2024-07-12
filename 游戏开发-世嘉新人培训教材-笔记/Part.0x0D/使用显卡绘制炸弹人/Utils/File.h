#pragma once
class File
{
public:
	File(const char*);
	~File();
	unsigned getEndia(int position, int size);
private:

	unsigned char* mFileByte;
};
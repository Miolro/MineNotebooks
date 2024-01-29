#pragma once
class File
{
public:
	File(const char*);
	~File();
	unsigned getEndia(int position);
private:

	unsigned char* mFileByte;
};
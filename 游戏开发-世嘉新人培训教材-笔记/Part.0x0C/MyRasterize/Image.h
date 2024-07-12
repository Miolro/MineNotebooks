#pragma once
#include "File.h"
class Image
{
public:
	Image(const char*);
	~Image();
	int iWidth();
	int iHeight();
	unsigned pixel(int x, int y);
private:
	int mWidth;
	int mHeight;
	unsigned* mPiexlInfo;
};
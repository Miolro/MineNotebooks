#pragma once
#ifndef INCLUDE_IMAGE_HEADER
#define INCLUDE_IMAGE_HEADER

#include"File.h"

class Image
{
public:
	Image();
	~Image();
	Image(const char* fileName);
	void imageCellDraw(unsigned iBegPosX, unsigned iBegPosY, unsigned iEndPosX, unsigned iEndPosY, unsigned iVramPosX, unsigned iVramPosY);
private:
	unsigned* mImageData;
	unsigned mImageHeight;
	unsigned mImageWidth;
};
#endif INCLUDE_IMAGE_HEADER

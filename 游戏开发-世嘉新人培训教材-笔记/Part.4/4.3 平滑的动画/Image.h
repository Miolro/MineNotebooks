#pragma once
#include "File.h"
class Image
{
public:
	Image();
	Image(const char* iFile);
	~Image();

	unsigned* getImageData();

	void drawImage(int iVideoX, int iVideoY, int iPositionX, int iPosition, int cutSize1, int cutSize2) const;


	int mImageHeight;
	int mImageWidth;
	char* mFile;
	unsigned* mImageData;

};

enum ImageID {

};
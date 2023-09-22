#pragma once
#include "File.h"
class Image
{
public:
	Image();
	Image(const char* iFile);
	~Image();

	unsigned* getImageData();

	unsigned mImageHeight;
	unsigned mImageWidth;
	char* mFile;
	unsigned* mImageData;

};

enum ImageID {

};
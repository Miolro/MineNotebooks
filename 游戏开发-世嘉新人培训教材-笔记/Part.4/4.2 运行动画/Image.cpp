#include "Image.h"

Image::Image()
{
}
Image::Image(const char* iFile)
{
	File file(iFile);
	mImageHeight = file.getEndian(0x0C);
	mImageWidth = file.getEndian(0x10);
	mImageData = new unsigned[mImageHeight * mImageWidth];
	for (unsigned i = 0; i < mImageHeight * mImageWidth; i++)
	{
		mImageData[i] = file.getEndian(i * 4 + 0x80);
	}
}
Image::~Image()
{
	delete[]mImageData;
	mImageData = nullptr;
}

unsigned* Image::getImageData()
{
	return mImageData;
}




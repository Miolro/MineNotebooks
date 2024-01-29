#include "Image.h"
#include "File.h"
#include "GameLib/GameLib.h"

Image::Image(const char* fileName)
{
	File file(fileName);
	mHeight = file.getEndia(0x0c);
	mWidth = file.getEndia(0x10);
	mPiexlInfo = new unsigned[mHeight * mWidth];
	for (int i = 0; i < mHeight * mWidth; i++)
	{
		mPiexlInfo[i] = file.getEndia(i * 4 + 0x80);
	}
}
Image::~Image()
{
	SAFE_DELETE_ARRAY(mPiexlInfo);
}
int Image::iWidth()
{
	return mWidth;
}
int Image::iHeight()
{
	return mHeight;
}
unsigned Image::pixel(int x, int y)
{
	return mPiexlInfo[y * mWidth + x];
}
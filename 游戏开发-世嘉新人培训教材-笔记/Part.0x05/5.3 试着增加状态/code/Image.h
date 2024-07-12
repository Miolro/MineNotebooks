#pragma once
#include "File.h"
#include "GameLib/GameLib.h"
#include "GameLib/Framework.h"
class Image
{
public:
	Image();
	Image(const char* path);
	~Image();
	void draw(int vramx, int vramy, int imgPositionX, int imgPositionY, int width, int height);
	int getSize();
	int getWidth();
	unsigned* getData();

private:
	int mHeight;
	int	mWidth;
	unsigned* mImageData;
};


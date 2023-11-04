#include "Image.h"

Image::Image()
{

}

Image::Image(const char* path)
{
	File image = File(path);
	mHeight = image.getBigEndia(0x0C);
	mWidth = image.getBigEndia(0x10);
	mImageData = new unsigned[mHeight * mWidth];
	for (int i = 0; i < mHeight * mWidth; i++)
	{
		mImageData[i] = image.getBigEndia(i * 4 + 0x80);
	}
}
int Image::getWidth()
{
	return mWidth;
}
int Image::getHeight()
{
	return mHeight;
}
Image::~Image()
{
	SAFE_DELETE_ARRAY(mImageData);
}

int Image::getSize()
{
	return mHeight * mWidth;
}
unsigned* Image::getData()
{
	return mImageData;
}


void Image::draw(int vramx, int vramy, int imgPositionX, int imgPositionY, int width, int height)
{
	int vWidth = GameLib::Framework::instance().width();
	unsigned* vram = GameLib::Framework::instance().videoMemory();
	for (int a = imgPositionY, b = 0;a < imgPositionY + height;a++, b++)
	{
		for (int c = imgPositionX, d = 0; c < imgPositionX + width; c++, d++)
		{
			unsigned imgFlag = mImageData[a * mWidth + c];
			unsigned* vramFlag = &vram[(vramy + b) * vWidth + d + vramx];

			unsigned imgA = imgFlag >> 24 > 0x80 ? 0xff : 0x00;


			unsigned imgR = imgFlag & 0x00ff0000;
			unsigned imgG = imgFlag & 0x0000ff00;
			unsigned imgB = imgFlag & 0x000000ff;

			unsigned vramR = *vramFlag & 0x00ff0000;
			unsigned vramG = *vramFlag & 0x0000ff00;
			unsigned vramB = *vramFlag & 0x000000ff;

			unsigned remixR = (imgR - vramR) * imgA / 255 + vramR;
			unsigned remixG = (imgG - vramG) * imgA / 255 + vramG;
			unsigned remixB = (imgB - vramB) * imgA / 255 + vramB;

			unsigned remixRGB = remixR | remixG | remixB;
			*vramFlag = remixRGB;
		}
	}
}
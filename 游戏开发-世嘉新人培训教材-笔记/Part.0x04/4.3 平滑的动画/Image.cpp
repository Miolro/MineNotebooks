#include "Image.h"
#include "GameLib/Framework.h"
using namespace GameLib;
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
// video Î»ÖÃ £¨x,y£©²Ã¼ôÍ¼Æ¬µÄÎ»ÖÃ(x,y),²Ã¼ôÍ¼Æ¬µÄ´óÐ¡(w,h)
void Image::drawImage(int iVideoX, int iVideoY, int iPositionX, int iPositionY, int cutSize1, int cutSize2)const
{

	unsigned* videoMemory = Framework::instance().videoMemory();
	int videoWidth = Framework::instance().width();

	int vx = iVideoX;
	int vy = iVideoY;

	for (int i = iPositionY, y = 0; i < iPositionY + cutSize2; i++, y++)
	{
		for (int j = iPositionX, x = 0; j < iPositionX + cutSize1; j++, x++)
		{
			unsigned* videoPeixl = &videoMemory[(vy + y) * videoWidth + (vx + x)];
			// Í¼Ïñµþ¼Ó
			unsigned imagePeixl = mImageData[i * mImageWidth + j];

			unsigned  alpha = imagePeixl >> 24;
			alpha = alpha > 0x80 ? 0xff : 0x00;

			unsigned videoRed = *videoPeixl & 0x00ff0000;
			unsigned videoGre = *videoPeixl & 0x0000ff00;
			unsigned videoBlu = *videoPeixl & 0x000000ff;

			unsigned imageRed = imagePeixl & 0x00ff0000;
			unsigned imageGre = imagePeixl & 0x0000ff00;
			unsigned imageBlu = imagePeixl & 0x000000ff;

			unsigned r = (imageRed - videoRed) * alpha / 255 + videoRed;
			unsigned g = (imageGre - videoGre) * alpha / 255 + videoGre;
			unsigned b = (imageBlu - videoBlu) * alpha / 255 + videoBlu;

			*videoPeixl = (r & 0x00ff0000) | (g & 0x0000ff00) | b;
		}
	}

}

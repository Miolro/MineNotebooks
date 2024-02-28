#include "Image.h"
#include "File.h"
#include "GameLib/GameLib.h"
#include "GameLib/Framework.h"
static int powerOfTwo(int in)
{
	unsigned result = 2;
	int tmp = in;
	while (true) {
		if (tmp >>= 1) {
			result <<= 1;
		}
		else
		{
			break;
		}
	}
	return result;
}



//Image::Image(const char* fileName)
//{
//	File file(fileName);
//	mHeight = file.getEndia(0x0c);
//	mWidth = file.getEndia(0x10);
//	mPiexlInfo = new unsigned[mHeight * mWidth];
//	for (int i = 0; i < mHeight * mWidth; i++)
//	{
//		mPiexlInfo[i] = file.getEndia(i * 4 + 0x80);
//	}
//}
// dds读取转纹理存储
Image::Image(const char* fileName)
{
	File file(fileName);
	mImageWidth = file.getEndia(0x10, 4);
	mImageHeight = file.getEndia(0x0c, 4);

	int indexDataSize = mImageHeight * mImageWidth;
	unsigned* textureData = new unsigned[indexDataSize];
	for (size_t i = 0; i < indexDataSize; i++)
	{
		textureData[i] = file.getEndia(0x80 + i * 4, 4);
	}

	mTextureHeight = powerOfTwo(mImageHeight);
	mTextureWidth = powerOfTwo(mImageWidth);
	GameLib::Framework::instance().createTexture(&mTexture, mTextureWidth, mTextureHeight, textureData, mImageWidth, mImageHeight);
	SAFE_DELETE_ARRAY(textureData); // 清除临时变量
}

Image::~Image()
{
	GameLib::Framework::instance().destroyTexture(&mTexture);
	/*SAFE_DELETE_ARRAY(mPiexlInfo);*/
}
int Image::getTextureWidth()
{
	return mImageWidth;
}
int Image::getTextureHeight()
{
	return mImageHeight;
}

void Image::drawTexture(int screenPositionX, int screenPositionY, int imageBCutX, int imageBCutY, int imageWidth, int imageHeight) const
{
	GameLib::Framework::instance().setTexture(mTexture);
	// 0 1
	// 2 3
	double doubleScPosX0 = static_cast<double>(screenPositionX);
	double doubleScPosY0 = static_cast<double>(screenPositionY);
	double doubleScPosX1 = doubleScPosX0 + static_cast<double>(imageWidth);
	double doubleScPosY1 = doubleScPosY0 + static_cast<double>(imageHeight);

	double p0[2] = { doubleScPosX0 ,doubleScPosY0 };
	double p1[2] = { doubleScPosX1 ,doubleScPosY0 };
	double p2[2] = { doubleScPosX0 ,doubleScPosY1 };
	double p3[2] = { doubleScPosX1 ,doubleScPosY1 };
	//计算屏幕延展比例
	double tw = 1.0 / static_cast<double>(mTextureWidth);
	double th = 1.0 / static_cast<double>(mTextureHeight);
	double v = imageBCutX * tw;
	double h = imageBCutY * th;
	double v1 = (imageWidth + imageBCutX) * tw;
	double h1 = (imageHeight + imageBCutY) * th;
	double t0[2] = { v,h };
	double t1[2] = { v1,h };
	double t2[2] = { v,h1 };
	double t3[2] = { v1,h1 };

	GameLib::Framework::instance().drawTriangle2D(p0, p1, p2, t0, t1, t2);
	GameLib::Framework::instance().drawTriangle2D(p3, p1, p2, t3, t1, t2);
}
void Image::drawTexture(int width, int height)
{
	drawTexture(0, 0, 0, 0, width, height);
}
void Image::drawString(int screenX, int screenY, const char* str, unsigned color = 0xffffffff)
{
	GameLib::Framework::instance().setTexture(mTexture);
	int fontWidth = 8;
	int fontHeight = 16;
	int rows = 16;
	for (int i = 0; str[i] != '\0'; i++)
	{
		int fontPosition = static_cast<int>(str[i]) - 0x00000020; // 对齐  然后计算xy的位置
		int positionX = fontPosition % rows;
		int positionY = fontPosition / rows;


		double p0[2] = { screenX ,screenY };
		double p1[2] = { screenX + mImageWidth ,screenY };
		double p2[2] = { screenX ,screenY + mImageHeight };
		double p3[2] = { screenX + mImageWidth ,screenY + mImageHeight };
		//计算屏幕延展比例
		double tw = 1.0 / static_cast<double>(mTextureWidth);
		double th = 1.0 / static_cast<double>(mTextureHeight);
		double v = mImageWidth * tw;
		double h = mImageHeight * th;
		double t0[2] = { 0.0,0.0 };
		double t1[2] = { v,0.0 };
		double t2[2] = { 0.0,h };
		double t3[2] = { v,h };

		GameLib::Framework::instance().drawTriangle2D(p0, p1, p2, t0, t1, t2);
		GameLib::Framework::instance().drawTriangle2D(p3, p1, p2, t3, t1, t2);
	}
}
//unsigned Image::pixel(int x, int y)
//{
//	return mPiexlInfo[y * mWidth + x];
//}


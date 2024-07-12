#pragma once
#include "File.h"
#include "GameLib/Framework.h"
class Image
{
public:
	Image(const char*);
	~Image();
	//int iWidth();
	//int iHeight();

	int getTextureWidth();
	int getTextureHeight();
	void drawTexture(int screenPositionX, int screenPositionY, int imageBCutX, int imageBCutY, int imageWidth, int imageHeight) const;
	void drawTexture(int width, int height);
	void drawString(int x, int y, const char* str, unsigned color);
	unsigned pixel(int x, int y);
private:
	int mImageWidth;	// TGA宽度 c-d
	int mImageHeight;	// TGA宽度 e-f

	int mTextureWidth;
	int	mTextureHeight;
	//unsigned* mPiexlInfo; // 原有的素组存储被纹理取代
	int horizontal;  // TGA水平坐标 // 8-9字节
	int vertical;    // TGA垂直坐标 // a-b字节
	GameLib::Texture* mTexture;
};
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
	int mImageWidth;	// TGA��� c-d
	int mImageHeight;	// TGA��� e-f

	int mTextureWidth;
	int	mTextureHeight;
	//unsigned* mPiexlInfo; // ԭ�е�����洢������ȡ��
	int horizontal;  // TGAˮƽ���� // 8-9�ֽ�
	int vertical;    // TGA��ֱ���� // a-b�ֽ�
	GameLib::Texture* mTexture;
};
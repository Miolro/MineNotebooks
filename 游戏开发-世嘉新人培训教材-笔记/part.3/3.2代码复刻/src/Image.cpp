#include"Image.h"
#include <State.h>

Image::Image()
{
}

Image::~Image()
{
}

Image::Image(const char* iFileName)
{
	File file(iFileName);
	char* tFileData = file.getData();
	unsigned tFileSize = file.getSize();
	mImageWidth = file.getEndian(0x10);
	mImageHeight = file.getEndian(0x0C);

	mImageData = new unsigned[mImageWidth * mImageHeight];

	// 这里从文件的128位开始读 128前面的DDS结构体 步长4 一个像素颜色用4个字节表达
	for (unsigned tIndex = 0x80, tPeixl = 0; tIndex < tFileSize; tIndex += 4, tPeixl++)
	{	// 以一条直线写入数据

		unsigned* tBuffer = &mImageData[tPeixl];
		*tBuffer = file.getEndian(tIndex);
	}
}

void Image::imageCellDraw(
	unsigned iBegPosX, unsigned iBegPosY,
	unsigned iEndPosX, unsigned iEndPosY,
	unsigned iVramPosX, unsigned iVramPosY)
{
	unsigned* tVram = Framework::instance().videoMemory();
	unsigned tVramWidth = Framework::instance().width();

	unsigned tXSize = iEndPosX - iBegPosX;
	unsigned tySize = iEndPosY - iBegPosY;

	for (unsigned ty = iBegPosY, tdrawY = 0; ty <= iEndPosY; ty++, tdrawY++)
	{
		for (unsigned tx = iBegPosX, tdrawX = 0; tx <= iEndPosX; tx++, tdrawX++)
		{	// 绘制的起点  原始位置+补偿位置
			unsigned* dts = &tVram[(tdrawY * tVramWidth + tdrawX)
				+ (iVramPosY * tySize * tVramWidth + (iVramPosX * tXSize))
			];
			*dts = mImageData[ty * mImageWidth + tx];
		}
	}
}



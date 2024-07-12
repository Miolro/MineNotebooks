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
	{	// 以一条直线写入数据  这里对引用的ImageData写入数据

		unsigned* tBuffer = &mImageData[tPeixl];
		// 转大端后写入到引用的ImageData中
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
			//3.3中内容  透明度混合
			// 拆分通道
			unsigned imageARGB = mImageData[ty * mImageWidth + tx];

			double tColorA = static_cast<double> ((imageARGB & 0xFF000000) >> 24);		// A通道
			double tColorR = static_cast<double> ((imageARGB & 0x00FF0000) >> 16);		// R通道
			double tColorG = static_cast<double> ((imageARGB & 0x0000FF00) >> 8);			// G通道
			double tColorB = static_cast<double> ((imageARGB & 0x000000FF));				// B通道

			double tColorVramR = static_cast<double> ((*dts & 0x00FF0000) >> 16);
			double tColorVramG = static_cast<double> ((*dts & 0x0000FF00) >> 8);
			double tColorVramB = static_cast<double> ((*dts & 0x000000FF));

			// 比例混合 使用透明度tColorA

			double tRatio = tColorA / 255.0;
			// tRatio使用的比率 (1.00 - tRatio) 补充的比率
			double tColorSynthesisR = tColorR * tRatio + ((1.f - tRatio) * tColorVramR);
			double tColorSynthesisG = tColorG * tRatio + ((1.f - tRatio) * tColorVramG);
			double tColorSynthesisB = tColorB * tRatio + ((1.f - tRatio) * tColorVramB);
			// 转整形输出结果

			*dts = static_cast<unsigned>(tColorSynthesisR) << 16;
			*dts |= static_cast<unsigned>(tColorSynthesisG) << 8;
			*dts |= static_cast<unsigned>(tColorSynthesisB);
		}
	}
}



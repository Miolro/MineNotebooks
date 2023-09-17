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

	// ������ļ���128λ��ʼ�� 128ǰ���DDS�ṹ�� ����4 һ��������ɫ��4���ֽڱ��
	for (unsigned tIndex = 0x80, tPeixl = 0; tIndex < tFileSize; tIndex += 4, tPeixl++)
	{	// ��һ��ֱ��д������  ��������õ�ImageDataд������

		unsigned* tBuffer = &mImageData[tPeixl];
		// ת��˺�д�뵽���õ�ImageData��
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
		{	// ���Ƶ����  ԭʼλ��+����λ�� 
			unsigned* dts = &tVram[(tdrawY * tVramWidth + tdrawX)
				+ (iVramPosY * tySize * tVramWidth + (iVramPosX * tXSize))
			];
			//3.3������  ͸���Ȼ��
			// ���ͨ��
			unsigned imageARGB = mImageData[ty * mImageWidth + tx];

			double tColorA = static_cast<double> ((imageARGB & 0xFF000000) >> 24);		// Aͨ��
			double tColorR = static_cast<double> ((imageARGB & 0x00FF0000) >> 16);		// Rͨ��
			double tColorG = static_cast<double> ((imageARGB & 0x0000FF00) >> 8);			// Gͨ��
			double tColorB = static_cast<double> ((imageARGB & 0x000000FF));				// Bͨ��

			double tColorVramR = static_cast<double> ((*dts & 0x00FF0000) >> 16);
			double tColorVramG = static_cast<double> ((*dts & 0x0000FF00) >> 8);
			double tColorVramB = static_cast<double> ((*dts & 0x000000FF));

			// ������� ʹ��͸����tColorA

			double tRatio = tColorA / 255.0;
			// tRatioʹ�õı��� (1.00 - tRatio) ����ı���
			double tColorSynthesisR = tColorR * tRatio + ((1.f - tRatio) * tColorVramR);
			double tColorSynthesisG = tColorG * tRatio + ((1.f - tRatio) * tColorVramG);
			double tColorSynthesisB = tColorB * tRatio + ((1.f - tRatio) * tColorVramB);
			// ת����������

			*dts = static_cast<unsigned>(tColorSynthesisR) << 16;
			*dts |= static_cast<unsigned>(tColorSynthesisG) << 8;
			*dts |= static_cast<unsigned>(tColorSynthesisB);
		}
	}
}



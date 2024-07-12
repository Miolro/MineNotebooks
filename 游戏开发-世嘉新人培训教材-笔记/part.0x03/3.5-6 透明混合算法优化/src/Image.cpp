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

			//double tColorA = static_cast<double> ((imageARGB & 0xFF000000) >> 24);		// Aͨ��
			//double tColorR = static_cast<double> ((imageARGB & 0x00FF0000) >> 16);		// Rͨ��
			//double tColorG = static_cast<double> ((imageARGB & 0x0000FF00) >> 8);			// Gͨ��
			//double tColorB = static_cast<double> ((imageARGB & 0x000000FF));				// Bͨ��

			//double tColorVramR = static_cast<double> ((*dts & 0x00FF0000) >> 16);
			//double tColorVramG = static_cast<double> ((*dts & 0x0000FF00) >> 8);
			//double tColorVramB = static_cast<double> ((*dts & 0x000000FF));

			//// ������� ʹ��͸����tColorA

			//double tRatio = tColorA / 255.0;
			//// tRatioʹ�õı��� (1.00 - tRatio) ����ı���
			//double tColorSynthesisR = tColorR * tRatio + ((1.f - tRatio) * tColorVramR);
			//double tColorSynthesisG = tColorG * tRatio + ((1.f - tRatio) * tColorVramG);
			//double tColorSynthesisB = tColorB * tRatio + ((1.f - tRatio) * tColorVramB);
			//3.5 ͸������㷨�Ż� (����)(ȥת��)

			//unsigned tColorA = (imageARGB & 0xFF000000) >> 24;		// Aͨ��
			//unsigned tColorR = (imageARGB & 0x00FF0000) >> 16;		// Rͨ��
			//unsigned tColorG = (imageARGB & 0x0000FF00) >> 8;			// Gͨ��
			//unsigned tColorB = (imageARGB & 0x000000FF);				// Bͨ��

			//unsigned tColorVramR = (*dts & 0x00FF0000) >> 16;
			//unsigned tColorVramG = (*dts & 0x0000FF00) >> 8;
			//unsigned tColorVramB = (*dts & 0x000000FF);

			//unsigned tColorSynthesisR = tColorA * (tColorR - tColorVramR) / 255 + tColorVramR;
			//unsigned tColorSynthesisG = tColorA * (tColorG - tColorVramG) / 255 + tColorVramG;
			//unsigned tColorSynthesisB = tColorA * (tColorB - tColorVramB) / 255 + tColorVramB;
			//// ת����������

			//*dts = tColorSynthesisR << 16;
			//*dts |= tColorSynthesisG << 8;
			//*dts |= tColorSynthesisB;

			//3.5.2 ȥ����λ++

			unsigned tColorA = (imageARGB & 0xFF000000) >> 24;		// Aͨ��

			// ͸����Ե����ֵ(��ֵ��) �Ǻڼ���							// ���ӻ���ֹ����������
			tColorA = (tColorA > 0x50) ? 0xFF : 0x00;

			unsigned tColorR = imageARGB & 0x00FF0000;			// Rͨ�� 0x00 73 00 00
			unsigned tColorG = imageARGB & 0x0000FF00;			// Gͨ�� 0x00 00 7a 00
			unsigned tColorB = imageARGB & 0x000000FF;			// Bͨ�� 0x00 00 00 a6

			unsigned tColorVramR = *dts & 0x00FF0000;
			unsigned tColorVramG = *dts & 0x0000FF00;
			unsigned tColorVramB = *dts & 0x000000FF;

			unsigned tColorSynthesisR = tColorA * (tColorR - tColorVramR) / 255 + tColorVramR; // 0x00 73 00 00
			unsigned tColorSynthesisG = tColorA * (tColorG - tColorVramG) / 255 + tColorVramG; // 0x00 00 7a 00
			unsigned tColorSynthesisB = tColorA * (tColorB - tColorVramB) / 255 + tColorVramB; // 0x00 00 00 a6

			// ת����������
			unsigned dtsout = tColorSynthesisR;
			dtsout |= tColorSynthesisG;
			dtsout |= tColorSynthesisB;

			*dts = tColorSynthesisR;
			*dts |= tColorSynthesisG;
			*dts |= tColorSynthesisB;
		}
	}
}



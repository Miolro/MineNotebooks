# 第三章

`混合公式`

```
    x+y = 1
    xA+(1-y)B = 比例混合后的结果
```

下面代码中`tVram`取到每一位和`mImageData[ty * mImageWidth + tx]`中的值按照透明通道的值做混合 透明比率为`mImageData[ty * mImageWidth + tx]`中A通道的值除以它的上限255得到结果透明比率

 通过DDS文件可以看到小人周围都是`透明色彩`  所以在小人周围会显示第一次着色时候的颜色  代码中通过两次着色  第一次绘制背景  第二次绘制小人和箱子

```C++
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



```
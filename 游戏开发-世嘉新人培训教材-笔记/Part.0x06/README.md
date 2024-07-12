# 第六章 文本绘制方法

## 6.1 字体图片 

如何在画面上显示字体呢

只需要在写满字符的图片上切割区域即可

## 6.2 文本绘制函数

那么我们尝试采用更简单的风格比如

``` C++
drawString(0,0,"BAKAME")
```

首先函数内部将进行对字符串逐一取出字符,然后定位文字位置,然后显示在画面上

```C++
void drawString(int x, int y, const char* inputString)
{
	for (int i = 0;inputString[i] != '\0'; i++)
	{
		// 对齐ASCII码
		int asciiPosition = inputString[i] - 0x20;
		int x = asciiPosition % 16;
		int y = asciiPosition / 16;
		cellImage(x * 8, y * 16, 8, 16, i * 8, 20);
		GameLib::cout << asciiPosition << GameLib::endl;
	}
}
```

取出单元格中的图片

```C++
void cellImage(int positionx, int positiony, int width, int height, int varmx, int varmy) {
	//取出单元格 画到显示上
	for (int y = positiony, vy = varmy; y < positiony + height; y++, vy++)
		{
		for (int x = positionx, vx = varmx; x < positionx + width; x++, vx++)
		{
		    varm[vy * varmWidth + vx] = mImagePiexl[y * imageSize[1] + x];
		}
	}
}
```

完整代码

```C++
#include "GameLib/Framework.h"
#include <fstream>
class File {
public:
	File(const char* filePath)
	{
		std::ifstream fileRead(filePath, std::ifstream::binary);
		if (fileRead.fail()) { GameLib::cout << "error" << GameLib::endl; }
		fileRead.seekg(0, std::ifstream::end);
		fileSize = fileRead.tellg();
		fileRead.seekg(0, std::ifstream::beg);
		fileByte = new char[fileSize];
		fileRead.read(fileByte, fileSize);
	};
	~File()
	{
		SAFE_DELETE_ARRAY(fileByte);
	};
	unsigned getEndia(int position)
	{
		unsigned char* unsignChars = reinterpret_cast<unsigned char*>(fileByte);
		unsigned result = unsignChars[position];
		result |= unsignChars[position + 1] << 8;
		result |= unsignChars[position + 2] << 16;
		result |= unsignChars[position + 3] << 24;
		return result;
	}
private:
	int fileSize;
	char* fileByte;
};
class Image {
public:
	Image(const char* filePath) :imageSize(0)
	{
		File imageFile = File(filePath);
		imageSize = new int[2];
		imageSize[0] = imageFile.getEndia(0x0C);	// 高
		imageSize[1] = imageFile.getEndia(0x10);	// 宽
		//initializer ImageDataSize
		mImagePiexl = new unsigned[imageSize[0] * imageSize[1]];
		for (unsigned i = 0; i < imageSize[0] * imageSize[1]; i++)
		{
			mImagePiexl[i] = imageFile.getEndia(i * 4 + 0x80);
		}
		varm = GameLib::Framework::instance().videoMemory();
		varmWidth = GameLib::Framework::instance().width();

	};
	~Image() {
		SAFE_DELETE_ARRAY(imageSize);
		SAFE_DELETE_ARRAY(mImagePiexl);
	};
	void cellImage(int positionx, int positiony, int width, int height, int varmx, int varmy) {
		//取出单元格 画到显示上
		for (int y = positiony, vy = varmy; y < positiony + height; y++, vy++)
		{
			for (int x = positionx, vx = varmx; x < positionx + width; x++, vx++)
			{
				varm[vy * varmWidth + vx] = mImagePiexl[y * imageSize[1] + x];
			}
		}
	}
	void drawString(int x, int y, const char* inputString)
	{

		for (int i = 0;inputString[i] != '\0'; i++)
		{
			// 对齐ASCII码
			int asciiPosition = inputString[i] - 0x20;
			int x = asciiPosition % 16;
			int y = asciiPosition / 16;
			cellImage(x * 8, y * 16, 8, 16, i * 8, 20);
			GameLib::cout << asciiPosition << GameLib::endl;
		}
	}
	int& getSize() {
		return *imageSize;
	}
private:
	int* imageSize;
	unsigned* mImagePiexl;
	unsigned* varm;
	unsigned varmWidth;
};

namespace GameLib {
	char flag = 0;
	Image* gImage = nullptr;
	void Framework::update() {
		if (flag == 0) {
			gImage = new  Image("image/font.dds");
			//gImage->cellImage(0, 0, 128, 96, 0, 0); // 全字体打印
			gImage->drawString(0, 0, "Miolro");
			flag = 1;
		}
	}
}

```

颜色修改
```C++
unsigned replaceStringColor(unsigned pixel, int color)
{
	unsigned pixelAlp = pixel & 0xFF000000;
	if (color != 0 && pixelAlp) {
		// reset Alp
		unsigned result = color; // 设置颜色
		return result |= pixelAlp; // 重新设置透明通道
	}
	return pixel;
};
```

附带颜色字体的代码

```C++
#include "GameLib/Framework.h"
#include <fstream>
class File {
public:
	File(const char* filePath)
	{
		std::ifstream fileRead(filePath, std::ifstream::binary);
		if (fileRead.fail()) { GameLib::cout << "error" << GameLib::endl; }
		fileRead.seekg(0, std::ifstream::end);
		fileSize = fileRead.tellg();
		fileRead.seekg(0, std::ifstream::beg);
		fileByte = new char[fileSize];
		fileRead.read(fileByte, fileSize);
	};
	~File()
	{
		SAFE_DELETE_ARRAY(fileByte);
	};
	unsigned getEndia(int position)
	{
		unsigned char* unsignChars = reinterpret_cast<unsigned char*>(fileByte);
		unsigned result = unsignChars[position];
		result |= unsignChars[position + 1] << 8;
		result |= unsignChars[position + 2] << 16;
		result |= unsignChars[position + 3] << 24;
		return result;
	}
private:
	int fileSize;
	char* fileByte;
};
class Image {
public:
	Image(const char* filePath) :imageSize(0)
	{
		File imageFile = File(filePath);
		imageSize = new int[2];
		imageSize[0] = imageFile.getEndia(0x0C);	// 高
		imageSize[1] = imageFile.getEndia(0x10);	// 宽
		//initializer ImageDataSize
		mImagePixel = new unsigned[imageSize[0] * imageSize[1]];
		for (unsigned i = 0; i < imageSize[0] * imageSize[1]; i++)
		{
			mImagePixel[i] = imageFile.getEndia(i * 4 + 0x80);
		}
		varm = GameLib::Framework::instance().videoMemory();
		varmWidth = GameLib::Framework::instance().width();

	};
	~Image() {
		SAFE_DELETE_ARRAY(imageSize);
		SAFE_DELETE_ARRAY(mImagePixel);
	};
	void cellImage(int positionx, int positiony, int width, int height, int varmx, int varmy, int color, bool isAdd) {
		//取出单元格 画到显示上
		for (int y = positiony, vy = varmy; y < positiony + height; y++, vy++)
		{
			for (int x = positionx, vx = varmx; x < positionx + width; x++, vx++)
			{
				//颜色叠加
				unsigned varmColor = varm[vy * varmWidth + vx];
				// 提取屏幕颜色
				unsigned varmColorR = varmColor & 0x00FF0000;
				unsigned varmColorG = varmColor & 0x0000FF00;
				unsigned varmColorB = varmColor & 0x000000FF;
				// 提取图片颜色
				unsigned piexlColor = replaceStringColor(mImagePixel[y * imageSize[1] + x], color);
				unsigned piexlColorA = piexlColor & 0xFF000000;
				unsigned piexlColorR = piexlColor & 0x00FF0000;
				unsigned piexlColorG = piexlColor & 0x0000FF00;
				unsigned piexlColorB = piexlColor & 0x000000FF;
				unsigned result = 0;
				if (isAdd)  // 是否进行颜色叠加
				{
					if (piexlColorA)
					{
						piexlColorA = piexlColorA >> 24;

						result |= varmColorR + (piexlColorR - varmColorR) * piexlColorA / 255;
						result |= varmColorG + (piexlColorG - varmColorG) * piexlColorA / 255;
						result |= varmColorB + (piexlColorB - varmColorB) * piexlColorA / 255;
					}
				}
				else
				{
					result |= piexlColor;
				}
				varm[vy * varmWidth + vx] = result;
			}
		}
	}
	unsigned replaceStringColor(unsigned pixel, int color)
	{
		unsigned pixelAlp = pixel & 0xFF000000;
		if (color != 0 && pixelAlp) {
			// reset Alp
			unsigned result = color; // 设置颜色
			return result |= pixelAlp; // 重新设置透明通道
		}
		return pixel;
	};
	// 位置控制  输入字符
	void drawString(int px, int py, const char* inputString, int color)
	{
		for (int i = 0;inputString[i] != '\0'; i++)
		{
			// 对齐ASCII码
			int asciiPosition = inputString[i] - 0x20;
			int x = asciiPosition % 16;
			int y = asciiPosition / 16;
			cellImage(x * 8, y * 16, 8, 16, i * 8 + px, py, color, true);
			GameLib::cout << asciiPosition << GameLib::endl;
		}
	}
	int& getSize() {
		return *imageSize;
	}
private:
	int* imageSize;
	unsigned* mImagePixel;
	unsigned* varm;
	unsigned varmWidth;
};

namespace GameLib {
	char flag = 0;
	Image* gImage = nullptr;
	unsigned color = 0;
	int change = 0;
	void Framework::update() {
		GameLib::Framework::instance().setFrameRate(144);
		if (flag == 0) {
			gImage = new  Image("image/font.dds");
			//gImage->cellImage(0, 0, 128, 96, 0, 0, 0x0000ffff); // 全字体打印
			gImage->drawString(10, 10, "Miolro", 0x00ff00ff);
			flag = 1;
		}
		GameLib::cout << color << GameLib::endl;
	}
}

```

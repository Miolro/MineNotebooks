#pragma once
#include "File.h"
#include "Array2D.h"
#include "Object.h"
#include "Image.h"
class State
{
public:
	State();
	State(const char* iMap, const char* iImage);
	~State();

	void loadStateMap(const char* iMap);
	void loadStateImage(const char* iImage);
	void drawCell(int iVideoX, int iVideoY, int id);

	void drawEntity(int x, int y, unsigned currentTime);

	void drawBackground(int positionX, int positionY, Object obj);
	void drawForeground(int positionX, int positionY, Object obj);

	void move(int moveWayX, int moveWayY);

private:
	int mWidth = 0;
	int mHieght = 0;

	//int mImageHeight = 0;
	//int mImageWidth = 0;
	Image* mImage;
	//unsigned* mImageData = nullptr;
	int mMoveCount = 0;
	Array2D<Object> mArray2DObject;
	Array2D<bool> mGoalFlag;
};


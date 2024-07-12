#pragma once
#include "GameLib/GameLib.h"
#include "File.h"
#include "Array2D.h"
#include "Image.h"
class Object
{
public:
	Object();
	~Object();
	enum ObjectType
	{
		OBJ_WALL,
		OBJ_SPACE,
		OBJ_PLAYER,
		OBJ_BLOCK,

		OBJ_UNKNOW
	};
	enum ImageType
	{
		IMG_PLAYER,
		IMG_WALL,
		IMG_BLOCK,
		IMG_GOAL,
		IMG_SPACE
	};
	ObjectType mTpye;
	ObjectType mNextStatus;
	int mX = 0;
	int mY = 0;
	int mMoveCount = 0;
private:

};


class State
{
public:
	State();
	~State();
	State(const char* path);
	void draw();
	void move(char const input);
	bool gameOver();
private:
	int mMoveCount;
	int mWidth;
	int mHeight;
	Image* mImage;
	Array2D<Object> mArray2dObject;
	Array2D<bool> mIsGoal;
	void drawBackground(int x, int y, Object object);
	void drawForeground(int x, int y, Object object);
	void debugArray2d();
	void setNextStatus();
};


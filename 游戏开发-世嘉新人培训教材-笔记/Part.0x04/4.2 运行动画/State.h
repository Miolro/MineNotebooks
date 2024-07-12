#pragma once
#include"File.h"
#include "Array2D.h"
#include "Image.h"
class StateType
{
public:
	StateType();
	~StateType();
	enum Entity
	{
		ENT_SPACE,
		ENT_WALL,
		ENT_BLOCK,
		ENT_PLAYER,

		OBJ_UNKNOWN,
	};
	enum ImageId
	{
		IMAGE_ID_PLAYER,
		IMAGE_ID_WALL,
		IMAGE_ID_BLOCK,
		IMAGE_ID_GOAL,
		IMAGE_ID_SPACE,
	};
	
	void setType(Entity iType);
	Entity getType();
	int shiftingX;
	int shiftingY;

private:

	Entity mType;
};
class State
{
public:
	State();
	~State();
	State(const char* iStateFile, const char* iImageFile);
	void drawStateBackground();
	bool drawStateEntity();
	void drawCell(unsigned iImageIdX, unsigned iImageIdY, unsigned tDrawX, unsigned tDrawY);
	void moveCell(char iContolle);
	unsigned findPlayerPosition();
	bool checkGame();

	unsigned mStateMaxWidth;
	unsigned mStateMaxHeight;
	Array2D<StateType> mArray2DSatetType;
	Array2D<bool> mGoalFlag;
	Image* mImage;
};


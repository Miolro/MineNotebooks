#include "State.h"
#include"include/GameLib/Framework.h"

StateType::StateType() :shiftingX(0), shiftingY(0), mType(OBJ_UNKNOWN)
{
}

StateType::~StateType()
{
}

void StateType::setType(Entity iType)
{
	mType = iType;
}

StateType::Entity StateType::getType()
{
	return mType;
}


State::State(const char* iStateFile, const char* iImageFile)
{

	File tStateFileObject(iStateFile);
	// 解析地图
	char* tStateFileByte = tStateFileObject.getFileByte();
	unsigned tFilesize = tStateFileObject.getFileSize();
	/*******************************************************************************************/
	unsigned tMaxX = 0;
	unsigned tMaxY = 0;
	mStateMaxWidth = mStateMaxHeight = 0;

	for (unsigned tIndex = 0; tIndex < tFilesize; tIndex++, tStateFileByte++)
	{
		switch (*tStateFileByte)
		{
		case '#':
		case 'o':
		case 'O':
		case ' ':
		case '.':
		case 'p':
		case 'P':
			tMaxX++;
			break;
		case '\n':
			tMaxX = 0;tMaxY++;
			break;
		}
		mStateMaxWidth = tMaxX > mStateMaxWidth ? tMaxX : mStateMaxWidth;
		mStateMaxHeight = tMaxY > mStateMaxHeight ? tMaxY : mStateMaxHeight;
	}
	/*****************************************************************************************/

	unsigned tPositionY = 0;
	unsigned tPositionX = 0;
	mArray2DSatetType.setArray2DSize(mStateMaxWidth, mStateMaxHeight);
	mGoalFlag.setArray2DSize(mStateMaxWidth, mStateMaxHeight);
	tStateFileByte -= tFilesize;  // 重置地图位置
	for (unsigned i = 0; i < tFilesize; i++, tStateFileByte++)
	{
		StateType& stateType = mArray2DSatetType(tPositionX, tPositionY);
		bool& tGoalFlag = mGoalFlag(tPositionX, tPositionY);
		switch (*tStateFileByte)
		{
		case '#': stateType.setType(stateType.ENT_WALL);	tGoalFlag = false;tPositionX++;	break;
		case 'o': stateType.setType(stateType.ENT_BLOCK);	tGoalFlag = false;tPositionX++;	break;
		case 'O': stateType.setType(stateType.ENT_BLOCK);	tGoalFlag = true;tPositionX++;	break;
		case ' ': stateType.setType(stateType.ENT_SPACE);	tGoalFlag = false;tPositionX++;	break;
		case '.': stateType.setType(stateType.ENT_SPACE);	tGoalFlag = true;tPositionX++;	break;
		case 'p': stateType.setType(stateType.ENT_PLAYER);	tGoalFlag = false;tPositionX++;	break;
		case 'P': stateType.setType(stateType.ENT_PLAYER);	tGoalFlag = true;tPositionX++;	break;
		case '\n':tPositionX = 0;tPositionY++;break;
		}
	}
	/*****************************************************************************************/


	mImage = new Image(iImageFile);

	drawStateBackground();

}
void State::drawStateBackground()
{
	for (unsigned tIndex = 0; tIndex < mStateMaxHeight * mStateMaxWidth; tIndex++)
	{
		StateType& tState = mArray2DSatetType(tIndex);
		bool& tGoalFlag = mGoalFlag(tIndex);
		unsigned tImageId = tState.IMAGE_ID_SPACE;
		tImageId = tState.getType() == tState.ENT_WALL ? tState.IMAGE_ID_WALL : tImageId = !tGoalFlag ? tState.IMAGE_ID_SPACE : tState.IMAGE_ID_GOAL;
		unsigned X = tIndex % mStateMaxWidth;
		unsigned Y = tIndex / mStateMaxWidth;

		// 初始化偏移位置
		if (tState.shiftingX == 0)
		{
			tState.shiftingX = X * 32;
		}
		if (tState.shiftingY == 0)
		{
			tState.shiftingY = Y * 32;
		}
		drawCell(tImageId, 0, X * 32, Y * 32);
	}
}



bool State::drawStateEntity()
{
	bool endDraw = false;
	for (unsigned tIndex = 0; tIndex < mStateMaxHeight * mStateMaxWidth; tIndex++)
	{
		StateType& tState = mArray2DSatetType(tIndex);
		unsigned tImageId = tState.IMAGE_ID_SPACE;

		switch (tState.getType())
		{
		case tState.ENT_PLAYER:tImageId = tState.IMAGE_ID_PLAYER;break;
		case tState.ENT_BLOCK:tImageId = tState.IMAGE_ID_BLOCK;break;
		}
		if (tImageId != tState.IMAGE_ID_SPACE)
		{
			unsigned X = tIndex % mStateMaxWidth;  // 修改后的地址
			unsigned Y = tIndex / mStateMaxWidth;  // 修改后的地址


			if (tState.shiftingX != X * 32)
			{
				tState.shiftingX < X * 32 ? tState.shiftingX++ : tState.shiftingX--;
			}
			if (tState.shiftingY != Y * 32)
			{
				tState.shiftingY < Y * 32 ? tState.shiftingY++ : tState.shiftingY--;
			}
			drawCell(tImageId, 0, tState.shiftingX, tState.shiftingY);
		}
	}
	return endDraw;
}


void State::drawCell(const unsigned iImageIdX, const unsigned iImageIdY, unsigned iDrawX, unsigned iDrawY)
{
	unsigned tVideoWidth = GameLib::Framework::instance().width();
	unsigned* tVideoMemory = GameLib::Framework::instance().videoMemory();

	unsigned* tImageData = mImage->getImageData();

	unsigned tDwX = iDrawX;
	unsigned tDwY = iDrawY;

	unsigned iImageStartX = iImageIdX * 32;
	unsigned iImageEndX = iImageStartX + 32;

	unsigned iImageStartY = iImageIdY * 0;
	unsigned iImageEndY = iImageStartY + 32;

	for (unsigned i = iImageStartY; i < iImageEndY; i++)
	{
		for (unsigned j = iImageStartX; j < iImageEndX; j++)
		{
			unsigned& videoMemory = tVideoMemory[tDwY * tVideoWidth + tDwX];
			unsigned& imageData = tImageData[i * mImage->mImageWidth + j];

			unsigned tAlp = imageData >> 24;
			tAlp = tAlp < 0x80 ? 0 : 255;

			unsigned tVideoColorR = videoMemory & 0x00FF0000;
			unsigned tVideoColorG = videoMemory & 0x0000FF00;
			unsigned tVideoColorB = videoMemory & 0x000000FF;

			unsigned tImageColorR = imageData & 0x00FF0000;
			unsigned tImageColorG = imageData & 0x0000FF00;
			unsigned tImageColorB = imageData & 0x000000FF;

			unsigned tFinalColorR = (tImageColorR - tVideoColorR) * tAlp / 255 + tVideoColorR;
			unsigned tFinalColorG = (tImageColorG - tVideoColorG) * tAlp / 255 + tVideoColorG;
			unsigned tFinalColorB = (tImageColorB - tVideoColorB) * tAlp / 255 + tVideoColorB;

			unsigned tFinalColor = 0;
			tFinalColor |= tFinalColorR |= tFinalColorG |= tFinalColorB;
			videoMemory = tFinalColor;
			tDwX++;
		}
		tDwX = iDrawX;
		tDwY++;
	}
}
unsigned State::findPlayerPosition()
{
	unsigned tPosition = 0;

	for (; tPosition < mStateMaxWidth * mStateMaxHeight; tPosition++)
	{
		StateType& tStateType = mArray2DSatetType(tPosition);
		if (tStateType.getType() == tStateType.ENT_PLAYER)
		{
			break;
		}
	}
	return tPosition;
}

void State::moveCell(char iContolle)
{
	int tMoveX = 0;
	int tMoveY = 0;

	switch (iContolle)
	{
	case'w':	tMoveY -= 1;		break;
	case's':	tMoveY += 1;		break;
	case'a':	tMoveX -= 1;		break;
	case'd':	tMoveX += 1;		break;
	case'q':	GameLib::Framework::instance().requestEnd();		break;
	}

	unsigned tPlayerPosition = findPlayerPosition();
	unsigned tNextElement = tPlayerPosition + tMoveX + (tMoveY * mStateMaxWidth);
	unsigned tNextDoorElement = tPlayerPosition + (tMoveX * 2) + ((tMoveY * 2) * mStateMaxWidth);

	StateType& tPlayerObject = mArray2DSatetType(tPlayerPosition);
	StateType& tNextElementObject = mArray2DSatetType(tNextElement);
	StateType& tNextDoorElementObject = mArray2DSatetType(tNextDoorElement);

	if (tNextElementObject.getType() == tNextElementObject.ENT_SPACE) // 下一个元素不是墙那么就可以移动到那里
	{
		// 把旧地址赋值给偏移位置 此时shift保存的是旧实体的偏移位置
		tNextElementObject.shiftingX = tPlayerPosition % mStateMaxWidth * 32;
		tNextElementObject.shiftingY = tPlayerPosition / mStateMaxWidth * 32;

		tNextElementObject.setType(tPlayerObject.getType());
		tPlayerObject.setType(tPlayerObject.ENT_SPACE);
	}
	else
	{
		// 箱子推动 下一个元素是一个箱子且下一个元素是一个可移动的位置(SPACE(空位)\SPACE(标记位终点的空位))
		if (tNextElementObject.getType() == tNextElementObject.ENT_BLOCK && tNextDoorElementObject.getType() == tNextDoorElementObject.ENT_SPACE)
		{
			// 把旧地址赋值给偏移位置 此时shift保存的是旧实体的偏移位置
			tNextDoorElementObject.shiftingX = tNextElement % mStateMaxWidth * 32;
			tNextDoorElementObject.shiftingY = tNextElement / mStateMaxWidth * 32;
			// 把旧地址赋值给偏移位置
			tNextElementObject.shiftingX = tPlayerPosition % mStateMaxWidth * 32;
			tNextElementObject.shiftingY = tPlayerPosition / mStateMaxWidth * 32;

			tNextDoorElementObject.setType(tNextElementObject.getType());
			tNextElementObject.setType(tPlayerObject.getType());
			tPlayerObject.setType(tPlayerObject.ENT_SPACE);
		}
	}
}
bool State::checkGame()
{
	// 获取图层信息
	// 找到终点
	bool tEndGame = true;
	for (unsigned tPositionGoal = 0; tPositionGoal < mStateMaxWidth * mStateMaxHeight; tPositionGoal++)
	{
		if (mGoalFlag(tPositionGoal))
		{
			StateType& tStateType = mArray2DSatetType(tPositionGoal);
			if (tStateType.getType() == tStateType.ENT_SPACE)
			{
				tEndGame = false;
			}
		}

	}
	// 确认全部终点上方都是方块
	return tEndGame;
}

State::~State()
{
}


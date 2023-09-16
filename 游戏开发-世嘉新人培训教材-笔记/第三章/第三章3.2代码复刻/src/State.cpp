#include "State.h"

State::State()
{

}

State::~State()
{
}

State::State(const char* fileName)
{

	File file(fileName);
	// 读取场景数据
	char* mFileData = file.getData();
	unsigned mFileSize = file.getSize();
	// 创建显示图标
	image = new Image("./resources/nimotsuKunImage.dds");
	// 获取场景有效数据
	unsigned mSizeX = 0;
	unsigned mSizeY = 0;
	mStateSizeY = mStateSizeX = 0;
	char* tFileData = mFileData;

	for (unsigned tIndex = 0; tIndex < mFileSize; tIndex++, tFileData++)
	{
		switch (*tFileData)
		{
		case'#':case'o':case'O':
		case'.':case' ':
		case'p':case'P':
			mSizeX++;
			mStateSizeX = (mStateSizeX >= mSizeX) ? mStateSizeX : mSizeX;
			break;
		case '\n':
			mSizeY++;
			mSizeX = 0;
			mStateSizeY = (mStateSizeY >= mSizeY) ? mStateSizeY : mSizeY;
			break;
		}
	}
	// 为场景的有效数据赋予id 并保存到一个数组中

	unsigned tx = 0;
	unsigned ty = 0;
	mArray2D.setArraySize(mStateSizeX, mStateSizeY);
	mGoalFlag.setArraySize(mStateSizeX, mStateSizeY);
	tFileData = mFileData;
	for (unsigned tIndex = 0; tIndex < mFileSize; tIndex++, tFileData++)
	{
		Object tObject = OBJ_UNKNOWN;
		bool tGoal = false;
		switch (*tFileData)
		{
		case'#':tObject = OBJ_WALL; break;
		case'o':tObject = OBJ_BLOCK; break;
		case'.':tObject = OBJ_SPACE; tGoal = true; break;
		case' ':tObject = OBJ_SPACE; break;
		case'p':tObject = OBJ_MAN; break;
		case'P':tObject = OBJ_MAN; tGoal = true; break;
		case'O':tObject = OBJ_BLOCK; tGoal = true; break;
		case'\n':tx = 0; ty++; break;
		}
		if (tObject != OBJ_UNKNOWN)
		{
			mArray2D(tx, ty) = tObject;
			mGoalFlag(tx, ty) = tGoal;
			tx++;
		}
	}
	drawState(mStateSizeX, mStateSizeY);
}

void State::drawState(unsigned iStateSizeX, unsigned iStateSizeY)
{
	// 现在开始显示图像  双图层 终点图层  实体图层

	for (unsigned ty = 0; ty < iStateSizeY; ty++)
	{
		for (unsigned tx = 0; tx < iStateSizeX; tx++)
		{
			unsigned tImageMapperIdX = 1;
			unsigned tImageMapperIdY = 0;

			if (!mGoalFlag(tx, ty))
			{
				switch (mArray2D(tx, ty))
				{
				case OBJ_SPACE: tImageMapperIdX = IMAGE_ID_SPACE; break;
				case OBJ_WALL: tImageMapperIdX = IMAGE_ID_WALL; break;
				case OBJ_BLOCK: tImageMapperIdX = IMAGE_ID_BLOCK; break;
				case OBJ_MAN: tImageMapperIdX = IMAGE_ID_PLAYER; break;

				}
			}
			else
			{
				switch (mArray2D(tx, ty))
				{
				case OBJ_SPACE: tImageMapperIdX = IMAGE_ID_GOAL; break;
				case OBJ_WALL: tImageMapperIdX = IMAGE_ID_WALL; break;
				case OBJ_BLOCK: tImageMapperIdX = IMAGE_ID_BLOCK_ON_GOAL; break;
				case OBJ_MAN: tImageMapperIdX = IMAGE_ID_PLAYER; break;
				}
			}

			image->imageCellDraw(
				tImageMapperIdX * 32, 0,
				(tImageMapperIdX + 1) * 32, 32,
				tx, ty);
		}
	}
}

unsigned State::findPlayerPosition()
{
	unsigned tPosition = 0;

	for (; tPosition < mStateSizeX * mStateSizeY; tPosition++)
	{
		if (mArray2D(tPosition, 0) == OBJ_MAN)
		{
			break;
		}
	}
	return tPosition;
}

void State::moveCell(char iContolle)
{
	// 通过修改地图mArray2D和mGoalFlag达到目的
	unsigned tPlaerPosition = findPlayerPosition();

	unsigned tMoveX = 0;
	unsigned tMoveY = 0;

	switch (iContolle)
	{
	case'w':	tMoveY -= 1;		break;
	case's':	tMoveY += 1;		break;
	case'a':	tMoveX -= 1;		break;
	case'd':	tMoveX += 1;		break;
	case'q':	Framework::instance().requestEnd();		break;
	}

	// 下一个元素position
	unsigned tNextElement = tPlaerPosition + tMoveX + (tMoveY * mStateSizeX);
	// 下下个元素
	unsigned tNextDoorElement = tPlaerPosition + (tMoveX * 2) + ((tMoveY * 2) * mStateSizeX);

	if (mArray2D(tNextElement, 0) != OBJ_WALL && mArray2D(tNextElement, 0) != OBJ_BLOCK) // 下一个元素不是墙那么就可以移动到那里
	{
		mArray2D(tNextElement, 0) = mArray2D(tPlaerPosition, 0);
		// 抹除旧玩家位置
		mArray2D(tPlaerPosition, 0) = OBJ_SPACE;
	}
	else
	{
		// 箱子推动 下一个元素是一个箱子且下一个元素是一个可移动的位置(SPACE(空位)\SPACE(标记位终点的空位))
		if (mArray2D(tNextElement, 0) == OBJ_BLOCK && mArray2D(tNextDoorElement, 0) == OBJ_SPACE)
		{
			mArray2D(tNextDoorElement, 0) = mArray2D(tNextElement, 0);
			mArray2D(tNextElement, 0) = mArray2D(tPlaerPosition, 0);
			mArray2D(tPlaerPosition, 0) = OBJ_SPACE;
		}
	}

	drawState(mStateSizeX, mStateSizeY);
}

bool State::checkGame()
{
	// 获取图层信息
	// 找到终点
	bool tEndGame = true;
	for (unsigned tPositionGoal = 0; tPositionGoal < mStateSizeX * mStateSizeY; tPositionGoal++)
	{
		if (mGoalFlag(tPositionGoal, 0))
		{
			if (mArray2D(tPositionGoal, 0) == OBJ_SPACE)
			{
				tEndGame = false;
			}
		}

	}

	// 确认全部终点上方都是方块
	return tEndGame;
}
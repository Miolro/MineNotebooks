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
	// ��ȡ��������
	char* mFileData = file.getData();
	unsigned mFileSize = file.getSize();
	// ������ʾͼ��
	image = new Image("./resources/nimotsuKunImage.dds");
	// ��ȡ������Ч����
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
	// Ϊ��������Ч���ݸ���id �����浽һ��������

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
	// ���ڿ�ʼ��ʾͼ��  ˫ͼ�� �յ�ͼ��  ʵ��ͼ��

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
	// ͨ���޸ĵ�ͼmArray2D��mGoalFlag�ﵽĿ��
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

	// ��һ��Ԫ��position
	unsigned tNextElement = tPlaerPosition + tMoveX + (tMoveY * mStateSizeX);
	// ���¸�Ԫ��
	unsigned tNextDoorElement = tPlaerPosition + (tMoveX * 2) + ((tMoveY * 2) * mStateSizeX);

	if (mArray2D(tNextElement, 0) != OBJ_WALL && mArray2D(tNextElement, 0) != OBJ_BLOCK) // ��һ��Ԫ�ز���ǽ��ô�Ϳ����ƶ�������
	{
		mArray2D(tNextElement, 0) = mArray2D(tPlaerPosition, 0);
		// Ĩ�������λ��
		mArray2D(tPlaerPosition, 0) = OBJ_SPACE;
	}
	else
	{
		// �����ƶ� ��һ��Ԫ����һ����������һ��Ԫ����һ�����ƶ���λ��(SPACE(��λ)\SPACE(���λ�յ�Ŀ�λ))
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
	// ��ȡͼ����Ϣ
	// �ҵ��յ�
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

	// ȷ��ȫ���յ��Ϸ����Ƿ���
	return tEndGame;
}
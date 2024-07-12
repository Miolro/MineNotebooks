#include "State.h"


State::State(const char* iMap, const char* iImage)
{

	loadStateMap(iMap);
	loadStateImage(iImage);

}

State::~State()
{
	delete mImage;
	mImage = nullptr;
}

void State::loadStateMap(const char* iMap)
{
	File mapObj(iMap);
	unsigned fileSize = mapObj.getFileSize();
	char* fileByte = mapObj.getFileByte();
	char* fileByteCopy = fileByte;
	unsigned width = 0;
	unsigned height = 0;

	for (unsigned i = 0; i < fileSize; i++)
	{
		switch (*fileByteCopy)
		{
		case ' ':case'#':case'.':case 'o': case'p':
			width++;
			break;
		case '\n':
			width = 0;
			height++;
			break;
		}
		mWidth = mWidth < width ? width : mWidth;
		mHieght = mHieght < height ? height : mHieght;
		fileByteCopy++;
	}

	fileByteCopy = fileByte;
	mArray2DObject.setArray2DSize(mWidth, mHieght);
	mGoalFlag.setArray2DSize(mWidth, mHieght);
	for (unsigned i = 0, j = 0; i < fileSize; i++)
	{
		Object::mType type = Object::mType::OBJ_UNKNOW;
		mGoalFlag(j) = false;
		switch (*fileByteCopy)
		{
		case' ':	type = Object::mType::OBJ_SPACE;	break;
		case'#':	type = Object::mType::OBJ_WALL;		break;
		case'.':	type = Object::mType::OBJ_SPACE;mGoalFlag(j) = true;break;
		case'o':	type = Object::mType::OBJ_BLOCK;	break;
		case'p':	type = Object::mType::OBJ_PLAYER;	break;
		case '\n':  break;
		}
		if (type != Object::mType::OBJ_UNKNOW)
		{
			mArray2DObject(j).mObjType = type;
			mArray2DObject(j).changeType = type;
			j++;
		}
		fileByteCopy++;
	}
}

void State::loadStateImage(const char* iImage)
{
	mImage = new Image(iImage);
}

void State::drawCell(int iVideoX, int iVideoY, int id)
{
	mImage->drawImage(iVideoX, iVideoY, id * 32, id * 0, 32, 32);
}

void State::drawEntity(int x, int y, unsigned currentTime)
{
	if (x != 0 || y != 0)
	{
		move(x, y);
	}

	for (int i = 0; i < mHieght; i++)
	{
		for (int j = 0; j < mWidth; j++)
		{
			drawBackground(j, i, mArray2DObject(j, i));
		}
	}
	for (int i = 0; i < mHieght; i++)
	{
		for (int j = 0; j < mWidth; j++)
		{
			drawForeground(j, i, mArray2DObject(j, i));
		}
	}
	if (mMoveCount > 0)
	{
		mMoveCount++;
	}


	if (mMoveCount > 32)
	//if (mMoveCount > 500)
	{
		mMoveCount = 0;
		for (int i = 0; i < mHieght; i++)
		{
			for (int j = 0; j < mWidth; j++)
			{
				if (mArray2DObject(j, i).changeType != mArray2DObject(j, i).mObjType)
				{
					mArray2DObject(j, i).mObjType = mArray2DObject(j, i).changeType;
				}
			}
		}
	}
}

void State::drawBackground(int positionX, int positionY, Object obj)
{

	unsigned imageId = obj.OBJ_SPACE;
	if (obj.mObjType == obj.OBJ_WALL)
	{
		imageId = obj.OBJ_WALL;
	}
	else
	{
		imageId = mGoalFlag(positionX, positionY) ? obj.IMG_GOAL : obj.IMG_SPACE;
	}
	mImage->drawImage(positionX * 32, positionY * 32, 32 * imageId, 0 * imageId, 32, 32);
}

void State::drawForeground(int positionX, int positionY, Object obj)
{
	if (obj.mObjType == obj.OBJ_WALL)
	{
		return;
	}
	unsigned imageId = obj.IMG_SPACE;
	if (obj.mObjType == obj.OBJ_PLAYER)
	{
		imageId = obj.IMG_PLAYER;
	}
	if (obj.mObjType == obj.OBJ_BLOCK)
	{
		imageId = obj.IMG_BLOCK;
	}

	if (imageId != obj.IMG_SPACE)
	{
		mImage->drawImage((positionX * 32 + (obj.mMoveX * mMoveCount)), (positionY * 32 + (obj.mMoveY * mMoveCount)), 32 * imageId, 0 * imageId, 32, 32);
	}
}

// ����ÿ�����������ƫ��ֵ  �����λ�û��Ϊʲô��ֵ
void State::move(int moveWayX, int moveWayY)
{

	// ���λ��
	if (mMoveCount > 0) {
		return;
	}
	int px = 0;
	int py = 0;
	bool findTarget = false;



	for (py = 0; py < mHieght; py++)
	{
		for (px = 0; px < mWidth; px++)
		{
			Object obj = mArray2DObject(px, py);
			mArray2DObject(px, py).changeType = mArray2DObject(px, py).mObjType;
			if (obj.OBJ_PLAYER == obj.mObjType)
			{
				findTarget = true;
				break;
			}
		}
		if (findTarget)
		{
			break;
		}
	}
	// �ж��Ƿ����ƶ��Ǹ�λ��
	int pxn = px + moveWayX;
	int pyn = py + moveWayY;



	if (mArray2DObject(pxn, pyn).mObjType == Object::OBJ_SPACE)
	{
		mMoveCount = 1;
		mArray2DObject(px, py).mMoveX = moveWayX;
		mArray2DObject(px, py).mMoveY = moveWayY;
		mArray2DObject(px, py).changeType = Object::OBJ_SPACE;
		mArray2DObject(pxn, pyn).changeType = Object::OBJ_PLAYER;
	}

	if (mArray2DObject(pxn, pyn).mObjType == Object::OBJ_BLOCK)
	{
		int pxnn = pxn + moveWayX;
		int pynn = pyn + moveWayY;
		if (mArray2DObject(pxnn, pynn).mObjType == Object::OBJ_SPACE)
		{
			mMoveCount = 1;
			mArray2DObject(px, py).mMoveX = moveWayX;
			mArray2DObject(px, py).mMoveY = moveWayY;
			mArray2DObject(pxn, pyn).mMoveX = moveWayX;
			mArray2DObject(pxn, pyn).mMoveY = moveWayY;
			mArray2DObject(px, py).changeType = Object::OBJ_SPACE;
			mArray2DObject(pxn, pyn).changeType = Object::OBJ_PLAYER;
			mArray2DObject(pxnn, pynn).changeType = Object::OBJ_BLOCK;
		}
	}

	int pxnn = pxn + moveWayX;
	int pynn = pyn + moveWayY;

}
#include "State.h"
#include "StatusFrameGame.h"
Object::Object()
{

}
Object::~Object()
{

}
State::~State()
{
	SAFE_DELETE(mImage);
}

State::State(const char* path) :mMoveCount(0)
{
	File file = File(path);
	char* stateData = file.getByte();
	int fileSize = file.getSize();
	// 分析场景宽高
	int w, h;
	w = h = mWidth = mHeight = 0;
	for (int i = 0; i < fileSize; i++)
	{
		char buffer = stateData[i];
		switch (buffer)
		{
		case '#':case ' ':case '.':case 'p':case 'o':case 'P':case 'O':
			w++;
			mWidth = (mWidth > w) ? mWidth : w;
			break;
		case '\n':
			h++;
			w = 0;
			mHeight = (mHeight > h) ? mHeight : h;
			break;
		}
	}
	GameLib::cout << "场景大小:" << mWidth << mHeight << GameLib::endl;
	mArray2dObject.setArray2DSize(mWidth, mHeight);
	mIsGoal.setArray2DSize(mWidth, mHeight);
	// 读取场景元素
	w = h = 0;
	for (int i = 0; i < fileSize; i++)
	{
		char buffer = stateData[i];
		Object::ObjectType objectType = Object::OBJ_UNKNOW;
		bool isGoal = false;
		switch (buffer)
		{
		case '#':objectType = Object::OBJ_WALL;break;
		case ' ':objectType = Object::OBJ_SPACE;break;
		case '.':objectType = Object::OBJ_SPACE;isGoal = true;break;
		case 'p':objectType = Object::OBJ_PLAYER;break;
		case 'o':objectType = Object::OBJ_BLOCK;break;
		case 'P':objectType = Object::OBJ_PLAYER;isGoal = true;break;
		case 'O':objectType = Object::OBJ_BLOCK;isGoal = true;break;
		case '\n':
			h++;
			w = 0;
			break;
		}
		if (objectType != Object::OBJ_UNKNOW)
		{
			mArray2dObject(w, h).mTpye = objectType;
			mArray2dObject(w, h).mNextStatus = objectType;
			mIsGoal(w, h) = isGoal;
			w++;
		}
	}
	GameLib::cout << "元素加载完成" << GameLib::endl;

	mImage = new Image("nimotsuKunImage2.dds");
}

void State::draw(Sequence::StatusFrameGame * frame)
{
	for (int j = 0; j < mHeight; j++)
	{
		for (int i = 0; i < mWidth; i++)
		{
			drawBackground(i, j, mArray2dObject(i, j));
		}
	}
	for (int j = 0; j < mHeight; j++)
	{
		for (int i = 0; i < mWidth; i++)
		{
			drawForeground(i, j, mArray2dObject(i, j));
		}
	}
	if (mMoveCount > 0)
	{
		mMoveCount++;
	}

	if (mMoveCount > 32)
	{
		setNextStatus();
		mMoveCount = 0;
		debugArray2d();
		if (gameOver())
		{
			frame->setNextStatus(Sequence::StatusFrameGame::Status::STA_CLEAR);
		}
	}
}
void State::drawBackground(int x, int y, Object object)
{

	Object::ImageType imgType = object.mTpye == Object::OBJ_WALL ? Object::IMG_WALL : mIsGoal(x, y) ? Object::IMG_GOAL : Object::IMG_SPACE;
	mImage->draw(x * 32, y * 32, 32 * imgType, 32 * 0, 32, 32);

}
void State::drawForeground(int x, int y, Object object)
{
	int shifingX = object.mX * mMoveCount;
	int shifingY = object.mY * mMoveCount;
	Object::ImageType  imageId = Object::IMG_SPACE;
	switch (object.mTpye)
	{
	case Object::OBJ_PLAYER: imageId = Object::IMG_PLAYER;break;
	case Object::OBJ_BLOCK: imageId = Object::IMG_BLOCK;break;
	}
	if (imageId == Object::IMG_SPACE)
	{
		return;
	}
	mImage->draw(x * 32 + shifingX, y * 32 + shifingY, 32 * imageId, 32 * 0, 32, 32);
}
void State::setNextStatus() {
	for (int j = 0; j < mHeight; j++)
	{
		for (int k = 0; k < mWidth; k++)
		{
			mArray2dObject(k, j).mTpye = mArray2dObject(k, j).mNextStatus;
		}
	}
}

void State::move(char const input)
{
	if (mMoveCount != 0)
	{
		return;
	}
	int moveX = 0;
	int moveY = 0;
	switch (input)
	{
	case'w':moveY = -1; break;
	case's':moveY = 1; break;
	case'a':moveX = -1; break;
	case'd':moveX = 1; break;
	}
	int pp = 0;  // 玩家位置
	bool findFlag = false;

	int px = 0;
	int py = 0;

	for (int i = 0; i < mHeight; i++)
	{
		for (int j = 0; j < mWidth; j++)
		{
			if (mArray2dObject(j, i).mTpye == Object::OBJ_PLAYER)
			{
				px = j;
				py = i;
				findFlag = true;
				break;
			}
		}
		if (findFlag)
		{
			break;
		}
	}

	int npy = moveY + py;
	int npx = moveX + px;

	if (mArray2dObject(npx, npy).mTpye == Object::OBJ_SPACE)
	{
		mArray2dObject(px, py).mX = moveX;
		mArray2dObject(px, py).mY = moveY;
		mArray2dObject(px, py).mNextStatus = Object::OBJ_SPACE;
		mArray2dObject(npx, npy).mNextStatus = Object::OBJ_PLAYER;
		mMoveCount = 1;
		return;
	}
	if (mArray2dObject(npx, npy).mTpye == Object::OBJ_BLOCK)
	{
		int nnpy = moveY + npy;
		int nnpx = moveX + npx;
		if (mArray2dObject(nnpx, nnpy).mTpye == Object::OBJ_SPACE)
		{
			mArray2dObject(px, py).mX = moveX;
			mArray2dObject(px, py).mY = moveY;

			mArray2dObject(npx, npy).mX = moveX;
			mArray2dObject(npx, npy).mY = moveY;

			mArray2dObject(px, py).mNextStatus = Object::OBJ_SPACE;
			mArray2dObject(npx, npy).mNextStatus = Object::OBJ_PLAYER;
			mArray2dObject(nnpx, nnpy).mNextStatus = Object::OBJ_BLOCK;
			mMoveCount = 1;
			return;
		}

	}

}
bool State::gameOver()
{
	bool ret = false;
	for (int j = 0; j < mHeight; j++)
	{
		for (int i = 0; i < mWidth; i++)
		{
			if (mIsGoal(i, j))
			{
				ret = mArray2dObject(i, j).mTpye == Object::OBJ_SPACE ? false : true;
			}
		}
	}
	return ret;
}
void State::debugArray2d()
{
	for (int i = 0; i < mHeight; i++)
	{
		for (int j = 0; j < mWidth; j++)
		{
			GameLib::cout << mArray2dObject(j, i).mTpye;
		}
		GameLib::cout << "\n";
	}
}

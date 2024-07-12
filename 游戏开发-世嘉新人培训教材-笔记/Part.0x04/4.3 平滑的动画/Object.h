#pragma once
class Object
{
public:
	Object();
	~Object();

	enum mType
	{
		OBJ_SPACE,
		OBJ_WALL,
		OBJ_PLAYER,
		OBJ_BLOCK,
		OBJ_UNKNOW,
	};

	enum mImageId
	{
		IMG_PLAYER,
		IMG_WALL,
		IMG_BLOCK,
		IMG_GOAL,
		IMG_SPACE,
	};

	mType mObjType;
	int mMoveX = 0;
	int mMoveY = 0;
	mType changeType;
private:

};

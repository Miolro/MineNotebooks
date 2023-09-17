#ifndef INCLUDE_STATE_HEADER
#define INCLUDE_STATE_HEADER

#include "File.h"
#include "Array2D.h"
#include "GameLib/Framework.h"
#include "Image.h"

using namespace GameLib;

class State
{
public:
	State();
	~State();
	State(const char* fileName);
	void drawState(unsigned iPosX, unsigned iPosY);
	void moveCell(char iContolle);
	unsigned findPlayerPosition();
	bool checkGame();
private:
	// 地图实体
	enum Object {
		OBJ_SPACE,
		OBJ_WALL,
		OBJ_BLOCK,
		OBJ_MAN,

		OBJ_UNKNOWN,
	};

	//网格绘制函数
	enum ImageID {
		IMAGE_ID_PLAYER,
		IMAGE_ID_WALL,
		IMAGE_ID_BLOCK,
		//IMAGE_ID_BLOCK_ON_GOAL,
		IMAGE_ID_GOAL,
		IMAGE_ID_SPACE,
	};

	// 基本的场景横向和纵向的大小
	unsigned mStateSizeX;
	unsigned mStateSizeY;
	// 用于保存数据的2D模板
	Array2D<Object> mArray2D;
	// 分散图层
	Array2D<bool> mGoalFlag;
	Image* image;

};


#endif INCLUDE_STATE_HEADER


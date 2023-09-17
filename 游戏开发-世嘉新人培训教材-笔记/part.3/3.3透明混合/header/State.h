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
	// ��ͼʵ��
	enum Object {
		OBJ_SPACE,
		OBJ_WALL,
		OBJ_BLOCK,
		OBJ_MAN,

		OBJ_UNKNOWN,
	};

	//������ƺ���
	enum ImageID {
		IMAGE_ID_PLAYER,
		IMAGE_ID_WALL,
		IMAGE_ID_BLOCK,
		//IMAGE_ID_BLOCK_ON_GOAL,
		IMAGE_ID_GOAL,
		IMAGE_ID_SPACE,
	};

	// �����ĳ������������Ĵ�С
	unsigned mStateSizeX;
	unsigned mStateSizeY;
	// ���ڱ������ݵ�2Dģ��
	Array2D<Object> mArray2D;
	// ��ɢͼ��
	Array2D<bool> mGoalFlag;
	Image* image;

};


#endif INCLUDE_STATE_HEADER


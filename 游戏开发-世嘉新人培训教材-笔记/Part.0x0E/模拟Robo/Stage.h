#pragma once
#include "GameLib/Framework.h"
class Matrix44;
class Stage
{
public:
	Stage();
	~Stage();
	void draw(const Matrix44 pvm);
private:
	GameLib::Texture* mTexture;
};


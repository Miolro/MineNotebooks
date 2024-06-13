#pragma once
#include "GameLib/Framework.h"
#include "Vector3.h"
class Matrix44;

class Robo
{
public:
	Robo(int id);
	~Robo();
	void draw(Matrix44& pvm)const;
	void update();

	const Vector3* position()const;
	double angleY()const;
	void getDirection(Vector3* v);

	void setPosition(const Vector3& position);
	void setAngleY(double a);
private:
	Vector3 mPosition;
	double mAngleY;
	int mid;
	GameLib::Texture* mTexture;
};


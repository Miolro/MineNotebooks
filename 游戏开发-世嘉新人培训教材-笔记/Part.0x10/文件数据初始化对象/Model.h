#pragma once
#include "Vector3.h"
class Batch;
class Matrix44;
class Model
{
public:
	Model(const Batch* batch);
	void draw(const Matrix44& worldMatrix);
private:
	Vector3 mPosition;// 位置
	Vector3 mAngle; // xyz旋转角
	Vector3 mScale; // 放大比例
	const Batch* mBatch; // 角点信息
};


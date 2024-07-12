#include "Model.h"

#include "Batch.h"
#include "Matrix44.h"
#include "Matrix34.h"
#include "GameLib/Framework.h"
Model::Model(const Batch* batch) :mPosition(0.0, 0.0, 0.0), mAngle(0.0, 0.0, 0.0), mScale(1.0, 1.0, 1.0), mBatch(batch)
{

}

void Model::draw(const Matrix44& worldMatrix)
{
	Matrix34 wm;
	wm.setTranslation(mPosition);
	Matrix44 transform;
	transform.setMul(worldMatrix,wm);
	mBatch->draw(transform);
}



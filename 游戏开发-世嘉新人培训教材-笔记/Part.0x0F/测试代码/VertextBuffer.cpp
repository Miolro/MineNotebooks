#include "VertextBuffer.h"
#include "Vector2.h"
#include "Vector3.h"
VertextBuffer::VertextBuffer(int iSize)
{
	mSize = iSize;
	mPointPosition = new Vector3[iSize];
	mUVPosition = new Vector2[iSize];
}

VertextBuffer::~VertextBuffer()
{

}

void VertextBuffer::setPosition(int index, Vector3 xyzPoint)const
{
	mPointPosition[index] = xyzPoint;
}

void VertextBuffer::setUVPosition(int index, Vector2 xyzPoint)const
{
	mUVPosition[index] = xyzPoint;
}

Vector3 VertextBuffer::getPosition(int index)const
{
	return mPointPosition[index];
}

Vector2 VertextBuffer::getUVPosition(int index)const
{
	return mUVPosition[index];
}

int VertextBuffer::size()const
{
	return mSize;
}

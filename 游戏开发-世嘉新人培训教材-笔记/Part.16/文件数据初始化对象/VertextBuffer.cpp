#include "VertextBuffer.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Element.h"
#include "Attribute.h"
VertextBuffer::VertextBuffer(int iSize)
{
	mSize = iSize;
	mPointPosition = new Vector3[iSize];
	mUVPosition = new Vector2[iSize];
}

VertextBuffer::VertextBuffer(const Element* child)
{
	mSize = child->size();
	mPointPosition = new Vector3[mSize];
	mUVPosition = new Vector2[mSize];

	if (!mSize)
	{
		return;
	}
	for (int i = 0; i < mSize; i++) // 遍历节点
	{
		const Element* vertextBufferNode = child->child(i); // child内部的子节点
		for (int j = 0; j < vertextBufferNode->attributeSize(); j++)  // 遍历单个节点里的属性
		{
			const Attribute* attribute = vertextBufferNode->attribute(j);
			const string* name = attribute->name();
			if (*name == "position")
			{
				attribute->getDoubleValues(&mPointPosition[i].x, 3); // 获取内存首地址直接写入
			}
			else if (*name == "uv")
			{
				attribute->getDoubleValues(&mUVPosition[i].x, 2);
			}
		}
	}
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

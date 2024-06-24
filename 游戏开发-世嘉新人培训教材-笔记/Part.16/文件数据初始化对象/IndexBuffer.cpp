#include "IndexBuffer.h"
#include "Element.h"
#include "Attribute.h"
IndexBuffer::IndexBuffer(int iSize)
{
	mSize = iSize;
	mIndexValue = new unsigned[iSize];
}

void IndexBuffer::setIndex(int index, unsigned indexValue)const
{
	mIndexValue[index] = indexValue;
}

unsigned IndexBuffer::getIndexValue(int index)const
{
	return mIndexValue[index];
}

int IndexBuffer::size()const
{
	return mSize;
}
IndexBuffer::IndexBuffer(const Element* child)
{
	mSize = child->size();
	mIndexValue = new unsigned[mSize];

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
			if (*name == "indices")
			{
				attribute->getIntagerValues(&mIndexValue[3 * i], 3); // 获取内存首地址直接写入
			}
		}
	}
}
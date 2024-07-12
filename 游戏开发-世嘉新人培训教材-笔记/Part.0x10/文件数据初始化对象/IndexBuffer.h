#pragma once
class Vector3;
class Element;
class IndexBuffer
{
public:
	IndexBuffer(int mSize);
	IndexBuffer(const Element* child);
	~IndexBuffer();
	// 索引和三角形顶点坐标
	void setIndex(int index, unsigned indexValue)const;
	unsigned getIndexValue(int index)const;
	int size()const;
private:
	unsigned* mIndexValue;
	int mSize;
};


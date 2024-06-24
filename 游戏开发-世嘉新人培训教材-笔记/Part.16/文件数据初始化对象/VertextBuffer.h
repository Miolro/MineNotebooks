#pragma once
class Vector3;
class Vector2;
class Element;
class VertextBuffer
{
public:
	VertextBuffer(int mSize);
	VertextBuffer(const Element* child);
	~VertextBuffer();
	void setPosition(int index, Vector3 xyzPoint) const;
	void setUVPosition(int index, Vector2 xyzPoint) const;
	Vector3 getPosition(int index)const;
	Vector2 getUVPosition(int index)const;
	int size()const;
	// 索引和三角形顶点坐标
private:
	int mSize; // 顶点个数
	Vector3* mPointPosition; // 顶点坐标位置
	Vector2* mUVPosition;	// 纹理坐标
};


#pragma once
class Vector2
{
public:
	Vector2(); // 空向量
	Vector2(int x, int y); // 带有值的初始化向量 int
	Vector2(double x, double y);
	~Vector2();

	void operator*= (double in);
	void operator+=(const Vector2&); // 向量加法
	void operator-=(const Vector2&);	// 向量减法
	void operator=(const Vector2&);	// 向量复制

	void setSub(const Vector2& p0, const Vector2& p1);

	void addVector(Vector2 v0, Vector2 v1);
	void setInterpolation(Vector2& a, const Vector2& ab, double absize, const Vector2& ac, double acsize);// 向量补间
	//向量 
	double x;
	double y;
};

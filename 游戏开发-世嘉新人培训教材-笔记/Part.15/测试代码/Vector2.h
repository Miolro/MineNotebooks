#pragma once
class Vector2
{
public:
	Vector2() {};
	Vector2(double x, double y);
	void set(double x, double y);
	void setSub(Vector2 v1, Vector2 v2);
	void setMul(Vector2 v1, double);

	void operator-=(Vector2 v);
	void operator+=(Vector2 v);

	double x;
	double y;
};


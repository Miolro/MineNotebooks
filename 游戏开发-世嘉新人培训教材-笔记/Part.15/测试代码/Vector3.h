#pragma once
class Vector3
{
public:
	Vector3() {};
	Vector3(double x, double y, double z);
	void set(double x, double y, double z);
	void setSub(Vector3 v1, Vector3 v2);
	void setMul(Vector3 v1, double);

	void operator-=(Vector3 v);
	void operator+=(Vector3 v);

	double x;
	double y;
	double z;
};


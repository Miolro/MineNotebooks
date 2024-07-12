#pragma once
class Matrix34;
class Vector3;
class Matrix44
{
public:
	void setPerspectiveTransform(double fov, double windowWidth, double windowHeight, double nearClip, double farClip);
	void operator*=(const Matrix34);
	void multiply(double* out, Vector3 in);
private:
	double m00, m01, m02, m03;
	double m10, m11, m12, m13;
	double m20, m21, m22, m23;
	double m30, m31, m32, m33;
};


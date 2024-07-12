#pragma once
class Vector3;
class Matrix34
{
public:
	void setView(Vector3 view, Vector3 target);
	void setRotateX(double r); // ��X����ת
	void setRotateZ(double r); // ��X����ת
	void setRotateY(double r);
	void rotateY(double r);// ��Y����ת
	void setTranslation(Vector3 v);//
	void operator*=(const Matrix34);
	void translate(const Vector3& a);
	void multiply(double& vout, Vector3 v);
	void multiply(Vector3* vout, Vector3 v);
	double m00, m01, m02, m03;
	double m10, m11, m12, m13;
	double m20, m21, m22, m23;
private:

};


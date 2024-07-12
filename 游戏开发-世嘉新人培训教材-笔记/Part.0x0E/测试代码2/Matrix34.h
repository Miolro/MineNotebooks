#pragma once
class Vector3;
class Matrix34
{
public:
	void setView(Vector3 view, Vector3 target);
	void setRotateX(double r); // ÈÆXÖáĞı×ª
	void setRotateZ(double r); // ÈÆXÖáĞı×ª
	void rotateY(double r);// ÈÆYÖáĞı×ª
	void operator*=(const Matrix34);
	void translate(const Vector3& a);
	void change(double& vout, Vector3 v);
	double m00, m01, m02, m03;
	double m10, m11, m12, m13;
	double m20, m21, m22, m23;
private:

};


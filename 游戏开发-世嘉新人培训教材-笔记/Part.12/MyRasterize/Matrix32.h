class Vector2;
#pragma once
// 3*2 æÿ’Û
class Matrix32
{
public:
	Matrix32();
	Matrix32(double m00, double m01, double m02, double m10, double m11, double m12);
	~Matrix32();
	void multiply(Vector2* out, const Vector2& in)const;

	void transfromMove(Vector2* out, const Vector2& in);
	void transfromMove(Vector2* out, const Vector2& in, double x, double y);
	void transfromRoll(Vector2* out, const Vector2& in, Vector2 offset);
	void transfromScal(Vector2* out, const Vector2& in, const Vector2 offset);

	double m00, m01, m02;
	double m10, m11, m12;
};
#pragma once
class Vector2
{
public:
	Vector2(); // ������
	Vector2(int x, int y); // ����ֵ�ĳ�ʼ������ int
	Vector2(double x, double y);
	~Vector2();

	void operator*= (double in);
	void operator+=(const Vector2&); // �����ӷ�
	void operator-=(const Vector2&);	// ��������
	void operator=(const Vector2&);	// ��������

	void setSub(const Vector2& p0, const Vector2& p1);

	void addVector(Vector2 v0, Vector2 v1);
	void setInterpolation(Vector2& a, const Vector2& ab, double absize, const Vector2& ac, double acsize);// ��������
	//���� 
	double x;
	double y;
};

#pragma once
#include "Vector3.h"
// 三行四列矩阵
namespace layour {
	class Matrix34
	{
	public:
		Matrix34();
		void setTranslation(const Vector3& v);
		void setScaling(const Vector3& v);
		void multiply(Vector3* out, const Vector3& in);
		//Matrix34(
		//	double arg00, double arg01, double arg02, double arg03,
		//	double arg10, double arg11, double arg12, double arg13,
		//	double arg20, double arg21, double arg22, double arg23);
		//void Matrix34Move(Vector3& vector3, double offsetX, double offsetY, double offsetZ);
	private:
		double arg00, arg01, arg02, arg03;
		double arg10, arg11, arg12, arg13;
		double arg20, arg21, arg22, arg23;
	};

}

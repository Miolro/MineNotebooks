#include "Matrix34.h"
namespace layour {
	Matrix34::Matrix34()
	{

	}

	/*
	|1 0 0 x|
	|0 1 0 y|
	|0 0 1 z|
	*/
	// 设置移动参数（距离）
	void Matrix34::setTranslation(const Vector3& v)
	{
		arg00 = arg11 = arg22 = 1.0f;
		arg01 = arg02 = arg10 = arg12 = arg20 = arg21 = 0.0f;
		arg03 = v.x; arg13 = v.y; arg23 = v.z;
	}
	/*
	|x 0 0 0|
	|0 y 0 0|
	|0 0 z 0|
	*/

	void Matrix34::setScaling(const Vector3& v)
	{
		arg01 = arg02 = arg03 = arg10 = arg12 = arg13 = arg20 = arg21 = arg23 = 0;
		arg00 = v.x;
		arg11 = v.y;
		arg22 = v.z;
	}

	void Matrix34::multiply(Vector3* out, const Vector3& in)
	{  // 最后的1原本应该是来自向量
		out->x = arg00 * in.x + arg01 * in.y + arg02 * in.z + arg03 * 1;
		out->y = arg10 * in.x + arg11 * in.y + arg12 * in.z + arg13 * 1;
		out->z = arg20 * in.x + arg21 * in.y + arg22 * in.z + arg23 * 1;
	}
}
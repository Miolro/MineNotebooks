#pragma once
#include "GameLib/GameLib.h"
template <class T>
class Array2D
{
public:
	Array2D() {};
	~Array2D() {SAFE_DELETE_ARRAY(mArray2D) };
	void setArray2DSize(int x, int y)
	{
		mWidth = x;
		mArray2D = new T[x * y];
	};
	T& operator()(int px,int py)
	{
		return mArray2D[py * mWidth + px];
	}
private:
	int mWidth;
	T* mArray2D;
};
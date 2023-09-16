#pragma once
#ifndef INCLUDE_ARRAY_2D_HEADER
#define INCLUDE_ARRAY_2D_HEADER

template <class T>
class Array2D
{
public:
	Array2D()
	{

	}
	~Array2D()
	{
		delete[]mArray2D;
		mArray2D = nullptr;
	}
	void setArraySize(unsigned iSizeX, unsigned iSizeY)
	{
		mWidth = iSizeX;
		mArray2D = new T[iSizeX * iSizeY];
	}

	T& operator()(unsigned ix, unsigned iy)
	{
		return mArray2D[iy * mWidth + ix];
	}

	const T& operator()(unsigned ix, unsigned iy) const
	{
		return mArray2D[iy * mWidth + ix];
	}

private:
	unsigned mWidth;
	T* mArray2D;
};


#endif INCLUDE_ARRAY_2D_HEADER

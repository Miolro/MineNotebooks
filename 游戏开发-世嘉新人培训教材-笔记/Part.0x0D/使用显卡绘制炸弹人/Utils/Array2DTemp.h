#pragma once

template<class T> class Array2DTemplate
{
public:
	Array2DTemplate() :cols(0), rows(0)
	{
	};
	~Array2DTemplate()
	{
		SAFE_DELETE_ARRAY(arrayData);
	};
	void setSize(int irows, int icols)
	{
		rows = irows;
		cols = icols;
		arrayData = new T[rows * cols];
	}
	T& operator()(int irows, int icols)
	{
		return arrayData[icols * rows + irows];
	};
	const T& operator()(int irows, int icols)const
	{
		return arrayData[icols * rows + irows];
	};
private:
	T* arrayData;
	int cols; // ÐÐ
	int rows; // ÁÐ
};
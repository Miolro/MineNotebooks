template<class T>
class Array2D
{
public:
	Array2D() :array2DWidth(0), array2DData(nullptr)
	{

	}
	~Array2D()
	{
		delete[] array2DData;
		array2DData = nullptr;
	}
	void setArray2DSize(unsigned iMaxX, unsigned iMaxY)
	{
		array2DWidth = iMaxX;
		array2DData = new T[iMaxX * iMaxY];
	}

	T& operator()(unsigned iPositionX, unsigned iPositionY) {
		return array2DData[iPositionY * array2DWidth + iPositionX];
	}

	T& operator()(unsigned iPosition) {
		return array2DData[iPosition];
	}

private:
	unsigned array2DWidth;
	T* array2DData;
};
#include "Attribute.h"
#include <sstream>
Attribute::Attribute(const char* name, const char* value)
	:mName(name),
	mValue(value)
{
}

int Attribute::getDoubleValues(double* out, int size)const
{
	int retSize = 0;
	istringstream iss(mValue);
	for (int i = 0; i < size; i++)
	{
		iss >> out[i];
		if (iss.fail())
		{
			break;
		}
		retSize++;
		iss.ignore(mValue.size(), ',');
	}

	return retSize;
}

int Attribute::getIntagerValues(unsigned* out, int size) const
{
	int retSize = 0;
	istringstream iss(mValue);
	for (int i = 0; i < size; i++)
	{
		iss >> out[i];
		if (iss.fail())
		{
			break;
		}
		retSize++;
		iss.ignore(mValue.size(), ',');
	}
	return retSize;
}

const string* Attribute::name() const
{
	return &mName;
}

const string* Attribute::value() const
{
	return &mValue;
}
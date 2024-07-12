#pragma once
#include <string>
using namespace std;
class Attribute
{
public:
	Attribute(const char* name, const char* value);
	int getDoubleValues(double* out, int size)const;
	int getIntagerValues(unsigned* out, int size)const;
	const string* name()const;
	const string* value()const;
private:
	string mName;
	string mValue;
};


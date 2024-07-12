#pragma once
#include <string>
using namespace std;
class Attribute
{
public:
	Attribute(const char* name, const char* value);
private:
	string mName;
	string mValue;
};


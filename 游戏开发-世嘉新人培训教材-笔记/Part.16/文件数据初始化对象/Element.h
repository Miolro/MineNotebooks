#pragma once
#include <string>
#include <vector>
using namespace std;
class Tag;
class Attribute;
class Element
{
public:
	Element(Tag* tagName, const char** begin, const char* end);
	int size()const;
	const string* name()const;
	const Element* child(int index)const;
	const Attribute* attribute(int index)const;
	const int getDouble(double out)const;
	const int getDoubleList(double* out, int size)const;
	const int attributeSize()const;
private:
	string mName;
	string mValue;
	vector<Attribute*> mAttributes;
	vector<Element*> mChildren;
};


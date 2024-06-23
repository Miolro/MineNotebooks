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
private:
	string mName;
	string mValue;
	vector<Attribute*> mAttributes;
	vector<Element*> mChildren;
};


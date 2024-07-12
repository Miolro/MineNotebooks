#pragma once
#include <string>
#include "Attribute.h"
#include "Tag.h"
#include "Element.h"
using namespace std;
class Document
{
public:
	Document(const char* xmlFileName);
private:
	Element* mRoot;
};
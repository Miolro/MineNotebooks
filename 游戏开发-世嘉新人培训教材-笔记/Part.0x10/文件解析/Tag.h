#pragma once
#include <vector>
#include <string>
using namespace std;

class Attribute;
class Tag
{
public:
	enum TagType
	{
		TAG_BEGIN,
		TAG_END
	};
	~Tag();
	Tag(const char* tagName);
	Tag(const char** begin, const char* end);
	const string* name()const;
	const vector<Attribute*>* attributes();
	TagType type() const;
private:
	TagType mType;
	string mName;
	vector< Attribute* > mAttributes;
};


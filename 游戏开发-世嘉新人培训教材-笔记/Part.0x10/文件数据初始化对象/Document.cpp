#include "Document.h"
#include "File.h"
#include "GameLib/Framework.h"
#include <vector>




Document::Document(const char* fileName)
{
	File file(fileName);
	const char* begin = file.getData();
	const char* end = file.getData() + file.getSize();
	Tag tag("<ROOT>");
	mRoot = new Element(&tag, &begin, end);
}

const Element* Document::root() const
{
	// TODO: 在此处插入 return 语句
	return mRoot;
}



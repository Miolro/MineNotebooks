#include "Element.h"
#include "Tag.h"
#include <sstream>
Element::Element(Tag* tagName, const char** begin, const char* end)
{
	mName = *(tagName->name());
	mAttributes = *tagName->attributes();
	while (*begin < end)
	{
		if (**begin == '<')  // 16  找到下一个<开头的标签  <Tag>(节点/子节点) 或者 </Tag>(结束标签)
		{
			++(*begin);
			Tag tag(begin, end);
			if (tag.type() == Tag::TAG_BEGIN) // 14 获取解析结果
			{
				mChildren.push_back(new Element(&tag, begin, end));  // 15 创建节点信息(拷贝标签名和属性vector)
			}
			else if (tag.type() == Tag::TAG_END)		// 18 递归结束返回new的结果push_back到mChildren中
			{
				break;
			}
		}
		else
		{
			++(*begin);		// 不停的找下一个<的位置
		}
	}
}

int Element::size()const
{
	return mChildren.size();
}

const string* Element::name() const
{
	return &mName;
}

const Element* Element::child(int index) const
{
	return mChildren[index];
}

const Attribute* Element::attribute(int index) const
{
	return mAttributes[index];
}

const int Element::getDouble(double out)const
{
	return 0;
}

const int Element::getDoubleList(double* out, int size)const
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

const int Element::attributeSize()const 
{
	return mAttributes.size();
}



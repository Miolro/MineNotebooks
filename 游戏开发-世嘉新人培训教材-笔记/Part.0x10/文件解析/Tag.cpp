#include "Tag.h"
#include "Attribute.h"
bool isNormalChar(const char inChar)
{
	if (inChar <= '9' && inChar >= '0')
	{
		return true; //A 0100 0001  //a 0110 0001
	}
	else if ((inChar | 0x20) >= 'a' && (inChar | 0x20) <= 'z')
	{
		return true;
	}
	else if (inChar == '-' || inChar == ',' || inChar == '.')
	{
		return true;
	}
	return false;
}
Tag::~Tag()
{
}
Tag::Tag(const char* tagName) :mName(tagName)
{

}

Tag::Tag(const char** begin, const char* end) :mType(TAG_BEGIN)
{
	int m = 0;
	string name;
	string value;
	bool flag = false;
	while (*begin < end) {
		char c = **begin;
		++(*begin);
		switch (m)
		{
		case 0:
			switch (c)
			{
			case '/': flag = true; mType = TAG_END;  break;   // 17 </Tag> 读到(/)表示已经读完当前节点里面的信息  设置跳出循环和跳出递归
			case ' ':break; // 跳过开始的空格<   Tag>的情况
			default: m = 1; break; // 1 读取标签第一个字符 此时会跳过第一个字符 会来到begin指向的位置 T这个位置->Tag>
			}
		case 1: // 读取标签名字
			if (isNormalChar(c))  //  2 碰到空格
			{
				mName += c;
				break;
			}
			m = 2;				  // 3 切换到读属性
			break;
		case 2:                   //  11 属性循环解析直到出现>表示这个节点循环结束
			if (c == '>')
			{
				flag = true;      //  12 跳出循环的标志
			}
			else if (isNormalChar(c))  // 4 开始读属性名字 (name)="value"
			{
				m = 3; name += c;
				break;
			}
			break;
		case 3:
			if (c == '"')				// 7 找到属性开头  name=(")value" 跳转到属性解析
			{
				m = 4;
			}
			else if (c == '=')			// 6  碰到=去这找开头的"  name(=)"value"
			{
				m = 3;
			}
			else if (isNormalChar(c)) {  // 5  正式读取属性名称
				name += c;
			}
			break;
		case 4:
			if (c == '"')		// 9   name="value(") 解析到结尾 返回到状态2解析是否还有其他属性
			{
				m = 2;
				mAttributes.push_back(new Attribute(name.c_str(), value.c_str()));  // 10 将属性和属性值保存到vector中
				name.clear();
				value.clear();
				break;
			}
			value += c;			// 8   name="(value)" 开始解析
			break;
		default:
			break;
		}
		if (flag)
		{
			break;				// 13 跳出递归
		}
	}
}

const string* Tag::name()const
{
	return &mName;
}

const vector<Attribute*>* Tag::attributes()
{
	return &mAttributes;
}

Tag::TagType Tag::type() const
{
	return mType;
}

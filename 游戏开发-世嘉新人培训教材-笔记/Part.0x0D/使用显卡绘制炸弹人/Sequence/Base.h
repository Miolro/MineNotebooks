#pragma once
class Base
{
public:
	virtual ~Base() {};
	virtual Base* update(Base*) = 0; // ±»×ÓÀà¼Ì³Ğ
};
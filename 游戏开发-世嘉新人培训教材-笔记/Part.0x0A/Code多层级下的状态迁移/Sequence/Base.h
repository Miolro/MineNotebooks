#pragma once
namespace Sequence
{
	class Base
	{
	public:
		virtual ~Base() {};
		virtual Base* update(Base*) = 0;
	};
}

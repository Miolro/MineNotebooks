#pragma once
#include "Base.h"
namespace Sequence
{
	class Parent;
	class Ending;
	class Title;
	class GameOver;
	class Child :public Base
	{
	public:
		virtual Base* update(Parent*) = 0; // ���virtual ... =0 ��ʶ���������child�ﱾ��û�������������������������������
		virtual ~Child() {}; // �յĺ���  ��֤��������������
		Base* update(Base* basePrt);
	};
}

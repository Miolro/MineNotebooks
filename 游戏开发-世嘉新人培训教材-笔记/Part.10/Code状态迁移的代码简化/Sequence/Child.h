#pragma once
class Parent;
namespace Sequence
{
	class Ending;
	class Title;
	class GameOver;
	class Child
	{
	public:
		virtual Child* update(Parent*) = 0; // ���virtual ... =0 ��ʶ���������child�ﱾ��û�������������������������������
		virtual ~Child() {}; // �յĺ���  ��֤��������������
	};


}

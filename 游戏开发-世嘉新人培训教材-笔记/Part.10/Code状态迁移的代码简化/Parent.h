#pragma once
namespace Sequence { class Child; };
class Parent
{
public:
	Parent();
	~Parent();

	//enum GameStaus
	//{
	//	STA_STAY,					// ���ڱ��ֵ�ǰ״̬
	//	STA_TITLE,
	//	STA_GAMEOVER,
	//	STA_GAME,
	//	STA_CLEAR
	//};
	//GameStaus thisSequence() const;  // ���ص�ǰ״̬
	void update();
private:

 	//GameStaus mStatus;
	Sequence::Child* mChild;					// ����һ����ǰ���ɵ�child
	Sequence::Child* mNextChild;				// ������һ��Child����
};
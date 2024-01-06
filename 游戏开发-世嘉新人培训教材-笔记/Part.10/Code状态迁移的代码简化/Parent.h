#pragma once
namespace Sequence { class Child; };
class Parent
{
public:
	Parent();
	~Parent();

	//enum GameStaus
	//{
	//	STA_STAY,					// 用于保持当前状态
	//	STA_TITLE,
	//	STA_GAMEOVER,
	//	STA_GAME,
	//	STA_CLEAR
	//};
	//GameStaus thisSequence() const;  // 返回当前状态
	void update();
private:

 	//GameStaus mStatus;
	Sequence::Child* mChild;					// 保存一个当前生成的child
	Sequence::Child* mNextChild;				// 保存下一个Child对象
};
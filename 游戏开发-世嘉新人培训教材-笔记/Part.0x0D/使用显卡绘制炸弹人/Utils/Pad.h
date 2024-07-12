#pragma once
class Pad
{
public:
	enum KeyList
	{ // 上 下  左  右 放置 操作取消
		W,S,A,D,Q,J,K
	};
	static bool isOn(KeyList, int playerID = 0);
	static bool isTriggered(KeyList, int playerID = 0);
};


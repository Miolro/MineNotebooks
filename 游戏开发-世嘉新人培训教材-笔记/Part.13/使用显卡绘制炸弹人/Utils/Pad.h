#pragma once
class Pad
{
public:
	enum KeyList
	{ // �� ��  ��  �� ���� ����ȡ��
		W,S,A,D,Q,J,K
	};
	static bool isOn(KeyList, int playerID = 0);
	static bool isTriggered(KeyList, int playerID = 0);
};


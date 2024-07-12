#pragma once
class Pad
{
public:
	enum Button
	{
		KEY_FORWARD,
		KEY_BACK,
		KEY_LEFT,
		KEY_RIGHT,
		KEY_FLY,
		KEY_AIM
	};
	static Pad* instance();
	static void create();
	static void destory();
	bool isOn(Button,int playerId);
	bool isTriggered(Button, int playerId);

private:
	Pad();
	~Pad();
	static Pad* mInstance;
};


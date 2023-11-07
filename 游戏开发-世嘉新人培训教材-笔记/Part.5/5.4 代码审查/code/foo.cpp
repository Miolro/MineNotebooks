#include "GameLib/Framework.h"
#include "File.h"
#include "Image.h"
#include "Sequence/Game/State.h"
#include "Sequence/StatusFrame.h"
namespace GameLib
{
	Sequence::StatusFrame* frame = nullptr;
	void mainLoop()
	{
		if (GameLib::Framework::instance().isKeyTriggered('q'))
		{
			SAFE_DELETE(frame);
			GameLib::Framework::instance().requestEnd();
		}
	}

	void Framework::update()
	{
		if (!frame)
		{
			frame = new Sequence::StatusFrame(); // ʹ�������������  ������ʹ��state��Ϊȫ��
		}
		setFrameRate(60);
		frame->update();
	}

}
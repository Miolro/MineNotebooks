#include "GameLib/Framework.h"
#include "Sequence/Parent.h"
#include "Utils/Image.h"
namespace GameLib {

	bool gInit = false;
	void Framework::update()
	{
		if (!gInit)
		{
			// ��ʼ�������Parent
			setFrameRate(60);
			Sequence::Parent::create();
			gInit = true;
		}
		// �Ե���Parent������и���
		Sequence::Parent::instance()->update();
	}
}
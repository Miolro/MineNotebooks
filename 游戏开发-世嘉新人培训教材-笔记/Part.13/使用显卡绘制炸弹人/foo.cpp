#include "GameLib/Framework.h"
#include "Sequence/Parent.h"
#include "Utils/Image.h"
namespace GameLib {

	bool gInit = false;
	void Framework::update()
	{
		if (!gInit)
		{
			// 初始化顶层的Parent
			setFrameRate(60);
			Sequence::Parent::create();
			gInit = true;
		}
		// 对单例Parent对象进行更新
		Sequence::Parent::instance()->update();
	}
}
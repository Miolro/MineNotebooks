#include "Title.h"
#include "../Image.h"
#include "StatusFrame.h"
#include "GameLib/Framework.h"
namespace Sequence {
	Title::Title()
	{
		mImage = new Image("data/image/title.dds");
	};
	Title::~Title()
	{
 		SAFE_DELETE(mImage);
	};
	void Title::update(StatusFrame* frame)
	{
		mImage->draw(0, 0, 0, 0, mImage->getWidth(), mImage->getHeight());
		if (GameLib::Framework::instance().isKeyTriggered(' ')) {
			frame->setNextStatus(Sequence::StatusFrame::StatusType::SEQ_STAGE_SELECT);
		}
	}
}
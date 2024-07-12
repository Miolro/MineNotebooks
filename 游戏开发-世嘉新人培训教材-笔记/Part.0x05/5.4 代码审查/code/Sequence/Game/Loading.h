#pragma once
class Image;

namespace Sequence {
	class StatusFrameGame;
	class Loading
	{
	public:
		Loading();
		~Loading();
		void update(StatusFrameGame*);
	private:
		Image* mImage;
		int mWaitTime;
		bool mStart;
	};
}

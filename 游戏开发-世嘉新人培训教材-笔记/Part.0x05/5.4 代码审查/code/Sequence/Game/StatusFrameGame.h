#pragma once
class State;
namespace Sequence {
	class Loading;
	class StatusFrame;
	class StatusFrameGame
	{
	public:
		enum class Status
		{
			STA_LOAD,
			STA_LOADED,
			STA_RUN,
			STA_CLEAR,
			STA_NONE
		};
		StatusFrameGame();
		StatusFrameGame(StatusFrame*);
		~StatusFrameGame();
		void update(StatusFrame*);
		void setNextStatus(StatusFrameGame::Status);
		void startLoading();
	private:
		Loading* mLoad;
		State* mState;

		int mStateId;
		Status mStatus;
		Status nextStatus;
	};
}



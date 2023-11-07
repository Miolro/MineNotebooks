
namespace Sequence {
	class Title;
	class StatusFrameGame;
	class StageSelect;
	class StatusFrame
	{
	public:
		StatusFrame();
		~StatusFrame();
		enum class StatusType
		{
			SEQ_STAGE_SELECT,
			SEQ_TITLE,
			SEQ_GAME,

			SEQ_NONE,
		};

		void update();
		void setStageId(int stageId);
		int getStageId();
		void setNextStatus(StatusType sequenceId);
	private:
		Title* mTitle;
		StatusFrameGame* mGame;
		StageSelect* mStage;
		int mStageId;
		StatusType mSeqId;
		StatusType mNextStatus;
	};
}



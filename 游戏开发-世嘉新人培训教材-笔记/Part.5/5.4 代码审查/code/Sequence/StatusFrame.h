
namespace Sequence {
	class Title;
	class Game;
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
		void setNextStatus(StatusType sequenceId);
	private:
		Title* mTitle;
		Game* mGame;
		StageSelect* mStage;
		int mStageId;
		StatusType mSeqId;
		StatusType mNextStatus;
	};
}



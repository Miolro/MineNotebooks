#pragma once
class Image;
namespace Sequence
{
	class StatusFrame;
	class StageSelect
	{
	public:
		StageSelect();
		~StageSelect();
		void update(StatusFrame*);
	private:
		Image* mImage;

	};
}


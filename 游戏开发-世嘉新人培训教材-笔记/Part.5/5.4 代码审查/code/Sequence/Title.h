
class Image;
namespace Sequence {
	class StatusFrame;
	class Title
	{
	public:
		Title();
		~Title();
		void update(StatusFrame*);
	private:
		Image* mImage;
	};
}
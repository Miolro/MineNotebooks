#include "Framework.h"

#include <string>
using namespace std;

namespace GameLib
{
	/*begin{}begin*/
	namespace
	{
		class Impl
		{
			Impl() :mWidth(320), mHeight(240),mFullScreen(false),mTitle("RemakeFramework")
			{
				
			}
			int mWidth;
			int mHeight;
			bool mFullScreen;
			string mTitle;
		};
		Impl* gImpl = nullptr;
	} 
	/*ender{}ender*/
	Framework::Framework()
	{

	}
}
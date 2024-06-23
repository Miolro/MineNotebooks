#include <sstream>
#include "GameLib/Framework.h"
#include "GameLib/Math.h"
#include "Document.h"
using namespace GameLib;
using namespace std;

Document* document;
bool init = false;
namespace GameLib {

	void Framework::update() {
		setFrameRate(60);
		if (!init)
		{

			document = new Document("data.txt");
			init = !init;
		}

	}
}
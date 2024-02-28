#include "Play.h"
#include "GameParent.h"
#include "Ending.h"
namespace Game
{
	Play::Play()
	{

	}
	Play::~Play()
	{
	}
	Base* Play::update(Game::Parent* parent)
	{
		State* state = parent->getState();
		State::Flag flag = state->update();
		if (flag == State::Flag::LOSE)
		{
			return new Ending();
		}
		state->draw();
		return this;
	}
}

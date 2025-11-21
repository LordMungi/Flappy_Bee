#pragma once
#include "GameState.h"

namespace game
{
	void init(int playerAmount);
	GameState update();
	void draw();
}
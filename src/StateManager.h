#pragma once
#include "BorjaLib.h"
#include "Ball.h"
#include "ObstacleManager.h"

enum class GameState {
	MAIN_MENU,
	GAMEPLAY,
	CREDITS
};

void MainLoop();
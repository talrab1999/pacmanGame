#pragma once
#include "game.h"

class LoadMode : public game
{
	~LoadMode() {}
	void gameLoop(bool)override;
};


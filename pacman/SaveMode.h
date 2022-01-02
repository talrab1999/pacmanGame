#pragma once
#include "game.h"

class SaveMode :public game
{
	~SaveMode() {}
	void gameLoop(bool)override;
};



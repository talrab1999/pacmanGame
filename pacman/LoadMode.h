#pragma once
#include "game.h"

class LoadMode : public game
{
	~LoadMode() {}

	void gameLoop(bool silent = false) override;
	void prepareFilesForLoadGame(string, ifstream&, ifstream&);
	void movePacmanWithDir(char&, pacman&, map&, string&);
};


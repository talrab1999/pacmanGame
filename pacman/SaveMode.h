#pragma once
#include "game.h"

enum class e_SaveOptionInput {
	PLAY = '1',
	INSTRUCTIONS = '8',
	EXIT = '9',
	DEFAULT = '0'
};

class SaveMode :public game
{
	~SaveMode() {}

	void gameLoop() override;
	void goToOption(char& input) override;
	void prepareFilesForNewGame(string, ofstream&, ofstream&);
	
};



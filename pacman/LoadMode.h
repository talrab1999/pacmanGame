#pragma once
#include "game.h"

class LoadMode : public game
{

public:
	~LoadMode() {}

	void gameLoop()override;

	//Silent Mode
	void setSilent(bool);
	bool getSilent();

	//Files Methods
	void prepareFilesForLoadGame(string, ifstream&, ifstream&);
	void readMoveFromSteps(string&, pacman&, ghost&, ghost&, fruit&);
	void readAndCheckResult(ifstream&, string&, unsigned long long int&, bool&, char&);
	void printRes(bool, ifstream&, ifstream&);

	//Entities Methods
	void movePacmanWithDir(char&, pacman&, map&, string&);
	void moveGhostWithDir(ghost&, map&);
	bool didGhostEatPacman(map& h, pacman& player1, ghost& Tinky_Winky, ghost& Po, char& key1, char& key2, bool& running1) override;

private:
	bool silentMode;
};
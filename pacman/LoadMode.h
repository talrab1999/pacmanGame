#pragma once
#include "game.h"

class LoadMode : public game
{

public:
	~LoadMode() {}

	void gameLoop()override;
	void prepareFilesForLoadGame(string, ifstream&, ifstream&);
	void movePacmanWithDir(char&, pacman&, map&, string&);
	bool didGhostEatPacman(map& h, pacman& player1, ghost& Tinky_Winky, ghost& Po, char& key1, char& key2, bool& running1) override;
	void setSilent(bool);
	bool getSilent();
	void readAndCheckResult(ifstream&, string&, unsigned long long int&, bool&, char&);
	void exitLoop(ifstream&, ifstream&);
	void moveGhostWithDir(ghost&, map&);
	void readMoveFromSteps(string&, pacman&, ghost&, ghost&, fruit&);
private:
	bool silentMode;
};
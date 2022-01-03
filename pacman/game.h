#pragma once

#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include <stack>
#include <queue>
#include <set>
#include "pacman.h"
#include "map.h"
#include "fruit.h"

using namespace std;

typedef pair<int, int> Pair;
typedef pair<int, pair<int, int> > pPair;

enum class e_GhostDiff {
	BEST = 'a',
	GOOD = 'b',
	NOVICE = 'c'
};

enum class e_OptionInput {
	PLAY = '1',
	CHOOSE_MAP = '2',
	INSTRUCTIONS = '8',
	EXIT = '9',
	DEFAULT = '0'
};

enum class e_GameMode {
	SIMPLE = '0',
	SAVE = '1',
	LOAD = '2',
	LOAD_SILENT='3'
};

struct cell {
	int parent_i, parent_j;
	double f, g, h;
};

class game {
protected:

	static string choices[4];
	enum {
		ESC = 27,
	};
	short lastOption, startLives, numGhosts, ghostspeed, speed;
	Pair legend;
	bool oneMap;

	string mapNum;
	char mode;

	queue<string> screenFiles;
	int numOfScreens;

public:

	game();
	virtual void gameLoop(bool silent = false);

	//Map Functions
	void chooseMap();
	bool getOneMap() const;
	void setOneMap(bool);
	void readEntities(map&, pacman&, ghost&, ghost&);

	//Menu Functions
	void runMenu();
	void gotoxy(int, int);
	void displayChoices() const;
	void displayChoices(short) const;
	virtual void goToOption(char&);
	void clearScreen() const;
	void displayInstructions() const;
	void displaywin() const;
	void displaylose() const;
	string getmapNum() const;
	void setmapNum(string);
	void prepareForNewGame(map&, pacman&, fruit&, ghost&, ghost&, char&, char&, unsigned long long int&);
	bool didGhostEatPacman(map&, pacman&, ghost&, ghost&, char&, char&, bool&);
	void setMode(char);
	void setLegend(int,int);
	Pair getLegend();

	//Pacman functions
	bool pacmanMove(pacman&, char&, char&, map&);

	//Ghost functions
	char chooseGhostsDifficulty();
	void ghostMove(ghost&, map&, pacman&);
	void BestMove(ghost&, map&, pacman&);
	bool FruitMetEntity(ghost&, ghost&, fruit&, pacman&, map&);
	
	//Pathfinding functions
	bool isValid(int row, int col);
	bool isUnBlocked(char grid[][COLS], int row, int col);
	bool isDestination(int row, int col, Pair dest);
	int calculateHValue(int row, int col, Pair dest);
	Pair tracePath(cell cellDetails[][COLS], Pair dest);
	Pair aStarSearch(char grid[][COLS], Pair src, Pair dest);

	//Files functions
	void getFiles();
	
	//Queue functions
	void showq (queue<string> q);


};
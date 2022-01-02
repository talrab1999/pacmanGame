#pragma once
using namespace std;
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <stack>
#include <set>
#include "pacman.h"
#include "map.h"
#include "fruit.h"


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
	LOAD = '2'
};

struct cell {
	int parent_i, parent_j;
	double f, g, h;
};

class game {
private:
	static string choices[4];
	enum {
		ESC = 27,
	};
	short lastOption, startLives, numGhosts, ghostspeed, speed;
	string mapNum;
	Pair legend;
	char mode;
	
	bool oneMap;
public:
	game();

	void gameLoop(bool silent = false);

	//Map Functions
	void chooseMap();
	bool getOneMap() const;
	void setOneMap(bool);
	void readEntities(map&, pacman&, ghost&, ghost&);

	//Menu Functions
	void gotoxy(int, int);
	void displayChoices() const;
	void displayChoices(short) const;
	void goToOption(char&);
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
	

};
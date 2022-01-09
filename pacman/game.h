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

enum class e_speedChoise {
	FAST = '1',
	NORMAL = '2',
	SLOW = '3'
};

enum class e_GameSpeed {
	FAST = 50,
	NORMAL = 100,
	SLOW = 200
};

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

	short lastOption, startLives, numGhosts, ghostspeed;
	Pair legend;
	bool oneMap;
	string mapNum;
	char mode;
	queue<string> screenFiles;
	int numOfScreens, speed;

public:

	game();

	virtual void gameLoop();

	//Map Functions
	void chooseMap();
	bool getOneMap() const;
	void setOneMap(bool);
	bool is_number(const string& s);
	string getmapNum() const;
	void setmapNum(string);
	bool readEntities(map&, pacman&, ghost&, ghost&);

	//Menu Functions
	void runMenu();
	void gotoxy(int, int);
	void displayChoices() const;
	void displayChoices(short) const;
	virtual void goToOption(char&);
	void displayInstructions() const;

	//Screen Functions
	void clearScreen() const;
	void displaywin() const;
	void displaylose() const;

	//Game set functions
	void setMode(char);
	void setLegend(int, int);
	char getMode();
	Pair getLegend();
	void setSpeed(int);
	int getSpeed();
	void chooseGameSpeed();

	bool prepareForNewGame(map&, pacman&, fruit&, ghost&, ghost&, char&, char&, unsigned long long int&);
	virtual bool didGhostEatPacman(map&, pacman&, ghost&, ghost&, char&, char&, bool&);
	bool checkIfGameLost(pacman&, bool&);
	
	//Pacman functions
	bool pacmanMove(pacman&, char&, char&, map&);

	//Ghost functions
	char chooseGhostsDifficulty();
	void ghostMove(ghost&, map&, pacman&);
	void BestMove(ghost&, map&, pacman&);
	bool FruitMetEntity(ghost&, ghost&, fruit&, pacman&, map&);
	void calcDirection(ghost&, int, int, int, int);
		
	//Pathfinding functions
	bool isValid(int row, int col);
	bool isUnBlocked(char grid[][COLS], int row, int col);
	bool isDestination(int row, int col, Pair dest);
	int calculateHValue(int row, int col, Pair dest);
	Pair tracePath(cell cellDetails[][COLS], Pair dest);
	Pair aStarSearch(char grid[][COLS], Pair src, Pair dest);

	//Files functions
	void getFiles();
	void resetScreens();
	bool ends_with_screen(const string& fileName);

	//Queue functions
	void showq (queue<string> q);
	string showQIndex(int i);
};
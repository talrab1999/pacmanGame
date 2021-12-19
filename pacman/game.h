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
	
	bool oneMap;
public:
	game();
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
	void gameLoop();
	void prepareForNewGame(map&, pacman&, fruit&, ghost&, ghost&, char&, char&);
	bool didGhostEatPacman(map&, pacman&, ghost&, ghost&, char&, char&, bool&);
	bool getOneMap() const;
	void setOneMap(bool);
	void readEntities(map&, pacman&, ghost&, ghost&);
	void setLegend(int,int);
	Pair getLegend();
	
	//pathfinding
	bool isValid(int row, int col);
	bool isUnBlocked(char grid[][COLS], int row, int col);
	bool isDestination(int row, int col, Pair dest);
	int calculateHValue(int row, int col, Pair dest);
	Pair tracePath(cell cellDetails[][COLS], Pair dest);
	Pair aStarSearch(char grid[][COLS], Pair src, Pair dest);
	char chooseGhostsDifficulty();
	void ghostMove(ghost&,map&, pacman&);
	void BestMove(ghost&, map&, pacman&);
	bool FruitMetEntity(ghost&, ghost&,fruit&, pacman&, map&);
	void chooseMap();

};
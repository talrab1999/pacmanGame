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
#include "ghost.h"
#include "pacman.h"
#include "map.h"

typedef pair<int, int> Pair;
typedef pair<double, pair<int, int> > pPair;

struct cell {
	int parent_i, parent_j;
	double f, g, h;
};

class game {
private:
	static string choices[3];
	enum {
		ESC = 27,
	};
	short lastOption, startLives, numGhosts, ghostspeed, speed;
	string filename;
public:
	game();
	void gotoxy(int,int);
	void displayChoices() const;
	void displayChoices(short) const;
	void goToOption(short);
	void clearScreen() const;
	void displayInstructions() const;
	void displaywin() const;
	void displaylose() const;
	string getFilename() const;
	void setFilename(string);
	void gameLoop();
	//pathfinding
	bool isValid(int row, int col);
	bool isUnBlocked(char grid[][COLS], int row, int col);
	bool isDestination(int row, int col, Pair dest);
	double calculateHValue(int row, int col, Pair dest);
	Pair tracePath(cell cellDetails[][COLS], Pair dest);
	Pair aStarSearch(char grid[][COLS], Pair src, Pair dest);
};
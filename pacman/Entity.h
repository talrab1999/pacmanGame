#pragma once

#include <Windows.h>
#include <iostream>
#include <string>
#include "map.h"
using namespace std;

/*Entity class includes either the pacman or the ghosts(maybe the food later)*/

enum class e_EntityAction {
	UP = 0,
	DOWN = 1,
	LEFT = 2,
	RIGHT = 3,
	STAY = 4,
	WAKE_UP = 5,
	SLEEP = 6
};

class Entity {
private:
	short x, y, lives;
	short defaultX, defaultY;
	int lastmove;
	char symbol;

public:
	Entity();
	Entity(short, short, short, char, short);

	////Set Methods////
	void setX(short);
	void setY(short); 
	void setLives(short);
	void setSymbol(char);
	void setLastMove();
	void setLastMove(int);
	void setDefault(int, int);

	//Get Methods
	short getX() const;
	short getY() const; 
	short getLives() const;
	char getSymbol() const;
	int getLastMove();
	
	//Move Methods
	void move_rand(map&);

	//Location Methods
	void gotoxy(short, short) const;
	void replace() const;

	void display();
	void display(char);

	void reset(int x, int y);
	void resetEntity();

};

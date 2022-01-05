#pragma once

#include <Windows.h>
#include <iostream>
#include <string>
#include "map.h"
#include "color.h"
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
	Color color;

public:
	Entity();
	Entity(short, short, short, char, short, Color);
	void setX(short); 
	void setY(short); 
	short getX() const;
	short getY() const; 
	void setLives(short); 
	void setSymbol(char);   
	void setColor(Color);
	//move 
	void move_rand(map&);

	//void setTextColor(Color);
	short getLives() const;   
	char getSymbol() const;
	void gotoxy(short, short) const;
	void display();
	void display(char);
	void replace() const;
	void reset(int x, int y);
	void resetEntity();
	void setLastMove();
	void setLastMove(int);
	short getLastMove();
	void setDefault(int, int);
	
};

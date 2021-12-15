#pragma once

#include <Windows.h>
#include <iostream>
#include <string>
#include "map.h"
#include "color.h"
using namespace std;

/*Entity class includes either the pacman or the ghosts(maybe the food later)*/

class Entity {
private:
	short x, y, lives;
	char symbol;
	Color color;
public:
	Entity();
	Entity(short, short, short, char, Color);
	void setX(short); 
	void setY(short); 
	short getX() const;
	short getY() const; 
	void setLives(short); 
	void setSymbol(char);   
	void setColor(Color);
	//void setTextColor(Color);
	short getLives() const;   
	char getSymbol() const;
	void gotoxy(short, short) const;
	void display();
	void display(char);
	void replace() const;
};

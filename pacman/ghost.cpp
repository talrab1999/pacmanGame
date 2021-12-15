#include "ghost.h"

ghost::ghost()
{
	lastmove = 0;
	edible = 0;
	setLives(1);
	setSymbol('$');
	//setColor(Color::RED);
}
void ghost::reset1() {
	setX(30);
	setY(8);
}
void ghost::reset2() {
	setX(15);
	setY(8);
}

void ghost::move_rand(map& m)
{
	short nextX = 0, nextY = 0;
	short direction = lastmove;
	while (true) {
		switch (direction) {
		case 0: nextY = getY() - 1;
			nextX = getX();   
			break;
		case 1: nextY = getY() + 1; 
			nextX = getX();  
			break;
		case 2: nextY = getY();  
			nextX = getX() - 1;
			break;
		case 3: nextY = getY(); 
			nextX = getX() + 1;
			break;
		}
		if (m.getmapat(nextY, nextX) != '#' && m.getmapat(nextY, nextX) != '!') {
			setY(nextY);
			setX(nextX);
			lastmove = direction;
			break;
		}
		else {
			direction = rand() % 4;
		}
	}
}
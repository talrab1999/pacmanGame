#include "ghost.h"

ghost::ghost(char diff)
{
	//lastmove = 0;
	//edible = 0;
	setLives(1);
	setSymbol('$');
	setDifficulty(diff);
	setGoodCounter(0);
	setTurnCounter(1);
	//setColor(Color::RED);
}

void ghost::reset(int x, int y) {
	setX(x);
	setY(y);
}

/*void ghost::reset2() {
	setX(15);
	setY(7);
}*/

/*void ghost::move_rand(map& m)
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
}*/

void ghost::move(short x, short y) {
	setY(y);
	setX(x);
}

void ghost::setDifficulty(char diff) {
	difficulty = diff;
}
void ghost::setGoodCounter(int count) {
	goodGhostCounter = count;
}
void ghost::setTurnCounter(int count) {
	turnCounter = count;
}

char ghost::getDifficulty() {
	return difficulty;
}
int ghost::getGoodCounter() {
	return goodGhostCounter;
}
int ghost::getTurnCounter() {
	return turnCounter;
}


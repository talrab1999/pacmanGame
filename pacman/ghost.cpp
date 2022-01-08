#include "ghost.h"

ghost::ghost(char diff)
{
	setLives(1);
	setSymbol('$');
	setDifficulty(diff);
	setGoodCounter(0);
	setTurnCounter(1);
	//setColor(Color::RED);
}

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

void ghost::resetCounter() {
	setTurnCounter(0);
}

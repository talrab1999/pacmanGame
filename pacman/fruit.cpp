#include "fruit.h"

fruit::fruit(char diff) :ghost(diff)
{
	//lastmove = 0;
	//edible = 0;
	setLives(1);
	setRandomSymbol();
	setSleep(false);
	//setColor(Color::RED);
}

void fruit::setRandomSymbol() {
	char sym = rand() % 5 + 5 + '0';
	setSymbol(sym);
}

void fruit::sleepFruit(map& h) {
	setSymbol(' ');
	gotoxy(h.getWidth() + 1, 0);
	setSleep(true);
}

void fruit::setSleep(bool sleep) {
	this->sleep = sleep;
}

bool fruit::getSleep() {
	return sleep;
}




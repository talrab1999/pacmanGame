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
	setX(h.getWidth() + 1);
	setY(0);
	setSleep(true);
}

void fruit::setSleep(bool sleep) {
	this->sleep = sleep;
}

bool fruit::getSleep() {
	return sleep;
}

void fruit::wakeUpFruit(map& h) {
	resetLocation(h);
	setSleep(false);
	resetCounter();
	gotoxy(h.getWidth() + 1, 0);
	cout << "  ";
	setRandomSymbol();
}

void fruit::resetLocation(map& h) {
	int x, y;
	x = rand() % 16 + 1;
	y = rand() % 57 + 1;
	while (h.board[x][y] != ' ' && h.board[x][y] != '.') {
		x = rand() % 16 + 1;
		y = rand() % 57 + 1;
	}
	reset(y, x);
	setDefault(y, x);
}



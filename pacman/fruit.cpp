#include "fruit.h"

fruit::fruit()
{
	//lastmove = 0;
	//edible = 0;
	setLives(1);
	char sym = rand() % 5 + 5 + '0';
	setSymbol(sym);
	//setColor(Color::RED);
}
#include <iostream>
#include "game.h"
using namespace std;

void main()
{
	game Game;
	int input = 0;

	while (input != -1) {
		Game.goToOption(input);
		//cin >> input;
	}
}

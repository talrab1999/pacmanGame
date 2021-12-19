#include <iostream>
#include "game.h"
using namespace std;

void main()
{
	srand(time(0));

	game Game;
	char input = 0;
	
	while (input != '9') {
		Game.goToOption(input);
		//cin >> input;
	}
}

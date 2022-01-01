#include <iostream>
#include "game.h"
using namespace std;

void main(int argc, char** argv)
{
	srand(time(0));
	game Game;
	char input = 0;

	//if (strcmp(argv[1], "-save") == 0) {
	//	//play Save Mode
	//	Game.setMode(char(e_GameMode::SAVE));
	//	while (input != '9') {
	//		Game.goToOption(input);
	//	}
	//}

	if (strcmp(argv[1], "-load") == 0) {
		Game.setMode(char(e_GameMode::LOAD));
		if (argc == 3)
			if (strcmp(argv[2], "-silent") == 0) {
				Game.gameLoop(true);
			}
			else {
				Game.gameLoop();
			}
	}

	else {
		if (strcmp(argv[1], "-save") == 0)
			Game.setMode(char(e_GameMode::SAVE));
		else
			Game.setMode(char(e_GameMode::SIMPLE));

		while (input != '9') {
			Game.goToOption(input);
		}
	}
}

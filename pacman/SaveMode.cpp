#include "SaveMode.h"


void SaveMode::goToOption(char& input)
{
	clearScreen();

	switch (input) {
		case char(e_OptionInput::PLAY) :
		{
			gameLoop();
			input = char(e_OptionInput::DEFAULT);
			break;
		}
		case char(e_OptionInput::INSTRUCTIONS) :
		{
			displayInstructions();
			clearScreen();
			input = char(e_OptionInput::DEFAULT);
			break;
		}
		case char(e_OptionInput::EXIT) :
			break;

		default:
		{
			displayChoices();
			input = _getch();
			while (input != char(e_OptionInput::PLAY)
				&& input != char(e_OptionInput::INSTRUCTIONS)
				&& input != char(e_OptionInput::EXIT))
			{
				if (_kbhit())
					input = _getch();
			}
			break;
		}
	}
}



void SaveMode::gameLoop(bool) {

	char ghostDiff = chooseGhostsDifficulty();
	bool running1 = true;
	bool checkInput;
	char key1, key2;
	int currMap = 1;
	unsigned long long int frame;   //can get realy high numbers...

	pacman player1;
	ghost Tinky_Winky(ghostDiff);
	ghost Po(ghostDiff);
	fruit Dipsy;
	map h;
	ofstream save;

	prepareForNewGame(h, player1, Dipsy, Tinky_Winky, Po, key1, key2, frame);

	cout << "this is save mode game loop" << endl;
	system("pause");

	while (running1)
	{
		player1.display(' ');
		h.setmapat(player1.getY(), player1.getX(), ' ');
		switch (numGhosts) {
		case 3: Dipsy.display(h.getmapat(Dipsy.getY(), Dipsy.getX()));
		case 2: Tinky_Winky.display(h.getmapat(Tinky_Winky.getY(), Tinky_Winky.getX()));
		case 1: Po.display(h.getmapat(Po.getY(), Po.getX()));
		}
		checkInput = false;

		if (_kbhit())
			key1 = _getch();


		while (checkInput == false) { //Check if user pressed invalid key
			if (key1 == ESC) {	//If user pressed ESC
				h.pause(h, getLegend().first, getLegend().second);
				player1.display();
				Tinky_Winky.display();
				Po.display();
				short flag;
				flag = _getch();
				while (flag != ESC)
					flag = _getch();
				Tinky_Winky.display(h.getmapat(Tinky_Winky.getY(), Tinky_Winky.getX()));
				Po.display(h.getmapat(Po.getY(), Po.getX()));
				key1 = key2;
				h.unpause(h, getLegend().first, getLegend().second);
				checkInput = true;
			}

			else if (pacmanMove(player1, key1, key2, h))
				checkInput = true;
			else
				continue;

		}
		key2 = key1;
		//if (save) game.mode == "save" Save !load put move in steps file

		if (didGhostEatPacman(h, player1, Tinky_Winky, Po, key1, key2, running1) == true)
		{
			continue;
		}
		if ((FruitMetEntity(Tinky_Winky, Po, Dipsy, player1, h) == true)) {
			Dipsy.sleepFruit(h);
			Dipsy.resetCounter();
		}

		if (player1.getDotsate() == h.getDots()) { //Check if game won     
			if (getOneMap() == false) {
				clearScreen();
				currMap++;
				if (currMap == 4) {
					displaywin();
					running1 = false;
					continue;
				}
				cout << "Good luck in the next map" << endl;
				system("pause");
				clearScreen();
				setmapNum(to_string(currMap)); //Sets new map number
				h.setFilename(getmapNum());    //Loades next map
				prepareForNewGame(h, player1, Dipsy, Tinky_Winky, Po, key1, key2, frame);
				continue;
			}
			else {
				clearScreen();
				displaywin();
				setOneMap(false);
				running1 = false;
				continue;
			}
		}


		if (frame % ghostspeed == 0) { //Every Second frame ghosts move
			ghostMove(Tinky_Winky, h, player1);
			ghostMove(Po, h, player1);

			//if save game 
			if ((FruitMetEntity(Tinky_Winky, Po, Dipsy, player1, h) == true)) {
				Dipsy.sleepFruit(h);
				Dipsy.resetCounter();
			}
			if (Dipsy.getSleep() == false) { //Fruit not asleep
				ghostMove(Dipsy, h, player1);
				if ((FruitMetEntity(Tinky_Winky, Po, Dipsy, player1, h) == true)) {
					Dipsy.sleepFruit(h);
					Dipsy.resetCounter();
				}
			}
			else {	// Fruit asleep
				if (Dipsy.getTurnCounter() == 50) {
					Dipsy.wakeUpFruit(h);
				}
				Dipsy.setTurnCounter(Dipsy.getTurnCounter() + 1);
			}
		}



		if (didGhostEatPacman(h, player1, Tinky_Winky, Po, key1, key2, running1) == true)
		{
			continue;
		}
		player1.displayPoints(h, getLegend().first, getLegend().second);
		player1.display();

		switch (numGhosts) {  //Dipslays Ghosts and fruit
		case 3: Dipsy.display();
		case 2: Tinky_Winky.display();
		case 1: Po.display();
		}

		Sleep(speed);
		frame++;
	}
}

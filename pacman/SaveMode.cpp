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



void SaveMode::gameLoop() {

	char ghostDiff = chooseGhostsDifficulty();
	bool running1 = true;
	bool checkInput;
	char key1, key2;
	unsigned long long int frame;   //can get realy high numbers...

	pacman player1;
	ghost Tinky_Winky(ghostDiff);
	ghost Po(ghostDiff);
	fruit Dipsy;
	map h;

	string writeFile = "";
	ofstream mySteps, myResult;
	
	resetScreens();		//Resets Queue of Screens
	getFiles();			//Fill Queue with screen files

	h.setFilename(screenFiles.front()); //Choose first map in alphabetical queue to play 

	prepareForNewGame(h, player1, Dipsy, Tinky_Winky, Po, key1, key2, frame);
	prepareFilesForNewGame(screenFiles.front(), mySteps, myResult);

	while (running1)
	{
		writeFile = "";

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


		//TODO - FIx Esc so frames wil bbe correct
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
				player1.display(' ');
				h.setmapat(player1.getY(), player1.getX(), ' ');
				key1 = key2;
				h.unpause(h, getLegend().first, getLegend().second);
				checkInput = true;
			}

			//If pacman moved, return true ,if invalid key pressed returns false
			 if (pacmanMove(player1, key1, key2, h)) {
				checkInput = true;
				writeFile = to_string(player1.getLastMove());
			}
			else
				continue;

		}
		key2 = key1;

		if (didGhostEatPacman(h, player1, Tinky_Winky, Po, key1, key2, running1) == true)
		{
			mySteps << writeFile + "446 ";
			myResult << "D " << frame << "\n";
			frame++;
			if (checkIfGameLost(player1, running1) == true) {
				displaylose();
				mySteps.close();
				myResult.close();
			}
			continue;
		}
		if ((FruitMetEntity(Tinky_Winky, Po, Dipsy, player1, h) == true)) {
			Dipsy.sleepFruit(h);
			Dipsy.setLastMove(int(e_EntityAction::SLEEP));
			Dipsy.resetCounter();
		}

		if (player1.getDotsate() == h.getDots()-350) { //Check if game won     

			clearScreen();
			screenFiles.pop();
			mySteps << writeFile + "446";
			myResult << "W " << frame << "\n";
			myResult.close();
			mySteps.close();
			if (screenFiles.empty()) {
				displaywin();
				running1 = false;
				continue;
			}
			cout << "Good luck in the next map" << endl;
			system("pause");
			clearScreen();
			h.setFilename(screenFiles.front());    //Loades next map
			prepareForNewGame(h, player1, Dipsy, Tinky_Winky, Po, key1, key2, frame);
			prepareFilesForNewGame(screenFiles.front(), mySteps, myResult);
			continue;
		}

		if (frame % ghostspeed == 0) { //Every Second frame ghosts move
			ghostMove(Tinky_Winky, h, player1);
			ghostMove(Po, h, player1);
			writeFile += to_string(Tinky_Winky.getLastMove());
			writeFile += to_string(Po.getLastMove());

			if ((FruitMetEntity(Tinky_Winky, Po, Dipsy, player1, h) == true)) {
				Dipsy.sleepFruit(h);
				Dipsy.setLastMove(int(e_EntityAction::SLEEP));
				Dipsy.resetCounter();
			}
			if (Dipsy.getSleep() == false) { //Fruit not asleep
				ghostMove(Dipsy, h, player1);
				writeFile += to_string(Dipsy.getLastMove());

				if ((FruitMetEntity(Tinky_Winky, Po, Dipsy, player1, h) == true)) {
					Dipsy.sleepFruit(h);
					Dipsy.setLastMove(int(e_EntityAction::SLEEP));
					Dipsy.resetCounter();
				}
			}
			else {	// Fruit asleep
				if (Dipsy.getTurnCounter() == 50) {
					Dipsy.wakeUpFruit(h);
					Dipsy.setLastMove(int(e_EntityAction::WAKE_UP));
					writeFile += to_string(Dipsy.getLastMove());
					writeFile += " " + to_string(Dipsy.getY()) + " " + to_string(Dipsy.getX());
					Dipsy.setLastMove();
				}
				else
					writeFile += to_string(Dipsy.getLastMove());

				Dipsy.setTurnCounter(Dipsy.getTurnCounter() + 1);
			}
		}
		else { //Not ghosts turn
			writeFile += to_string(int(e_EntityAction::STAY));	//Ghost1 
			writeFile += to_string(int(e_EntityAction::STAY));	//Ghost2 

			if (Dipsy.getLastMove() == int(e_EntityAction::SLEEP))	//Fruit 
				writeFile += to_string(Dipsy.getLastMove());
			else
				writeFile += to_string(int(e_EntityAction::STAY));
		}

		mySteps << writeFile << " ";
		frame++;

		if (didGhostEatPacman(h, player1, Tinky_Winky, Po, key1, key2, running1) == true)
		{
			myResult << "D " << frame-1 << "\n";
			if (checkIfGameLost(player1, running1) == true) {
				displaylose();
				mySteps.close();
				myResult.close();
			}
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
	}
}

void SaveMode::prepareFilesForNewGame(string fileName, ofstream& mySteps, ofstream& myResult)
{

	string fixName = fileName;
	int i = 2;

	while (fixName[i] != '.') {
		i++;
	}
	fixName = fixName.substr(0, i);

	mySteps.open(fixName + ".steps", ios::trunc | ios::out);
	myResult.open(fixName + ".result", ios::trunc | ios::out);

}

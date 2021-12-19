#include "game.h"

bool game::isValid(int row, int col)
{
	return (row >= 0) && (row < ROWS) && (col >= 0) && (col < COLS);
}

bool game::isUnBlocked(char grid[][COLS], int row, int col)
{
	// Returns true if the cell is not blocked else false
	if (grid[row][col] == '#')
		return (false);
	else if (grid[row][col] == '!')
		return (false);
	else
		return (true);
}

bool game::isDestination(int row, int col, Pair dest)
{
	if (row == dest.first && col == dest.second)
		return (true);
	else
		return (false);
}

int game::calculateHValue(int row, int col, Pair dest)
{
	return abs(row - dest.first) + abs(col - dest.second);
}

Pair game::tracePath(cell cellDetails[][COLS], Pair dest)
{
	int row = dest.first;
	int col = dest.second;

	stack<Pair> Path;

	while (!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col)) {
		Path.push(make_pair(row, col));
		int temp_row = cellDetails[row][col].parent_i;
		int temp_col = cellDetails[row][col].parent_j;
		row = temp_row;
		col = temp_col;
	}
	int i = 0;
	Pair target;
	Path.push(make_pair(row, col));
	while (!Path.empty()) {
		Pair p = Path.top();
		if (i == 1) {
			target = p;
		}
		Path.pop();
		//printf("-> (%d,%d) ", p.first, p.second);
		//gotoxy(p.second, p.first+1);
		//cout << "*";
		i++;
	}

	return target;
}

Pair game::aStarSearch(char grid[][COLS], Pair src, Pair dest)
{
	
	// Create a closed list and initialise it to false which
	// means that no cell has been included yet This closed
	// list is implemented as a boolean 2D array
	bool closedList[ROWS][COLS];
	memset(closedList, false, sizeof(closedList));

	// Declare a 2D array of structure to hold the details
	// of that cell
	cell cellDetails[ROWS][COLS];

	int i, j;

	for (i = 0; i < ROWS; i++) {
		for (j = 0; j < COLS; j++) {
			cellDetails[i][j].f = 1000;
			cellDetails[i][j].g = 1000;
			cellDetails[i][j].h = 1000;
			cellDetails[i][j].parent_i = -1;
			cellDetails[i][j].parent_j = -1;
		}
	}

	// Initialising the parameters of the starting node
	i = src.first, j = src.second;
	cellDetails[i][j].f = 0;
	cellDetails[i][j].g = 0;
	cellDetails[i][j].h = 0;
	cellDetails[i][j].parent_i = i;
	cellDetails[i][j].parent_j = j;

	set<pPair> openList;

	openList.insert(make_pair(0, make_pair(i, j)));

	bool foundDest = false;
	Pair target;
	while (!openList.empty()) {
		pPair p = *openList.begin();

		// Remove this vertex from the open list
		openList.erase(openList.begin());

		// Add this vertex to the closed list
		i = p.second.first;
		j = p.second.second;
		closedList[i][j] = true;

		// To store the 'g', 'h' and 'f' of the 8 successors
		int gNew, hNew, fNew;

		//-----------(up) ------------

		// Only process this cell if this is a valid one
		if (isValid(i - 1, j) == true) {
			// If the destination cell is the same as the
			// current successor
			if (isDestination(i - 1, j, dest) == true) {
				// Set the Parent of the destination cell
				cellDetails[i - 1][j].parent_i = i;
				cellDetails[i - 1][j].parent_j = j;
				target = tracePath(cellDetails, dest);
				foundDest = true;
				return target;
			}
			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
			else if (closedList[i - 1][j] == false && isUnBlocked(grid, i - 1, j) == true) {
				gNew = cellDetails[i][j].g + 1;
				hNew = calculateHValue(i - 1, j, dest);
				fNew = gNew + hNew;

				// If it isn’t on the open list, add it to
				// the open list. Make the current square
				// the parent of this square. Record the
				// f, g, and h costs of the square cell
				//			 OR
				// If it is on the open list already, check
				// to see if this path to that square is
				// better, using 'f' cost as the measure.
				if (cellDetails[i - 1][j].f == FLT_MAX || cellDetails[i - 1][j].f > fNew) {
					openList.insert(make_pair(fNew, make_pair(i - 1, j)));

					// Update the details of this cell
					cellDetails[i - 1][j].f = fNew;
					cellDetails[i - 1][j].g = gNew;
					cellDetails[i - 1][j].h = hNew;
					cellDetails[i - 1][j].parent_i = i;
					cellDetails[i - 1][j].parent_j = j;
				}
			}
		}

		//-----------(down) ------------

		if (isValid(i + 1, j) == true) {

			if (isDestination(i + 1, j, dest) == true) {
				cellDetails[i + 1][j].parent_i = i;
				cellDetails[i + 1][j].parent_j = j;
				target = tracePath(cellDetails, dest);
				foundDest = true;
				return target;
			}

			else if (closedList[i + 1][j] == false && isUnBlocked(grid, i + 1, j) == true) {
				gNew = cellDetails[i][j].g + 1;
				hNew = calculateHValue(i + 1, j, dest);
				fNew = gNew + hNew;

				if (cellDetails[i + 1][j].f == FLT_MAX || cellDetails[i + 1][j].f > fNew) {
					openList.insert(make_pair(fNew, make_pair(i + 1, j)));
					cellDetails[i + 1][j].f = fNew;
					cellDetails[i + 1][j].g = gNew;
					cellDetails[i + 1][j].h = hNew;
					cellDetails[i + 1][j].parent_i = i;
					cellDetails[i + 1][j].parent_j = j;
				}
			}
		}

		//-----------(right) ------------

		if (isValid(i, j + 1) == true) {

			if (isDestination(i, j + 1, dest) == true) {
				cellDetails[i][j + 1].parent_i = i;
				cellDetails[i][j + 1].parent_j = j;
				target = tracePath(cellDetails, dest);
				foundDest = true;
				return target;
			}

			else if (closedList[i][j + 1] == false && isUnBlocked(grid, i, j + 1) == true) {
				gNew = cellDetails[i][j].g + 1;
				hNew = calculateHValue(i, j + 1, dest);
				fNew = gNew + hNew;

				if (cellDetails[i][j + 1].f == FLT_MAX || cellDetails[i][j + 1].f > fNew) {
					openList.insert(make_pair(fNew, make_pair(i, j + 1)));
					cellDetails[i][j + 1].f = fNew;
					cellDetails[i][j + 1].g = gNew;
					cellDetails[i][j + 1].h = hNew;
					cellDetails[i][j + 1].parent_i = i;
					cellDetails[i][j + 1].parent_j = j;
				}
			}
		}

		//-----------(left) ------------

		if (isValid(i, j - 1) == true) {

			if (isDestination(i, j - 1, dest) == true) {
				cellDetails[i][j - 1].parent_i = i;
				cellDetails[i][j - 1].parent_j = j;
				target = tracePath(cellDetails, dest);
				foundDest = true;
				return target;
			}

			else if (closedList[i][j - 1] == false && isUnBlocked(grid, i, j - 1) == true) {
				gNew = cellDetails[i][j].g + 1;
				hNew = calculateHValue(i, j - 1, dest);
				fNew = gNew + hNew;

				if (cellDetails[i][j - 1].f == FLT_MAX || cellDetails[i][j - 1].f > fNew) {
					openList.insert(make_pair(fNew, make_pair(i, j - 1)));
					cellDetails[i][j - 1].f = fNew;
					cellDetails[i][j - 1].g = gNew;
					cellDetails[i][j - 1].h = hNew;
					cellDetails[i][j - 1].parent_i = i;
					cellDetails[i][j - 1].parent_j = j;
				}
			}
		}
	}
}

char instructions[15][32] = {
	"+#############################+",
	"|  LEFT     |     a or A      |",
	"|#############################|",
	"|#############################|",
	"|  RIGHT    |     d or D      |",
	"|#############################|",
	"|#############################|",
	"|  UP       |     w or W      |",
	"|#############################|",
	"|#############################|",
	"|  DOWN     |     x or X      |",
	"|#############################|",
	"|#############################|",
	"|  STAY     |     s or S      |",
	"+#############################+"
}; //Displayes game keys

char win[9][63] = {
	"##########################################################",
	"#                                                        #",
	"#  #   #  #####  #   #     #           #   #  #     #    #",
	"#   # #   #   #  #   #      #         #    #  # #   #    #",
	"#    #    #   #  #   #       #   #   #     #  #  #  #    #",
	"#    #    #   #  #   #        # # # #      #  #   # #    #",
	"#    #    #####  #####         #   #       #  #     #    #",
	"#                                                        #",
	"##########################################################",
};

char lose[9][63] = {
	"##########################################################",
	"#                                                        #",
	"#  #   #  #####  #   #     #      #####  #####  #####    #",
	"#   # #   #   #  #   #     #      #   #  #      #        #",
	"#    #    #   #  #   #     #      #   #  #####  #####    #",
	"#    #    #   #  #   #     #      #   #      #  #        #",
	"#    #    #####  #####     #####  #####  #####  #####    #",
	"#                                                        #",
	"##########################################################",
};

string game::choices[4] = {
	"1 - Start a new game",
	"2 - Choose map",
	"8 - Instructions and keys",
	"9 - Quit" };

game::game()
{
	numGhosts = 3;
	speed = 100;
	ghostspeed = 2;      //means X2 slower than the pacman
	startLives = 3;
	oneMap = false;
}

void game::gotoxy(int x, int y)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { x, y };

	SetConsoleCursorPosition(hStdout, position);
}

void game::displayChoices() const
{
	for (auto x : choices)
		cout << x << "\n";
}

void game::displayChoices(short curr) const {
	for (auto x : choices) {
		if (x != choices[curr])
			cout << x << "\n";
	}
}

void game::goToOption(char &input)
{
	clearScreen();

	switch (input) {
	case char(e_OptionInput::PLAY):
		gameLoop();
		input = char(e_OptionInput::DEFAULT);
		break;
	case char(e_OptionInput::CHOOSE_MAP) :
		chooseMap();
		clearScreen();
		gameLoop();
		input = char(e_OptionInput::DEFAULT);
		break;
	case char(e_OptionInput::INSTRUCTIONS) :
		displayInstructions();
		clearScreen();
		input = char(e_OptionInput::DEFAULT);
		break;
	case char(e_OptionInput::EXIT) :
		break;

	default:
		displayChoices();
		input = _getch();
		while (input != char(e_OptionInput::PLAY) 
			&& input != char(e_OptionInput::CHOOSE_MAP)
			&&	input != char(e_OptionInput::INSTRUCTIONS)
			&& input != char(e_OptionInput::EXIT))
		{
			if (_kbhit())
				input = _getch();
		}
		break;
	}
}

void game::clearScreen() const
{
	/*HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { 0, 0 };
	SetConsoleCursorPosition(hStdout, position);
	position = { 0,0 };
	SetConsoleCursorPosition(hStdout, position);*/
	system("CLS");
}

void game::displayInstructions() const
{
	for (int i = 0; i < 15; i++) {
		printf("%s\n", instructions[i]);
	}
	cout << "\nUse the controls above to move the pacman." << endl;
	cout << "Eat all the breadcrumbs to win the game." << endl;
	cout << "You lose 1 life each time the ghost hunts you." << endl;
	cout << "Once lost all 3 lifes, you lose and the game ends." << endl;
	cout << "Good luck!\n\n";
	cout << "Press any key to go back to the menu..." << endl;
	short flag;
	flag = _getch();
}

void game::displaywin() const
{
	for (int i = 0; i < 9; i++) {
		printf("%s\n", win[i]);
		Sleep(100);
	}
	system("pause");
}

void game::displaylose() const
{
	for (int i = 0; i < 9; i++) {
		printf("%s\n", lose[i]);
		Sleep(100);
	}
	system("pause");
}

string game::getmapNum() const {
	return mapNum;
}

void game::setmapNum(string f) {
	mapNum = f;
}

void game::gameLoop() {

	char ghostDiff = chooseGhostsDifficulty();
	bool running1 = true;
	bool checkInput;
	char key1, key2;
	int currMap = 1;
	unsigned long long int frame = 0;   //can get realy high numbers...

	pacman player1;
	ghost Tinky_Winky(ghostDiff);
	ghost Po(ghostDiff);
	fruit Dipsy;
	map h;

	if (getOneMap()) 
		h.setFilename(getmapNum()); //Choose specific map to play once

	prepareForNewGame(h, player1, Dipsy, Tinky_Winky, Po, key1, key2); 


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
				h.pause(h,getLegend().first, getLegend().second);
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
			}

			//Pacman move
			else if (key1 == 'w' || key1 == 'W')
				player1.move_up(h);
			else if (key1 == 'x' || key1 == 'X')
				player1.move_down(h);
			else if (key1 == 'a' || key1 == 'A')
				player1.move_left(h);
			else if (key1 == 'd' || key1 == 'D')
				player1.move_right(h);
			else if (key1 == 's' || key1 == 'S')
				player1.stop(h);
			else {
				key1 = key2;
				continue;
			}
			checkInput = true;
		}
		key2 = key1;

		if (didGhostEatPacman(h, player1, Tinky_Winky, Po, key1, key2,running1) == true)
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
				prepareForNewGame(h, player1, Dipsy, Tinky_Winky, Po, key1, key2);
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

		if (didGhostEatPacman(h, player1, Tinky_Winky, Po, key1, key2,running1) == true)
		{
			continue;
		}
		player1.displayPoints(h,getLegend().first,getLegend().second);
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

bool game::didGhostEatPacman(map& h, pacman& player1, ghost& Tinky_Winky, ghost& Po, char& key1, char& key2,bool& running1) {
	if ((Tinky_Winky.getX() == player1.getX() && Tinky_Winky.getY() == player1.getY()) || (Po.getX() == player1.getX() && Po.getY() == player1.getY()))
	{	//If reached this point, one life is lost
		player1.setLives(player1.getLives() - 1);
		Sleep(4000);
		player1.displayLives(h,getLegend().first, getLegend().second);
		key1 = 's', key2='s';
		//Resets Entities
		player1.resetEntity();
		switch (numGhosts - 1) {
		case 2:
			Tinky_Winky.display(h.getmapat(Tinky_Winky.getY(), Tinky_Winky.getX()));
			Tinky_Winky.resetEntity();
		case 1:
			Po.display(h.getmapat(Po.getY(), Po.getX()));
			Po.resetEntity();
		}
		if (player1.getLives() == 0)	//Check if Game lost
		{
			clearScreen();
			displaylose();
			setOneMap(false);
			running1 = false;
		}
		return true;
	}
	return false;
}
void game::prepareForNewGame(map& h, pacman& player1, fruit& Dipsy, ghost& Tinky_Winky, ghost& Po, char& key1, char& key2) {
	//Resets the map and the entities to their default locations
	h.fillmap();
	readEntities(h, player1, Tinky_Winky, Po);

	key1 = 's', key2 = 's';
	h.ShowMap();
	player1.setDotsate(0);
	player1.displayLives(h, getLegend().first, getLegend().second);
	player1.resetEntity();
	player1.display();
	h.setmapat(player1.getY(), player1.getX(), player1.getSymbol());

	switch (numGhosts) { //ResetsGhosts
	case 3:
		Dipsy.resetLocation(h);
		Dipsy.display();
	case 2:
		Tinky_Winky.resetEntity();
		Tinky_Winky.display();
	case 1:
		Po.resetEntity();
		Po.display();
	}
}

char game::chooseGhostsDifficulty() {
	clearScreen();
	cout << "Please select ghost difficulty:" << endl;
	cout << "(a) BEST (b) GOOD and (c) NOVICE" << endl;
	
	char input;
	cin >> input;

	while (input != char(e_GhostDiff::BEST)
		&& input != char(e_GhostDiff::GOOD)
		&& input != char(e_GhostDiff::NOVICE)) 
	{
		cout << "invalid Input" << endl;
		cin >> input;
	}
	clearScreen();
	return input;
}

void game::ghostMove(ghost& currGhost, map& h, pacman& player1) {

	switch (currGhost.getDifficulty())
	{
		case int(e_GhostDiff::NOVICE) :
		{
			if (currGhost.getTurnCounter() % 20 == 0) { //Random move every 20 turns
				currGhost.setLastMove();
			}
			currGhost.move_rand(h);
			break;
		}
		//Ghost difficulty is GOOD or BEST

		case int(e_GhostDiff::GOOD) :
		{
			if (currGhost.getTurnCounter() % 20 == 0) {  //Every 20's turn act random for 5 turns
				currGhost.move_rand(h);
				currGhost.setGoodCounter(1);
				break;	//Move like NOVICE and exit switch
			}
			else if (1<=currGhost.getGoodCounter()&& 
						currGhost.getGoodCounter() <= 5) { 
				currGhost.move_rand(h);
				currGhost.setGoodCounter(currGhost.getGoodCounter() + 1);
				break; //Move like NOVICE and exit switch
			}
			if (currGhost.getGoodCounter() == 6) { //Moved rand for 5 turns, resets to "BEST" behavior
				currGhost.setGoodCounter(0);
				currGhost.setTurnCounter(1);
			}
			BestMove(currGhost, h, player1);
			break;
		}
		case int(e_GhostDiff::BEST) : //Chasing Pacman
		{
			BestMove(currGhost, h, player1);
			break;
		}
	}
	currGhost.setTurnCounter(currGhost.getTurnCounter() + 1);
}

void game::BestMove(ghost& currGhost, map&h, pacman& player1) {
	Pair move, src, dest;
	short nextX, nextY;
	dest = make_pair(player1.getY(), player1.getX());

	src = make_pair(currGhost.getY(), currGhost.getX());
	if (dest == src)
		return;

	move = aStarSearch(h.board, src, dest);
	nextY = (short)move.first;
	nextX = (short)move.second;
	currGhost.move(nextX, nextY);
}

bool game::FruitMetEntity(ghost& Tinky_Winky, ghost& Po, fruit& Dipsy, pacman& player1, map& h) {
	
	if (Dipsy.getX() == player1.getX() && Dipsy.getY() == player1.getY()) { //Fruit met pacman
		int score = (Dipsy.getSymbol() - '0');
		player1.setPoints(player1.getPoints() + score);
		return true;
	}
	
	else if ((Tinky_Winky.getX() == Dipsy.getX() && Tinky_Winky.getY() == Dipsy.getY()) || (Po.getX() == Dipsy.getX() && Po.getY() == Dipsy.getY()) || Dipsy.getTurnCounter() == 60) {
		//If Fruit ran out of time or hit a ghost
		return true;
	}
	return false;
}

void game::chooseMap() {

	cout << "Please choose a map number: "<< endl;
	cout << "1" << endl << "2" << endl << "3" << endl;
	
	cin >> mapNum;
	while (mapNum != "1" && mapNum != "2" && mapNum != "3") {
		cout << "Please enter a number between 1-3" << endl;
		cin >> mapNum;
	}
	oneMap = true;
	cout << "You chose map number:"<<mapNum<< endl<<"Good Luck!"<<endl;
	system("pause");

}

bool game::getOneMap() const {
	return oneMap;
}
void game::setOneMap(bool isOneMap) {
	oneMap = isOneMap;
}

void game::readEntities(map& h, pacman& player1, ghost& ghost1, ghost& ghost2) {
	int rows = h.getHeight();
	int cols = h.getWidth();
	int ghostCounter = 0;
	for (int i = 0; i <rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (h.board[i][j] == '@')
				player1.setDefault(j, i);
			else if (h.board[i][j] == '$') {
				if (ghostCounter == 0)
					ghost1.setDefault(j, i);
				else
					ghost2.setDefault(j, i);
				ghostCounter++;
			}
			else if (h.board[i][j] == '&') {
				setLegend(j, i);
				j = cols;
			}
		}
	}
}

void game::setLegend(int x, int y) {
	legend.first = x;
	legend.second = y;
}

Pair game::getLegend() {
	return legend;
}


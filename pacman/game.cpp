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
	mode = char(e_GameMode::SIMPLE);
	numOfScreens = 0;
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
		setOneMap(true);
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

void game::gameLoop(bool silent) {

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
	
	resetScreens();		//Resets Queue of Screens
	getFiles();			//Fill Queue with screen files
	
	if (getOneMap()) {
		chooseMap();
		string curr = showQIndex(stoi(mapNum));

		h.setFilename(curr); //Choose specific map to play once
	}
	else
		h.setFilename(screenFiles.front()); //Choose first map in alphabetical queue to play 

	prepareForNewGame(h, player1, Dipsy, Tinky_Winky, Po, key1, key2, frame); 


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
				checkInput = true;
			}

			//If pacman moved, return true ,if invalid key pressed returns false
			else if (pacmanMove(player1, key1, key2, h))
					checkInput = true;
				else
					continue;
			
		}
		key2 = key1;
		//TODO//if (save) game.mode == "save" Save !load put move in steps file

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
				screenFiles.pop();	
				if (screenFiles.empty()) {
					displaywin();
					running1 = false;
					continue;
				}
				cout << "Good luck in the next map" << endl;
				system("pause");
				clearScreen();
				h.setFilename(screenFiles.front());    //Loades next map
				prepareForNewGame(h, player1, Dipsy, Tinky_Winky, Po, key1, key2,frame);
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
void game::prepareForNewGame(map& h, pacman& player1, fruit& Dipsy, ghost& Tinky_Winky, ghost& Po, char& key1, char& key2, unsigned long long int& frame) {
	//Resets the map and the entities to their default locations
	h.fillmap();
	readEntities(h, player1, Tinky_Winky, Po);

	frame = 0;
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
	calcDirection(currGhost, currGhost.getX(), currGhost.getY(), nextX, nextY);
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

	queue<string> copyQ = screenFiles;

	cout << "Please choose the number of the desired map: " << endl;

	showq(screenFiles);
	cin >> mapNum;

	bool flag = false;

	while (!flag) {

		if (!is_number(mapNum)) {
			cout << "Invalid input " << endl;
			cin >> mapNum;
		}
		else {
			int num = stoi(mapNum);
			if (num > screenFiles.size() || num < 1) {
				cout << "Invalid input " << endl;
				cin >> mapNum;
			}
			else
				flag = true;

		}
	}
	
	cout << "You chose option number: " << mapNum << endl << "Good Luck!" << endl;

	system("pause");
	clearScreen();

}

bool game::is_number(const string& s) {
	return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
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

void game::setMode(char m) {
	this->mode = m;
}

bool game::pacmanMove(pacman& pacman, char& key1, char& key2,map& h) {
	
	switch (key1) {
	case 'w': 	case 'W': 
		pacman.move_up(h);
		pacman.setLastMove(0);
		break;

	case 'x':case 'X':
		pacman.move_down(h);
		pacman.setLastMove(1);
		break;

	case 'a': 	case 'A':
		pacman.move_left(h);
		pacman.setLastMove(2);
		break;

	case 'd': 	case 'D':
		pacman.move_right(h);
		pacman.setLastMove(3);
		break;

	case 's': 	case 'S':
		pacman.stop(h);
		pacman.setLastMove(4);
		break;

	default:
		key1 = key2;
		return false;
	}
	return true;
}

void game::runMenu() {

	char input = 0;
	while (input != '9') {
		this->goToOption(input);
	}
}

void game::getFiles() {

	for (const auto& entry : filesystem::directory_iterator(".")) {
		if (entry.path().string().ends_with("screen")) {
			screenFiles.push(entry.path().string());
			numOfScreens++;
		}
	}
}

void game::showq(queue<string> q)
{
	queue<string> g = q;
	int i = 1;
	while (!g.empty()) {
		cout << i << ". " << g.front() << endl;
		g.pop();
		i++;
	}
	cout << '\n';
}

string game::showQIndex(int index) {
	
	for (int i = 1; i < index; i++) {
		screenFiles.pop();
	}
	return screenFiles.front();
}

void game::resetScreens() {
	screenFiles = {};	
	numOfScreens = 0;
}

void game::calcDirection(ghost& curr, int srcX, int srcY, int nextX, int nextY) {

	if (srcX - nextX < 0) 
		curr.setLastMove(int(e_EntityAction::RIGHT));
	else if (srcX - nextX > 0)
		curr.setLastMove(int(e_EntityAction::LEFT));
	else if (srcY - nextY < 0)
		curr.setLastMove(int(e_EntityAction::DOWN));
	else if (srcY - nextY > 0)
		curr.setLastMove(int(e_EntityAction::UP));
	else 
		curr.setLastMove(int(e_EntityAction::STAY));
	
}
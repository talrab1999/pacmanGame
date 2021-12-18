
#include "map.h"

map::map()
{
	width = 61;
	height = 19;
	length = width * height;
	filename = "map.txt";
}

void map::gotoxy(short i, short j) const
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { i, j };
	SetConsoleCursorPosition(hStdout, position);
}

short map::getWidth() const
{
	return width;
}

short map::getHeight() const
{
	return height;
}

short map::getLength() const
{
	return length;
}

string map::getFilename() const
{
	return filename;
}

char map::getmapat(short y, short x) const
{
	return map_vec[x + width * y];
}

void map::setWidth(short w)
{
	width = w;
}

void map::setHeight(short h)
{
	height = h;
}

void map::setFilename(string f)
{
	filename = f;
}

void map::setmapat(short y, short x, char c) {
	map_vec[x + width * y] = c;
}

void map::fillmap()
{
	ifstream INF(filename);
	string line = "";
	if (!INF) {
		cout << "ERROR " << filename << " COULD NOT BE OPENED!";
	}
	while (getline(INF, line)) {
		for (short i = 0; i < width; i++) {
			if (line[i] == ' ')
				line[i] = '.';
			else if (line[i] == '%')
				line[i] = ' ';
		}
		for (short i = 0; i < width; i++) {
			map_vec.push_back(line[i]);
		}
	}
	INF.close();
}

void map::fillboard() {

	ifstream INF(filename);
	string line = "";
	if (!INF) {
		cout << "ERROR " << filename << " COULD NOT BE OPENED!";
	}
	int i = 0;
	while (getline(INF, line)) {
		for (int j = 0; j < width; j++) {
			board[i][j] = line[j];
		}
		i++;
	}
}

void map::test() {
	gotoxy(0, 0);
	for (int i = 0; i < height; i++) {
		printf("\n");
		for (int j = 0; j < width; j++) {
			cout << board[i][j];
		}
	}

}

void map::ResetMap()
{
	map_vec.clear();
	gotoxy(0, 0);
	fillmap();
}

void map::ShowMap()
{
	for (short i = 1; i <= length; i++)
	{

		if (i % width == 0)
		{
			//setTextColor(BLUE);
			cout << "\n";
		}
		else
		{
			/*if(map_vec[i - 1] == '#')
				setTextColor(BLUE);
			else
				setTextColor(WHITE);*/
			cout << map_vec[i - 1];
		}

	}
}


void map::pause(map& h) {
	gotoxy(0, h.getHeight() + 1);
	cout << "Game paused, press ESC again to continue" << endl;
}

void map::unpause(map& h) {
	gotoxy(0, h.getHeight() + 1);
	cout << "                                           " << endl;
}
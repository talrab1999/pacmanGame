#include "Entity.h"
Entity::Entity()
{
	x = 0;
	y = 0;
	lives = 1;
	symbol = '%';
	//color = WHITE;
}

Entity::Entity(short X, short Y, short L, char S, Color COLOR)
{
	x = X;
	y = Y;
	lives = L;
	symbol = S;
	//color = COLOR;
}


void Entity::setX(short val)
{
	x = val;
}

void Entity::setY(short val)
{
	y = val;
}

short Entity::getX() const
{
	return x;
}

short Entity::getY() const
{
	return y;
}

void Entity::setLives(short val)
{
	lives = val;
}

void Entity::setSymbol(char val)
{
	symbol = val;
}

short Entity::getLives() const
{
	return lives;
}

char Entity::getSymbol() const
{
	return symbol;
}

void Entity::setColor(Color c) {
	color = c;
}

/*void Entity::setTextColor(Color colorToSet) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)colorToSet);
}*/

void Entity::gotoxy(short i, short j) const
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { i, j };
	SetConsoleCursorPosition(hStdout, position);
}

void Entity::display() {
	gotoxy(x, y);
	//setTextColor(color);
	cout << symbol;
}

void Entity::display(char c) {
	gotoxy(x, y);
	//setTextColor(color);
	cout << c;
}

void Entity::replace() const {
	gotoxy(x, y);
}


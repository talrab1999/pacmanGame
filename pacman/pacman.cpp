#include "pacman.h"

pacman::pacman()
{
	setX(13);
	setY(15);
	setLives(3);
	setSymbol('@');
	//setColor(Color::YELLOW);
	points = 0;
	dotsate = 0;
}

void pacman::setDotsate(short d)
{
	dotsate = d;
}

short pacman::getDotsate() const
{
	return dotsate;
}

void pacman::setPoints(short p) {
	points = p;
}

short pacman::getPoints() const {
	return points;
}

void pacman::displayPoints(map& m,int x, int y) const {
	gotoxy(x, y+1);
	cout << "Points: " << points;
}

void pacman::displayLives(map& m,int x, int y)
{
	gotoxy(x,y);
	cout << "Lives:             ";
	gotoxy(x+8,y);
	for (short i = this->getLives(); i > 0; i--) {
		cout << "@ ";
	}
}



void pacman::move_up(map& m)
{
	if (m.getmapat(getY() - 1, getX()) == '.')
	{
		setY(getY() - 1);
		points++;
		dotsate++;
	}
	else if (m.getmapat(getY() - 1, getX()) == ' ')
	{
		setY(getY() - 1);
	}
	else if (m.getmapat(getY() - 1, getX()) == '!')
	{
		setY(17);
	}
}

void pacman::move_down(map& m)
{
	if (m.getmapat(getY() + 1, getX()) == '.')
	{
		setY(getY() + 1);
		points++;
		dotsate++;
	}
	else if (m.getmapat(getY() + 1, getX()) == ' ')
	{
		setY(getY() + 1);
	}
	else if (m.getmapat(getY() + 1, getX()) == '!')
	{
		setY(1);
	}
}

void pacman::move_left(map& m)
{
	if (m.getmapat(getY(), getX() - 1) == '.')
	{
		setX(getX() - 1);
		points++;
		dotsate++;
	}
	else if (m.getmapat(getY(), getX() - 1) == ' ')
	{
		setX(getX() - 1);
	}
	else if (m.getmapat(getY(), getX() - 1) == '!')
	{
		setX(58);
	}
}
void pacman::move_right(map& m)
{
	if (m.getmapat(getY(), getX() + 1) == '.')
	{
		setX(getX() + 1);
		points++;
		dotsate++;
	}
	else if (m.getmapat(getY(), getX() + 1) == ' ')
	{
		setX(getX() + 1);
	}
	else if (m.getmapat(getY(), getX() + 1) == '!')
	{
		setX(1);
	}

}

void pacman::stop(map& m)
{
	setX(getX());
	setY(getY());
}

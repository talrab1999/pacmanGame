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

short pacman::getPoints() const {
	return points;
}

void pacman::displayPoints(map& m) const {
	gotoxy(m.getWidth() + 1, m.getHeight());
	cout << "Points: " << points;
}

void pacman::displayLives(map& m)
{
	gotoxy(m.getWidth() + 1, m.getHeight() - 1);
	cout << "Lives:                     ";
	gotoxy(m.getWidth() + 8, m.getHeight() - 1);
	for (short i = this->getLives(); i > 0; i--) {
		cout << "@ ";
	}
}

/*void pacman::whathappened(map& m)
{
	gotoxy(m.getWidth() + 1, m.getHeight() - 3);
	cout << "EAT???";
	Sleep(4000);
	gotoxy(m.getWidth() + 1, m.getHeight() - 3);
	cout << "      ";
}*/

void pacman::reset()
{
	setX(13);
	setY(15);
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

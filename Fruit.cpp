#include "Fruit.h"
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method sets the figure of a fruit.

Fruit::Fruit(bool _silent) :MovingObj(_silent)
{
	int digit;
	digit = rand() % 5;
	figure =(digit + '5');
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method moves the fruit on the board.

void Fruit::moveMovingObj(char ch)
{
	if (color)
		setTextColor(Color::WHITE);
	MovingObj::moveMovingObj(ch);
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method write the coordinates of the fruit to the a string.

void Fruit::addCoord(int y, int x)
{
	moves += convertNum(y);
	moves.push_back(',');
	moves += convertNum(x);
	moves.push_back(',');
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method read the coordinate of the fruit from the txt file.

int Fruit::readCoord()
{
	int coord = 0;
	char temp = readMove();
	while (temp != ',')
	{
		coord = 10 * coord + (temp - '0');
		changePlace();
		temp = readMove();
	}
	changePlace();
	return coord;
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method read the time of the fruit's revive from the txt file.

void Fruit::writeTimeTo()
{
	int timeTo = 0;
	char temp = readMove();
	while (temp != '.' &&temp != 'k' && place != moves.size())
	{
		timeTo = 10 * timeTo + (temp - '0');
		changePlace();
		temp = readMove();
	}
	changePlace();
	timeToApear = timeTo;
}
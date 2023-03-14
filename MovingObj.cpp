#include "MovingObj.h"
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method set a moving object to be with or without colors
void MovingObj::setMovingObjColor(bool _color)
{
	color = _color;
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method sets a direction for the ghost's eyes.

void MovingObj::continueOldDir(const int& dir)
{
	Eyes.move(dir, false);
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method prints the Ghost's figure on the board.

void MovingObj::drawMovingObj()
{
	if (!silent)
	{
		if (color)
			setTextColor(Color::LIGHTRED);
		body.draw(figure);
	}
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/

int MovingObj::updateEyes()
{
	return Eyes.moveRandom();
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void MovingObj::setEyesLocation(int y, int x)
{
	Eyes.setXY(y, x);
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void MovingObj::initLocation(const int& y, const int& x)
{
	body.setXY(y, x);
	Eyes.setXY(y, x);
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method updates the max values for a moving object.

void MovingObj::UpdateBorders(int _Maxrow, int MaxCol)
{
	body.setMaxRow(_Maxrow);
	Eyes.setMaxRow(_Maxrow);
	body.setMaxCol(MaxCol);
	Eyes.setMaxCol(MaxCol);
}

void MovingObj::moveMovingObj(char ch)
{
	gotoxy(getMovingObjBodyX(), getMovingObjBodyY());
	if(!silent)
		cout << ch;
	gotoxy(getMovingObjEyesX(), getMovingObjEyesY());
	initLocation(getMovingObjEyesY(), getMovingObjEyesX());
	drawMovingObj();
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method moves the index of the string forward.

void MovingObj::changePlace(int i)
{
	place = i * place + i;
}

void MovingObj::addTime(int time)
{
	moves += convertNum(time);
	moves.push_back('.');
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method converts chars to a number.

string MovingObj::convertNum(int num)
{
	string str;
	while (num != 0)
	{
		string temp;
		temp.push_back(num % 10 + '0');
		str.insert(0, temp);
		num /= 10;
	}
	return str;
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method fill the moves string.

void MovingObj::fillString(string& str)
{
	moves.clear();
	moves = str.substr(2, str.size() - 2);
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method reads a move from the string.

char MovingObj::readMove()
{
	if (getPlace() < moves.size())
		return moves[getPlace()];
	else
		return (int)Directions::STAY + '0';
}


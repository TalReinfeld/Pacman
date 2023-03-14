#include "Point.h"
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method draws a shape.

void Point::draw(char ch)const
{
	gotoxy(x, y);
	cout << ch << endl;
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method moves the ghost randomly.

int  Point::moveRandom()
{
	int dir = rand() % 4;
	move(dir, false);
	return dir;
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method translates a direction to a new coordinate.

void Point::move(int direction, bool flag)
{

	switch (direction) {
	case (int)Directions::UP:
		--y;
		if (flag == true)
		{
			if (y < minRow) {
				y = maxRow ;
			}
		}
		break;
	case (int)Directions::DOWN:
		++y;
		if (flag == true)
		{
			if (y > maxRow ) {
				y = minRow;
			}
		}
		break;
	case (int)Directions::LEFT:
		--x;
		if (flag == true)
		{
			if (x < 0) {
				x = maxCol - 1;
			}
		}
		break;
	case (int)Directions::RIGHT:
		++x;
		if (flag == true)
		{
			if (x > maxCol - 1) {
				x = 0;
			}
		}
		break;

	case (int)Directions::STAY:
		break;
	}

}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/


void Point::setXY(int _y, int _x)
{
	y = _y;
	x = _x;
}
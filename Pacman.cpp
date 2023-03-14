#include "Pacman.h"
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method moves the pacman.

void Pacman::moveMovingObj(char ch)
{
	body.draw(ch);
	body.move(direction, true);
	drawMovingObj();
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method reurns the direction that the user's key represents.

int Pacman::getDirection(char key) const
{
	int i;
	for (i = 0; i < keyBoardSize; i++)
	{
		if (key == arrowKeys[i] || key == arrowKeys[i] - 32)
			return i;

	}
	return -1;
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void Pacman::setDirection(const int& dir)
{
	direction = dir;
}

void Pacman::updateEyes(int dir)
{
	Eyes.move(dir, true);
}


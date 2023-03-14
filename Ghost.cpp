#include "Ghost.h"

/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method moves a ghost on the board.

void Ghost::moveMovingObj(char ch)
{
	if (color)
	{
		setTextColor(Color::WHITE);
		if (ch == '$')
			setTextColor(Color::LIGHTRED);
	}
	MovingObj::moveMovingObj(ch);
}


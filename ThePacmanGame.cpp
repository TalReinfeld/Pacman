#include "ThePacmanGame.h"
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method set the game to be with or without colors
void ThePacmanGame::setGameColor(bool _color)
{
	color = _color;
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method initializes the game.

void ThePacmanGame::init()
{
	if (board.getCountOfFiles() != 0 && !board.GetError())
	{
		if (load)
		{
			if (!afterDeath)
			{
				SLFile.readColor();
				fillStrings();
				changeAfterDeath();
			}
		}
		hideCursor();
		board.setBoardColor(color);
		board.drawDisplayBoard();
		pacman.setDirection((int)Directions::STAY);
		pacman.setMovingObjColor(color);
		fruit.setMovingObjColor(color);
		initPacmanAndGhost();
	}
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method fill the moves string of an object.

void ThePacmanGame::fillStrings()
{
	string temp;
	SLFile.readStrFromFile(temp);
	pacman.fillString(temp);
	SLFile.readStrFromFile(temp);
	fruit.fillString(temp);
	for (int i = 0; i < board.getCountOfGhosts(); i++)
	{
		SLFile.readStrFromFile(temp);
		g[i].fillString(temp);
	}
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method runs the game.

void ThePacmanGame::run(bool flag)
{
	if (save)
		SLFile.colorMode(color);
	//if (load)
	//	giveMoves();//need to take the moves from the file
	char key = (int)Borders::Minimum;
	int dir = (int)Directions::STAY;
	int oldDir = (int)Directions::STAY;
	int count = 0, fruitCounter = 0, needAFruit = 0, tooMuch = 30, now = rand() % tooMuch;
	int timeTodisapear = 0;
	int num;
	do {

		if (save || load)
			time++;
		if (board.getCountOfFiles() != 0 && !board.GetError())
		{
			FruitOnTheScreen(fruitCounter, now, needAFruit, num, timeTodisapear);
			makeFullCycle(dir, oldDir, key, needAFruit, now, timeTodisapear);
			if (fruitCounter == tooMuch)
				fruitCounter = 0;
			fruitCounter++;
			if (board.getCountOfBreadCrumbs() == 0 && flag == false)
			{
				++count;
				if (count != board.getCountOfFiles())
				{
					NewLevel(count, flag, needAFruit, now, tooMuch);
				}
			}
		}
	
	} while ((lives > (int)Borders::Minimum && count!=board.getCountOfFiles())&&!(flag==true && board.getCountOfBreadCrumbs()==0)&& (board.getCountOfFiles() != 0) && !board.GetError());
	endGame(count, flag);
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method manage the end of the game.

void ThePacmanGame::endGame(int& count, bool& flag)
{
	if (board.GetError());
	else
	{
		if (save)
			emptyPage();
		system("cls");
		if ((count == board.getCountOfFiles() && board.getCountOfFiles() != 0) || (flag == true && board.getCountOfBreadCrumbs() == 0))
		{
			if (save)
				SLFile.writeToResults('W', time);
			if (load && silent)
			{
				if (SLFile.checkWhatHappend() != 'W' || time != SLFile.getTime())
					test = false;
			}
			if(!silent)
				victory();
		}
		else if (board.getCountOfFiles() == 0)
			cout << "Error No Files";
		else
		{
			if (save)
				SLFile.writeToResults('L', time);
			if (load && silent)
			{
				if (SLFile.checkWhatHappend() != 'L' || time != SLFile.getTime())
					test = false;
			}
			if(!silent)
				gameover();
		}
		if (color)
			setTextColor(Color::LIGHTGREY);
		if (load && silent)
		{
			system("cls");
			cout << "test " << (test ? "passed" : "failed");
		}
		Sleep(3000);
		system("cls");
	}

}

/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method incharge of the fruit appearance in the game.

void ThePacmanGame::FruitOnTheScreen(int& fruitCounter,int& now,int& needAFruit,int& num,int& timeTodisapear)
{

	if (load)
	{
		if (!fruit.getLifeSwitch())
		{
			fruit.writeTimeTo();
			fruit.changeSwitch();
		}
		if (time == fruit.getTimeTo())
		{
			needAFruit = 1;
			fruit.setFigure(fruit.readMove() - '5');
			fruit.changePlace();
			fruit.initLocation(fruit.readCoord(), fruit.readCoord());
		}
	}
	else
	{
		if (fruitCounter == now && needAFruit == 0)
		{
			int y = rand() % board.getPoint((int)Locations::MAXSIZE).getY(), x = rand() % board.getPoint((int)Locations::MAXSIZE).getX();
			needAFruit = 1;
			num = rand() % 5;
			fruit.setFigure(num);
			while (board.getFigure(y, x) == WALL || ((y < board.getPoint((int)Locations::DETAILSLOCATION).getY() + 3 && y >= board.getPoint((int)Locations::DETAILSLOCATION).getY())) && (x >= board.getPoint((int)Locations::DETAILSLOCATION).getX() && x < board.getPoint((int)Locations::DETAILSLOCATION).getX() + 20))
			{
				y = rand() % (board.getPoint((int)Locations::MAXSIZE).getY());
				x = rand() % board.getPoint((int)Locations::MAXSIZE).getX();
			}
			fruit.initLocation(y, x);
			if (save)
			{
				fruit.addMove((char)Objects::REVIVE);
				fruit.addTime(time);
				fruit.addMove(num + '5');
				fruit.addCoord(x, y);
			}
		}
		if (needAFruit == 1)
			timeTodisapear++;
	}
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method loads to the next level.

void ThePacmanGame::NewLevel(const int& count,const bool& flag,int& needAFruit,int& now,int& tooMuch)
{
	system("cls");
	if (!silent)
	{
		cout << "Level: " << count + 1;
		Sleep(400);
		system("cls");
	}
	oldGhostCount = board.getCountOfGhosts();
	if (save)
		SLFile.writeToResults('N', time);
	if (load && silent)
	{
		if (SLFile.checkWhatHappend() != 'N' || time != SLFile.getTime())
			test = false;
	}
	Board FreeBoard(flag, "a", silent, count);
	board = FreeBoard;
	if (save)
	{
		fruit.addMove((char)Objects::KILL);
		emptyPage();
		SLFile.closeFiles();
		SLFile.openFiles(save, load, board.getFileName(count));
		if (oldGhostCount > board.getCountOfGhosts())
			ghostCount = board.getCountOfGhosts();
	}
	pacman.UpdateBorders(board.getPoint((int)Locations::MAXSIZE).getY(), board.getPoint((int)Locations::MAXSIZE).getX());
	fruit.UpdateBorders(board.getPoint((int)Locations::MAXSIZE).getY(), board.getPoint((int)Locations::MAXSIZE).getX());
	for (int i = 0; i < board.getCountOfGhosts(); i++)
	{
		g[i].UpdateBorders(board.getPoint((int)Locations::MAXSIZE).getY(), board.getPoint((int)Locations::MAXSIZE).getX());
	}
	if(!load)
	{
		needAFruit = 0;
		now = rand() % tooMuch;
	}
	if (load)
	{
		pacman.restartObj();
		fruit.restartObj();
		for (int i = 0; i < board.getCountOfGhosts(); i++)
			g[i].restartObj();

		SLFile.closeFiles();
		SLFile.openFiles(save, load, board.getFileName(count));
		changeAfterDeath();
	}
	newLevel = true;
	init();
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method initialized the moves string of an object in the game.

void ThePacmanGame::emptyPage()
{
	SLFile.writeMoves(pacman.myMoves(), (char)Objects::PACMAN);
	pacman.restartObj();
	SLFile.writeMoves(fruit.myMoves(), (char)Objects::FRUIT);
	fruit.restartObj();
	for (int i = 0; i < board.getCountOfGhosts(); i++)
	{
		SLFile.writeMoves(g[i].myMoves(), (char)Objects::GHOST);
		g[i].restartObj();
	}
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method make a full cycle of getting a key from the player, move the pacman and move the ghosts.

void ThePacmanGame::makeFullCycle(int& dir, int& oldDir, char& key,int& needAfruit,int& now, int& _timeTodisapear)
{
	static int delayer = 0;
	int i;

	if (_kbhit() && !load)
	{
		if (dir != -1)
		{
			oldDir = dir;
		}
		key = _getch();
		PauseGame(key);
		dir = pacman.getDirection(key);
		pacmanMoveSmart(dir, oldDir,needAfruit,now, _timeTodisapear);
	}
	else
		pacmanMoveSmart(dir, oldDir,needAfruit,now, _timeTodisapear);
	UpdateDetails(dir, needAfruit, now, _timeTodisapear);
	becauseOfPac = false;
	if (delayer == 0)
	{
		CheckMode();
		delayer++;
	}
	else
		delayer--;
	if(needAfruit==1)
		checkMoveFruit();
	if(!silent)
		Sleep(300);
	UpdateDetails(dir,needAfruit,now, _timeTodisapear);
	becauseOfPac = true;
}

void  ThePacmanGame::CheckMode()
{
	if (mode == 'c')
	{
		NoviceMove();
	}
	else if (mode == 'b')
	{
		GoodMove();
	}
	else if (mode == 'd')
		loadMode();
	else
	{
		SmartGhost();
	}
}

void ThePacmanGame::loadMode()
{
	for (int i = 0; i < board.getCountOfGhosts(); i++)
	{
		g[i].continueOldDir(g[i].readMove() - '0');
		g[i].changePlace();
		g[i].moveMovingObj(board.getFigure(g[i].getMovingObjBodyY(), g[i].getMovingObjBodyX()));
	}
}

void ThePacmanGame::GoodMove()
{
	static int randomCounter = 0;
	if (randomCounter < 20)
	{
		SmartGhost();
		randomCounter++;
	}
	else
	{
		NoviceMove();
		randomCounter++;
		if (randomCounter == 25)
		{
			for (int i = 0; i < board.getCountOfGhosts(); i++)
				g[i].setEyesLocation(g[i].getMovingObjBodyY(), g[i].getMovingObjBodyX());
			randomCounter = 0;
		}
	}
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method move the ghost in the NOVICE mode.

void ThePacmanGame::NoviceMove()
{
	int x, y;
	static int oldDirections[4] = { 0 }, steps[4] = { 0 };
	for (int i = 0; i < board.getCountOfGhosts(); i++)
	{
		y = g[i].getMovingObjBodyY();
		x = g[i].getMovingObjBodyX();
		if (steps[i] == 0)
		{
			if (board.getFigure(g[i].getMovingObjEyesY(), g[i].getMovingObjEyesX()) == WALL || (g[i].getMovingObjEyesX() > board.getPoint((int)Locations::MAXSIZE).getX() - 1 || g[i].getMovingObjEyesX() < (int)Borders::Minimum) || (g[i].getMovingObjEyesY() > board.getPoint((int)Locations::MAXSIZE).getY() || g[i].getMovingObjEyesY() < (int)Borders::Minimum))
			{
				g[i].setEyesLocation(g[i].getMovingObjBodyY(), g[i].getMovingObjBodyX());
			}
			oldDirections[i] = g[i].updateEyes();
		}
		if (board.getFigure(g[i].getMovingObjEyesY(), g[i].getMovingObjEyesX()) != WALL && (g[i].getMovingObjEyesX() <= board.getPoint((int)Locations::MAXSIZE).getX() - 1 && g[i].getMovingObjEyesX() >= (int)Borders::Minimum) && (g[i].getMovingObjEyesY() <= board.getPoint((int)Locations::MAXSIZE).getY() && g[i].getMovingObjEyesY() >= (int)Borders::Minimum))
		{
			g[i].moveMovingObj(board.getFigure(g[i].getMovingObjBodyY(), g[i].getMovingObjBodyX()));
	
			steps[i]++;
			g[i].continueOldDir(oldDirections[i]);
		}
		else
		{
			steps[i] = 0;
			g[i].setEyesLocation(g[i].getMovingObjBodyY(), g[i].getMovingObjBodyX());
		}
		if (steps[i] == 20)
		{
			steps[i] = 0;
			g[i].setEyesLocation(g[i].getMovingObjBodyY(), g[i].getMovingObjBodyX());
		}
		if (save)
		{
			g[i].addMove(getDirForStr(y, x, i) + '0');
		}
	}
	if (afterDeath)
		changeAfterDeath();
	if(newLevel)
		newLevel = false;
}

int ThePacmanGame::getDirForStr(int oldY, int oldX, int i)
{
	if (g[i].getMovingObjBodyY() - oldY < 0)
		return (int)Directions::UP;
	else if(g[i].getMovingObjBodyY() - oldY > 0)
		return (int)Directions::DOWN;
	else if (g[i].getMovingObjBodyX() - oldX < 0)
		return (int)Directions::LEFT;
	else if (g[i].getMovingObjBodyX() - oldX > 0)
		return (int)Directions::RIGHT;
	else
		return (int)Directions::STAY;
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method manages the fruit movment.

void ThePacmanGame::checkMoveFruit()
{
	if (load)
	{
		char temp = fruit.readMove();
		if (temp != 'k')
		{
			fruit.continueOldDir(temp -'0');
			fruit.changePlace();
			fruit.moveMovingObj(board.getFigure(fruit.getMovingObjBodyY(), fruit.getMovingObjBodyX()));
		}
	}
	else
	{
		int fruitDir;
		fruitDir = fruit.updateEyes();
		while (board.getFigure(fruit.getMovingObjEyesY(), fruit.getMovingObjEyesX()) == WALL || (fruit.getMovingObjEyesX() > board.getPoint((int)Locations::MAXSIZE).getX() - 1 || fruit.getMovingObjEyesX() < (int)Borders::Minimum) || (fruit.getMovingObjEyesY() > board.getPoint((int)Locations::MAXSIZE).getY() || fruit.getMovingObjEyesY() < (int)Borders::Minimum))
		{
			fruit.setEyesLocation(fruit.getMovingObjBodyY(), fruit.getMovingObjBodyX());
			fruitDir = fruit.updateEyes();
		}
		fruit.moveMovingObj(board.getFigure(fruit.getMovingObjBodyY(), fruit.getMovingObjBodyX()));
		if (save)
		{
			fruit.addMove(fruitDir + '0');
		}
	}
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method manages the moving of the pacman in the game.

void ThePacmanGame::CheckMovePacman(int& direction , int& needAfruit, int& now, int& _timeTodisapear)
{
	if (board.getFigure(pacman.getMovingObjEyesY(), pacman.getMovingObjEyesX()) == WALL && !load)
	{
		pacman.setDirection((int)Directions::STAY);
	}
	else
	{
		if (load)
		{
			pacman.setDirection(pacman.readMove() - '0');
			coordFile2 << pacman.readMove();
			pacman.changePlace();
		}
		else
			pacman.setDirection(direction);

		if (board.getFigure(pacman.getMovingObjEyesY(), pacman.getMovingObjEyesX()) == BREADCRUMB)
		{
			board.updateBoard(pacman.getMovingObjBodyY(), pacman.getMovingObjBodyX(), SPACE);
			score++;
			board.setCountOfBreadCrumbs();
		}
	}
	pacman.moveMovingObj(SPACE);
	if (save)
	{
		pacman.addMove(pacman.getDirection() + '0');
	}
	board.updateBoard(pacman.getMovingObjBodyY(), pacman.getMovingObjBodyX(), SPACE);
	pacman.setEyesLocation(pacman.getMovingObjBodyY(), pacman.getMovingObjBodyX());
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method picks the relevantic direction and uses the methods that move the Pacman.

void ThePacmanGame::pacmanMoveSmart(int& dir1, int& copyDir1, int& _NeedAFruit, int& _now, int& _timeTodisapear)
{
	if (load)
	{
		pacman.updateEyes(pacman.readMove() - '0');
		CheckMovePacman(dir1, _NeedAFruit, _now, _timeTodisapear);
	}
	else
	{
		if (dir1 != -1)
		{
			pacman.updateEyes(dir1);
			CheckMovePacman(dir1, _NeedAFruit, _now, _timeTodisapear);
		}
		else
		{
			pacman.updateEyes(copyDir1);
			CheckMovePacman(copyDir1, _NeedAFruit, _now, _timeTodisapear);
		}
	}
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method checks if the pacman need to lose lives.

void ThePacmanGame::checkIfDie(int& dir)
{
	if (board.getCountOfGhosts() != 0)
	{
		for (int i = 0; i < board.getCountOfGhosts(); i++)
		{
			if ((pacman.getMovingObjBodyX() == g[i].getMovingObjBodyX() && pacman.getMovingObjBodyY() == g[i].getMovingObjBodyY()))
			{
				pacmaninjury(dir);
			}
				
		}
	}
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method manages the life losing of the pacman.

void ThePacmanGame::pacmaninjury(int& dir)
{
	lives--;
	if(save && lives > 0)
		SLFile.writeToResults('D', time);
	if (save || load)
	{
		if(save)
			pacman.addMove('-');
		pacman.changePlace();
		if (load && silent)
		{
			if(lives > 0)
				if(SLFile.checkWhatHappend() != 'D' || time != SLFile.getTime())
					test = false;
		}
		if (time == 157)
		{
			Sleep(10);
		}
		for (int i = 0; i < board.getCountOfGhosts(); i++)
		{
			if(save)
				g[i].addMove('-');
			g[i].changePlace();
		}
	}
	dir = (int)Directions::STAY;
	board.updateBoard(pacman.getMovingObjBodyY(), pacman.getMovingObjBodyX(), SPACE);
	system("cls");
	init();
	if(!load)
		changeAfterDeath();
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method checks if the fruit need to disapear.

void ThePacmanGame::checkIfEatFruit(int& _NeedAFruit, int& _now,int& _timeTodisapear)
{
	if ((pacman.getMovingObjBodyX() == fruit.getMovingObjBodyX()) && (pacman.getMovingObjBodyY() == fruit.getMovingObjBodyY()) && _NeedAFruit == 1)
	{
		score = score + fruit.getFigure();
		_NeedAFruit = 0;
		_now = rand() % 30;
		_timeTodisapear = 0;

		fruit.initLocation(81, 81);
		if (save)
			fruit.addMove((char)Objects::KILL);
		if (load)
		{
			fruit.changeSwitch();
			fruit.readMove();
			fruit.changePlace();
		}
	}
	else
	{
		for (int i = 0; i < board.getCountOfGhosts(); i++)
		{
			if (((g[i].getMovingObjBodyX() == fruit.getMovingObjBodyX()) && (g[i].getMovingObjBodyY() == fruit.getMovingObjBodyY()) || (_timeTodisapear == 60) && _NeedAFruit == 1) || (load && _NeedAFruit == 1 && fruit.readMove() == 'k'))
				ChangeToZeroFruits(_NeedAFruit, _now, _timeTodisapear);
		}
	}
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method count the time for the fruit to disapear.

void ThePacmanGame::ChangeToZeroFruits(int& _NeedAFruit, int& _now, int& _timeTodisapear)
{
	if (_timeTodisapear == 60)
	{
		gotoxy(fruit.getMovingObjBodyX(), fruit.getMovingObjBodyY());
		if (color)
		{
			setTextColor(Color::WHITE);
		}
		if(!silent)
			cout << board.getFigure(fruit.getMovingObjBodyY(), fruit.getMovingObjBodyX());
	}
	_NeedAFruit = 0;
	_now = rand() % 30;
	_timeTodisapear = 0;

	fruit.initLocation(81, 81);
	if (save)
		fruit.addMove((char)Objects::KILL);
	if (load)
	{
		fruit.changeSwitch();
		fruit.readMove();
		fruit.changePlace();
	}
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method updates the lives and scores.

void ThePacmanGame::UpdateDetails(int& dir,int& _NeedAFruit,int& _now, int& _timeTodisapear)
{
	if (color)
		setTextColor(Color::LIGHTGREEN);
	checkIfEatFruit(_NeedAFruit, _now, _timeTodisapear);
	gotoxy(board.getPoint((int)Locations::DETAILSLOCATION).getX()+6, board.getPoint((int)Locations::DETAILSLOCATION).getY() + 1);
	if(!silent)
		cout << score;
	checkIfDie(dir);
	if (color)
		setTextColor(Color::LIGHTGREEN);
	gotoxy(board.getPoint((int)Locations::DETAILSLOCATION).getX() + 6, board.getPoint((int)Locations::DETAILSLOCATION).getY() + 2);
	if(!silent)
		cout << lives;
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method pauses the game.

void ThePacmanGame::PauseGame(int keys)
{
	if (keys == ESC)
	{
		gotoxy(board.getPoint((int)Locations::DETAILSLOCATION).getX() , board.getPoint((int)Locations::DETAILSLOCATION).getY() );
		if(!silent)
			cout << "Game paused";
		keys = (int)Borders::Minimum;
		while (keys != ESC)
		{
			if (_kbhit())
			{
				keys = _getch();
			}
		}
	}
	gotoxy(board.getPoint((int)Locations::DETAILSLOCATION).getX(), board.getPoint((int)Locations::DETAILSLOCATION).getY());
	cout << "           ";
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method picks for a ghost the best direction for chasing the pacman.

void ThePacmanGame::SmartGhost()
{
	pos source, dest;
	vector<pos> dataBoard[80][25];
	int v = board.getPoint((int)Locations::MAXSIZE).getY();
	int newDir;
	int x, y;

	// array of vectors is used to store the graph
	// in the form of an adjacency list
	for (int i = 0; i < board.getPoint((int)Locations::MAXSIZE).getX(); i++)
	{
		for (int j = 0; j < board.getPoint((int)Locations::MAXSIZE).getY(); j++)
		{
			if (!isWall(i, j)) {
				if (!isWall(i, j + 1))
					add_edge(dataBoard, { i,j }, { i,j + 1 });
				if (!isWall(i + 1, j))
					add_edge(dataBoard, { i,j }, { i + 1,j });
				if (j != 0 && !isWall(i, j - 1))
					add_edge(dataBoard, { i,j }, { i,j - 1 });
				if (i != 0 && !isWall(i - 1, j))
					add_edge(dataBoard, { i,j }, { i - 1,j });
			}
		}
	}
	for (int i = 0; i < board.getCountOfGhosts(); i++)
	{
		y = g[i].getMovingObjBodyY();
		x = g[i].getMovingObjBodyX();
		char prevFigure;
		int saveDir;
		source = { g[i].getMovingObjBodyX(), g[i].getMovingObjBodyY() }, dest = { pacman.getMovingObjBodyX(),pacman.getMovingObjBodyY() };

		newDir = setGhostDir(dataBoard, source, dest, v);
		prevFigure = board.getFigure(g[i].getMovingObjBodyY(), g[i].getMovingObjBodyX());
		g[i].continueOldDir(saveDir = avoidMeetingGhosts(i, newDir, prevFigure));
		while (board.getFigure(g[i].getMovingObjEyesY(), g[i].getMovingObjEyesX()) == WALL)
		{
			g[i].setEyesLocation(g[i].getMovingObjBodyY(), g[i].getMovingObjBodyX());
			g[i].continueOldDir(saveDir = avoidMeetingGhosts(i, newDir, prevFigure));
		}
		g[i].moveMovingObj(prevFigure);
		if (save)
		{
			g[i].addMove(getDirForStr(y, x, i) + '0');
		}
	}

}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method avoid from the ghosts to meet.

int ThePacmanGame::avoidMeetingGhosts(const int& i, const int& newDir, char& prevFigure)
{
	for (int j = 0; j < board.getCountOfGhosts(); j++)
	{
		if (j != i)
		{
			if ((g[i].getMovingObjBodyY() == g[j].getMovingObjBodyY()) && (g[i].getMovingObjBodyX() == g[j].getMovingObjBodyX()))
				prevFigure = '$';

			if ((g[i].getMovingObjEyesY() == g[j].getMovingObjBodyY()) && (g[i].getMovingObjEyesX() == g[j].getMovingObjBodyX()))
				return rand() % 4;;
		}
	}
	return newDir;
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method add 2 positions for the dataBoard.

void ThePacmanGame::add_edge(vector<pos> dataBoard[80][25], pos src, pos dest)
{
	dataBoard[src.x][src.y].push_back(dest);
	dataBoard[dest.x][dest.y].push_back(src);
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method finds the best direction from the ghost to the pacman.

int ThePacmanGame::setGhostDir(vector<pos> dataBoard[80][25], pos s, pos dest, int v)
{
	// predecessor[i] array stores predecessor of
	// i and distance array stores distance of i
	// from s
	pos pred[80][25];
	int dist[80][25]; // size v

	if (BFS(dataBoard, s, dest, v, pred, dist) == false) {
		//cout << "No connection";
		return -1;
	}

	// vector path stores the shortest path
	vector<pos> path;
	pos crawl = dest;
	path.push_back(crawl);
	while (pred[crawl.x][crawl.y].x != -1) {
		path.push_back(pred[crawl.x][crawl.y]);
		crawl = pred[crawl.x][crawl.y];
	}

	if (path[path.size() - 1].x < path[path.size() - 2].x)
		return RIGHT;
	if (path[path.size() - 1].y < path[path.size() - 2].y)
		return DOWN;
	if (path[path.size() - 1].x > path[path.size() - 2].x)
		return LEFT;
	if (path[path.size() - 1].y > path[path.size() - 2].y)
		return UP;
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method calculates the shortest path from one position to another position.

bool ThePacmanGame::BFS(vector<pos> dataBoard[80][25], pos src, pos dest, int v, pos pred[80][25], int dist[80][25])
{
	// a queue to maintain queue of vertices whose
	// adjacency list is to be scanned as per normal
	// DFS algorithm
	list<pos> queue;

	// boolean array visited[] which stores the
	// information whether ith vertex is reached
	// at least once in the Breadth first search
	bool visited[80][25];

	// initially all vertices are unvisited
	// so v[i] for all i is false
	// and as no path is yet constructed
	// dist[i] for all i set to infinity
	for (int i = 0; i < 80; i++) {
		for (int j = 0; j < 25; j++)
		{
			visited[i][j] = false;
			dist[i][j] = INT_MAX;
			pred[i][j] = { -1,-1 };
		}
	}

	// now source is first to be visited and
	// distance from source to itself should be 0
	visited[src.x][src.y] = true;
	dist[src.x][src.y] = 0;
	queue.push_back(src);

	// standard BFS algorithm
	while (!queue.empty()) {
		pos u = queue.front();
		queue.pop_front();
		for (int i = 0; i < dataBoard[u.x][u.y].size(); i++)
		{
			for (int j = 0; j < dataBoard[u.x][u.y].size(); j++)
			{
				if (visited[dataBoard[u.x][u.y][i].x][dataBoard[u.x][u.y][i].y] == false)
				{
					visited[dataBoard[u.x][u.y][i].x][dataBoard[u.x][u.y][i].y] = true;
					dist[dataBoard[u.x][u.y][i].x][dataBoard[u.x][u.y][i].y] = dist[u.x][u.y] + 1;
					pred[dataBoard[u.x][u.y][i].x][dataBoard[u.x][u.y][i].y] = u;
					queue.push_back(dataBoard[u.x][u.y][i]);

					// We stop BFS when we find
					// destination.
					if (dataBoard[u.x][u.y][i] == dest)
						return true;
				}

			}
		}
	}

	return false;
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method checks if the current position is a wall.

bool ThePacmanGame::isWall(const int x, const int y)
{
	if (board.getFigure(y, x) == '#')
	{
		return true;
	}
	return false;
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method initialize the pacman and the ghosts by their positions in the text file.

void ThePacmanGame::initPacmanAndGhost()
{
	pacman.initLocation(board.getPoint((int)Locations::PACLOCATION).getY(), board.getPoint((int)Locations::PACLOCATION).getX());
	pacman.setEyesLocation(board.getPoint((int)Locations::PACLOCATION).getY(), board.getPoint((int)Locations::PACLOCATION).getX());
	pacman.moveMovingObj(SPACE);
	for (int i = 0; i < board.getCountOfGhosts(); i++)
	{
		g[i].initLocation(board.getPoint(i+1).getY(), board.getPoint(i+1).getX());
		g[i].setMovingObjColor(color);
		if (color)
			setTextColor(Color::LIGHTRED);
		gotoxy(board.getPoint(i + 1).getX(), board.getPoint(i + 1).getY());
		if(!silent)
			cout << '$';
	}
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method prints a message to the user after losing.

void ThePacmanGame::gameover()
{
	if (color)
		setTextColor(Color::RED);
	cout << "       $$$$$$       " << endl;
	cout << "      $$$$$$$$      " << endl;
	cout << "    $$$$$$$$$$$$    " << endl;
	cout << "  $$$$$$$$$$$$$$$$  " << endl;
	cout << "  $$$$$$$$$$$$$$$$  " << endl;
	cout << "  $$$   $$$$   $$$  " << endl;
	cout << "$$$$$   $$$$   $$$$$" << endl;
	cout << "$$$$$$$$$$$$$$$$$$$$" << endl;
	cout << "$$$$$$$$$$$$$$$$$$$$" << endl;
	cout << "$$$$ GAME OVER! $$$$" << endl;
	cout << "$$$$$$$$$$$$$$$$$$$$" << endl;
	cout << "$$$$$  $$$$$  $$$$$" << endl;
	cout << " $$$    $$$    $$$ " << endl;
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method prints a message to the user after winning.

void ThePacmanGame::victory()
{
	if (color)
		setTextColor(Color::YELLOW);
	cout << "    @@@@@@@@@@@@     " << endl;
	cout << "  @@@@@@@@@@@@@@@@   " << endl;
	cout << " @@@@@@@@@@@@@@@@@@  " << endl;
	cout << " @@@@@@@@@@@@@@@@@   " << endl;
	cout << "@@@@@@@@@@@@@@       " << endl;
	cout << "@@@@@@@@@@@          " << endl;
	cout << "@@@@@@@      YOU WON!" << endl;
	cout << "@@@@@@@@@@@          " << endl;
	cout << "@@@@@@@@@@@@@@       " << endl;
	cout << " @@@@@@@@@@@@@@@@@   " << endl;
	cout << " @@@@@@@@@@@@@@@@@@  " << endl;
	cout << "  @@@@@@@@@@@@@@@@   " << endl;
	cout << "    @@@@@@@@@@@@     " << endl;
}

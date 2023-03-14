#pragma once
#include "bitsStdc.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Menu.h"
#include "boardTable.h"
#include "Fruit.h"
#include <cmath>
#include <vector>
#include "bitsStdc.h"
#include"SaveLoad.h"

struct pos {
	int x, y;

	bool operator==(const pos& o) const {
		if (o.x == this->x && o.y == this->y)
			return true;
		return false;
	}
};
class ThePacmanGame {
	enum { ESC = 27, startingLives = 3,  DetailsLocation = 6, BREADCRUMB = '.', SPACE = ' ', WALL = '#',PAKMAN='@' ,UP=0,DOWN=1,LEFT=2,RIGHT=3, denyOption = 5000};
	bool withSpecificFile;
	bool silent = false;
	bool DataBoard[(int)Borders::ROWSIZE][(int)Borders::COLSIZE + 1] = {0};
	string firstFile ;
	Board board{withSpecificFile,firstFile, silent};
	Pacman pacman{board.getPoint((int)Locations::MAXSIZE).getY(),board.getPoint((int)Locations::MAXSIZE).getX(), silent};
	Fruit fruit{ silent };
	vector <Ghost> g{ { board.getPoint((int)Locations::MAXSIZE).getY(), board.getPoint((int)Locations::MAXSIZE).getX(),silent }, { board.getPoint((int)Locations::MAXSIZE).getY(),board.getPoint((int)Locations::MAXSIZE).getX(),silent}, { board.getPoint((int)Locations::MAXSIZE).getY(), board.getPoint((int)Locations::MAXSIZE).getX(),silent }, { board.getPoint((int)Locations::MAXSIZE).getY(), board.getPoint((int)Locations::MAXSIZE).getX(),silent } };
	int lives = startingLives;
	int score = (int)Borders::Minimum;
	bool color;
	char mode;
	bool afterDeath = false;
	bool becauseOfPac = true;
	bool save = false;
	bool load = false;

	bool newLevel = false;
	bool fruitOnBoard = false;
	int ghostCount = 0;
	int oldGhostCount = 0;
	int time = 0;
	int test = true;
	SaveLoad SLFile{ getSaveOption(), getLoadOption(), board.getFileName(0) };
	fstream coordFile;
	fstream coordFile2;
	int getTime() { return time; }
	bool getSaveOption() { return save; }
	bool getLoadOption() { return load; }
	void victory();
	void gameover();
	void checkIfDie(int& dir);
	void CheckMovePacman(int& direction, int& needAfruit, int& now, int& _timeTodisapear);
	void UpdateDetails(int& dir, int& _NeedAFruit, int& _now, int& _timeTodisapear);
	void PauseGame(int keys);
	void pacmanMoveSmart(int& dir1, int& copyDir1, int& _NeedAFruit, int& _now, int& _timeTodisapear);
	void makeFullCycle(int& dir, int& oldDir, char& key, int& needAfruit, int& now, int& _timeTodisapear);
	void initPacmanAndGhost();
	void checkMoveFruit();
	void checkIfEatFruit(int& _NeedAFruit, int& _now, int& _timeTodisapear);
	void CheckMode();
	void NoviceMove();
	void GoodMove();
	void loadMode();
	void ChangeToZeroFruits(int& _NeedAFruit, int& _now, int& _timeTodisapear);
	void pacmaninjury(int& dir);
	void NewLevel(const int& count, const bool& flag, int& needAFruit, int& now, int& tooMuch);
	void FruitOnTheScreen(int& fruitCounter, int& now, int& needAFruit, int& num, int& timeTodisapear);
	void add_edge(vector<pos> adj[80][25], pos src, pos dest);
	void SmartGhost();
	int setGhostDir(vector<pos> adj[80][25], pos s, pos dest, int v);
	bool BFS(vector<pos> adj[80][25], pos src, pos dest, int v, pos pred[80][25], int dist[80][25]);
	bool isWall(const int x, const int y);
	int avoidMeetingGhosts(const int& i, const int& newDir, char& prevFigure);
	void endGame(int& count, bool& flag);
	void emptyPage();
	void fillStrings();
	void changeAfterDeath() { afterDeath = !afterDeath; }
	int getDirForStr(int oldY, int oldX, int i);
public:
	ThePacmanGame(string name,char _mode,bool _withSpecificFile,bool _save, bool _load, bool _silent):firstFile(name),mode(_mode),withSpecificFile(_withSpecificFile), save(_save), load(_load), silent(_silent) { }
	void setGameColor(bool _color);
	void init();
	void run(bool flag);
};

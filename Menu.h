#pragma once
#include "ThePacmanGame.h"
#include "InputParser.h"

class Menu {
	void printLineOf(int amount, char shape);
	void printMenu();
	void printRules();
	void playingChoice(const int& num,const int& userchoice, bool save, bool load, bool silent);
	void rulesChioce();
	void invalidChoice();
	void filesOptions();
	void difficultyOptions();
	void checkMode(int argc, char** argv, bool& save, bool& load, bool& silent, bool& legal);
	void printProblem(char* path, bool& legal);
public:
	void startGame(int argc, char** argv);
};
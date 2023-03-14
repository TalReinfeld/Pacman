#include "Menu.h"
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method prints the menu.

void Menu::printMenu()
{
	printLineOf(45, '*');
	cout << endl << "*";
	printLineOf(19, ' ');
	cout << "MENU";
	printLineOf(20, ' ');
	cout << "*" << endl;
	cout << "*Please choose one of the following options:*" << endl;
	cout << "*";
	printLineOf(43, '_');
	cout << "*" << endl;
	cout << "*(0) Start a new game without colors        *\n" <<
		"*(1) Start a new game with colors           *\n" <<
		"*(8) Present instructions and keys          *\n" <<
		"*(9) EXIT                                   *" << endl;
	printLineOf(45, '*');
	cout << endl;
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method manages the menu.
void Menu::startGame(int argc, char** argv)
{
	bool save = false, load = false, silent = false, legal = true;
	checkMode(argc, argv, save, load, silent, legal);
	if (!legal)
		return;
	if (load)
	{
		ThePacmanGame playGame("", 'd', 0, save, load, silent);
		system("cls");
		playGame.init();
		playGame.run(false);
	}
	else
	{
		printMenu();
		string str;
		string filesOption;
		cin >> str;
		system("cls");
		while (str[0] != '9')
		{
			if ((str[0] == '1' || str[0] == '0') && str.size() == 1)
			{
				if (save)
					filesOption = "0";
				else
				{
					system("cls");
					filesOptions();
					cin >> filesOption;
				}

				while (filesOption[0] != '1' && filesOption[0] != '0' || str.size() != 1)
				{
					system("cls");
					invalidChoice();
					system("cls");
					filesOptions();
					cin >> filesOption;
				}
				playingChoice(str[0] - '0', filesOption[0] - '0', save, load, silent);
			}
			else if (str[0] == '8' && str.size() == 1)
			{
				rulesChioce();
			}
			else
			{
				system("cls");
				invalidChoice();
			}
			system("cls");
			printMenu();

			cin >> str;
		}
		cout << "GoodBye my friend";
	}

}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method prints an error message.

void Menu::printProblem(char* path, bool& legal)
{
	cout << "Usage: " << path << "[-save] [-load | -load -silent]" << endl;
	cout << "You should enter a valid mode: -save, -load, -silent or nothing" << endl;
	legal = false;
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method checks the mode of the game.

void Menu::checkMode(int argc, char** argv, bool& save, bool& load, bool& silent, bool& legal)
{
	if (argc < 4)
	{
		if (argc == 3)
		{
			if (strcmp("-load", argv[1]) != 0)
				printProblem(argv[0], legal);
			else
			{
				load = true;
				if (strcmp("-silent", argv[2]) != 0)
					printProblem(argv[0], legal);
				else
					silent = true;
			}
		}
		else if (argc == 2)
		{
			if (!strcmp("-load", argv[1]))
				load = true;
			else if (!strcmp("-save", argv[1]))
				save = true;
			else
				printProblem(argv[0], legal);
		}
	}
	else
	{
		printProblem(argv[0], legal);
		return;
	}
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void Menu::invalidChoice()
{
	cout << "Invalid choice" << endl;
	Sleep(1000);
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method shows the rules and the arrow keys of the game.

void Menu::rulesChioce()
{
	char delayer;
	system("cls");
	printRules();
	cin >> delayer;
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method manages the game. 

void Menu::playingChoice(const int& num, const int& filesOption, bool save, bool load, bool silent)
{
	string  level;
	bool withColor, withSpecificFile, FileCouldNotOpend = false;
	string str;
	if (num == 1)
	{
		withColor = true;
	}
	else
		withColor = false;

	if (filesOption == 1)
	{
		gotoxy(0, 5);
		cout << "Please enter a File's Name: " << endl;
		cin>>str;
		ifstream outFile(str);
		
		if (!outFile)
		{
			system("cls");
			cout << "File could not be opened!" << endl;
			FileCouldNotOpend = true;
			Sleep(1000);
		}
		else
		{
			outFile.close();
			withSpecificFile = true;
		}
	}
	else
	{
		str = "a";
		withSpecificFile = false;
	}
	if (FileCouldNotOpend == false)
	{
		system("cls");
		difficultyOptions();
		cin >> level;

		while (level[0] != 'a' && level[0] != 'b' && level[0] != 'c' || level .size() != 1)
		{
			system("cls");
			invalidChoice();
			system("cls");
			difficultyOptions();
			cin >> level;
		}
		ThePacmanGame playGame(str, level[0], withSpecificFile, save, load, silent);
		system("cls");
		playGame.setGameColor(withColor);
		playGame.init();
		playGame.run(withSpecificFile);
	}
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method prints the rules and keys for the game.

void Menu::printRules()
{
	printLineOf(63, '*');
	cout << endl << "*";
	printLineOf(28, ' ');
	cout << "RULES";
	printLineOf(28, ' ');
	cout << "*" << endl;
	cout << "*Your goal is to clear the maze by eating all the breadcrumbs.*" << endl;
	cout << "*You start the game with 3 Pac-Man lives.                     *" << endl;
	cout << "*When a ghost catchesthe Pac-Man, he loses a life.            *" << endl;
	cout << "*If the Pac-Man loses all his lives the game is over.         *" << endl;
	cout << "*";
	printLineOf(61, '_');
	cout << "*" << endl << "*";
	printLineOf(28, ' ');
	cout << "KEYS:";
	printLineOf(28, ' ');
	cout << "*" << endl;
	cout << "*UP    - w or W                                               *" << endl;
	cout << "*DOWN  - x or X                                               *" << endl;
	cout << "*LEFT  - a or A                                               *" << endl;
	cout << "*RIGHT - d or D                                               *" << endl;
	cout << "*STAY  - s or S                                               *" << endl;
	cout << "*PAUSE -   esc                                                *" << endl;
	printLineOf(20, '*');
	cout << "Enter any key to return";
	printLineOf(20, '*');
	cout << endl;
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method prints the files options.

void Menu::filesOptions()
{
	printLineOf(45, '*');
	cout << endl;
	cout << "*Please choose one of the following options:*" << endl;
	cout << "*(0) Start from the first level             *\n" <<
		"*(1) Choose a specific file                 *" << endl;
	printLineOf(45, '*');
	cout << endl;
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method prints the difficulty options.

void Menu::difficultyOptions()
{
	system("cls");
	printLineOf(45, '*');
	cout << endl;
	cout << "*Please choose one of the following options:*" << endl;
	cout << "*(a) BEST                                   *\n" <<
		"*(b) GOOD                                   *\n" <<
		"*(c) NOVICE                                 *" << endl;
	printLineOf(45, '*');
	cout << endl;
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method prints a line of the same shape.

void Menu::printLineOf(int amount, char shape)
{
	for (int i = 0; i < amount; i++)
		cout << shape;
}


#pragma once
#include "Point.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include "dirent.h"
#include <vector>

enum class Locations { PACLOCATION, G1LOCATION, G2LOCATION, G3LOCATION, G4LOCATION, DETAILSLOCATION, MAXSIZE };
class Board {
    vector<string> NamesFiles;
    char displayBoard[(int)Borders::ROWSIZE][(int)Borders::COLSIZE + 1];
    Point startings[7];
    bool color;
    bool flagPacman = false;
    bool flagGhostOnReadArea = false;
    int countOfBreadCrumbs = 0;
    int countOfGhost = 0;
    bool silent = false;
    int level = 0;
    int countOfFiles = 0;
    bool Error = false;
    void checkCountOfPacmanAndAmper(const int& countPacman, const int& countAmper);
    void getSmartLine(ifstream& in, const int& count, const int& num, int& countPacman, int& countAmper, bool& flagReadingArea);
    int readFirstLine(ifstream& in, int num);
    int readLineFromTXTFile(ifstream& in, int num, int& countPacman, int& countAmper, bool& flagReadingArea);
    void initBoard();
    void setLocationsAndUpdateBoard(ifstream& in, char ch, const int& num, int& i, const int& count, bool& foundDetails, bool& flag, bool& flagFood, int& countPacman, int& countAmper, bool& flagReadingArea);
    bool isGameFile(string path);
    void explore(char* dir_name);
    void openFileAndRead(ifstream& in, int& MaxCol, string str);
    void shortLine(int& i, const int& count, bool& flag, const int& num, bool& flagFood);
    void hadleWithDetails(int& i, const int& num, bool& foundDetails, ifstream& in, char& ch, bool& flagFood, const int& count, bool& flag, int& countPacman, int& countAmper, bool& flagReadingArea);
    void exceptionsError(const char* msg);
    void checkReadingArea(int& countPacman, int& countAmper, char ch);

public:
    Board(bool withSpecificFile, string str, bool _silent, int _level = 0);
    void drawDisplayBoard()const;
    inline void updateBoard(const int& y, const int& x, const char& ch) { displayBoard[y][x] = ch; }   //This method updates a specific coordinate on the board.
    inline char getFigure(int y, int x)const { return displayBoard[y][x]; }  //This method returns a character on a specific coordinate from the board.
    void setBoardColor(const bool& _color);
    Point getPoint(int index);
    inline int getCountOfBreadCrumbs() { return countOfBreadCrumbs; }
    inline void setCountOfBreadCrumbs() { countOfBreadCrumbs--; }
    inline  int getCountOfGhosts()const { return countOfGhost; }
    inline  int getCountOfFiles()const { return countOfFiles; }
    inline bool GetError() { return Error; }
    inline string getFileName(int level) { return NamesFiles[level]; }
};

#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include "constants.h"
using namespace std;

class SaveLoad {
	fstream resFile;
	fstream stepsFile;
public:
	SaveLoad(const bool& saveOption, const bool& loadOption, string fName);
	~SaveLoad() { closeFiles(); }
	void openFiles(const bool& saveOption, const bool& loadOption, string fName);
	void closeFiles() { stepsFile.close(); resFile.close(); }
	void writeToResults(char whatHappend, int when){ resFile << whatHappend << when << '.'; }
	void writeMoves(string& moves, char who) { stepsFile << '\n' << who << ':' << moves; }
	string changeName(string fName, string ending);
	void colorMode(bool color) { stepsFile << color << ';'; }
	void readColor() { while (stepsFile.get() != '\n'); }
	void readStrFromFile(string& str) { getline(stepsFile, str); }
	int getTime();
	char checkWhatHappend();
};
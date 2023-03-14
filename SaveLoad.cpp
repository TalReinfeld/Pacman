#include"SaveLoad.h"

SaveLoad::SaveLoad(const bool& saveOption, const bool& loadOption, string fName)
{
	if (saveOption || loadOption)
		openFiles(saveOption, loadOption, fName);
}

void SaveLoad::openFiles(const bool& saveOption, const bool& loadOption, string fName)
{
	if (saveOption)
	{
		stepsFile.open(changeName(fName, "steps"), ios_base::out);
		resFile.open(changeName(fName, "result"), ios_base::out);
	}
	else if (loadOption)
	{
		stepsFile.open(changeName(fName, "steps"), ios_base::in);
		resFile.open(changeName(fName, "result"), ios_base::in);
	}
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method changes the "screen" to "result" / "steps".

string SaveLoad::changeName(string fName, string ending)
{
	string newName = fName.substr(0, fName.size() - 6);
	return newName += ending;
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method returns what happend from the result file.

char SaveLoad::checkWhatHappend()
{
	char temp;
	resFile.get(temp);
	return temp;
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method return time from the result file.

int SaveLoad::getTime()
{
	char temp;
	int time = 0;
	resFile.get(temp);
	while (temp != '.')
	{
		time = 10 * time + temp - '0';
		resFile.get(temp);
	}
	return time;
}


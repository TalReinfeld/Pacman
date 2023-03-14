#include "BoardTable.h"
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method prints the game board.

void Board::drawDisplayBoard() const
{
    if (!silent)
    {
        for (int i = 0; i < (int)Borders::ROWSIZE; i++)
        {
            for (int j = 0; j < (int)Borders::COLSIZE; j++)
            {
                if (displayBoard[i][j] == '#' && color)
                    setTextColor(Color::LIGHTBLUE);
                else if (displayBoard[i][j] == '.' && color)
                    setTextColor(Color::WHITE);
                else if (color)
                    setTextColor(Color::LIGHTGREEN);
                cout << displayBoard[i][j];
            }
            cout << endl;
        }
        gotoxy(startings[(int)Locations::DETAILSLOCATION].getX(), startings[(int)Locations::DETAILSLOCATION].getY() + 2);
        cout << "LIVES:";
        gotoxy(startings[(int)Locations::DETAILSLOCATION].getX(), startings[(int)Locations::DETAILSLOCATION].getY() + 1);
        cout << "SCORE:";
    }
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method set the board to be with or without colors

void Board::setBoardColor(const bool& _color)
{
    color = _color;
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method returns if the file is a real screen for the pacman game.

bool Board::isGameFile(string path)
{
    int size = path.size();
    if (size < 6)
        return false;
    char endName[7] = {};

    for (int i = 0; i < 6; i++)
    {
        endName[5 - i] = *(path.rbegin() + i);

    }
    endName[6] = '\0';
    if (strcmp(endName, "screen") == 0)
        return true;
    return false;
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method finds all the screen files.

void Board::explore(char* dir_name)
{
    string str;
    DIR* dir;
    struct dirent* entry;
    struct stat info;
    //open
    dir = opendir(dir_name);
    if (!dir) {
        cout << "Directory was not found\n" << endl;
        return;
    }
    //read
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name[0] != '.')
        {
            string path = string(dir_name + 1) + string(entry->d_name);
            string* path1 = &path;
            if (isGameFile(path))
            {
                str = *(path1);
                NamesFiles.push_back(str);
            }
            int size = path.size();
            char* _path = new char[size];
            for (int i = 0; i < size; i++)
            {
                _path[i] = path[i];
            }
            stat(_path, &info);
            if (S_ISDIR(info.st_mode))
                explore(_path);
        }
    }
    //close
    closedir(dir);
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/

Board::Board(bool withSpecificFile, string str, bool _silent, int _level) :silent(_silent), level(_level)
{
    char str1[] = ".";
    explore(str1);
    int j;
    int Maxcol = 0;
    initBoard();
    ifstream outFile;
    if (withSpecificFile == false)
    {
        if (NamesFiles.size() != 0)
        {
            openFileAndRead(outFile, Maxcol, NamesFiles[level]);
        }
    }
    else
    {
        openFileAndRead(outFile, Maxcol, str);
    }
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method open a screen file and translate it into the board.

void Board::openFileAndRead(ifstream& in, int& MaxCol, string str)
{
    static int countPacman = 0;
    static int countAmper = 0;
    static bool flagReadingArea = false;
    flagReadingArea = false;
    countPacman = 0;
    countAmper = 0;
    int j;
    in.open(str);
    for (j = 0; j < (int)Borders::ROWSIZE; j++)
    {
        if (in.eof())
            break;
        else
            MaxCol = readLineFromTXTFile(in, j, countPacman, countAmper, flagReadingArea);
    }
    try
    {
        checkCountOfPacmanAndAmper(countPacman, countAmper);
    }
    catch (const char* msg) {
        exceptionsError(msg);
    }
    startings[(int)Locations::MAXSIZE].setXY(j - 1, MaxCol);
    countOfFiles = NamesFiles.size();
    in.close();
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method get a line from the screen file.

int Board::readLineFromTXTFile(ifstream& in, int num, int& countPacman, int& countAmper, bool& flagReadingArea)
{
    static int count = 0;
    if (num == 0)
    {
        try
        {
            count = readFirstLine(in, num);
        }
        catch (const char* msg) {
            exceptionsError(msg);
        }
    }

    getSmartLine(in, count, num, countPacman, countAmper, flagReadingArea);
    return count;
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method read a line from the screen file.

void Board::getSmartLine(ifstream& in, const int& count, const int& num, int& countPacman, int& countAmper, bool& flagReadingArea)
{
    int i;
    char ch = NULL;
    bool flag = false;
    bool flagFood = false;
    static bool foundDetails = false;
    for (i = 0; i < count; i++)
    {
        if (foundDetails == true)
        {
            hadleWithDetails(i, num, foundDetails, in, ch, flagFood, count, flag, countPacman, countAmper, flagReadingArea);
            if (flagFood == true)
                break;
        }
        else
        {
            ch = in.get();
            if (ch == '\n' || ch == EOF)
            {
                flagFood = true;
                shortLine(i, count, flag, num, flagFood);
                break;
            }
            else
            {
                try
                {
                    setLocationsAndUpdateBoard(in, ch, num, i, count, foundDetails, flag, flagFood, countPacman, countAmper, flagReadingArea);
                }
                catch (const char* msg) {
                    exceptionsError(msg);
                }
            }
        }
    }
    while (ch != '\n' && flag == false && !in.eof())
    {
        ch = in.get();
    }
}

void Board::hadleWithDetails(int& i, const int& num, bool& foundDetails, ifstream& in, char& ch, bool& flagFood, const int& count, bool& flag, int& countPacman, int& countAmper, bool& flagReadingArea)
{
    if (num == (startings[(int)Locations::DETAILSLOCATION].getY() + 1) && i == startings[(int)Locations::DETAILSLOCATION].getX() || (num == startings[(int)Locations::DETAILSLOCATION].getY() + 2) && i == startings[(int)Locations::DETAILSLOCATION].getX())
    {
        if (num == (startings[(int)Locations::DETAILSLOCATION].getY() + 2) && i == startings[(int)Locations::DETAILSLOCATION].getX())
        {
            foundDetails = false;
        }
        for (int j = 0; j < 20; j++)
        {
            ch = in.get();
            checkReadingArea(countPacman, countAmper, ch);
            if (ch == '\n')
            {
                flagFood = false;
                shortLine(i, count, flag, num, flagFood);
                break;
            }
            else
                i++;
        }
        i--;
    }
    else
    {
        ch = in.get();
        if (ch == '\n' || ch == EOF)
        {
            flagFood = true;
            shortLine(i, count, flag, num, flagFood);
        }
        try {
            setLocationsAndUpdateBoard(in, ch, num, i, count, foundDetails, flag, flagFood, countPacman, countAmper, flagReadingArea);
        }
        catch (const char* msg) {
            exceptionsError(msg);
        }
    }
}


/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method translate a note from the screen files to a legal note on the board.

void Board::setLocationsAndUpdateBoard(ifstream& in, char ch, const int& num, int& i, const int& count, bool& foundDetails, bool& flag, bool& flagFood, int& countPacman, int& countAmper, bool& flagReadingArea)
{
    int spaceCounter = i + 18;
    if (ch == '#')
        displayBoard[num][i] = ch;
    else if (ch == ' ')
    {
        displayBoard[num][i] = '.';
        countOfBreadCrumbs++;
    }
    else
    {
        if (ch == '&')
        {
            ++countAmper;
            if (countAmper > 1)
                throw "You have more than one & on the board";
            foundDetails = true;
            startings[(int)Locations::DETAILSLOCATION].setXY(num, i);
            while (spaceCounter != i)
            {
                ch = in.get();
                checkReadingArea(countPacman, countAmper, ch);
                if (ch == '\n')
                {
                    flagFood = false;
                    shortLine(i, count, flag, num, flagFood);
                    break;
                }
                i++;
            }
        }
        else  if (ch == '@')
        {
            ++countPacman;
            if (countPacman > 1)
                throw "You have more than one Pacman on the board";
            startings[(int)Locations::PACLOCATION].setXY(num, i);
        }
        else if (ch == '$')
        {
            startings[(int)Locations::G1LOCATION + countOfGhost].setXY(num, i);
            countOfGhost++;
            if (countOfGhost > 4)
                throw "You have more than four ghost on the board";

        }
        displayBoard[num][i] = ' ';
    }
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method gets the length of the first line.

int Board::readFirstLine(ifstream& in, int num)
{
    int count = 0;
    char ch = NULL;
    int i;
    bool flag = false;
    ch = in.get();
    while (ch != '\n')
    {
        if (ch == '&')
        {

            startings[(int)Locations::DETAILSLOCATION].setXY(num, count);
            for (i = 1; i < (int)Borders::EndOfDetails; i++)
            {
                ch = in.get();
                if (ch == '\n')
                {
                    flag = true;
                    i = 20;
                    break;
                }
            }
            count = count + i - 1;
            if (count < (int)Borders::EndOfDetails)
                count = (int)Borders::EndOfDetails;
        }
        if (flag == true)
            break;
        else
        {
            ch = in.get();
            count++;
        }
    }
    if (count >= (int)Borders::COLSIZE + 1 || count < (int)Borders::EndOfDetails)
        throw "The first row length of the board is invalid";

    in.seekg(0, ios::beg);
    return count;
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method handle a case of a short line in the screen file.

void Board::shortLine(int& i, const int& count, bool& flag, const int& num, bool& flagFood)
{
    while (i < count)
    {
        if ((flagFood == true && ((i < startings[(int)Locations::DETAILSLOCATION].getX() || i>startings[(int)Locations::DETAILSLOCATION].getX() + 19) && num == startings[(int)Locations::DETAILSLOCATION].getY() + 1 || (i < startings[(int)Locations::DETAILSLOCATION].getX() || i> startings[(int)Locations::DETAILSLOCATION].getX() + 19) && num == startings[(int)Locations::DETAILSLOCATION].getY() + 2)) || ((flagFood == true && num != startings[(int)Locations::DETAILSLOCATION].getY() + 1 && num != startings[(int)Locations::DETAILSLOCATION].getY() + 2)))

        {
            displayBoard[num][i] = '.';
            countOfBreadCrumbs++;
        }
        else
        {
            displayBoard[num][i] = ' ';
            if (i - startings[(int)Locations::DETAILSLOCATION].getX() == 20)
                flagFood = true;
        }
        i++;

    }
    flag = true;
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method return a point.

Point Board::getPoint(int index)
{
    return startings[index];
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//This method initialize the board for spaces.

void Board::initBoard()
{
    for (int i = 0; i < (int)Borders::ROWSIZE; i++)
    {
        for (int j = 0; j < (int)Borders::COLSIZE; j++)
        {
            displayBoard[i][j] = ' ';
        }
    }
}
void Board::exceptionsError(const char* msg)
{
    Error = true;
    system("cls");
    cout << msg << endl;
    Sleep(3000);
}
void Board::checkCountOfPacmanAndAmper(const int& countPacman, const int& countAmper)
{
    if (countPacman != 1)
        throw "You dont have one Pacman on the board";
    else if (countAmper != 1)
        throw "You dont have one & on the board";

}
void Board::checkReadingArea(int& countPacman, int& countAmper, char ch)
{
    if (ch == '&')
    {

        ++countAmper;
    }
    else if (ch == '@' && flagPacman == false)
    {
        flagPacman = true;
        ++countPacman;
        throw "There can not be  Pacman in the reading area";

    }
    else if (ch == '$' && flagGhostOnReadArea == false)
    {
        flagGhostOnReadArea = true;
        ++countOfGhost;
        throw "There can not be  Ghost in the reading area";
    }
}

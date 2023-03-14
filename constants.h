#pragma once
enum class Directions{	UP,	DOWN, LEFT, RIGHT, STAY };

enum class Borders{ ROWSIZE = 24, COLSIZE = 79, Minimum = 0, EndOfDetails = 20 };

enum class Objects { PACMAN = 'p', GHOST = 'g', FRUIT = 'f', REVIVE = 'r', KILL = 'k' };

enum class Color
{
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	BROWN = 6,
	LIGHTGREY = 7,
	DARKGREY = 8,
	LIGHTBLUE = 9,
	LIGHTGREEN = 10,
	LIGHTCYAN = 11,
	LIGHTRED = 12,
	LIGHTMAGENTA = 13,
	YELLOW = 14,
	WHITE = 15
};
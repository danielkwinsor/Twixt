
#include "stdafx.h"
#ifndef MY_DEFINES_H
#define MY_DEFINES_H

#define DEBUG
#define PROFILE


#define NUMDIRS 8
enum eDir
{
	leftUp = 0,
	upLeft = 1,
	upRight = 2,
	rightUp = 3,
	rightDown = 4,
	downRight = 5,
	downLeft = 6,
	leftDown = 7,
	NOTADIR = NUMDIRS
};

#define NUMJUMPS 5
enum eJump
{
	SingleJump = 0,
	DoubleDiamond = 1,
	DoubleSquare = 2,
	DoubleShortDiamond = 3,
	DoubleStraight = 4,
	NOTAJUMP = NUMJUMPS
};

void operator++(eJump& jumpType); // prefix ++
void operator--(eJump& jumpType); // prefix --
void operator++(eJump& jumpType, int); // postfix ++
void operator--(eJump& jumpType, int); // postfix --
eJump operator+(eJump& jumpType, int amount);
eJump operator-(eJump& jumpType, int amount);

enum ePlayer
{
	PlayerRed,
	PlayerBlack,
	ComputerRed,
	ComputerBlack,
	NotOwnable,
	CurrentlyUnowned,
	LinkableByAny,
	AnyPlayer,
	Green,
	Blue,
	Yellow,
	NOTAPLAYER
};

enum eAStar
{
	AStar_Init,
	AStar_Open,
	AStar_Closed
};

enum eDifficulty
{
	Dif_Easy,
	Dif_Medium,
	Dif_Hard
};

enum eSides
{
	NOTASIDE,
	TopSide,
	BottomSide,
	LeftSide,
	RightSide,
	TopAndBottom,
	LeftAndRight,
	AnySide
};

enum eWindowSize
{
	Window_DefaultSize,
	Window_BoardToWindow,
	Window_BoardToScreen
};

enum eLeftRight
{
	LEFT,
	RIGHT
};

struct DebugSettings
{
	bool	showLinks;
	bool	showParent;
	bool	showBestPath;
	bool	showSearched;
	bool	showNewest;
	bool	showAStarF;
	bool	showAStarG;
	bool	showAStarH;
	bool	debugLoadHistory;
};

struct GameData
{
	int			XBoardSize;
	int			YBoardSize;
	int			currentTurn;
	int			maxPlayers;
	int			numThreads;
	ePlayer		currentPlayer;
	ePlayer		firstPlayer;
	ePlayer		secondPlayer;
	bool		recentlySaved;
	bool		gameWon;
	eWindowSize	windowSize;
	eDifficulty	difficulty;
};

struct ValidSides
{
	bool	leftSide;
	bool	rightSide;
	bool	topSide;
	bool	bottomSide;
};

int		AdjustValueByDifficulty(int value, eDifficulty const difficulty);

/*
HEAP<MYPoint> GetBestPegFromHeap(CBinaryHeap<MYPoint>& heap,
								int const BoardSize);
*/

#define XDIR0 x-2
#define XDIR1 x-1
#define XDIR2 x+1
#define XDIR3 x+2
#define XDIR4 x+2
#define XDIR5 x+1
#define XDIR6 x-1
#define XDIR7 x-2

#define YDIR0 y-1
#define YDIR1 y-2
#define YDIR2 y-2
#define YDIR3 y-1
#define YDIR4 y+1
#define YDIR5 y+2
#define YDIR6 y+2
#define YDIR7 y+1

#define XDIR8 1
#define YDIR8 1

#define MAXBOARDSIZE	48
#define DEFAULTBOARDSIZE	24
#define DEFAULTNUMTHREADS	2
#define DEFAULTDIFFICULTY	Dif_Medium
#define NUMDIRS			8
#define ONEJUMP			6700
#define HALFJUMP		ONEJUMP/2
#define TWOJUMPS		ONEJUMP*2

#define DSTRAIGHTJUMP	1
#define DDIAMONDJUMP	1
#define DSQUAREJUMP		1
#define DSHORTJUMP		1
#define SINGLEJUMP		1

template<class T1, class T2> struct Can_copy {
		static void constraints(T1 a, T2 b) { T2 c = a; b = a; }
		Can_copy() { void(*p)(T1,T2) = constraints; }
	};




#endif
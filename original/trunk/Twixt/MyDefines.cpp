
#include "MyDefines.h"

void operator++(eJump& jumpType, int) // postfix ++
{
	jumpType = static_cast<eJump>(static_cast<int>(jumpType)+1);
	return;
}

void operator--(eJump& jumpType, int) // postfix --
{
	jumpType = static_cast<eJump>((jumpType + 1) * (NUMJUMPS-1) % NUMJUMPS);
	return;
}

void operator++(eJump& jumpType) // prefix ++
{
	jumpType = static_cast<eJump>(static_cast<int>(jumpType)+1);
	return;
}

void operator--(eJump& jumpType) // prefix --
{
	jumpType = static_cast<eJump>((jumpType + 1) * (NUMJUMPS-1) % NUMJUMPS);
	return;
}

eJump operator+(eJump& jumpType, int amount)
{
	return static_cast<eJump>((static_cast<int> (jumpType) + amount) % NUMJUMPS);
}

eJump operator-(eJump& jumpType, int amount)
{
	int temp = (static_cast<int>(jumpType) - amount) % NUMJUMPS;
	if (temp < 0) temp += 8;
	return static_cast<eJump>(temp);
}

int		AdjustValueByDifficulty(int value,
								eDifficulty const difficulty)
{
	switch (difficulty) {
	case Dif_Easy:
		return (value * (90 + (rand() % 20)) / 100);
	case Dif_Medium:
		return (value * (90 + (rand() % 10)) / 100);
	case Dif_Hard:
		return value;
	default:
		ASSERT(false);
	};
	return value;
}

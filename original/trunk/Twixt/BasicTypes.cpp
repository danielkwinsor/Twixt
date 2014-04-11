
#include "stdafx.h"

JumpStartData::JumpStartData()
{
	JumpStartData::startSide = NOTASIDE;
	JumpStartData::Dest = MYPoint(0,0);
	JumpStartData::player = NOTAPLAYER;
	return;
}//end ctor

JumpStartData::JumpStartData(eSides const startSide,
							 const MYPoint& Dest,
							 ePlayer const player)
{
	JumpStartData::startSide = startSide;
	JumpStartData::Dest = Dest;
	JumpStartData::player = player;
	return;
}//end ctor

bool CDir::operator==(CDir const other) const
{
	return (dir == other.dir ? true : false);
}

CDir CDir::GetOppositeDirection() const
{
	return static_cast<CDir> ((dir+4) % NUMDIRS);
}//end GetOppositeDirection

void CDir::operator++(int) // postfix ++
{
	dir = static_cast<eDir>(dir + 1);
	return;
}

void CDir::operator++() // prefix ++
{
	dir = static_cast<eDir>(dir + 1);
	return;
}

CDir CDir::operator+(int amount) const
{
	return static_cast<CDir>((static_cast<int> (dir) + amount) % NUMDIRS);
}

CDir CDir::operator-(int amount) const
{
	int temp = (dir - amount) % NUMDIRS;
	if (temp < 0) temp += 8;
	return static_cast<CDir>(temp);
}

CLink::operator int() {
	int a = convertToInt();
	int b = GetReversedLink().convertToInt();
	if (a <= b) {
		return a;
	}
	else {
		return b;
	}
}

bool CLink::IsDouble() const
{
	return (jump.IsDouble());
}

bool CLink::IsDoubleStraight() const
{
	return (jump.IsDoubleStraight());
}

CPathDirs CLink::GetPathDirs() const
{
	return (jump.GetPathDirs());
}

CDir CLink::GetPathDir(eLeftRight const leftRight) const
{
	return (jump.GetPathDir(leftRight));
}

int CLink::convertToInt() const
{
	return ((startPeg.x * MAXBOARDSIZE + startPeg.y) * NUMDIRS + jump.direction) * NUMJUMPS + jump.jumpType;
}

int CLink::convertToInt(eSides const side) const
{
	if (side == TopAndBottom) {
		return (startPeg.y * MAXBOARDSIZE + startPeg.x);
	}
	else {
		return (startPeg.x * MAXBOARDSIZE + startPeg.y);
	}
}//end convertToInt

void CLink::Set(const MYPoint& Peg, const CJump& Jump)
{
	startPeg = Peg;
	jump = Jump;
	return;
}

CLink::CLink(const MYPoint& Peg, const CJump& Jump)
{
	startPeg = Peg;
	jump = Jump;
	return;
}

void CLink::Set(const MYPoint& Peg, CDir const direction)
{
	startPeg = Peg;
	jump = CJump(direction);
	return;
}

CLink::CLink(const MYPoint& Peg, CDir const direction)
{
	startPeg = Peg;
	jump = CJump(direction);
	return;
}

bool CLink::operator==(const CLink& compare) const
{/*
	if (jump.jumpType == compare.jump.jumpType) {
		if (startPeg == compare.startPeg) {
			if (jump.direction == compare.jump.direction) {
				return true;
			}
		}
		else if (startPeg == compare.GetDestFromDir()) {
			if (jump.direction == compare.jump.direction.GetOppositeDirection()) {
				return true;
			}
		}
	}
	return false;
	*/
	return (*(int*)this == *(int*)&compare
		|| (jump.jumpType == compare.jump.jumpType
		&& jump.direction == compare.jump.direction.GetOppositeDirection()
		&& startPeg == compare.GetDestFromDir()));
}

bool CPathReturn::operator == (bool value)
{
	if (andOr == AND) {
		return ((leftPath && rightPath) == value);
	}
	else {
		return ((leftPath || rightPath) == value);
	}
}

bool CPathReturn::operator != (bool value)
{
	if (andOr == AND) {
		return ((leftPath && rightPath) != value);
	}
	else {
		return ((leftPath || rightPath) != value);
	}
}

CPathDirs::CPathDirs(CDir leftDir, CDir rightDir)
{
	CPathDirs::leftDir = leftDir;
	CPathDirs::rightDir = rightDir;
	return;
}

MYPoint CLink::GetIntPeg(eLeftRight const leftRight) const
{
	return ::GetDestFromDir(startPeg, jump.GetPathDir(leftRight));
}

CLink CLink::GetReversedLink() const
{
	CLink link;
	link.jump = CJump(jump.direction.GetOppositeDirection(), jump.jumpType);
	link.startPeg = CLink::GetDestFromDir();
	return link;
}

MYPoint CLink::GetDestFromDir() const
{
	return (::GetDestFromDir(startPeg, jump));
}

CPathDirs CJump::GetPathDirs() const
{
	switch (jumpType) {
	case SingleJump:
		return (CPathDirs(direction, NOTADIR));
	case DoubleStraight:
		return (CPathDirs(direction, direction));
	case DoubleDiamond:
		return (CPathDirs(direction - 1, direction));
	case DoubleSquare:
		return (CPathDirs(direction - 1, direction + 1));
	case DoubleShortDiamond:
		return (CPathDirs(direction - 2, direction + 1));
	default:
		return (CPathDirs());
	}
}//end GetPathDirs

CDir CJump::GetPathDir(eLeftRight const leftRight) const
{
	if (leftRight == LEFT) {
		switch (jumpType) {
		case SingleJump:
			return (direction);
		case DoubleStraight:
			return (direction);
		case DoubleDiamond:
			return (direction - 1);
		case DoubleSquare:
			return (direction - 1);
		case DoubleShortDiamond:
			return (direction - 2);
		}
	}
	else {
		switch (jumpType) {
		case SingleJump:
			return (NOTADIR);
		case DoubleStraight:
			return (direction);
		case DoubleDiamond:
			return (direction);
		case DoubleSquare:
			return (direction + 1);
		case DoubleShortDiamond:
			return (direction + 1);
		}
	}
	return (NOTADIR);
}//end GetPathDir

bool CJump::IsDouble() const
{
	return (jumpType != SingleJump);
}//end IsDouble

bool CJump::IsDoubleStraight() const
{
	return (jumpType == DoubleStraight);
}//end IsDouble

CJump::CJump(CDir const direction, eJump const jumpType)
{
	CJump::direction = direction;
	CJump::jumpType = jumpType;
	return;
}

MYPoint GetDestFromDir(const MYPoint& startPeg, CDir const direction)
{
	switch (direction) {
		case leftUp:
			return (MYPoint(startPeg.x - 2, startPeg.y - 1));
		case upLeft:
			return (MYPoint(startPeg.x - 1, startPeg.y - 2));
		case upRight:
			return (MYPoint(startPeg.x + 1, startPeg.y - 2));
		case rightUp:
			return (MYPoint(startPeg.x + 2, startPeg.y - 1));
		case rightDown:
			return (MYPoint(startPeg.x + 2, startPeg.y + 1));
		case downRight:
			return (MYPoint(startPeg.x + 1, startPeg.y + 2));
		case downLeft:
			return (MYPoint(startPeg.x - 1, startPeg.y + 2));
		case leftDown:
			return (MYPoint(startPeg.x - 2, startPeg.y + 1));
		default:
			return MYPoint(0,0);
	}
}//end GetDestFromDir

MYPoint GetDestFromDir(const MYPoint& startPeg, CDir const direction, eJump const jumpType)
{
	switch (jumpType) {
		case SingleJump:
			return (GetDestFromDir(startPeg, direction));
		case DoubleStraight:
			return (GetDestFromDir(GetDestFromDir(startPeg, direction), direction));
		case DoubleDiamond:
			return (GetDestFromDir(GetDestFromDir(startPeg, direction - 1), direction));
		case DoubleSquare:
			return (GetDestFromDir(GetDestFromDir(startPeg, direction - 1), direction + 1));
		case DoubleShortDiamond:
			return (GetDestFromDir(GetDestFromDir(startPeg, direction - 2), direction + 1));
		default:
			return MYPoint(0,0);
	}
}//end GetDestFromDir

MYPoint GetDestFromDir(const MYPoint& startPeg, const CJump& jump)
{
	return (GetDestFromDir(startPeg, jump.direction, jump.jumpType));
}//end GetDestFromDir

eJump GetJumpType(const MYPoint& StartPeg,
				  const MYPoint& DestPeg)
{
	int x = abs(StartPeg.x - DestPeg.x);
	int y = abs(StartPeg.y - DestPeg.y);
	switch (x + y)
	{
	case 0:
	case 1:
		return NOTAJUMP;
	case 2:
		return DoubleShortDiamond;
	case 3:
		return SingleJump;
	case 4:
		if (x == 1 || y == 1) {
			return DoubleSquare;
		}
		else if (x == 0 || y == 0) {
			return DoubleDiamond;
		}
		else {
			return NOTAJUMP;
		}
	case 5:
		return NOTAJUMP;
	case 6:
		if (x == 3) {
			return DoubleDiamond;
		}
		else if (x == 2 || y == 2) {
			return DoubleStraight;
		}
		else {
			return NOTAJUMP;
		}
	default:
		return NOTAJUMP;
	}
}//end GetJumpType

CJump GetJumpFromPegs(const MYPoint& StartPeg,
					  const MYPoint& DestPeg)
{
	PERFORMANCE_MARKER;
	CJump jump;
	jump.jumpType = GetJumpType(StartPeg, DestPeg);
	if (jump.jumpType != NOTAJUMP) {
		int changeX = StartPeg.x - DestPeg.x;
		int changeY = StartPeg.y - DestPeg.y;
		int absX = abs(changeX);
		int absY = abs(changeY);
		bool left = changeX >= 0;
		bool up = changeY >= 0;
		bool sidesGreater = absX >= absY; //true == leftUp, false == upLeft

		if (jump.jumpType == DoubleDiamond || jump.jumpType == DoubleShortDiamond) {
			left = changeX > 0 || (changeX == 0 && (changeY == -4 || changeY == -2));
			up = changeY > 0 || (changeY == 0 && (changeX == 4 || changeX == 2));
			if ((left == true && up == true)
				|| (left == false && up == false)) {
				sidesGreater = absX != absY;
			}
			else {
				sidesGreater = absX == absY;
			}
		}

		if (left == true && up == true && sidesGreater == true) {
			jump.direction = leftUp;
		}
		else if (left == true && up == true && sidesGreater == false) {
			jump.direction = upLeft;
		}
		else if (left == false && up == true && sidesGreater == false) {
			jump.direction = upRight;
		}
		else if (left == false && up == true && sidesGreater == true) {
			jump.direction = rightUp;
		}
		else if (left == false && up == false && sidesGreater == true) {
			jump.direction = rightDown;
		}
		else if (left == false && up == false && sidesGreater == false) {
			jump.direction = downRight;
		}
		else if (left == true && up == false && sidesGreater == false) {
			jump.direction = downLeft;
		}
		else if (left == true && up == false && sidesGreater == true) {
			jump.direction = leftDown;
		}
		else {
			ASSERT(false);
		}
	}

	return jump;
}//end GetJumpFromPegs
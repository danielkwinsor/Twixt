#ifndef BASICTYPES_H
#define BASICTYPES_H

class MYPoint
{
public:
	MYPoint() {return;};
	MYPoint(int const x, int const y) {MYPoint::x = (char)x; MYPoint::y = (char)y; return;};
#ifdef DEBUG
	short	x;
	short	y;
	bool operator == (MYPoint compare) const {return (*(int*)this == *(int*)&compare);};
	bool operator != (MYPoint compare) const {return (*(int*)this != *(int*)&compare);};
#else
	char	x;
	char	y;
	bool operator == (MYPoint compare) const {return (*(short*)this == *(short*)&compare);};
	bool operator != (MYPoint compare) const {return (*(short*)this != *(short*)&compare);};
#endif
};

class CPeg
{
public:
	MYPoint	peg;
	ePlayer	player;

	CPeg() {return;};
	CPeg(MYPoint peg, ePlayer player) {CPeg::peg = peg; CPeg::player = player; return;};
};

class CSolution
{
public:
	MYPoint	solution;
	float	solutionWeight;

	CSolution() {return;};
	CSolution(MYPoint solution, float solutionWeight) {CSolution::solution = solution; CSolution::solutionWeight = solutionWeight; return;};
};

class CDir
{
public:
	CDir	() {return;};

	void	operator++(int);//postfix
	void	operator++();//prefix
	CDir	operator+(int amount) const;
	CDir	operator-(int amount) const;
	bool	operator==(CDir const dir) const;
	operator const int() const {return static_cast<int>(dir);};
	CDir	GetOppositeDirection() const;

#ifdef DEBUG
	eDir		dir;
	CDir		(eDir direction) {dir = direction; return;};
	CDir		(int direction) {dir = static_cast<eDir>(direction); return;};
#else
	char		dir;
	CDir		(eDir direction) {dir = static_cast<char>(direction); return;};
	CDir		(int direction) {dir = static_cast<char>(direction); return;};
#endif
};

class CPathDirs
{
public:
	CPathDirs	() {return;};
	CPathDirs	(CDir leftDir, CDir rightDir);

	CDir	leftDir;
	CDir	rightDir;
private:
};

enum eAndOr
{
	OR = false,//false
	AND = true//true
};

class CPathReturn
{
public:
	bool	leftPath;
	bool	rightPath;
	eAndOr	andOr;//true is and, false is or
	bool	operator == (bool value);
	bool	operator != (bool value);
};

class CJumpType
{
public:
#ifdef DEBUG
	eJump		jumpType;
	operator eJump () const {return jumpType;};
	void operator = (const eJump jump) {jumpType = jump;};
#else
	char		jumpType;
	operator eJump () const {return static_cast<eJump>(jumpType);};
	void operator = (const eJump jump) {jumpType = static_cast<char>(jump);};
#endif
};

class CJump
{
public:
	CJump		() {return;};
	CJump		(CDir const direction, eJump const jumpType = SingleJump);
	bool		IsDouble()const;
	bool		IsDoubleStraight()const;
	CPathDirs	GetPathDirs()const;
	CDir		GetPathDir(eLeftRight const leftRight)const;
	CJumpType	jumpType;
	CDir		direction;

};

class CLink
{
public:
	CLink() {return;};
	CLink(const MYPoint& startPeg, const CJump& jump);
	CLink(const MYPoint& startPeg, CDir const direction);

	bool		IsDouble()const;
	bool		IsDoubleStraight()const;
	CPathDirs	GetPathDirs()const;
	CDir		GetPathDir(eLeftRight const leftRight)const;
	CLink		GetReversedLink()const;
	MYPoint		GetDestFromDir()const;
	MYPoint		GetIntPeg(eLeftRight const intPeg)const;
	void		Set(const MYPoint& startPeg, const CJump& jump);
	void		Set(const MYPoint& startPeg, CDir const direction);
	int			convertToInt() const;
	int			convertToInt(eSides const side) const;

	bool		operator==(const CLink& compare)const;
	operator	int();

	MYPoint		startPeg;
	CJump		jump;
};

typedef std::list<CLink> NineLinks;

MYPoint	GetDestFromDir(const MYPoint& startPeg, CDir const direction);
MYPoint	GetDestFromDir(const MYPoint& startPeg, CDir const direction, eJump const jumpType);
MYPoint	GetDestFromDir(const MYPoint& startPeg, const CJump& jumpType);

struct AStar_Data
{
	unsigned int	AStarF;
	unsigned int	AStarG;
	unsigned int	AStarH;
	CLink			ParentLink;
};

class JumpStartData
{
public:
	JumpStartData();
	JumpStartData(eSides const startSide,
				  const MYPoint& Dest,
				  ePlayer const player);
	
	eSides		startSide;
	MYPoint		Dest;
	ePlayer		player;
};

eJump		GetJumpType		(const MYPoint& StartPeg,
							const MYPoint& DestPeg);

CJump		GetJumpFromPegs	(const MYPoint& StartPeg,
							const MYPoint& DestPeg);

#endif
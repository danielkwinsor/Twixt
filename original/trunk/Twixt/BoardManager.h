#ifndef BOARD_MANAGER_H
#define BOARD_MANAGER_H
#include "stdafx.h"
using namespace std;

class SharedAStarData
{
public:
	char		numLinks;
	char		linkGroup;
	char		blockedDirs[NUMDIRS];
	bool		linkedDirs[NUMDIRS];
	ePlayer		owner;
	ePlayer		originalOwner;
	bool		isOwnerEnemy		(ePlayer const player);
	bool		isOwnerLinkable		(ePlayer const player);
	bool		isOwnerAPlayer		();

};

class MainAStarData
{
public:
	eAStar		AStarStatus;
	AStar_Data	AStarData;

};

class CBoardManager
{
private:
	MainAStarData	MainBoard[MAXBOARDSIZE][MAXBOARDSIZE];
	//pMainBoard is a pointer to an array of MainAStarDatas
	MainAStarData	(*pMainBoard)[MAXBOARDSIZE][MAXBOARDSIZE];

	//SharedBoard is a pointer to an array of SharedAStarDatas
	SharedAStarData		(*SharedBoard)[MAXBOARDSIZE][MAXBOARDSIZE];

	NineLinks		leftNine;
	NineLinks		rightNine;

public:
	int				XBoardSize;
	int				YBoardSize;

	ePlayer			currentPlayer;//used to determine whether a double needs an extra turn

	CBoardManager();
	CBoardManager(SharedAStarData (*SharedBoard)[MAXBOARDSIZE][MAXBOARDSIZE],
		int const XBoardSize,
		int const YBoardSize);

	void	GetDoublesFromPeg		(const MYPoint& Peg,
									ePlayer const player,
									vector<CLink>& pDoubles);

	int		CountTurnsToLink		(const CLink& link,
									ePlayer const player);

	vector<MYPoint>* GetPlayerPegList(ePlayer const player);

	void	SetBoardSize			(int const xSize,
									int const ySize);

	void	GetNineLinks			(const CLink& link,
									NineLinks& nineLinks);

	bool	canEnemyBlockLinkLogic	(const NineLinks& pNineLinks,
									ePlayer const linkPlayer);

	bool	CanPlayerBlockLinkLogic	(const NineLinks& pNineLinks,
									ePlayer const pegPlayer);

	bool	arePegsLinked			(const MYPoint& Peg1,
									const MYPoint& Peg2);

	bool	arePegsLinked			(const CLink& link);

	bool	canLinkBeBlocked		(const CLink& link,
									ePlayer const player);

	bool	canLinkBeBlocked		(const CLink& link,
									ePlayer const player,
									bool const opponentsTurn);

	CPathReturn	willPegBlockLink	(const MYPoint& Peg,
									const CLink& link,
									ePlayer const pegPlayer,
									ePlayer const linkPlayer);

	bool	canPegBlockLink			(const MYPoint& peg,
									const CLink& link,
									ePlayer const pegPlayer,
									ePlayer const linkPlayer);

	bool	willPegBlockJump		(const MYPoint& Peg,
									const MYPoint& linkPeg,
									CDir const linkDir,
									ePlayer const pegPlayer,
									ePlayer const linkPlayer);

	CPathReturn	canPegLink			(const MYPoint& Peg,
									const CJump& jump,
									ePlayer const player);

	bool	doesPegHaveLinks		(const MYPoint& Peg);

	bool	isOwnerEnemy			(const MYPoint& Peg,
									ePlayer const player);

	bool	isOwnerAPlayer			(const MYPoint& Peg);

	bool	isOwnerThis				(const MYPoint& Peg,
									ePlayer const player);

	bool	isOwnerLinkable			(const MYPoint& Peg,
									ePlayer const player);

	bool	isPegValid				(const MYPoint& Peg,
									ePlayer const player);

	bool	isLinkValid				(const CLink& link,
									ePlayer const player);

	CPathReturn	isDestBlocked		(const MYPoint& Peg,
									const CJump& jump,
									ePlayer const player);

	bool	isDestBlocked			(const MYPoint& Peg,
									CDir const direction);

	CPathReturn	isDestLinked		(const MYPoint& Peg,
									const CJump& jump,
									ePlayer const player);

	bool	isDestLinked			(const MYPoint& Peg,
									CDir const direction);

	bool	isPegAvailable			(const MYPoint& Peg);

	bool	isPegWithinBoard		(const MYPoint& Source);

	bool	isPegWithinBoard		(const MYPoint& Source,
									ePlayer const player);

	bool	isLinkWithinBoard		(const CLink& link);

	bool	isPegOnSide				(const MYPoint& Peg,
									eSides const Side);

	CPathReturn	isLinkWithinBoard	(const CLink& link,
									ePlayer const player);

	bool	isSideValid				(ePlayer const player,
									eSides const DestSide);


	bool	compareCoordToSide		(const MYPoint& Peg,
									eSides const DestSide);

	void	insertPeg				(const MYPoint& Source,
									ePlayer const player);

	void	removePeg				(const MYPoint& Source,
									ePlayer const player);

	int		GetJumpTypeWeight		(eJump const jumpType);

	int		GetJumpTypeCost			(eJump const jumpType);

	ePlayer GetOwner				(const MYPoint& Peg);

	ValidSides	GetValidSides		(ePlayer const player);

	int		GetAStarG				(const MYPoint& Peg);
	void	SetAStarG				(const MYPoint& Peg,
									int const G);

	int		GetAStarF				(const MYPoint& Peg);
	void	SetAStarF				(const MYPoint& Peg,
									int const F);

	int		GetAStarH				(const MYPoint& Peg);
	void	SetAStarH				(const MYPoint& Peg,
									int const H);

	CLink	GetAStarLink			(const MYPoint& ChildPeg);
	void	SetAStarLink			(const MYPoint& ChildPeg,
									const CLink& ParentLink);

	eAStar	GetAStarStatus			(const MYPoint& Peg);
	void	SetAStarStatus			(const MYPoint& Peg,
									eAStar const status);


	int		GetLinkGroup			(const MYPoint& Peg);
	void	SetLinkGroup			(const MYPoint& Peg,
									int const linkGroup);

	MainAStarData*	GetMainAStarData(const MYPoint& Peg);

	void	ClearPegList			();

	bool	canDoubleBeBlocked		(const CLink& Link,
									ePlayer const player,
									bool const bOpponentsTurn);

	bool	canPegLink				(const MYPoint& Peg,
									CDir const direction,
									ePlayer const player);

	bool	canPegAndLinkBeBlocked	(const CLink& link,
									const MYPoint& pegInLink,
									ePlayer const player);

	bool	isDestLinked			(const MYPoint& Peg,
									CDir const direction,
									ePlayer const player);

private:
	void	RemoveDuplicateNineLinks(NineLinks& nineLinks,
									NineLinks& otherLinks,
									NineLinks& duplicateLinks);

	void	addLink					(const MYPoint& Peg,
									CDir const direction);

	void	addBlock				(const MYPoint& Peg,
									CDir const direction);

	void	removeLink				(const MYPoint& Peg,
									CDir const direction);

	void	removeBlock				(const MYPoint& Peg,
									CDir const direction);

	void	removeInvalidNineLinks	(NineLinks& nineLinks,
									bool const wasEmpty,
									NineLinks::iterator front);

	bool	canDoubleBeBlockedLogic	(const CLink& link,
									ePlayer const player);

	bool	canPegBlockLinkLogic	(const MYPoint& peg,
									const CLink& link,
									ePlayer const pegPlayer,
									ePlayer const linkPlayer);

	bool	canPegBlockDouble		(const MYPoint& peg,
									const CLink& link,
									ePlayer const pegPlayer,
									ePlayer const linkPlayer);

	bool	canPegBlockDoubleLogic	(const MYPoint& peg,
									const CLink& link,
									ePlayer const pegPlayer);

	bool	canPathLink				(const MYPoint& Peg,
									CDir const dir1,
									CDir const dir2,
									ePlayer const player);

	bool	isDestBlocked			(const MYPoint& Peg,
									CDir const direction,
									ePlayer const player);

	void	BuildGroupList			(const MYPoint& Peg,
									list<MYPoint>& groupList);

	int		GetNextLinkGroup		();
};

#endif
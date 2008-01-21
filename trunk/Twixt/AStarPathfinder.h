
#ifndef ASTAR_PATHFINDER_H
#define ASTAR_PATHFINDER_H
#include "stdafx.h"

using namespace std;

class CPath : public list<CLink>
{
public:
	void	BuildPathList	(const MYPoint& LastStep,
							eSides const TerminalSide,
							const MYPoint& TerminalPeg,
							CBoardManager& pBoard);

	void	GetIntersection	(const CPath& enemyPath,
							CPath& pPathIntersection,
							CPath& pEnemyIntersection,
							CBoardManager& pBoard) const;

	void	PathToLinks		(CPath& pLinkList,
							CBoardManager& pBoard) const;

	void	OrderPath		(eSides const side);

	void	OrderLinks		(eSides const side);

private:
	int		GetBestDistance	(const CLink& link,
							const CLink& compare) const;

	void	InsertIntoPathList(const CLink& link,
							bool const wasEmpty);
};

class AStarPathfinder : public CBoardManager
{
public:
	AStarPathfinder();
	AStarPathfinder(SharedAStarData (*SharedBoard)[MAXBOARDSIZE][MAXBOARDSIZE],
		int const XBoardSize,
		int const YBoardSize);

	vector<MYPoint>			ClosedList;
	CBinaryHeap<MYPoint>		OpenHeap;

	HEAP<MYPoint>	AStar	(const MYPoint& Source,
							const MYPoint& Dest,
							ePlayer const player,
							eSides const DestSide,
							bool const completeSearch);

	void	JumpStartAStar	(JumpStartData const jumpStartData);

	void	ResetAStarList	();

	int		CountLinks		(const MYPoint& Peg,
							ePlayer const player);

	void	CountLinksAndBlocksLogic(const MYPoint& Peg,
							CDir const dir,
							ePlayer const player,
							int* pLinks,
							int* pBlocks);

	void	CountLinksAndBlocks(const MYPoint& Peg,
							ePlayer const player,
							int* pLinks,
							int* pBlocks);

	int		CountDoubles	(const MYPoint& Peg,
							ePlayer const player);

	float	currentAStarWeightsScore;//0.0
	float	bestAStarWeightsScore;//0.0

	void	LoadAStarWeights	();
	void	SaveAStarWeights	();
	void	PerturbAStarWeights	();

	void	LoadAStarWeightsFromBackup(std::vector<std::vector<int>>& weights);
	void	SaveAStarWeightsToBackup(std::vector<std::vector<int>>& weights);

private:
	bool	ExecuteAStarLogic(const MYPoint& Source,
							 const MYPoint& DestForCalcH,
							 const CJump& jump,
							 ePlayer const player,
							 eSides const DestSide,
							 bool const completeSearch);

	int		CalcH			(const MYPoint& Source,
							const MYPoint& Dest,
							eSides const DestSide,
							ePlayer const player);

	int		CalcJumpH		(const CLink& Link,
							ePlayer const player);

	bool	ReachedDest		(MYPoint& Peg,
							MYPoint Dest,
							eSides const DestSide);

	int		GetAStarLinkWeight	();
	int		GetAStarBlockWeight	();
	int		GetAStarDoubleSetupWeight	();

public://sorry but must be public
	void	SetAStarLinkWeight	(int const newLinkWeight);
	void	SetAStarBlockWeight	(int const newBlockWeight);
	void	SetAStarDoubleSetupWeight	(int const newDoubleWeight);

};

#endif

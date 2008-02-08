
#ifndef ASTAR_PATHFINDER_H
#define ASTAR_PATHFINDER_H
#include "stdafx.h"

using namespace std;

class CAStarWeights
{
public:
	float	weightsScore;
	int		linksWeight;//500
	int		blocksWeight;//200
	int		doubleWeight;//200

	bool	operator == (const CAStarWeights& compare) {return ((this->linksWeight == compare.linksWeight)
															&& (this->blocksWeight == compare.blocksWeight)
															&& (this->doubleWeight == compare.doubleWeight));};
};

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

	void	MergePathList	(const CPath& otherPath);

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
	CBinaryHeap<MYPoint>	OpenHeap;

	HEAP<MYPoint>	AStar	(const MYPoint& Source,
							const MYPoint& Dest,
							ePlayer const player,
							eSides const DestSide,
							bool const completeSearch);

	HEAP<MYPoint>	_DebugPath(const CPath& path,
							const MYPoint& Source,
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

	void	LoadAStarWeightsFromBackup(std::vector<CAStarWeights>& weights);
	void	SaveAStarWeightsToBackup(std::vector<CAStarWeights>& weights);

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
	float	GetAStarWeightsScore();
public://sorry but must be public
	void	SetAStarWeights	(int const newLinkWeight,
							int const newBlockWeight,
							int const newDoubleWeight);

};

#endif

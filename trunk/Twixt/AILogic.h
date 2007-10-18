
#ifndef AILOGIC_H
#define AILOGIC_H
#include "stdafx.h"

using namespace std;

class AILogic : public AStarPathfinder
{
public:
	int		linksWeight;
	int		blocksWeight;
	int		doubleWeight;

	unsigned int	NUMTURNSINHISTORY;//2
	float	baseDefenseWeight;//1.0
	float	baseOffenseWeight;//1.0
	float	offRiskyDoubleJump;//0.8
	float	defHasNoLinks;//0.8
	float	defIsStartPeg;//0.8
	float	defCantBlockLink;//0.35
	float	defEndBlock;//0.8
	float	defEndBlockStraight;//0.9
	float	defBlocks1JumpLink;//1.25
	float	defBlocks2JumpLink;//0.85
	float	defBlocks3JumpLink;//1.05
	float	offDoesntBlockOpponent;//0.9

	AILogic();
	AILogic(SharedAStarData (*SharedBoard)[MAXBOARDSIZE][MAXBOARDSIZE],
		CThreadManager* pThreadManager,
		int const XBoardSize,
		int const YBoardSize,
		eDifficulty const difficulty);

	void	Init			(int const XBoardSize,
							int const YBoardSize,
							eDifficulty const difficulty,
							SharedAStarData (*SharedBoard)[MAXBOARDSIZE][MAXBOARDSIZE]);

	int		GetBestPath		(ePlayer const opponent,
							CPath* pPathList);

	void	DoTurn			(MYPoint* Dest,
							ePlayer const player,
							ePlayer const opponent);

	void	DoFirstTurn		(MYPoint* Dest,
							ePlayer const player);

	MYPoint	generateRandomXYCoord(int counter,
							ePlayer const player,
							eSides const Side);

	void	GetStartData	(ePlayer const player,
							MYPoint& StartPeg,
							MYPoint& DestPeg,
							eSides& startSide,
							eSides& destSide,
							vector<MYPoint>** pPegList);

	bool	CheckForWin		(ePlayer const player);

	int		CountBlocksFromDouble(const CLink& doubleLink,
							vector<CLink>& skipLinks,
							ePlayer const player,
							const CPath& enemyIntersection);

	int		CountDoubleBlocks(const MYPoint& peg,
							ePlayer const player,
							const CPath& enemyIntersection);

	void	UndoTurn		();

private:
	CThreadManager*			pThreadManager;
	CBinaryHeap<MYPoint>		heap;
	eDifficulty				difficulty;

	vector<MYPoint>			offensivePegs;
	vector<MYPoint>			defensivePegs;
	vector<int>				offensiveValues;
	vector<int>				defensiveValues;
	vector<int>				defensiveBaseValues;
	vector<int>				playerTurns;
	vector<int>				opponentTurns;

	void	LoadAIWeights	();

	int		CanPathBeBlocked(const CPath& path,
							ePlayer const player);

	int		CountTurnsToComplete(const CPath& path,
							ePlayer const player);

	void	GeneralEvaluation(vector<MYPoint>& pegs,
							vector<int>& values);

	void	EvaluateDefense(const CPath& enemyPath,
							ePlayer const player,
							ePlayer const opponent,
							const CPath& pathIntersection,
							const CPath& enemyIntersection);

	void	EvaluateDefenseLogic(const MYPoint& peg,
							vector<MYPoint>& linkPegs,
							const CLink& link,
							ePlayer const player,
							ePlayer const opponent,
							const CPath& enemyIntersection);

	int		GetLinksWeight	();

	int		GetBlocksWeight	();

	int		GetSetupWeight	();

	int		GetDefenseJumpTypeWeight(eJump const jumpType);

	void	GetLinksWithPeg	(const MYPoint& Peg,
							const CPath& links,
							CPath& pLinksWithPeg);

	int		EvaluatePeg		(const MYPoint& Peg,
							const CLink& Link,
							const CLink& connectingLink,
							ePlayer const player);

	int		EvaluatePegLogic(const MYPoint& Peg,
							const CLink& Link,
							ePlayer const player);

	void	EvaluateOffense(const CPath& PathList,
							ePlayer const player);

	void	EvaluateOffenseLogic(const MYPoint& Peg,
							ePlayer const player,
							const CLink& link,
							const CLink& connectingLink);

	void	MergeOffAndDefValues(vector<MYPoint>& pegs,
							vector<int>& values);

	void	AdjustWeights	(const CPath& path,
							const CPath& enemyPath,
							ePlayer const player,
							ePlayer const enemy);

	MYPoint	GetBestPeg		(const vector<MYPoint>& pegs,
							const vector<int>& values);

	int		CountBlocks		(const MYPoint& Peg,
							ePlayer const player,
							const CPath& EnemyIntersection);

};

#endif
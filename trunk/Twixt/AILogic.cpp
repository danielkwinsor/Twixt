
#include "stdafx.h"

using namespace std;

AILogic::AILogic(SharedAStarData (*SharedBoard)[MAXBOARDSIZE][MAXBOARDSIZE],
				 CThreadManager* pThreadManager,
				 int const XBoardSize,
				 int const YBoardSize,
				 eDifficulty const difficulty)
: AStarPathfinder(SharedBoard, XBoardSize, YBoardSize)
{
	AILogic::pThreadManager = pThreadManager;
	AILogic::difficulty = difficulty;
	Init(XBoardSize, YBoardSize, difficulty, SharedBoard);
	playerTurns.clear();
	opponentTurns.clear();
	currentWeightsScore = 0.0f;
	return;
}//end ctor

void AILogic::LoadAIWeights()
{
	ifstream weights("AIBestWeights.txt");
	if (weights) {
		char temp[128];
		weights >> bestAIWeightsScore; weights.getline(temp, 128);
		weights >> NUMTURNSINHISTORY; weights.getline(temp, 128);
		weights >> baseDefenseWeight; weights.getline(temp, 128);
		weights >> baseOffenseWeight; weights.getline(temp, 128);
		weights >> offRiskyDoubleJump; weights.getline(temp, 128);
		weights >> defHasNoLinks; weights.getline(temp, 128);
		weights >> defIsStartPeg; weights.getline(temp, 128);
		weights >> defCantBlockLink; weights.getline(temp, 128);
		weights >> defEndBlock; weights.getline(temp, 128);
		weights >> defEndBlockStraight; weights.getline(temp, 128);
		weights >> defBlocks1JumpLink; weights.getline(temp, 128);
		weights >> defBlocks2JumpLink; weights.getline(temp, 128);
		weights >> defBlocks3JumpLink; weights.getline(temp, 128);
		weights >> offDoesntBlockOpponent; weights.getline(temp, 128);
	}
	else {
		bestAIWeightsScore = 0.0f;
		NUMTURNSINHISTORY = 2;//2
		baseDefenseWeight = 1.0f;//1.0
		baseOffenseWeight = 1.0f;//1.0
		offRiskyDoubleJump = 0.8f;//0.8
		defHasNoLinks = 0.8f;//0.8
		defIsStartPeg = 0.8f;//0.8
		defCantBlockLink = 0.35f;//0.35
		defEndBlock = 0.8f;//0.8
		defEndBlockStraight = 0.9f;//0.9
		defBlocks1JumpLink = 1.25f;//1.25
		defBlocks2JumpLink = 0.85f;//0.85
		defBlocks3JumpLink = 1.05f;//1.05
		offDoesntBlockOpponent = 0.9f;//0.9
	}
	return;
}//end LoadAIWeights

void AILogic::SaveAIWeights()
{
	if (currentAIWeightsScore > bestAIWeightsScore) {
		ofstream weights("AIBestWeights.txt");
		bestAIWeightsScore = currentAIWeightsScore;

		weights << currentAIWeightsScore << " = bestAIWeightsScore\n";

		weights << NUMTURNSINHISTORY << " = NUMTURNSINHISTORY\n";
		weights << baseDefenseWeight << " = baseDefenseWeight\n";
		weights << baseOffenseWeight << " = baseOffenseWeight\n";
		weights << offRiskyDoubleJump << " = offRiskyDoubleJump\n";
		weights << defHasNoLinks << " = defHasNoLinks\n";
		weights << defIsStartPeg << " = defIsStartPeg\n";
		weights << defCantBlockLink << " = defCantBlockLink\n";
		weights << defEndBlock << " = defEndBlock\n";
		weights << defEndBlockStraight << " = defEndBlockStraight\n";
		weights << defBlocks1JumpLink << " = defBlocks1JumpLink\n";
		weights << defBlocks2JumpLink << " = defBlocks2JumpLink\n";
		weights << defBlocks3JumpLink << " = defBlocks3JumpLink\n";
		weights << offDoesntBlockOpponent << " = offDoesntBlockOpponent\n";
	}
	else {
		ofstream weights("AICurrentWeights.txt");

		weights << currentAIWeightsScore << " = currentAIWeightsScore\n";

		weights << NUMTURNSINHISTORY << " = NUMTURNSINHISTORY\n";
		weights << baseDefenseWeight << " = baseDefenseWeight\n";
		weights << baseOffenseWeight << " = baseOffenseWeight\n";
		weights << offRiskyDoubleJump << " = offRiskyDoubleJump\n";
		weights << defHasNoLinks << " = defHasNoLinks\n";
		weights << defIsStartPeg << " = defIsStartPeg\n";
		weights << defCantBlockLink << " = defCantBlockLink\n";
		weights << defEndBlock << " = defEndBlock\n";
		weights << defEndBlockStraight << " = defEndBlockStraight\n";
		weights << defBlocks1JumpLink << " = defBlocks1JumpLink\n";
		weights << defBlocks2JumpLink << " = defBlocks2JumpLink\n";
		weights << defBlocks3JumpLink << " = defBlocks3JumpLink\n";
		weights << offDoesntBlockOpponent << " = offDoesntBlockOpponent\n";

	}
	return;
}//end SaveAIWeights

void AILogic::PerturbAIWeights()
{
	baseDefenseWeight *= (((rand()%2000) * 0.0002f) + 0.9f);
	baseOffenseWeight *= (((rand()%2000) * 0.0002f) + 0.9f);
	offRiskyDoubleJump *= (((rand()%2000) * 0.0002f) + 0.9f);
	defHasNoLinks *= (((rand()%2000) * 0.0002f) + 0.9f);
	defIsStartPeg *= (((rand()%2000) * 0.0002f) + 0.9f);
	defCantBlockLink *= (((rand()%2000) * 0.0002f) + 0.9f);
	defEndBlock *= (((rand()%2000) * 0.0002f) + 0.9f);
	defEndBlockStraight *= (((rand()%2000) * 0.0002f) + 0.9f);
	defBlocks1JumpLink *= (((rand()%2000) * 0.0002f) + 0.9f);
	defBlocks2JumpLink *= (((rand()%2000) * 0.0002f) + 0.9f);
	defBlocks3JumpLink *= (((rand()%2000) * 0.0002f) + 0.9f);
	offDoesntBlockOpponent *= (((rand()%2000) * 0.0002f) + 0.9f);


	if (baseDefenseWeight < 0.2f || baseDefenseWeight > 4.0f) baseDefenseWeight = 1.0f;
	if (baseOffenseWeight < 0.2f || baseOffenseWeight > 4.0f) baseOffenseWeight = 1.0f;
	if (offRiskyDoubleJump < 0.2f || offRiskyDoubleJump > 4.0f) offRiskyDoubleJump = 0.8f;
	if (defHasNoLinks < 0.2f || defHasNoLinks > 4.0f) defHasNoLinks = 0.8f;
	if (defIsStartPeg < 0.2f || defIsStartPeg > 4.0f) defIsStartPeg = 0.8f;
	if (defCantBlockLink < 0.2f || defCantBlockLink > 4.0f) defCantBlockLink = 0.35f;
	if (defEndBlock < 0.2f || defEndBlock > 4.0f) defEndBlock = 0.8f;
	if (defEndBlockStraight < 0.2f || defEndBlockStraight > 4.0f) defEndBlockStraight = 0.9f;
	if (defBlocks1JumpLink < 0.2f || defBlocks1JumpLink > 4.0f) defBlocks1JumpLink = 1.25f;
	if (defBlocks2JumpLink < 0.2f || defBlocks2JumpLink > 4.0f) defBlocks2JumpLink = 0.85f;
	if (defBlocks3JumpLink < 0.2f || defBlocks3JumpLink > 4.0f) defBlocks3JumpLink = 1.05f;
	if (offDoesntBlockOpponent < 0.2f || offDoesntBlockOpponent > 4.0f) offDoesntBlockOpponent = 0.9f;

	return;
}//end PerturbAIWeights

void AILogic::UndoTurn()
{
	if (playerTurns.empty() == false) {
		playerTurns.pop_back();
		opponentTurns.pop_back();
	}
	return;
}//end UndoTurn

void AILogic::Init(int const XBoardSize,
				   int const YBoardSize,
				   eDifficulty const difficulty,
				   SharedAStarData (*SharedBoard)[MAXBOARDSIZE][MAXBOARDSIZE])
{
	PERFORMANCE_MARKER
	AILogic::difficulty = difficulty;
	SetBoardSize(XBoardSize, YBoardSize);
	for (int x = 0; x < XBoardSize; x++) {
		for (int y = 0; y < YBoardSize; y++) {
			(*SharedBoard)[x][y].owner = CurrentlyUnowned;
			(*SharedBoard)[x][y].originalOwner = CurrentlyUnowned;
			(*SharedBoard)[x][y].numLinks = 0;
			(*SharedBoard)[x][y].linkGroup = 0;
			for (int z = 0; z < NUMDIRS; z++) {
				(*SharedBoard)[x][y].linkedDirs[z] = 0;
				(*SharedBoard)[x][y].blockedDirs[z] = 0;
			}
		}
	}
	ClearPegList();
	return;
}//end Init

void AILogic::GetStartData(ePlayer const player,
						   MYPoint& StartPeg,
						   MYPoint& DestPeg,
						   eSides& startSide,
						   eSides& destSide,
						   vector<MYPoint>** pPegList)
{
	if (isSideValid(player, TopAndBottom)) {
		startSide = TopSide;
		destSide = BottomSide;
		DestPeg = MYPoint(XBoardSize/2, YBoardSize-1);
		StartPeg = MYPoint(XBoardSize/2, 0);
		*pPegList = GetPlayerPegList(player);
	}
	else {
		startSide = LeftSide;
		destSide = RightSide;
		DestPeg = MYPoint(XBoardSize-1, YBoardSize/2);
		StartPeg = MYPoint(0, YBoardSize/2);
		*pPegList = GetPlayerPegList(player);
	}
	return;
}//end GetStartData

int AILogic::GetBestPath(ePlayer const player,
						 CPath* pPathList)
{
	PERFORMANCE_MARKER
	eSides startSide;
	eSides destSide;
	MYPoint DestPeg;
	MYPoint StartPeg;
	vector<MYPoint>* pPegList;
	GetStartData(player, StartPeg, DestPeg, startSide, destSide, &pPegList);
	bool jumpStartAStar = false;
	bool completeSearch = true;
	bool buildPathList = false;

	pThreadManager->PushAStarData(ThreadInput(XBoardSize, YBoardSize,
		StartPeg, DestPeg, destSide, player,
		true, JumpStartData(startSide, DestPeg, player),
		completeSearch, 0, buildPathList, currentPlayer));
	pThreadManager->PushAStarData(ThreadInput(XBoardSize, YBoardSize,
		DestPeg, StartPeg, startSide, player,
		true, JumpStartData(destSide, StartPeg, player),
		completeSearch, 0, buildPathList, currentPlayer));

	MYPoint nullPeg;
	vector<int> LinkGroupList;
	for each (MYPoint Peg in *pPegList) {
		int linkGroup = GetLinkGroup(Peg);
		bool add = true;
		if (linkGroup != 0) {
			//see if the peg is linked to a peg already searched
			if (find(LinkGroupList.begin(), LinkGroupList.end(), linkGroup) != LinkGroupList.end()) {
				add = false;
			}
		}
		//sides have already been searched
		if (isPegOnSide(Peg, startSide) == true) {
			add = false;
		}
		if (isPegOnSide(Peg, destSide) == true) {
			add = false;
		}

		if (add == true) {
			//make sure the linked pegs are not searched
			LinkGroupList.push_back(linkGroup);

			//find the paths from this peg to the 2 sides
			pThreadManager->PushAStarData(ThreadInput(XBoardSize, YBoardSize, Peg, DestPeg, destSide, player,
				jumpStartAStar, JumpStartData(), completeSearch, 1, buildPathList, currentPlayer));

			pThreadManager->PushAStarData(ThreadInput(XBoardSize, YBoardSize, Peg, StartPeg, startSide, player,
				jumpStartAStar, JumpStartData(), completeSearch, 2, buildPathList, currentPlayer));
		}
	}

	pThreadManager->WaitTillDone();
	MYPoint bestPeg = pThreadManager->GetBestPeg();
	pThreadManager->ClearData();

	int pathCost = 0;
	if (bestPeg != MYPoint(0,0)) {
		//although we have the best peg, the best path has been ruined, so reconstruct it
		HEAP<MYPoint> topHeap;
		ResetAStarList();
		topHeap = AStar(bestPeg, DestPeg, player, destSide, true);
		if (topHeap.key != -1) {
			pathCost += topHeap.key;
			pPathList->BuildPathList(topHeap.data, NOTASIDE, bestPeg, *this);
		}
		if (bestPeg != StartPeg) {
			ResetAStarList();
			topHeap = AStar(bestPeg, StartPeg, player, startSide, true);
			if (topHeap.key != -1) {
				pathCost += topHeap.key;
				pPathList->BuildPathList(topHeap.data, NOTASIDE, bestPeg, *this);
			}
		}
	}
	return pathCost;
}//end GetBestPath

void AILogic::EvaluateOffense(const CPath& PathList,
							   ePlayer const player)
{
	PERFORMANCE_MARKER
	CLink connectingLink = CLink();

	//handle the special case of the rearmost peg, it has no connectingLink
	EvaluateOffenseLogic(PathList.back().GetDestFromDir(), player,
		PathList.back().GetReversedLink(), connectingLink);

	CLink previous = PathList.front();
	for each (CLink link in PathList) {
		if (previous != link) {
			//nor does the first peg have a connectingLink
			connectingLink = previous.GetReversedLink();
		}
		previous = link;

		if (arePegsLinked(link.startPeg, link.GetDestFromDir()) == true) {
			continue;
		}
		EvaluateOffenseLogic(link.startPeg, player, link, connectingLink);

		if (link.IsDouble() == true) {
			EvaluateOffenseLogic(link.GetIntPeg(LEFT), player, link, connectingLink);

			if (link.IsDoubleStraight() == false) {
				EvaluateOffenseLogic(link.GetIntPeg(RIGHT), player, link, connectingLink);
			}
		}
	}
#ifdef DEBUG
	ofstream file("offense.txt");
	for (unsigned int index = 0; index < offensivePegs.size(); ++index) {
		file << '\n' << (int)offensivePegs[index].x << ' ' << (int)offensivePegs[index].y << ' ' << offensiveValues[index];
	}
#endif
	return;
}//end EvaluateOffense

void AILogic::EvaluateOffenseLogic(const MYPoint& Peg,
									 ePlayer const player,
									 const CLink& link,
									 const CLink& connectingLink)
{
	PERFORMANCE_MARKER
	if (isPegValid(Peg, player) == true && isOwnerThis(Peg, player) == false) {
		int pegRanking = EvaluatePeg(Peg, link, connectingLink, player);
		offensiveValues.push_back(pegRanking);
		offensivePegs.push_back(Peg);
	}
	return;
}//end EvaluateOffenseLogic

void AILogic::GetLinksWithPeg(const MYPoint& Peg,
							  const CPath& links,
							  CPath& pLinksWithPeg)
{
	PERFORMANCE_MARKER
	for each (CLink link in links) {
		if (Peg == link.startPeg || Peg == link.GetDestFromDir()) {
			pLinksWithPeg.push_back(link);
		}
	}
	return;
}//end GetLinksWithPeg

void AILogic::GeneralEvaluation(vector<MYPoint>& pegs,
								vector<int>& values)
{
	PERFORMANCE_MARKER
	for (unsigned int count = 0; count < pegs.size(); ++count) {
		MYPoint Peg = pegs[count];
		int value = values[count];
		value += (abs(XBoardSize / 2 - Peg.x) + abs(YBoardSize / 2 - Peg.y));
		values[count] = value;
	}
#ifdef DEBUG
	ofstream file("evaluation.txt");
	for (unsigned int index = 0; index < values.size(); ++index) {
		file << '\n' << (int)pegs[index].x << ' ' << (int)pegs[index].y << ' ' << values[index];
	}
#endif
	return;
}//end GeneralEvaluation

void AILogic::AdjustWeights(const CPath& path,
							const CPath& enemyPath,
							ePlayer const player,
							ePlayer const enemy)
{
	PERFORMANCE_MARKER
#pragma warning (disable: 4244)
	float numOpponentTurns = CountTurnsToComplete(enemyPath, enemy);
	float numPlayerTurns = CountTurnsToComplete(path, player);
	for (unsigned int count = playerTurns.size(); count < NUMTURNSINHISTORY; ++count) {
		playerTurns.push_back(numPlayerTurns);
		opponentTurns.push_back(numOpponentTurns);
	}

	float playerAccumulator = 0;
	float opponentAccumulator = 0;
	vector<int>::reverse_iterator turns = playerTurns.rbegin();
	for (unsigned int count = 0; count < NUMTURNSINHISTORY; ++count) {
		playerAccumulator += *turns;
		++turns;
	}
	turns = opponentTurns.rbegin();
	for (unsigned int count = 0; count < NUMTURNSINHISTORY; ++count) {
		opponentAccumulator += *turns;
		++turns;
	}
	playerTurns.push_back(numPlayerTurns);
	opponentTurns.push_back(numOpponentTurns);

	float defModifier = (playerAccumulator / opponentAccumulator)
						+ (numPlayerTurns / numOpponentTurns);
	float offModifier = (opponentAccumulator / playerAccumulator)
						+ (numOpponentTurns / numPlayerTurns);

	int playerBlocks = CanPathBeBlocked(enemyPath, enemy);
	int opponentBlocks = CanPathBeBlocked(path, player);

	if (playerBlocks > opponentBlocks) {
		offModifier *= 2.0f;
	}
	else if (opponentBlocks > playerBlocks) {
		defModifier *= 2.0f;
	}
	defModifier *= baseDefenseWeight;
	offModifier *= baseOffenseWeight;

	for (unsigned int index = 0; index < defensiveValues.size(); ++index) {
		defensiveValues[index] *= defModifier;
		defensiveBaseValues[index] *= defModifier;
	}
	for (unsigned int index = 0; index < offensiveValues.size(); ++index) {
		offensiveValues[index] *= offModifier;
	}
	return;
}//end AdjustWeights

void AILogic::MergeOffAndDefValues(vector<MYPoint>& pegs,
								   vector<int>& values)
{
	PERFORMANCE_MARKER
	heap.clear();
	bool found = false;
	int value;
	//compare offensive list to defensive list
	for (unsigned int index = 0; index < offensivePegs.size(); ++index) {
		MYPoint peg = offensivePegs[index];
		found = false;
		for (unsigned int compare = 0; compare < defensivePegs.size(); ++compare) {
			if (peg == defensivePegs[compare]) {
				//if they overlap, merge them
				value = offensiveValues[index] + defensiveValues[compare] + defensiveBaseValues[compare];
				values.push_back(value);
				pegs.push_back(peg);
				found = true;
				break;
			}
		}
		if (found == false) {
			//if not found, peg was offense only
			value = offensiveValues[index];
			values.push_back(value);
			pegs.push_back(peg);
		}
	}

	for (unsigned int index = 0; index < defensivePegs.size(); ++index) {
		MYPoint peg = defensivePegs[index];
		found = false;
		for (unsigned int compare = 0; compare < offensivePegs.size(); ++compare) {
			if (peg == offensivePegs[compare]) {
				//ignore pegs that overlap, they were already inserted
				found = true;
				break;
			}
		}
		if (found == false) {
			//if not found, peg was defense only
			value = defensiveValues[index] + defensiveBaseValues[index];
			values.push_back(value);
			pegs.push_back(peg);
		}
	}
#ifdef DEBUG
	ofstream file("merged.txt");
	for (unsigned int index = 0; index < values.size(); ++index) {
		file << '\n' << (int)pegs[index].x << ' ' << (int)pegs[index].y << ' ' << values[index];
	}
#endif
	return;
}//end MergeOffAndDefValues

MYPoint AILogic::GetBestPeg(const vector<MYPoint>& pegs,
						   const vector<int>& values)
{
	PERFORMANCE_MARKER
	heap.clear();
	for (unsigned int index = 0; index < pegs.size(); ++index) {
		MYPoint peg = pegs[index];
		int value = values[index];
		value = AdjustValueByDifficulty(value, difficulty);
		heap.insertElement(peg, value);
	}

	return heap.peekTopHeap().data;
}//end GetBestPeg

int AILogic::CanPathBeBlocked(const CPath& path,
							  ePlayer const player)
{
	PERFORMANCE_MARKER
	int blocks = 0;
	for each (CLink link in path) {
		if (arePegsLinked(link.startPeg, link.GetDestFromDir()) == false) {
			if (canLinkBeBlocked(link, player, true) == true) {
				if (canLinkBeBlocked(link, player, false) == false) {
					++blocks;
				}
			}
		}
	}
	return blocks;
}//end CanPathBeBlocked

int AILogic::EvaluatePeg(const MYPoint& Peg,
						 const CLink& Link,
						 const CLink& connectingLink,
						 ePlayer const player)
{
	PERFORMANCE_MARKER
	//assumes link is valid
	int links = CountLinks(Peg, player);
	int setup = CountDoubles(Peg, player);

	int cost = (links * GetLinksWeight() + setup * GetSetupWeight());
	if (cost == 0) {
		return 0;
	}
	float modifier = -1.0f;

	//decrease priority if the peg is on the side and doesn't block the opponent
	//the player should rather work on the other end of the path
	bool blocksOpponent = true;
	if (isPegOnSide(Peg, LeftAndRight) == true) {
		blocksOpponent = false;
		for (CDir dir = leftUp; dir != NOTADIR; ++dir) {
			if (canPegLink(Peg, dir, player) == true) {
				MYPoint Dest = GetDestFromDir(Peg, dir);
				if (abs(Peg.x - Dest.x) > 1) {
					blocksOpponent = true;
					break;
				}
			}
		}
	}
	else if (isPegOnSide(Peg, TopAndBottom) == true) {
		blocksOpponent = false;
		for (CDir dir = leftUp; dir != NOTADIR; ++dir) {
			if (canPegLink(Peg, dir, player) == true) {
				MYPoint Dest = GetDestFromDir(Peg, dir);
				if (abs(Peg.y - Dest.y) > 1) {
					blocksOpponent = true;
					break;
				}
			}
		}
	}
	//decrease priority if the peg is on the side and doesn't block the opponent
	if (blocksOpponent == false) {
		modifier *= offDoesntBlockOpponent;
	}

	//decrease priority if the peg starts a risky double jump
	if (canPegAndLinkBeBlocked(Link, Peg, player) == true) {
		modifier *= offRiskyDoubleJump;
	}
	if (connectingLink.startPeg != MYPoint(0,0)
		&& Peg == connectingLink.startPeg
		&& isDestLinked(connectingLink.startPeg, connectingLink.jump, player) == false
		&& canPegLink(connectingLink.startPeg, Link.jump, player) == true
		&& canPegAndLinkBeBlocked(connectingLink, Peg, player) == true) {
		modifier *= offRiskyDoubleJump;
	}

	if (Link.IsDouble() == true) {
		//peg is an intermediate peg, decrease priority if it doesn't complete a double jump
		int turns = CountTurnsToLink(Link, player);
		if (turns == 1 || turns == 2) {
			//check if the int peg completes a threatened double jump
			cost += EvaluatePegLogic(Peg, Link, player);
		}
		else {
			modifier *= (1.0f - (0.1f * turns));
		}
	}
	//lower numbers are better with the heap
	return static_cast<int>(cost * modifier);
}//end EvaluatePeg

int AILogic::EvaluatePegLogic(const MYPoint& Peg,
							  const CLink& Link,
							  ePlayer const player)
{
	PERFORMANCE_MARKER
	CPathDirs pathDirs = Link.GetPathDirs();
	CDir dir1;
	CDir dir2;
	if (Peg == GetDestFromDir(Link.startPeg, pathDirs.leftDir)) {
		//Peg falls on left path of a double jump
		dir1 = pathDirs.leftDir;
		dir2 = pathDirs.rightDir;
	}
	else {
		//Peg falls on right path of a double jump
		dir1 = pathDirs.rightDir;
		dir2 = pathDirs.leftDir;
	}

	//this intpeg is not player owned, so the double is linkable only if
	//the start and dest of the double are player owned
	if (canPegLink(Link.startPeg, dir1, player) == true
		&& canPegLink(Peg, dir2, player) == true) {
		//If the link can be blocked, give extra consideration to this peg,
		//since this peg completes the double
		if (canLinkBeBlocked(Link, player, true) == true) {
			int links, blocks;
			CountLinksAndBlocks(Peg, player, &links, &blocks);
			return TWOJUMPS + (blocks * GetBlocksWeight());
		}
	}
	return 0;
}//end EvaluatePegLogic

int AILogic::CountDoubleBlocks(const MYPoint& peg,
							   ePlayer const player,
							   const CPath& enemyIntersection)
{
	PERFORMANCE_MARKER
	int blocks = 0;
	vector<CLink> skipLinks;//don't count the same link that is part of 2 doubles
	vector<CLink> doubles;
	GetDoublesFromPeg(peg, player, doubles);
	for each (CLink doubleLink in doubles) {
		blocks += CountBlocksFromDouble(doubleLink, skipLinks, player, enemyIntersection);
	}
	return blocks;
}//end CountDoubleBlocks

int AILogic::CountBlocksFromDouble(const CLink& doubleLink,
								   vector<CLink>& skipLinks,
								   ePlayer const player,
								   const CPath& enemyIntersection)
{
	PERFORMANCE_MARKER
	int blocks = 0;
	NineLinks nineLinks;
	CPathDirs pathDirs = doubleLink.GetPathDirs();
	CLink link;
	MYPoint IntPeg = GetDestFromDir(doubleLink.startPeg, pathDirs.leftDir);
	if (isDestBlocked(doubleLink.startPeg, pathDirs.leftDir) == false
		&& isDestBlocked(IntPeg, pathDirs.rightDir) == false) {
		link.Set(IntPeg, CJump(pathDirs.rightDir));
		if (isLinkValid(link, player) == true) {
			if (find(skipLinks.begin(), skipLinks.end(), link) == skipLinks.end()) {
				nineLinks.clear();
				GetNineLinks(link, nineLinks);
				skipLinks.push_back(link);
			}
		}
	}
	if (doubleLink.IsDoubleStraight() == false) {
		IntPeg = GetDestFromDir(doubleLink.startPeg, pathDirs.rightDir);
		if (isDestBlocked(doubleLink.startPeg, pathDirs.rightDir) == false
			&& isDestBlocked(IntPeg, pathDirs.leftDir) == false) {
			link.Set(IntPeg, CJump(pathDirs.leftDir));
			if (isLinkValid(link, player) == true) {
				if (find(skipLinks.begin(), skipLinks.end(), link) == skipLinks.end()) {
					GetNineLinks(link, nineLinks);
					skipLinks.push_back(link);
				}
			}
		}
	}

	if (nineLinks.empty() == true) {
		return 0;
	}

	for each (CLink enemyLink in enemyIntersection) {
		if (find(nineLinks.begin(), nineLinks.end(), enemyLink) != nineLinks.end()) {
			++blocks;
		}
	}
	return blocks;
}//end CountBlocksFromDouble

int AILogic::CountBlocks(const MYPoint& Peg,
						 ePlayer const player,
						 const CPath& EnemyIntersection)
{
	PERFORMANCE_MARKER
	//assumes Peg is currently unowned but player is considering it
	int blocks = 0;
	NineLinks nineLinks;
	for (CDir dir = leftUp; dir != NOTADIR; ++dir) {
		CLink thisLink(Peg, dir);
		//if it is an intersection link, find any *extra* blocks
		nineLinks.clear();
		GetNineLinks(thisLink, nineLinks);
		for each (CLink enemy in EnemyIntersection) {
			if (Peg == enemy.startPeg || Peg == enemy.GetDestFromDir()) {
				++blocks;
			}
			else if (find(nineLinks.begin(), nineLinks.end(), enemy) != nineLinks.end()) {
				++blocks;
			}
		}

		MYPoint Dest = GetDestFromDir(Peg, dir);
		if (isPegWithinBoard(Dest) == true &&
			isDestBlocked(Peg, dir) == false) {
			if (isOwnerEnemy(Dest, player) == true) {
			//by inserting the peg here, we block opponents ability to link in this dir
				if (canPegLink(Peg, dir, GetOwner(Dest)) == true) {
					//unless it is already blocked
					++blocks;
				}
			}

			else if (canPegLink(Peg, dir, player) == true) {
				//count the blocks made from any links
				for each (CLink nine in nineLinks) {
					if (isOwnerEnemy(nine.startPeg, player) == true) {
						if (canPegLink(nine.startPeg, nine.jump.direction,
							GetOwner(nine.startPeg)) == true) {
							blocks += 2;
						}
					}
					else {
						MYPoint dest = nine.GetDestFromDir();
						if (isOwnerEnemy(dest, player) == true) {
							if (canPegLink(dest, nine.jump.direction, GetOwner(dest)) == true) {
								blocks += 2;
							}
						}
					}
				}
			}
		}
	}

	return blocks;
}//end CountBlocks

int AILogic::CountTurnsToComplete(const CPath& path,
								  ePlayer const player)
{
	PERFORMANCE_MARKER
	int turns = 0;
	if (path.empty() == false) {
		if (GetOwner(path.begin()->startPeg) != player) {
			turns = 1;
		}
	}
	for each (CLink link in path) {
		turns += CountTurnsToLink(link, player);		
		if (GetOwner(link.startPeg) != player) {
			turns -= 1;
		}
	}
	return turns;
}//end CountTurnsToComplete

void AILogic::DoTurnAndEval(MYPoint* Dest,
							ePlayer const player,
							ePlayer const opponent,
							std::vector<CSolution>& solutions,
							bool const forceEvalPegsOnPath)
{
	if (solutions.empty() == true) {
		return;
	}

	currentPlayer = player;
	eSides sides;
	MYPoint DestPeg;
	MYPoint StartPeg;
	isSideValid(player, TopAndBottom) ? sides = TopAndBottom : sides = LeftAndRight;

	//find the player's path only, enemy path may not be necessary
	CPath path;
	GetBestPath(player, &path);
	path.OrderPath(sides);
	if (path.empty() == true) {
		return;
	}

	std::vector<MYPoint> pegs;
	for each (CLink link in path) {
		pegs.push_back(link.startPeg);
		if (link.IsDouble() == true) {
			pegs.push_back(link.GetIntPeg(LEFT));
			if (link.IsDoubleStraight() == false) {
				pegs.push_back(link.GetIntPeg(RIGHT));
			}
		}
	}
	pegs.push_back(path.back().GetDestFromDir());

	//evaluate the path, do we have any of the solutions in it?
	float bestWeightsScore = 0.0f;
	for each (CSolution solution in solutions) {
		if (find(pegs.begin(), pegs.end(), solution.solution) != pegs.end()) {
			if (solution.solutionWeight > bestWeightsScore) {
				bestWeightsScore = solution.solutionWeight;
			}
		}
	}
	currentWeightsScore += bestWeightsScore;

	//if we found a solution peg on the path, then we can simulate the rest of the turn
	if (forceEvalPegsOnPath == true || bestWeightsScore != 0.0f) {
		CPath enemyPath;
		GetBestPath(opponent, &enemyPath);
		isSideValid(opponent, TopAndBottom) ? sides = TopAndBottom : sides = LeftAndRight;
		enemyPath.OrderPath(sides);

		CPath enemyIntersection;
		CPath pathIntersection;
		path.GetIntersection(enemyPath, pathIntersection, enemyIntersection, *this);

		defensivePegs.clear();
		defensiveValues.clear();
		defensiveBaseValues.clear();
		offensivePegs.clear();
		offensiveValues.clear();
		EvaluateDefense(enemyPath, player, opponent, pathIntersection, enemyIntersection);

		EvaluateOffense(path, player);

		AdjustWeights(path, enemyPath, player, opponent);

		vector<MYPoint> pegs;
		vector<int> values;
		MergeOffAndDefValues(pegs, values);
		GeneralEvaluation(pegs, values);

		*Dest = GetBestPeg(pegs, values);

		//now that we have our best peg, and a heap of second-best pegs,
		//add up all the extra scores based on weights
		float tempBestWeightScore = 0.0f;
		bestWeightsScore = 0.0f;
		int bestScore = heap.peekTopHeap().key;
		while (heap.size()) {
			HEAP<MYPoint> bestPoint = heap.popTopHeap();
			for each (CSolution solution in solutions) {
				if (bestPoint.data == solution.solution) {
					tempBestWeightScore = solution.solutionWeight * bestPoint.key / bestScore;
					if (tempBestWeightScore > bestWeightsScore) {
						bestWeightsScore = tempBestWeightScore;
					}
					break;
				}
			}
		}
		currentWeightsScore += bestWeightsScore;
	}
	return;
}//end DoTurnAndEval


void AILogic::DoTurn(MYPoint* Dest,
					 ePlayer const player,
					 ePlayer const opponent)
{
	PERFORMANCE_MARKER
	currentPlayer = player;
	eSides sides;
	MYPoint DestPeg;
	MYPoint StartPeg;
	isSideValid(player, TopAndBottom) ? sides = TopAndBottom : sides = LeftAndRight;

	CPath path;
	GetBestPath(player, &path);
	path.OrderPath(sides);
	if (path.empty() == true) {
		//no path, the most this player can hope for is stalemate
		//but instead, surrender of course
		*Dest = MYPoint(0,0);
		return;
	}

	CPath enemyPath;
	GetBestPath(opponent, &enemyPath);
	isSideValid(opponent, TopAndBottom) ? sides = TopAndBottom : sides = LeftAndRight;
	enemyPath.OrderPath(sides);

	CPath enemyIntersection;
	CPath pathIntersection;
	path.GetIntersection(enemyPath, pathIntersection, enemyIntersection, *this);

	defensivePegs.clear();
	defensiveValues.clear();
	defensiveBaseValues.clear();
	offensivePegs.clear();
	offensiveValues.clear();
	EvaluateDefense(enemyPath, player, opponent, pathIntersection, enemyIntersection);

	EvaluateOffense(path, player);

	AdjustWeights(path, enemyPath, player, opponent);

	vector<MYPoint> pegs;
	vector<int> values;
	MergeOffAndDefValues(pegs, values);
	GeneralEvaluation(pegs, values);
	*Dest = GetBestPeg(pegs, values);

	return;
}//end DoTurn

bool AILogic::CheckForWin(ePlayer const player)
{
	PERFORMANCE_MARKER
	eSides side1, side2;
	if (isSideValid(player, TopAndBottom) == true) {
		side1 = TopSide;
		side2 = BottomSide;
	}
	else {
		side1 = LeftSide;
		side2 = RightSide;
	}

	vector<int> side1Groups;
	vector<int> side2Groups;
	vector<MYPoint>* pPlayerPegs = GetPlayerPegList(player);
	for each (MYPoint Peg in *pPlayerPegs) {
		if (isPegOnSide(Peg, side1) == true
			&& GetLinkGroup(Peg) != 0) {
			side1Groups.push_back(GetLinkGroup(Peg));
		}
		else if (isPegOnSide(Peg, side2) == true
			&& GetLinkGroup(Peg) != 0) {
			side2Groups.push_back(GetLinkGroup(Peg));
		}
	}
	for each (int linkGroup in side1Groups) {
		if (find(side2Groups.begin(), side2Groups.end(), linkGroup) != side2Groups.end()) {
			return true;
		}
	}
	//TODO
	//check for stalemate
	return false;
}//end CheckForWin

void AILogic::EvaluateDefense(const CPath& enemyPath,
							  ePlayer const player,
							  ePlayer const opponent,
							  const CPath& pathIntersection,
							  const CPath& enemyIntersection)
{
	PERFORMANCE_MARKER
	NineLinks blockingLinks;
	vector<MYPoint> linkPegs;
	for each (CLink enemyLink in enemyPath) {
		linkPegs.clear();
		MYPoint startPeg = enemyLink.startPeg;
		MYPoint destPeg = enemyLink.GetDestFromDir();
		if (arePegsLinked(startPeg, destPeg) == true) {
			continue;
		}

		//evaluate source and dest, those can block too
		EvaluateDefenseLogic(startPeg, linkPegs, enemyLink,
			player, opponent, enemyIntersection);
		EvaluateDefenseLogic(destPeg, linkPegs, enemyLink,
			player, opponent, enemyIntersection);

		if (canLinkBeBlocked(enemyLink, opponent, true) == true) {
			//evaluate Int pegs
			if (enemyLink.IsDouble() == true) {
				EvaluateDefenseLogic(enemyLink.GetIntPeg(LEFT), linkPegs, enemyLink,
					player, opponent, enemyIntersection);
				if (enemyLink.IsDoubleStraight() == false) {
					EvaluateDefenseLogic(enemyLink.GetIntPeg(RIGHT), linkPegs, enemyLink,
						player, opponent, enemyIntersection);
				}
			}

			//only evaluate the nineLinks if it can be blocked in time
			blockingLinks.clear();
			GetNineLinks(enemyLink, blockingLinks);
			for each (CLink nine in blockingLinks) {
				if (isLinkValid(nine, player) == false) {
					continue;
				}

				EvaluateDefenseLogic(nine.startPeg, linkPegs, enemyLink,
					player, opponent, enemyIntersection);
				EvaluateDefenseLogic(nine.GetDestFromDir(), linkPegs, enemyLink,
					player, opponent, enemyIntersection);
			}
		}
	}
#ifdef DEBUG
	ofstream file("defense.txt");
	for (unsigned int index = 0; index < defensiveValues.size(); ++index) {
		file << '\n' << (int)defensivePegs[index].x << "\t" << (int)defensivePegs[index].y
			<< "\t" << defensiveValues[index] << "\t" << defensiveBaseValues[index]
			<< "\t" << defensiveValues[index] + defensiveBaseValues[index];
	}
#endif
	return;
}//end EvaluateDefense

void AILogic::EvaluateDefenseLogic(const MYPoint& peg,
								  vector<MYPoint>& linkPegs,
								  const CLink& link,
								  ePlayer const player,
								  ePlayer const opponent,
								  const CPath& enemyIntersection)
{
	PERFORMANCE_MARKER
	if (isPegWithinBoard(peg, player) == false
		|| isPegAvailable(peg) == false) {
		return;
	}

	if (find(linkPegs.begin(), linkPegs.end(), peg) != linkPegs.end()) {
		return;//don't count pegs that fall on duplicate nineLinks of a link
	}

	unsigned int index = 0;
	linkPegs.push_back(peg);
	bool found = false;
	for (index = 0; index < defensivePegs.size(); ++index) {
		if (defensivePegs[index] == peg) {
			found = true;
			break;
		}
	}
	int weight = GetDefenseJumpTypeWeight(link.jump.jumpType);
	float modifier = -200.0f;
	int numLinks = -CountLinks(peg, player);
	if (numLinks == 0) {
		modifier *= defHasNoLinks;
	}
	if (found == false) {
		defensivePegs.push_back(peg);
		defensiveValues.push_back(0);

		int links = 0;
		int blocks = 0;
		CountLinksAndBlocks(peg, player, &links, &blocks);
		//int baseValue = CountBlocks(peg, player, enemyIntersection);
		int baseValue = blocks;
		baseValue += CountDoubleBlocks(peg, player, enemyIntersection);
		defensiveBaseValues.push_back((baseValue * modifier) + (numLinks * GetLinksWeight()));
	}

	bool endPeg = (link.startPeg == peg || link.GetDestFromDir() == peg);
	if (endPeg == true) {
		modifier *= defIsStartPeg;
	}

	if (canPegBlockLink(peg, link, player, opponent) == true) {
		if (endPeg == true && numLinks == 0) {
			//a block that is a technicality, opponent can often go around
			if (link.IsDoubleStraight() == true) {
				//can't go around this
				modifier *= defEndBlockStraight;
			}
			else {
				modifier *= defEndBlock;
			}
		}
		int turns = CountTurnsToLink(link, opponent);
		if (turns == 1) {
			modifier *= defBlocks1JumpLink;
		}
		else if (turns == 3) {
			modifier *= defBlocks3JumpLink;
		}
		else {
			modifier *= defBlocks2JumpLink;
		}
	}
	else {
		modifier *= defCantBlockLink;
	}
	int value = static_cast<int>(weight * modifier);
	
	//if (value < defensiveValues[index]) {
		defensiveValues[index] += value;
	//}
	return;
}//end EvaluateDefenseLogic

int AILogic::GetDefenseJumpTypeWeight(eJump const jumpType)
{
	switch (jumpType) {
	case SingleJump:
		return 6;
	case DoubleStraight:
		return 10;
	case DoubleDiamond:
		return 16;
	case DoubleSquare:
		return 14;
	case DoubleShortDiamond:
		return 7;
	default:
		ASSERT(false);
		return 0;
	}
}//end GetDefenseJumpTypeWeight

void AILogic::DoFirstTurn(MYPoint* Dest,
						  ePlayer const player)
{
	MYPoint point = generateRandomXYCoord(0, player, AnySide);
	*Dest = point;
	return;
}//end DoFirstTurn

MYPoint AILogic::generateRandomXYCoord(int counter,
									  ePlayer const player,
									  eSides const Side)
{
	if (counter == 0) {
		srand(static_cast<int> (time(NULL)));
	}
	//make sure it doesnt go on forever, especially when all pegs have been occupied
	if (counter > 1000) {
		return MYPoint(0,0);
	}

	MYPoint point;
	point.x = rand() % XBoardSize;
	point.y = rand() % YBoardSize;
	switch (Side)
	{
	case NOTASIDE:
		break;
	case TopSide:
		point.y = rand() % ((YBoardSize + 1) / 2);
		break;
	case BottomSide:
		point.y = rand() % ((YBoardSize + 1) / 2);
		point.y += YBoardSize / 2;
		break;
	case LeftSide:
		point.x = rand() % ((XBoardSize + 1) / 2);
		break;
	case RightSide:
		point.x = rand() % ((XBoardSize + 1) / 2);
		point.x += XBoardSize / 2;
		break;
	}

	if ((isPegWithinBoard(point, player) == false) ||
		(isPegAvailable(point) == false)) {
		counter++;
		point = generateRandomXYCoord(counter, player, Side);
	}
	return (point);
}//end generateRandomXYCoord

int AILogic::GetLinksWeight()
{
	return TWOJUMPS;
}//end GetLinksWeight

int AILogic::GetBlocksWeight()
{
	return TWOJUMPS / 3;
}//end GetBlocksWeight

int AILogic::GetSetupWeight()
{
	return TWOJUMPS / 5;
}//end GetSetupWeight

#include "stdafx.h"

using namespace std;

//need to be global for all the instances of AStar
CAStarWeights AStarWeights;

void CPath::OrderPath(eSides const side)
{
	PERFORMANCE_MARKER
	if (this->empty() == true) {
		return;
	}

	int bestValue = 9999999;
	CLink link;
	CLink bestLink;

	CPath::iterator bestIter;
	for (CPath::iterator iter = this->begin(); iter != this->end(); ++iter) {
		link = *iter;
		int linkValue = link.convertToInt(side);
		int oppositeValue = link.GetReversedLink().convertToInt(side);
		if (linkValue < bestValue) {
			bestValue = linkValue;
			bestLink = link;
			bestIter = iter;
		}
		if (oppositeValue < bestValue) {
			bestValue = oppositeValue;
			bestLink = link.GetReversedLink();
			bestIter = iter;
		}
	}

	this->erase(bestIter);
	if (this->empty() == true) {
		this->push_back(bestLink);
		return;
	}
	vector<CLink> links;
	links.push_back(bestLink);
	CLink nextLink;
	bool foundNext = false;
	do {
		MYPoint previousDest = links.back().GetDestFromDir();
		foundNext = false;
		for (CPath::iterator iter = this->begin(); iter != this->end(); ++iter) {
			if (iter->startPeg == previousDest) {
				nextLink = *iter;
				foundNext = true;
			}
			else if (iter->GetDestFromDir() == previousDest) {
				nextLink = iter->GetReversedLink();
				foundNext = true;
			}
			if (foundNext == true) {
				this->erase(iter);
				if (links.back().IsDouble() == false && nextLink.IsDouble() == false) {
					//merge consecutive single jumps into double jumps
					links.back() = CLink(links.back().startPeg, 
						GetJumpFromPegs(links.back().startPeg, nextLink.GetDestFromDir()));
				}
				else {
					links.push_back(nextLink);
				}
				break;
			}
		}
	} while (foundNext == true && this->empty() == false);

	OrderPath(side);//order anything that wasn't removed

	CPath::iterator front = this->begin();
	for (vector<CLink>::iterator iter = links.begin(); iter != links.end(); ++iter) {
		this->insert(front, *iter);
		//*this is ordered, but no links are in the path,
		//path goes in front of these unlinked links
	}

	return;
}//end OrderPath

void CPath::OrderLinks(eSides const side)
{
	PERFORMANCE_MARKER
	if (this->empty() == true) {
		return;
	}

	CLink link;
	int bestValue;
	CLink bestLink;
	CPath::iterator bestIter;

	vector<CLink> links;
	while (this->empty() == false) {
		bestValue = 99999999;
		for (CPath::iterator iter = this->begin(); iter != this->end(); ++iter) {
			link = *iter;
			int linkValue = link.convertToInt(side);
			int oppositeValue = link.GetReversedLink().convertToInt(side);
			if (linkValue < bestValue) {
				bestValue = linkValue;
				bestLink = link;
				bestIter = iter;
			}
			if (oppositeValue < bestValue) {
				bestValue = oppositeValue;
				bestLink = link.GetReversedLink();
				bestIter = iter;
			}
		}
		this->erase(bestIter);
		links.push_back(bestLink);
	}

	for (vector<CLink>::iterator iter = links.begin(); iter != links.end(); ++iter) {
		this->push_back(*iter);
	}
	return;
}//end OrderLinks

void CPath::GetIntersection(const CPath& enemyPath,
							CPath& pPathIntersection,
							CPath& pEnemyIntersection,
							CBoardManager& pBoard) const
{
	PERFORMANCE_MARKER
	int const MAXDISTANCE = 2;
	CPath pathLinks;
	CPath enemyLinks;
	this->PathToLinks(pathLinks, pBoard);
	enemyPath.PathToLinks(enemyLinks, pBoard);

	for each (CLink link in pathLinks) {
		for each (CLink enemyLink in enemyLinks) {
			int distance = GetBestDistance(link, enemyLink);
			if (distance <= MAXDISTANCE) {
				pPathIntersection.push_back(link);
				break;
			}
		}
	}
	for each (CLink enemyLink in enemyLinks) {
		for each (CLink link in pathLinks) {
			int distance = GetBestDistance(link, enemyLink);
			if (distance <= MAXDISTANCE) {
				pEnemyIntersection.push_back(enemyLink);
				break;
			}
		}
	}
	//there is now a small list of links that are semi near one another
	return;
}//end GetIntersection

int CPath::GetBestDistance(const CLink& link,
						   const CLink& compareLink) const
{
	PERFORMANCE_MARKER
	MYPoint Dest = link.GetDestFromDir();
	MYPoint CompareDest = compareLink.GetDestFromDir();
	int best = abs(link.startPeg.x - compareLink.startPeg.x) + abs(link.startPeg.y - compareLink.startPeg.y);
	int compare = abs(link.startPeg.x - CompareDest.x) + abs(link.startPeg.y - CompareDest.y);
	if (compare < best) {
		best = compare;
	}
	compare = abs(Dest.x - CompareDest.x) + abs(Dest.y - CompareDest.y);
	if (compare < best) {
		best = compare;
	}
	compare = abs(Dest.x - compareLink.startPeg.x) + abs(Dest.y - compareLink.startPeg.y);
	if (compare < best) {
		best = compare;
	}
	return best;
}//end GetBestDistance

void CPath::PathToLinks(CPath& pLinkList,
						CBoardManager& pBoard) const
{
	PERFORMANCE_MARKER
	for each (CLink link in *this) {
		if (link.IsDouble() == false) {
			if (pBoard.isDestBlocked(link.startPeg, link.jump.direction) == false) {
				pLinkList.push_back(link);
			}
		}
		else {
			//don't bother with sublinks that are blocked!
			CPathDirs pathDirs = link.GetPathDirs();
			CLink link(link.startPeg, pathDirs.leftDir);
			if (pBoard.isLinkWithinBoard(link) == true) {
				if (pBoard.isDestBlocked(link.startPeg, link.jump.direction) == false) {
					pLinkList.push_back(link);
				}
			}

			link.Set(link.GetIntPeg(LEFT), pathDirs.rightDir);
			if (pBoard.isLinkWithinBoard(link) == true) {
				if (pBoard.isDestBlocked(link.startPeg, link.jump.direction) == false) {
					pLinkList.push_back(link);
				}
			}

			if (link.IsDoubleStraight() == false) {
				link.Set(link.startPeg, pathDirs.rightDir);
				if (pBoard.isLinkWithinBoard(link) == true) {
					if (pBoard.isDestBlocked(link.startPeg, link.jump.direction) == false) {
						pLinkList.push_back(link);
					}
				}

				link.Set(link.GetIntPeg(RIGHT), pathDirs.leftDir);
				if (pBoard.isLinkWithinBoard(link) == true) {
					if (pBoard.isDestBlocked(link.startPeg, link.jump.direction) == false) {
						pLinkList.push_back(link);
					}
				}
			}
		}
	}
	return;
}//end PathToLinks

void CPath::BuildPathList(const MYPoint& LastStep,
						  eSides const TerminalSide,
						  const MYPoint& TerminalPeg,
						  CBoardManager& pBoard)
{
	PERFORMANCE_MARKER
	if (LastStep == TerminalPeg) {
		return;
	}
	bool wasEmpty = this->empty();
	CLink parentLink = pBoard.GetAStarLink(LastStep);
	//terminal peg can be (0,0) so as to accommodate the terminal side
	while (pBoard.isPegOnSide(parentLink.startPeg, TerminalSide) == false
		&& parentLink.startPeg != TerminalPeg) {
		InsertIntoPathList(parentLink, wasEmpty);
		parentLink = pBoard.GetAStarLink(parentLink.startPeg);
	}
	InsertIntoPathList(parentLink, wasEmpty);

	return;
}//end BuildPathList

void CPath::InsertIntoPathList(const CLink& link,
							   bool const wasEmpty)
{
	PERFORMANCE_MARKER
	if (wasEmpty == false) {
		if (find(begin(), end(), link) != end()) {
			return;
		}
	}
	this->push_back(link);
	return;
}//end InsertIntoPathList

AStarPathfinder::AStarPathfinder(SharedAStarData (*SharedBoard)[MAXBOARDSIZE][MAXBOARDSIZE],
	int const XBoardSize,
	int const YBoardSize)
	: CBoardManager(SharedBoard, XBoardSize, YBoardSize)
{
	return;
}


int AStarPathfinder::CountLinks(const MYPoint& Peg,
								ePlayer const player)
{
	PERFORMANCE_MARKER
	//assumes Peg is currently unowned but player is considering it
	int links = 0;
	for (CDir dir = leftUp; dir != NOTADIR; ++dir) {
		if (isDestLinked(Peg, dir) == false) {
			if (canPegLink(Peg, dir, player) == true) {
				++links;
			}
		}
	}
	return links;
}//end CountLinks

void AStarPathfinder::JumpStartAStar(JumpStartData const jumpStartData)
{
	PERFORMANCE_MARKER
	eSides startSide = jumpStartData.startSide;
	ePlayer player = jumpStartData.player;
	MYPoint Dest = jumpStartData.Dest;
	bool leftRight;
	int a;
	eSides destSide;
	switch (startSide) {
	case LeftSide:
		leftRight = true;
		a = 0;
		destSide = RightSide;
		break;
	case RightSide:
		leftRight = true;
		a = XBoardSize-1;
		destSide = LeftSide;
		break;
	case TopSide:
		leftRight = false;
		a = 0;
		destSide = BottomSide;
		break;
	case BottomSide:
	default:
		leftRight = false;
		a = YBoardSize-1;
		destSide = TopSide;
	}

	int AStarF = 0;
	if (leftRight == true) {
		for (int b = 1; b < YBoardSize-1; ++b) {
			MYPoint Source(a, b);
			ASSERT(isPegWithinBoard(Source) == true);
			SetAStarStatus(Source, AStar_Open);
			if (isOwnerThis(Source, player) == true) {
				AStarF = 0;
			}
			else {
				AStarF = CalcH(Source, Dest, destSide, player);
			}
			OpenHeap.insertElement(Source, AStarF);
		}
	}
	else {
		for (int b = 1; b < XBoardSize-1; ++b) {
			MYPoint Source(b, a);
			ASSERT(isPegWithinBoard(Source) == true);
			SetAStarStatus(Source, AStar_Open);
			if (isOwnerThis(Source, player) == true) {
				AStarF = 0;
			}
			else {
				AStarF = CalcH(Source, Dest, destSide, player);
			}
			OpenHeap.insertElement(Source, AStarF);
		}
	}

	return;
}//end JumpStartAStar

void AStarPathfinder::CountLinksAndBlocksLogic(const MYPoint& Peg,
											   CDir const dir,
											   ePlayer const player,
											   int* pLinks,
											   int* pBlocks)
{
	PERFORMANCE_MARKER
	if (isDestBlocked(Peg, dir) == false) {
		MYPoint Dest = GetDestFromDir(Peg, dir);
		if (isPegWithinBoard(Dest) == true) {
			if (isPegValid(Dest, player) == true
				&& (isOwnerLinkable(Peg, player) == true
				|| isOwnerLinkable(Dest, player) == true)) {
				++(*pLinks);
				//count the blocks made from any links
				NineLinks nineLinks;
				GetNineLinks(CLink(Peg, dir), nineLinks);
				for each (CLink nine in nineLinks) {
					if (isOwnerEnemy(nine.startPeg, player) == true) {
						if (canPegLink(nine.startPeg, nine.jump.direction,
							GetOwner(nine.startPeg)) == true) {
							++(*pBlocks);
						}
					}
					else {
						MYPoint blockDest = nine.GetDestFromDir();
						if (isOwnerEnemy(blockDest, player) == true) {
							if (canPegLink(blockDest, nine.jump.direction, GetOwner(blockDest)) == true) {
								++(*pBlocks);
							}
						}
					}
				}
			}
			else if (isOwnerEnemy(Dest, player) == true) {
				if (isPegValid(Peg, GetOwner(Dest)) == true) {
				//by inserting the peg here, we block opponents ability to link in this dir
					//unless it is not valid
					++(*pBlocks);
				}
			}
		}
	}
	return;
}//end CountLinksAndBlocksLogic

void AStarPathfinder::CountLinksAndBlocks(const MYPoint& Peg,
										  ePlayer const player,
										  int* pLinks,
										  int* pBlocks)
{
	PERFORMANCE_MARKER
	*pLinks = 0;
	*pBlocks = 0;
	//assumes Peg is currently unowned but player is considering it
	for (CDir dir = leftUp; dir != NOTADIR; ++dir) {
		if (isDestLinked(Peg, dir) == false) {
			//for each single jump, count links and blocks from those links
			CountLinksAndBlocksLogic(Peg, dir, player, pLinks, pBlocks);
		}
	}
	return;
}//end CountLinksAndBlocks

int AStarPathfinder::CountDoubles(const MYPoint& Peg,
								  ePlayer const player)
{
	PERFORMANCE_MARKER
	//assumes Peg is currently unowned but player is considering it
	int doublesWeight = 0;
	int temp = 0;
	vector<CLink> allDoubles;
	list<CLink> goodDoubles;
	GetDoublesFromPeg(Peg, player, allDoubles);
	for each (CLink iter in allDoubles) {
		//there is a double that could take place,
		//but can the opponent block it in time?
		temp = GetJumpTypeWeight(iter.jump.jumpType);
		if (canLinkBeBlocked(iter, player) == false) {
			doublesWeight += temp;
			goodDoubles.push_back(iter);
		}
	}
restart:
	//there are some pegs where it can double jump to multiple destinations
	//if those destinations are linked, there is no need to count BOTH doubles setup
	for (list<CLink>::iterator iter = goodDoubles.begin(); iter != goodDoubles.end(); ++iter) {
		for (list<CLink>::iterator compare = goodDoubles.begin(); compare != goodDoubles.end(); ++compare) {
			if (iter == compare) {
				continue;
			}
			MYPoint startPeg = iter->GetDestFromDir();
			MYPoint destPeg = compare->GetDestFromDir();
			CJump possibleJump = GetJumpFromPegs(startPeg, destPeg);
			if (possibleJump.jumpType == NOTAJUMP) {
				continue;
			}
			if (isDestBlocked(startPeg, possibleJump, player) == true) {
				continue;
			}
			if (arePegsLinked(startPeg, destPeg) == true
				|| canLinkBeBlocked(CLink(startPeg, possibleJump), player, true) == false) {
				if (GetJumpTypeWeight(iter->jump.jumpType) > GetJumpTypeWeight(compare->jump.jumpType)) {
					doublesWeight -= GetJumpTypeWeight(compare->jump.jumpType);
					goodDoubles.erase(compare);
				}
				else {
					doublesWeight -= GetJumpTypeWeight(iter->jump.jumpType);
					goodDoubles.erase(iter);
				}
				goto restart;
			}
		}
	}
	return doublesWeight;
}//end CountDoubles

bool AStarPathfinder::ReachedDest(MYPoint& Peg,
								  MYPoint Dest,
								  eSides const destSide)
{
	if (Peg == Dest) {
		return true;
	}
	else if (compareCoordToSide(Peg, destSide) == true) {
		return true;
	}
	return false;
}//end Reached Dest

int AStarPathfinder::CalcJumpH(const CLink& link,
							   ePlayer const player)
{
	PERFORMANCE_MARKER
	MYPoint Source = link.startPeg;
	CJump jump = link.jump;
	int add = 0;
	if (isDestLinked(Source, jump, player) == true) {
		return 0;
	}

	int baseCost = GetJumpTypeCost(jump.jumpType);
	int multi = 1;
	if (canLinkBeBlocked(link, player) == true) {
		multi = 2;
	}

	if (jump.IsDouble() == true) {
		if (isOwnerLinkable(Source, player) == false
			|| isOwnerLinkable(link.GetDestFromDir(), player) == false) {

			CPathReturn pathBlocked = isDestBlocked(Source, jump, player);
			pathBlocked.andOr = OR;
			if (pathBlocked == true) {
				add += HALFJUMP;
			}
		}
		else {
			baseCost = GetJumpTypeCost(SingleJump);
		}
	}
	return (baseCost + add) * multi;
}//end CalcJumpH

bool AStarPathfinder::ExecuteAStarLogic(const MYPoint& Source,
										const MYPoint& DestForCalcH,
										const CJump& jump,
										ePlayer const player,
										eSides const DestSide,
										bool const completeSearch)
{
	PERFORMANCE_MARKER
	CLink link(Source, jump);
	if (isLinkValid(link, player) == false) {
		return false;
	}
	if (isDestBlocked(Source, jump, player) == true) {
		return false;
	}

	MYPoint Dest = link.GetDestFromDir();
	//if its owned by an enemy, or if its unownable, exit
	if (isOwnerEnemy(Dest, player) == true
		|| isOwnerThis(Dest, NotOwnable) == true) {
		return false;
	}
	//dont bother searching if the dest peg is closed
	eAStar AStarStatus = GetAStarStatus(Dest);
	if (AStarStatus == AStar_Closed) {
		return false;
	}

	int		SourceG = GetAStarG(Source);
	int		DestAStarG = GetAStarG(Dest);
	int		DestAStarH = CalcH(Dest, DestForCalcH, DestSide, player);
	int		JumpH = CalcJumpH(link, player);
	int		DestAStarF = 0;
	int		OriginalDestAStarF = GetAStarF(Dest);
	bool	performLogic = false;
	bool	insertUpdate = false;//true = insert, false = update
	int		links = 0;
	int		blocks = 0;

	if ((AStarStatus == AStar_Init) &&
		(isDestBlocked(Source, jump, player) == false)) {
		//calculate the AStar elements for this peg
		SetAStarG(Dest, SourceG + JumpH);
		SetAStarH(Dest, DestAStarH);
		DestAStarF = SourceG + DestAStarH + JumpH;
		if (completeSearch == true) {
			CountLinksAndBlocks(Dest, player, &links, &blocks);
			DestAStarF -= links * GetAStarLinkWeight();
			DestAStarF -= blocks * GetAStarBlockWeight();
			DestAStarF -= CountDoubles(Dest, player) * GetAStarDoubleSetupWeight();
		}
		else {
			links = CountLinks(Dest, player);
			DestAStarF -= links * GetAStarLinkWeight();
		}
		SetAStarF(Dest, DestAStarF);

		SetAStarLink(Dest, link);
		//the dest peg is in the initialization state, change to open
		SetAStarStatus(Dest, AStar_Open);
		//insert this AStar element into the heap
		insertUpdate = true;
		performLogic = true;

	}
	else if ((AStarStatus == AStar_Open) && 
		(DestAStarG > SourceG + JumpH)) {
		//if dest has already been found as an open peg, and the source peg path
		//is shorter than the destination's previous path, then update it

		//update the AStar elements for this peg
		SetAStarG(Dest, SourceG + JumpH);
		SetAStarH(Dest, DestAStarH);
		DestAStarF = SourceG + DestAStarH + JumpH;
		if (completeSearch == true) {
			CountLinksAndBlocks(Dest, player, &links, &blocks);
			DestAStarF -= links * GetAStarLinkWeight();
			DestAStarF -= blocks * GetAStarBlockWeight();
			DestAStarF -= CountDoubles(Dest, player) * GetAStarDoubleSetupWeight();
		}
		else {
			links = CountLinks(Dest, player);
			DestAStarF -= links * GetAStarLinkWeight();
		}
		SetAStarF(Dest, DestAStarF);

		SetAStarLink(Dest, link);
		if (DestAStarF <= OriginalDestAStarF) {
			//update the heap with the new AStar elements
			insertUpdate = false;
			performLogic = true;
		}
	}
	if (performLogic) {
		if (insertUpdate) {
			OpenHeap.insertElement(Dest, DestAStarF);
		}
		else {
			OpenHeap.editElement(Dest, Dest, OriginalDestAStarF, DestAStarF);
		}
	}

	return true;
}//end ExecuteAStarLogic

void AStarPathfinder::ResetAStarList()
{
	PERFORMANCE_MARKER
	for each (MYPoint Peg in ClosedList) {
		SetAStarStatus(Peg, AStar_Init);
		SetAStarG(Peg, 0);
		SetAStarF(Peg, 0);
		//SetAStarLink(Peg, CLink(MYPoint(0,0), CJump(NOTADIR, NOTAJUMP)));
	}
	for (int size = OpenHeap.size(); size > 0; --size) {
		MYPoint Peg = OpenHeap.peekElement(size).data;
		SetAStarStatus(Peg, AStar_Init);
		SetAStarG(Peg, 0);
		SetAStarF(Peg, 0);
		//SetAStarLink(Peg, CLink(MYPoint(0,0), CJump(NOTADIR, NOTAJUMP)));
	}
	ClosedList.clear();
	OpenHeap.clear();
	return;
}//end ResetAStarList

HEAP<MYPoint> AStarPathfinder::AStar(const MYPoint& Source,
									const MYPoint& Dest,
									ePlayer const player,
									eSides const DestSide,
									bool const completeSearch)
{
	PERFORMANCE_MARKER
	//if the AStar was jumpstarted, do this
	if (GetAStarStatus(Source) == AStar_Open) {
		OpenHeap.removeElement(Source);
	}
	HEAP<MYPoint> TopHeap(Source, 0);
	MYPoint LastStep = Source;
	eJump stopJump;
	(completeSearch == true) ? stopJump = NOTAJUMP : stopJump = DoubleStraight;

	for (;;) {
		//this peg is now closed
		SetAStarStatus(LastStep, AStar_Closed);
		ClosedList.push_back(LastStep);
		if (ReachedDest(LastStep, Dest, DestSide) == true) {
			break;
		}

		//this adds to the heap pegs that might be a path
		for (eJump jumpType = SingleJump; jumpType != stopJump; ++jumpType) {
			for (CDir dir = leftUp; dir != NOTADIR; ++dir) {
				ExecuteAStarLogic(LastStep, Dest, CJump(dir,jumpType), player, DestSide, completeSearch);
			}
		}

		if (OpenHeap.size() == 0) {
			TopHeap = HEAP<MYPoint>(MYPoint(0,0), -1);
			break;
		}
		//get the best peg so far from the heap
		TopHeap = OpenHeap.popTopHeap();
		LastStep = TopHeap.data;
		//ASSERT(GetAStarStatus(LastStep) == AStar_Open);
	}
	return TopHeap;
}//end AStar

int AStarPathfinder::CalcH(const MYPoint& Source,
						   const MYPoint& Dest,
						   eSides const DestSide,
						   ePlayer const player)
{
	PERFORMANCE_MARKER
	int absX = 0;
	int absY = 0;

	if (DestSide == AnySide || DestSide == NOTASIDE) {
		absX = abs(Dest.x - Source.x);
		absY = abs(Dest.y - Source.y);
		switch (absX + absY) {
		case 0:
			if (isOwnerLinkable(Source, player) == true) {
				return -(ONEJUMP);
			}
			else {
				return -(HALFJUMP);
			}
		case 1:
			return ONEJUMP * 3;
		case 2:
			return ONEJUMP * 2;
		case 3:
			if (absX == 0 || absY == 0) {
				return ONEJUMP * 3;
			}
			else {
				return ONEJUMP * 1;
			}
		case 4:
			if (absX == 2 && absY == 2) {
				return ONEJUMP * 4;
			}
			else {
				return ONEJUMP * 2;
			}
		default:
			return ((absX + absY + 1) / 2  * ONEJUMP);
		};
	}
	else {
		switch (DestSide) {
			case LeftSide:
				absX = Source.x;
				break;
			case TopSide:
				absY = Source.y;
				break;
			case RightSide:
				absX = (XBoardSize - 1) - Source.x;
				break;
			case BottomSide:
				absY = (YBoardSize - 1) - Source.y;
				break;
			case AnySide:
			default:
				ASSERT(false);
		};

		switch (absX + absY) {
			case 0:
				if (isOwnerLinkable(Source, player) == true) {
					return -(ONEJUMP);
				}
				else {
					return 0;
				}
			case 1:
				return 1; //enemy path is effectively blocked
			case 2:
				return ONEJUMP;
			case 3:
				if (absX == 0 || absY == 0) {
					return TWOJUMPS;
				}
				else {
					return ONEJUMP;
				}
			case 4:
				if (absX == 2 && absY == 2) {
					return TWOJUMPS * 2;
				}
				else {
					return TWOJUMPS;
				}
			default:
				return ((absX + absY + 1) / 2  * ONEJUMP);
		};
	}
}//end CalcH

void AStarPathfinder::SetAStarWeights(int const newLinkWeight,
									  int const newBlockWeight,
									  int const newDoubleWeight)
{
	AStarWeights.linksWeight = newLinkWeight;
	AStarWeights.blocksWeight = newBlockWeight;
	AStarWeights.doubleWeight = newDoubleWeight;
}

int AStarPathfinder::GetAStarLinkWeight()
{
	return AStarWeights.linksWeight;
}

int AStarPathfinder::GetAStarBlockWeight()
{
	return AStarWeights.blocksWeight;
}

int AStarPathfinder::GetAStarDoubleSetupWeight()
{
	return AStarWeights.doubleWeight;
}

float AStarPathfinder::GetAStarWeightsScore()
{
	return AStarWeights.weightsScore;
}

void AStarPathfinder::LoadAStarWeights()
{
	ifstream weights("AStarBestWeights.txt");
	if (weights) {
		char temp[128];
		weights >> bestAStarWeightsScore; weights.getline(temp, 128);
		weights >> AStarWeights.linksWeight; weights.getline(temp, 128);
		weights >> AStarWeights.blocksWeight; weights.getline(temp, 128);
		weights >> AStarWeights.doubleWeight; weights.getline(temp, 128);
	}
	else {
		bestAStarWeightsScore = -1.0f;
		currentAStarWeightsScore = 0.0f;
		AStarWeights.linksWeight = 500;
		AStarWeights.blocksWeight = 200;
		AStarWeights.doubleWeight = 200;
	}
	return;
}//end LoadAStarWeights

void AStarPathfinder::LoadAStarWeightsFromBackup(std::vector<CAStarWeights>& weights)
{
	char temp[128];
	float backupBestAStarWeightsScore;
	int backupLinksWeight, backupBlocksWeight, backupDoubleWeight;
	for (int x = 0; x < 3; ++x) {
		std::string dir;
		if (x == 0) {
			dir = "..\\release\\";
		}
		else if (x == 1) {
			dir = "..\\debug\\";
		}
		else {
			dir = "";
		}

		std::string filename;
		for (int y = 0; y < 3; ++y) {
			if (y == 0) {
				filename = dir + "AStarBestWeights.txt";
			}
			else if (y == 1) {
				filename = dir + "AStarBackupWeights.txt";
			}
			else {
				filename = dir + "AStarTiedWeights.txt";
			}
			ifstream backup(filename.c_str());
			if (backup) {
				for (;;) {
					backup >> backupBestAStarWeightsScore; backup.getline(temp, 128);
					backup >> backupLinksWeight; backup.getline(temp, 128);
					backup >> backupBlocksWeight; backup.getline(temp, 128);
					backup >> backupDoubleWeight; backup.getline(temp, 128);
					if (backup.good()) {
						CAStarWeights backupWeights;
						backupWeights.weightsScore = backupBestAStarWeightsScore;
						backupWeights.linksWeight = backupLinksWeight;
						backupWeights.blocksWeight = backupBlocksWeight;
						backupWeights.doubleWeight = backupDoubleWeight;
						if (find(weights.begin(), weights.end(), backupWeights) == weights.end()) {
							weights.push_back(backupWeights);
						}
					}
					else {
						break;
					}
				}
				backup.close();
			}
		}
	}
	return;
}//end LoadAStarWeights

void AStarPathfinder::SaveAStarWeightsToBackup(std::vector<CAStarWeights>& weights)
{
	ofstream backup("AStarBackupWeights.txt");
	if (backup) {
		for each (CAStarWeights backupWeights in weights) {
			backup << backupWeights.weightsScore << " = backupBestAStarWeightsScore\n";
			backup << backupWeights.linksWeight << " = backupLinksWeight\n";
			backup << backupWeights.blocksWeight << " = backupBlocksWeight\n";
			backup << backupWeights.doubleWeight << " = backupDoubleWeight\n";
			backup << "\n";
		}
	}
	return;
}//end LoadAStarWeights

void AStarPathfinder::SaveAStarWeights()
{
	if (currentAStarWeightsScore > bestAStarWeightsScore) {
		ofstream weights("AStarBestWeights.txt");

		weights << currentAStarWeightsScore << " = bestAStarWeightsScore\n";
		weights << AStarWeights.linksWeight << " = linksWeight\n";
		weights << AStarWeights.blocksWeight << " = blocksWeight\n";
		weights << AStarWeights.doubleWeight << " = doubleWeight\n";
		weights.close();

		//and I want to store a backup of the new best
		if (bestAStarWeightsScore != 0.0f) {
			ofstream tied("AStarTiedWeights.txt",std::ios::app);
			tied << currentAStarWeightsScore << " = bestAStarWeightsScore\n";
			tied << AStarWeights.linksWeight << " = linksWeight\n";
			tied << AStarWeights.blocksWeight << " = blocksWeight\n";
			tied << AStarWeights.doubleWeight << " = doubleWeight\n";
			tied << "\n";
		}
		bestAStarWeightsScore = currentAStarWeightsScore;
	}
	else {
		if (currentAStarWeightsScore >= bestAStarWeightsScore - 1.0f) {
			ofstream tied("AStarTiedWeights.txt",std::ios::app);
			tied << currentAStarWeightsScore << " = tiedAStarWeightsScore\n";
			tied << AStarWeights.linksWeight << " = linksWeight\n";
			tied << AStarWeights.blocksWeight << " = blocksWeight\n";
			tied << AStarWeights.doubleWeight << " = doubleWeight\n";
			tied << "\n";
			tied.close();
		}
		ofstream weights("AStarCurrentWeights.txt");

		weights << currentAStarWeightsScore << " = currentAStarWeightsScore\n";
		weights << AStarWeights.linksWeight << " = linksWeight\n";
		weights << AStarWeights.blocksWeight << " = blocksWeight\n";
		weights << AStarWeights.doubleWeight << " = doubleWeight\n";
	}
	return;
}//end SaveAStarWeights

void AStarPathfinder::PerturbAStarWeights()
{
	AStarWeights.linksWeight *= (((rand()%2000) * 0.0002f) + 0.8f);
	AStarWeights.blocksWeight *= (((rand()%2000) * 0.0002f) + 0.8f);
	AStarWeights.doubleWeight *= (((rand()%2000) * 0.0002f) + 0.8f);

	if (AStarWeights.linksWeight < 25 || AStarWeights.linksWeight > 10000) AStarWeights.linksWeight = 500;
	if (AStarWeights.blocksWeight < 10 || AStarWeights.blocksWeight > 4000) AStarWeights.blocksWeight = 200;
	if (AStarWeights.doubleWeight < 10 || AStarWeights.doubleWeight > 4000) AStarWeights.doubleWeight = 200;

	return;
}//end PerturbAStarWeights



#include "stdafx.h"

vector<MYPoint>				verticalPlayerPegs;
vector<MYPoint>				horizontalPlayerPegs;
vector<list<MYPoint>>		LinkGroups;

CBoardManager::CBoardManager(SharedAStarData (*pSharedBoard)[MAXBOARDSIZE][MAXBOARDSIZE],
							 int const XBoardSize,
							 int const YBoardSize)
{
	PERFORMANCE_MARKER
	pMainBoard = &MainBoard;
	SharedBoard = pSharedBoard;
	CBoardManager::XBoardSize = XBoardSize;
	CBoardManager::YBoardSize = YBoardSize;
	for (int x = 0; x < MAXBOARDSIZE; x++) {
		for (int y = 0; y < MAXBOARDSIZE; y++) {
			(*pMainBoard)[x][y].AStarStatus = AStar_Init;
			(*pMainBoard)[x][y].AStarData.AStarF = 0;
			(*pMainBoard)[x][y].AStarData.AStarG = 0;
			(*pMainBoard)[x][y].AStarData.AStarH = 0;
			(*pMainBoard)[x][y].AStarData.ParentLink = CLink(MYPoint(0,0), CJump(NOTADIR, NOTAJUMP));
		}
	}
	return;
}//end ctor

void CBoardManager::SetBoardSize(int const xSize,
								 int const ySize)
{
	XBoardSize = xSize;
	YBoardSize = ySize;
	return;
}//end SetBoardSize

void CBoardManager::GetNineLinks(const CLink& link,
								 NineLinks& nineLinks)
{
	PERFORMANCE_MARKER
	if (link.IsDouble() == false) {
		bool wasEmpty = nineLinks.empty();
		NineLinks::iterator front = nineLinks.begin();
		int x = link.startPeg.x;
		int y = link.startPeg.y;
		switch (link.jump.direction)
		{
		case leftUp:
			nineLinks.push_front(CLink(MYPoint(x-1, y), upLeft));
			nineLinks.push_front(CLink(MYPoint(x-1, y), upRight));
			nineLinks.push_front(CLink(MYPoint(x-1, y), rightUp));
			nineLinks.push_front(CLink(MYPoint(x-1, y-1), downRight));
			nineLinks.push_front(CLink(MYPoint(x-1, y-1), downLeft));
			nineLinks.push_front(CLink(MYPoint(x-1, y-1), leftDown));
			nineLinks.push_front(CLink(MYPoint(x, y-1), downLeft));
			nineLinks.push_front(CLink(MYPoint(x, y-1), leftDown));
			nineLinks.push_front(CLink(MYPoint(x-2, y), upRight));
			break;
		case upLeft:
			nineLinks.push_front(CLink(MYPoint(x, y-1), downLeft));
			nineLinks.push_front(CLink(MYPoint(x, y-1), leftDown));
			nineLinks.push_front(CLink(MYPoint(x, y-1), leftUp));
			nineLinks.push_front(CLink(MYPoint(x-1, y-1), upRight));
			nineLinks.push_front(CLink(MYPoint(x-1, y-1), rightUp));
			nineLinks.push_front(CLink(MYPoint(x-1, y-1), rightDown));
			nineLinks.push_front(CLink(MYPoint(x-1, y), upRight));
			nineLinks.push_front(CLink(MYPoint(x-1, y), rightUp));
			nineLinks.push_front(CLink(MYPoint(x, y-2), leftDown));
			break;
		case upRight:
			nineLinks.push_front(CLink(MYPoint(x+1, y-1), leftDown));
			nineLinks.push_front(CLink(MYPoint(x+1, y-1), leftUp));
			nineLinks.push_front(CLink(MYPoint(x+1, y-1), upLeft));
			nineLinks.push_front(CLink(MYPoint(x, y-1), rightUp));
			nineLinks.push_front(CLink(MYPoint(x, y-1), rightDown));
			nineLinks.push_front(CLink(MYPoint(x, y-1), downRight));
			nineLinks.push_front(CLink(MYPoint(x, y-2), rightDown));
			nineLinks.push_front(CLink(MYPoint(x, y-2), downRight));
			nineLinks.push_front(CLink(MYPoint(x+1, y), leftUp));
			break;
		case rightUp:
			nineLinks.push_front(CLink(MYPoint(x+1, y-1), rightDown));
			nineLinks.push_front(CLink(MYPoint(x+1, y-1), downRight));
			nineLinks.push_front(CLink(MYPoint(x+1, y-1), downLeft));
			nineLinks.push_front(CLink(MYPoint(x+1, y), leftUp));
			nineLinks.push_front(CLink(MYPoint(x+1, y), upLeft));
			nineLinks.push_front(CLink(MYPoint(x+1, y), upRight));
			nineLinks.push_front(CLink(MYPoint(x+2, y), leftUp));
			nineLinks.push_front(CLink(MYPoint(x+2, y), upLeft));
			nineLinks.push_front(CLink(MYPoint(x, y-1), downRight));
			break;
		case rightDown:
			nineLinks.push_front(CLink(MYPoint(x+1, y), downRight));
			nineLinks.push_front(CLink(MYPoint(x+1, y), downLeft));
			nineLinks.push_front(CLink(MYPoint(x+1, y), leftDown));
			nineLinks.push_front(CLink(MYPoint(x+1, y+1), upLeft));
			nineLinks.push_front(CLink(MYPoint(x+1, y+1), upRight));
			nineLinks.push_front(CLink(MYPoint(x+1, y+1), rightUp));
			nineLinks.push_front(CLink(MYPoint(x, y+1), upRight));
			nineLinks.push_front(CLink(MYPoint(x, y+1), rightUp));
			nineLinks.push_front(CLink(MYPoint(x+2, y), downLeft));
			break;
		case downRight:
			nineLinks.push_front(CLink(MYPoint(x, y+1), upRight));
			nineLinks.push_front(CLink(MYPoint(x, y+1), rightUp));
			nineLinks.push_front(CLink(MYPoint(x, y+1), rightDown));
			nineLinks.push_front(CLink(MYPoint(x+1, y+1), downLeft));
			nineLinks.push_front(CLink(MYPoint(x+1, y+1), leftDown));
			nineLinks.push_front(CLink(MYPoint(x+1, y+1), leftUp));
			nineLinks.push_front(CLink(MYPoint(x+1, y), downLeft));
			nineLinks.push_front(CLink(MYPoint(x+1, y), leftDown));
			nineLinks.push_front(CLink(MYPoint(x, y+2), rightUp));
			break;
		case downLeft:
			nineLinks.push_front(CLink(MYPoint(x-1, y+1), rightUp));
			nineLinks.push_front(CLink(MYPoint(x-1, y+1), rightDown));
			nineLinks.push_front(CLink(MYPoint(x-1, y+1), downRight));
			nineLinks.push_front(CLink(MYPoint(x, y+1), leftDown));
			nineLinks.push_front(CLink(MYPoint(x, y+1), leftUp));
			nineLinks.push_front(CLink(MYPoint(x, y+1), upLeft));
			nineLinks.push_front(CLink(MYPoint(x, y+2), leftUp));
			nineLinks.push_front(CLink(MYPoint(x, y+2), upLeft));
			nineLinks.push_front(CLink(MYPoint(x-1, y), rightDown));
			break;
		case leftDown:
			nineLinks.push_front(CLink(MYPoint(x-1, y+1), leftUp));
			nineLinks.push_front(CLink(MYPoint(x-1, y+1), upLeft));
			nineLinks.push_front(CLink(MYPoint(x-1, y+1), upRight));
			nineLinks.push_front(CLink(MYPoint(x-1, y), rightDown));
			nineLinks.push_front(CLink(MYPoint(x-1, y), downRight));
			nineLinks.push_front(CLink(MYPoint(x-1, y), downLeft));
			nineLinks.push_front(CLink(MYPoint(x-2, y), rightDown));
			nineLinks.push_front(CLink(MYPoint(x-2, y), downRight));
			nineLinks.push_front(CLink(MYPoint(x, y+1), upLeft));
			break;
		default:
			break;
		};

		removeInvalidNineLinks(nineLinks, wasEmpty, front);
	}
	else {
		CPathDirs pathDirs = link.GetPathDirs();
		MYPoint IntPeg = GetDestFromDir(link.startPeg, pathDirs.leftDir);
		GetNineLinks(CLink(link.startPeg, pathDirs.leftDir), nineLinks);
		GetNineLinks(CLink(IntPeg, pathDirs.rightDir), nineLinks);
		if (link.IsDoubleStraight() == false) {
			IntPeg = GetDestFromDir(link.startPeg, pathDirs.rightDir);
			GetNineLinks(CLink(link.startPeg, pathDirs.rightDir), nineLinks);
			GetNineLinks(CLink(IntPeg, pathDirs.leftDir), nineLinks);
		}
		else {
			/*
			for (CDir dir = leftUp; dir != NOTADIR; ++dir) {
				if (dir != link.jump.direction && dir != link.jump.direction.GetOppositeDirection()) {
					if (isPegWithinBoard(GetDestFromDir(IntPeg, dir)) == true) {
						nineLinks.push_front(CLink(IntPeg, dir));
					}
				}
			}
			*/
		}
	}
	return;
}//end GetNineLinks

void CBoardManager::removeInvalidNineLinks(NineLinks& nineLinks,
										   bool const wasEmpty,
										   NineLinks::iterator front)
{
	PERFORMANCE_MARKER
	NineLinks::iterator startIter = nineLinks.begin();
	for (int count = 0; count < 9; ++count) {
		if (isLinkWithinBoard(*startIter) == false) {
			startIter = nineLinks.erase(startIter);
		}
		else {
			if (wasEmpty == false) {
				for (NineLinks::iterator compareIter = front; compareIter != nineLinks.end(); ++compareIter) {
					if (*compareIter == *startIter) {
						if (front == compareIter) {
							front = nineLinks.erase(compareIter);
						}
						else {
							nineLinks.erase(compareIter);
						}
						break;
					}
				}
			}
			++startIter;
		}
	}
	return;
}//end removeInvalidNineLinks

int CBoardManager::CountTurnsToLink(const CLink& link,
									ePlayer const player)
{
	PERFORMANCE_MARKER
	MYPoint destPeg = link.GetDestFromDir();
	if (arePegsLinked(link.startPeg, destPeg) == true) {
		return 0;
	}

	int turns = 0;
	if (isOwnerLinkable(link.startPeg, player) == false) {
		++turns;
	}
	if (isOwnerLinkable(destPeg, player) == false) {
		++turns;
	}
	if (link.IsDouble() == true) {
		CPathDirs pathDirs = link.GetPathDirs();
		MYPoint leftPeg = GetDestFromDir(link.startPeg, pathDirs.leftDir);
		MYPoint rightPeg = GetDestFromDir(link.startPeg, pathDirs.rightDir);
		if ((isPegValid(leftPeg, player) == true
			&& isOwnerLinkable(leftPeg, player) == true
			&& isDestBlocked(link.startPeg, pathDirs.leftDir) == false
			&& isDestBlocked(leftPeg, pathDirs.rightDir) == false)
			|| (isPegValid(rightPeg, player) == true
			&& isOwnerLinkable(rightPeg, player) == true
			&& isDestBlocked(link.startPeg, pathDirs.rightDir) == false
			&& isDestBlocked(rightPeg, pathDirs.leftDir) == false)) {
		}
		else {
			++turns;
		}
	}
	return turns;
}//end CountTurnsToLink

bool CBoardManager::canPegAndLinkBeBlocked(const CLink& link,
										   const MYPoint& pegInLink,
										   ePlayer const player)
{
	PERFORMANCE_MARKER
	insertPeg(pegInLink, player);
	bool returnValue = false;
	if (isDestLinked(link.startPeg, link.jump, player) == false) {
		returnValue = canLinkBeBlocked(link, player, true);
	}

	removePeg(pegInLink, player);
	return returnValue;
}//end canPegAndLinkBeBlocked

bool CBoardManager::canLinkBeBlocked(const CLink& link,
									 ePlayer const player)
{
	return canLinkBeBlocked(link, player, (player != currentPlayer));
}//end canLinkBeBlocked

bool CBoardManager::canLinkBeBlocked(const CLink& link,
									ePlayer const player,
									bool const opponentsTurn)
{
	PERFORMANCE_MARKER
	if (isLinkValid(link, player) == false) {
		return true;
	}
	if (isDestBlocked(link.startPeg, link.jump, player) == true) {
		return true;
	}

	if (link.IsDouble() == true) {
		return canDoubleBeBlocked(link, player, opponentsTurn);
	}

	if (opponentsTurn == true
		&& isOwnerLinkable(link.startPeg, player) == false
		&& isOwnerLinkable(link.GetDestFromDir(), player) == false) {
		return true;
	}

	NineLinks nineLinks;
	GetNineLinks(link, nineLinks);
	return canEnemyBlockLinkLogic(nineLinks, player);
}//end canLinkBeBlocked

bool CBoardManager::CanPlayerBlockLinkLogic(const NineLinks& pNineLinks,
											ePlayer const pegPlayer)
{
	for each (CLink link in pNineLinks) {
		if (canPegLink(link.startPeg, link.jump.direction, pegPlayer) == true) {
			return true;
		}
	}
	return false;
}//end CanPlayerBlockLinkLogic

bool CBoardManager::canEnemyBlockLinkLogic(const NineLinks& pNineLinks,
										   ePlayer const linkPlayer)
{
	for each (CLink link in pNineLinks) {
		if (isOwnerEnemy(link.startPeg, linkPlayer) == true) {
			if (canPegLink(link.startPeg, link.jump.direction, GetOwner(link.startPeg)) == true) {
				return true;
			}
		}
		else {
			MYPoint Dest = link.GetDestFromDir();
			if (isOwnerEnemy(Dest, linkPlayer) == true
				&& canPegLink(link.startPeg, link.jump.direction, GetOwner(Dest)) == true) {
				return true;
			}
		}
	}
	return false;
}//end canEnemyBlockLinkLogic

bool CBoardManager::canDoubleBeBlocked(const CLink& link,
									   ePlayer const player,
									   bool const bOpponentsTurn)
{
	//a player needs 3 turns to place a double jump from scratch (2 turns after placing this next peg)
	//if 3 is needed, then the opponent can block it in 2 turns
	//if the player needs 2 turns (1 after placing this peg)
	//then the opponent needs at least 1 block *in place* to block it in time
	PERFORMANCE_MARKER
	int neededLeftTurns = 3;
	int neededRightTurns = 3;
	if (isOwnerLinkable(link.startPeg, player) == true) {
		--neededLeftTurns;
		--neededRightTurns;
	}
	if (isOwnerLinkable(link.GetDestFromDir(), player) == true) {
		--neededLeftTurns;
		--neededRightTurns;
	}

	//assumes startPeg and DestPeg are valid for the player,
	//but the intermediate pegs may not be
	CPathDirs pathDirs = link.GetPathDirs();
	MYPoint LeftPeg = GetDestFromDir(link.startPeg, pathDirs.leftDir);
	MYPoint RightPeg = LeftPeg;
	bool leftPegValid = true;
	bool rightPegValid = true;
	if (link.IsDoubleStraight() == false) {
		RightPeg = GetDestFromDir(link.startPeg, pathDirs.rightDir);
		leftPegValid = isPegValid(LeftPeg, player);
		rightPegValid = isPegValid(RightPeg, player);
	}

	//determine if the paths are currently unblocked
	//although this does not prove they won't be blocked later
	bool leftPathUnblocked = (leftPegValid == true
		&& isOwnerEnemy(LeftPeg, player) == false
		&& isDestBlocked(link.startPeg, pathDirs.leftDir) == false
		&& isDestBlocked(LeftPeg, pathDirs.rightDir) == false);

	bool rightPathUnblocked = leftPathUnblocked;
	if (link.IsDoubleStraight() == false) {
		rightPathUnblocked = (rightPegValid == true
			&& isOwnerEnemy(RightPeg, player) == false
			&& isDestBlocked(link.startPeg, pathDirs.rightDir) == false
			&& isDestBlocked(RightPeg, pathDirs.leftDir) == false);
	}

	bool leftIntPeg = (leftPathUnblocked == true && isOwnerLinkable(LeftPeg, player) == true);
	bool rightIntPeg = (rightPathUnblocked == true && isOwnerLinkable(RightPeg, player) == true);
	//if the int peg is player owned and that path is not blocked, decrease turns needed
	if (leftIntPeg == true) {
		--neededLeftTurns;
	}
	if (rightIntPeg == true) {
		--neededRightTurns;
	}
	if (bOpponentsTurn == false && (neededLeftTurns <= 1 || neededRightTurns <= 1)) {
		return false;
	}

	//opponentsTurns should be 1 higher to represent the fact he goes second
	int opponentsLeftTurns = 2;
	int opponentsRightTurns = 2;
	if (bOpponentsTurn == true) {
		--opponentsLeftTurns;
		--opponentsRightTurns;
	}
	if (leftPathUnblocked == false) {
		neededLeftTurns = 4;
		opponentsLeftTurns = 0;
	}
	bool rightPathValid = (rightPathUnblocked == true && link.IsDoubleStraight() == false);
	if (rightPathValid == false) {
		neededRightTurns = 4;
		opponentsRightTurns = 0;
	}
	if (neededLeftTurns > opponentsLeftTurns && neededRightTurns > opponentsRightTurns) {
		return true;
	}
	if (neededLeftTurns <= opponentsLeftTurns - 1
		|| neededRightTurns <= opponentsRightTurns - 1) {
		//check if there is even a chance of blocking
		return false;
	}

	bool leftBlockNeeded = (neededLeftTurns > opponentsLeftTurns - 1
							&& leftPathUnblocked == true);
	bool rightBlockNeeded = (neededRightTurns > opponentsRightTurns - 1
							&& link.IsDoubleStraight() == false
							&& rightPathUnblocked == true);

	leftNine.clear();
	rightNine.clear();
	if (leftBlockNeeded == true) {
		GetNineLinks(CLink(link.startPeg, pathDirs.leftDir), leftNine);
		GetNineLinks(CLink(LeftPeg, pathDirs.rightDir), leftNine);
		if (rightBlockNeeded == false) {
			for each (CLink left in leftNine) {
				if (canDoubleBeBlockedLogic(left, player) == true) {
					return true;
				}
			}
		}
	}

	if (rightBlockNeeded == true){
		GetNineLinks(CLink(link.startPeg, pathDirs.rightDir), rightNine);
		GetNineLinks(CLink(RightPeg, pathDirs.leftDir), rightNine);
		if (leftBlockNeeded == false) {
			for each (CLink right in rightNine) {
				if (canDoubleBeBlockedLogic(right, player) == true) {
					return true;
				}
			}
		}
		else {
			//find the move that blocks both sides at once
			for each (CLink left in leftNine) {
				NineLinks::iterator found = find(rightNine.begin(), rightNine.end(), left);
				if (found != rightNine.end()) {
					if (canDoubleBeBlockedLogic(left, player) == true) {
						return true;
					}
				}
			}
		}
	}
	return false;
}//end canDoubleBeBlocked

bool CBoardManager::canDoubleBeBlockedLogic(const CLink& link,
											ePlayer const player)
{
	PERFORMANCE_MARKER
	MYPoint dest = link.GetDestFromDir();
	if (isOwnerEnemy(link.startPeg, player) == true) {
		if (isDestBlocked(link.startPeg, link.jump.direction) == false
			&& isPegValid(dest, GetOwner(link.startPeg)) == true) {
			return true;
		}
		//return false;
	}
	else if (isOwnerEnemy(dest, player) == true
		&& isDestBlocked(link.startPeg, link.jump.direction) == false
		&& isPegValid(link.startPeg, GetOwner(dest)) == true) {
		return true;
	}
	return false;
}//end canDoubleBeBlockedLogic

void CBoardManager::RemoveDuplicateNineLinks(NineLinks& nineLinks,
											 NineLinks& otherLinks,
											 NineLinks& duplicateLinks)
{
	PERFORMANCE_MARKER
	for (NineLinks::iterator nine = nineLinks.begin(); nine != nineLinks.end();) {
		NineLinks::iterator found = find(otherLinks.begin(), otherLinks.end(), *nine);
		if (found != otherLinks.end()) {
			duplicateLinks.push_back(*nine);
			nine = nineLinks.erase(nine);
			otherLinks.erase(found);
		}
		else {
			++nine;
		}
	}
	return;
}//end RemoveDuplicateNineLinks

bool CBoardManager::canPegBlockLink(const MYPoint& peg,
									const CLink& link,
									ePlayer const pegPlayer,
									ePlayer const linkPlayer)
{
	PERFORMANCE_MARKER
	if (isDestBlocked(link.startPeg, link.jump, linkPlayer) == true) {
		return false;
	}
	insertPeg(peg, pegPlayer);
	bool returnValue = true;
	if (canPegLink(link.startPeg, link.jump, linkPlayer) == true) {
		returnValue = canPegBlockLinkLogic(peg, link, pegPlayer, linkPlayer);
	}

	removePeg(peg, pegPlayer);
	return returnValue;
}//end canPegBlockLink

bool CBoardManager::canPegBlockLinkLogic(const MYPoint& peg,
										 const CLink& link,
										 ePlayer const pegPlayer,
										 ePlayer const linkPlayer)
{
	//already blocked, don't return false positives
	if (isLinkValid(link, linkPlayer) == false) {
		return false;
	}

	if (link.IsDouble() == true) {
		return canPegBlockDouble(peg, link, pegPlayer, linkPlayer);
	}
	else {
		//check if the peg is one of the pegs in the 9 blocking links
		NineLinks nineLinks;
		GetNineLinks(link, nineLinks);
		for each (CLink link in nineLinks) {
			if (link.startPeg == peg) {
				if (canPegLink(link.startPeg, link.jump.direction, pegPlayer) == true) {
					return true;
				}
			}
			else {
				MYPoint Dest = link.GetDestFromDir();
				if (Dest == peg
					&& canPegLink(link.startPeg, link.jump.direction, pegPlayer) == true) {
					return true;
				}
			}
		}
	}
	return false;
}//end canPegBlockLinkLogic

bool CBoardManager::canPegBlockDouble(const MYPoint& peg,
									  const CLink& link,
									  ePlayer const pegPlayer,
									  ePlayer const linkPlayer)
{
	int neededLeftTurns = 3;
	int neededRightTurns = 3;
	bool startLinkable = isOwnerLinkable(link.startPeg, linkPlayer);
	if (startLinkable == true) {
		--neededLeftTurns;
		--neededRightTurns;
	}
	bool destLinkable = isOwnerLinkable(link.GetDestFromDir(), linkPlayer);
	if (destLinkable == true) {
		--neededLeftTurns;
		--neededRightTurns;
	}

	//assumes startPeg and DestPeg are valid for the player,
	//but the intermediate pegs may not be
	CPathDirs pathDirs = link.GetPathDirs();
	MYPoint LeftPeg = GetDestFromDir(link.startPeg, pathDirs.leftDir);
	MYPoint RightPeg = LeftPeg;
	bool leftPegValid = true;
	bool rightPegValid = true;
	if (link.IsDoubleStraight() == false) {
		RightPeg = GetDestFromDir(link.startPeg, pathDirs.rightDir);
		leftPegValid = isPegValid(LeftPeg, linkPlayer);
		rightPegValid = isPegValid(RightPeg, linkPlayer);
	}

	//determine if the paths are currently unblocked
	//although this does not prove they won't be blocked later
	bool leftPathUnblocked = (leftPegValid == true
		&& isOwnerEnemy(LeftPeg, linkPlayer) == false
		&& isDestBlocked(link.startPeg, pathDirs.leftDir) == false
		&& isDestBlocked(LeftPeg, pathDirs.rightDir) == false);

	bool rightPathUnblocked = leftPathUnblocked;
	if (link.IsDoubleStraight() == false) {
		rightPathUnblocked = (rightPegValid == true
			&& isOwnerEnemy(RightPeg, linkPlayer) == false
			&& isDestBlocked(link.startPeg, pathDirs.rightDir) == false
			&& isDestBlocked(RightPeg, pathDirs.leftDir) == false);
	}

	bool leftIntPeg = (leftPathUnblocked == true && isOwnerLinkable(LeftPeg, linkPlayer) == true);
	bool rightIntPeg = (rightPathUnblocked == true && isOwnerLinkable(RightPeg, linkPlayer) == true);
	//if the int peg is player owned and that path is not blocked, decrease turns needed
	if (leftIntPeg == true) {
		--neededLeftTurns;
	}
	if (rightIntPeg == true) {
		--neededRightTurns;
	}
	if (neededLeftTurns <= 1 || neededRightTurns <= 1) {
		return false;
	}

	//opponentsTurns should be 1 higher to represent the fact he goes second
	int opponentsLeftTurns = 2;
	int opponentsRightTurns = 2;
	if (leftPathUnblocked == false) {
		neededLeftTurns = 4;
		opponentsLeftTurns = 0;
	}
	bool rightPathValid = (rightPathUnblocked == true && link.IsDoubleStraight() == false);
	if (rightPathValid == false) {
		neededRightTurns = 4;
		opponentsRightTurns = 0;
	}
	if (neededLeftTurns > opponentsLeftTurns && neededRightTurns > opponentsRightTurns) {
		//changed from true to false, don't report false positives
		return false;
	}
	if (neededLeftTurns <= opponentsLeftTurns - 1
		|| neededRightTurns <= opponentsRightTurns - 1) {
		//check if there is even a chance of blocking
		return false;
	}

	if (link.IsDoubleStraight() == true
		&& peg == LeftPeg) {
		if (isPegWithinBoard(LeftPeg, pegPlayer) == true
			&& isPegAvailable(LeftPeg) == true) {
			for (CDir dir = leftUp; dir != NOTADIR; ++dir) {
				if (canPegLink(LeftPeg, dir, pegPlayer) == true) {
					return true;
				}
			}
		}
	}

	bool leftBlockNeeded = (neededLeftTurns > opponentsLeftTurns - 1
							&& leftPathUnblocked == true);
	bool rightBlockNeeded = (neededRightTurns > opponentsRightTurns - 1
							&& link.IsDoubleStraight() == false
							&& rightPathUnblocked == true);

	leftNine.clear();
	rightNine.clear();
	if (leftBlockNeeded == true) {
		//handle the special case of a double straight
		if (! (link.IsDoubleStraight() == true
			&& (startLinkable == true || leftIntPeg == true))) {
			GetNineLinks(CLink(link.startPeg, pathDirs.leftDir), leftNine);
		}
		if (! (link.IsDoubleStraight() == true
			&& (destLinkable == true || leftIntPeg == true))) {
			GetNineLinks(CLink(LeftPeg, pathDirs.rightDir), leftNine);
		}
		if (rightBlockNeeded == false) {
			for each (CLink left in leftNine) {
				if (canPegBlockDoubleLogic(peg, left, pegPlayer) == true) {
					return true;
				}
			}
		}
	}

	if (rightBlockNeeded == true){
		GetNineLinks(CLink(link.startPeg, pathDirs.rightDir), rightNine);
		GetNineLinks(CLink(RightPeg, pathDirs.leftDir), rightNine);
		if (leftBlockNeeded == false) {
			for each (CLink right in rightNine) {
				if (canPegBlockDoubleLogic(peg, right, pegPlayer) == true) {
					return true;
				}
			}
		}
		else {
			//find the move that blocks both sides at once
			for each (CLink left in leftNine) {
				NineLinks::iterator found = find(rightNine.begin(), rightNine.end(), left);
				if (found != rightNine.end()) {
					if (canPegBlockDoubleLogic(peg, left, pegPlayer) == true) {
						return true;
					}
				}
			}
		}
	}
	return false;
}//end canPegBlockDouble

bool CBoardManager::canPegBlockDoubleLogic(const MYPoint& peg,
										   const CLink& link,
										   ePlayer const pegPlayer)
{
	PERFORMANCE_MARKER
	MYPoint dest = link.GetDestFromDir();
	if (link.startPeg == peg) {
		if (isDestBlocked(link.startPeg, link.jump.direction) == false
			&& isPegValid(dest, pegPlayer) == true) {
			return true;
		}
		//return false;
	}
	else if (dest == peg
		&& isDestBlocked(link.startPeg, link.jump.direction) == false
		&& isPegValid(link.startPeg, pegPlayer) == true) {
		return true;
	}
	return false;
}//end canPegBlockDoubleLogic

CPathReturn CBoardManager::willPegBlockLink(const MYPoint& Peg,
											const CLink& link,
											ePlayer const pegPlayer,
											ePlayer const linkPlayer)
{
	PERFORMANCE_MARKER
	CPathReturn pathReturn;
	if (link.IsDouble() == false) {
		pathReturn.leftPath = pathReturn.rightPath = willPegBlockJump(Peg,
			link.startPeg, link.jump.direction, pegPlayer, linkPlayer);
	}
	else {
		bool nearLeftBlocked = true;
		bool farLeftBlocked = true;
		bool nearRightBlocked = true;
		bool farRightBlocked = true;
		CPathDirs pathDirs = link.GetPathDirs();
		MYPoint IntPeg = GetDestFromDir(link.startPeg, pathDirs.leftDir);
		//if the int peg is not valid for the link player, this path is blocked!
		if (isPegValid(IntPeg, linkPlayer) == true) {
			nearLeftBlocked = willPegBlockJump(Peg, link.startPeg, pathDirs.leftDir, pegPlayer, linkPlayer);
			farLeftBlocked = willPegBlockJump(Peg, IntPeg, pathDirs.rightDir, pegPlayer, linkPlayer);
		}

		if (link.IsDoubleStraight() == false) {
			IntPeg = GetDestFromDir(link.startPeg, pathDirs.rightDir);
			if (isPegValid(IntPeg, linkPlayer) == true) {
				nearRightBlocked = willPegBlockJump(Peg, link.startPeg, pathDirs.rightDir, pegPlayer, linkPlayer);
				farRightBlocked = willPegBlockJump(Peg, IntPeg, pathDirs.leftDir, pegPlayer, linkPlayer);
			}
		}

		pathReturn.leftPath = (nearLeftBlocked && farRightBlocked)
							|| (farLeftBlocked && nearRightBlocked);

		pathReturn.rightPath = (nearLeftBlocked && nearRightBlocked)
							|| (farLeftBlocked && farRightBlocked);
		pathReturn.andOr = OR;
	}
	return pathReturn;
}//end willPegBlockLink

bool CBoardManager::willPegBlockJump(const MYPoint& Peg,
									 const MYPoint& linkPeg,
									 CDir const linkDir,
									 ePlayer const pegPlayer,
									 ePlayer const linkPlayer)
{
	PERFORMANCE_MARKER
	if (Peg == linkPeg || Peg == GetDestFromDir(linkPeg, linkDir)) {
		if (pegPlayer == linkPlayer
			|| pegPlayer == LinkableByAny) {
			return false;
		}
		else {
			return true;
		}
	}
	if (isDestBlocked(linkPeg, linkDir, linkPlayer) == true) {
		return true;
	}
	NineLinks nineLinks;
	GetNineLinks(CLink(linkPeg, linkDir), nineLinks);
	for each (CLink link in nineLinks) {
		if (link.startPeg == Peg) {
			if (canPegLink(link.startPeg, link.jump.direction, pegPlayer) == true) {
				return true;
			}
		}
		else if (link.GetDestFromDir() == Peg) {
			if (canPegLink(link.startPeg, link.jump.direction, pegPlayer) == true) {
				return true;
			}
		}
	}
	return false;
}//end willPegBlockJump

bool CBoardManager::canPegLink(const MYPoint& Peg,
							   CDir const direction,
							   ePlayer const player)
{
	PERFORMANCE_MARKER
	if (isDestLinked(Peg, direction) == true) {
		return true;
	}
	if (isDestBlocked(Peg, direction, player) == true) {
		return false;
	}
	MYPoint Dest = GetDestFromDir(Peg, direction);
	if (isPegValid(Dest, player) == false) {
		return false;
	}
	if (isOwnerLinkable(Dest, player) == true
		|| isOwnerLinkable(Peg, player) == true) {
		return true;
	}
	return false;
}//end canPegLink

vector<MYPoint>* CBoardManager::GetPlayerPegList(ePlayer const player)
{
	if (isSideValid(player, TopAndBottom) == true) {
		return &verticalPlayerPegs;
	}
	else {
		return &horizontalPlayerPegs;
	}
}//end GetPlayerPegList

void CBoardManager::ClearPegList()
{
	verticalPlayerPegs.clear();
	horizontalPlayerPegs.clear();
	LinkGroups.clear();
	return;
}//end ClearPegList

void CBoardManager::GetDoublesFromPeg(const MYPoint& Peg,
									  ePlayer const player,
									  vector<CLink>& pDoubles)
{
	PERFORMANCE_MARKER
	list<CLink> doubles;
	vector<MYPoint>* pPegList = GetPlayerPegList(player);
	for (vector<MYPoint>::iterator Dest = pPegList->begin();
		Dest != pPegList->end(); ++Dest) {
		CJump jump = GetJumpFromPegs(Peg, *Dest);
		if (jump.jumpType != NOTAJUMP && jump.jumpType != SingleJump) {
			if (arePegsLinked(Peg, *Dest) == true) {
				continue;
			}

			bool nearLeftBlock = true;
			bool farLeftBlock = true;
			bool nearRightBlock = true;
			bool farRightBlock = true;

			CPathDirs pathDirs = jump.GetPathDirs();
			MYPoint IntPeg = GetDestFromDir(Peg, pathDirs.leftDir);
			if (isPegValid(IntPeg, player) == true) {
				nearLeftBlock = isDestBlocked(Peg, pathDirs.leftDir, player);
				farLeftBlock = isDestBlocked(IntPeg, pathDirs.rightDir, player);
				if (arePegsLinked(IntPeg, *Dest) == true) {
					if (nearLeftBlock == false) {
						//this is not a double, it is a single
						continue;
					}
				}
				else if (arePegsLinked(Peg, IntPeg) == true) {
					if (farLeftBlock == false) {
						//this is not a double, it is a single
						continue;
					}
				}
			}

			if (jump.IsDoubleStraight() == false) {
				IntPeg = GetDestFromDir(Peg, pathDirs.rightDir);
				if (isPegValid(IntPeg, player) == true) {
					nearRightBlock = isDestBlocked(Peg, pathDirs.rightDir, player);
					farRightBlock = isDestBlocked(IntPeg, pathDirs.leftDir, player);
					if (arePegsLinked(IntPeg, *Dest) == true) {
						if (nearRightBlock == false) {
							//this is not a double, it is a single
							continue;
						}
					}
					else if (arePegsLinked(Peg, IntPeg) == true) {
						if (farRightBlock == false) {
							//this is not a double, it is a single
							continue;
						}
					}
				}
			}
			if ((nearLeftBlock || farLeftBlock) && (nearRightBlock || farRightBlock)) {
				continue;
			}
			doubles.push_back(CLink(Peg, jump));
		}
	}
	
start:
	for (list<CLink>::iterator iter = doubles.begin(); iter != doubles.end(); ++iter) {
		bool remove = false;
		list<CLink>::iterator compare = iter;
		for (++compare; compare != doubles.end(); ++compare) {
			//alternate method is if they have an int peg in common
			MYPoint Dest1 = iter->GetDestFromDir();
			MYPoint Dest2 = compare->GetDestFromDir();
			if (arePegsLinked(Dest1, Dest2) == true) {
				remove = true;
				break;
			}
			CJump jump = GetJumpFromPegs(Dest1, Dest2);
			if (jump.jumpType == NOTAJUMP) {
				continue;
			}
			if (isDestBlocked(Dest1, jump, player) == false) {
				remove = true;
				break;
			}
		}
		if (remove == true) {
			if (GetJumpTypeWeight(iter->jump.jumpType) > GetJumpTypeWeight(compare->jump.jumpType)) {
				doubles.erase(compare);
			}
			else {
				doubles.erase(iter);
			}
			goto start;
		}
		else {
			pDoubles.push_back(*iter);
		}
	}

	return;
}//end GetDoublesFromPeg

int CBoardManager::GetJumpTypeCost(eJump const jumpType)
{
	switch (jumpType) {
	case SingleJump:
		return ONEJUMP + 10;
	case DoubleStraight:
		return TWOJUMPS + 18;
	case DoubleDiamond:
		return TWOJUMPS;
	case DoubleSquare:
		return TWOJUMPS + 5;
	case DoubleShortDiamond:
		return TWOJUMPS + 16;
	default:
		return 999;
	}
}//end GetJumpTypeCost

int CBoardManager::GetJumpTypeWeight(eJump const jumpType)
{
	switch (jumpType) {
	case SingleJump:
		return 3;
	case DoubleStraight:
		return 7;
	case DoubleDiamond:
		return 20;
	case DoubleSquare:
		return 14;
	case DoubleShortDiamond:
		return 6;
	default:
		ASSERT(false);
		return 0;
	}
}//end GetJumpTypeWeight

CPathReturn CBoardManager::canPegLink(const MYPoint& Peg,
									  const CJump& jump,
									  ePlayer const player)
{
	PERFORMANCE_MARKER
	CPathReturn returnValue;
	if (jump.jumpType == SingleJump) {
		returnValue.leftPath = canPegLink(Peg, jump.direction, player);
		returnValue.rightPath = returnValue.leftPath;
	}
	else {
		CPathDirs pathDirs = jump.GetPathDirs();
		returnValue.leftPath = canPathLink(Peg, pathDirs.leftDir, pathDirs.rightDir, player);
		returnValue.rightPath = canPathLink(Peg, pathDirs.rightDir, pathDirs.leftDir, player);
		returnValue.andOr = OR;
	}
	return returnValue;
}//end canPegLink

bool CBoardManager::canPathLink(const MYPoint& Peg,
								CDir const dir1,
								CDir const dir2,
								ePlayer const player)
{
	PERFORMANCE_MARKER
	MYPoint IntPeg = GetDestFromDir(Peg, dir1);
	if (isPegValid(IntPeg, player) == false) {
		return false;
	}
	MYPoint Dest = GetDestFromDir(IntPeg, dir2);
	if (isPegValid(Dest, player) == false) {
		return false;
	}
	if (isDestBlocked(Peg, dir1, player) == true) {
		return false;
	}
	if (isDestBlocked(IntPeg, dir2, player) == true) {
		return false;
	}
	
	return true;
}//end canPathLink

bool CBoardManager::isOwnerEnemy(const MYPoint& Peg,
								 ePlayer const player)
{
	return (*SharedBoard)[Peg.x][Peg.y].isOwnerEnemy(player);
}//end isOwnerEnemy

bool CBoardManager::isOwnerAPlayer(const MYPoint& Peg)
{
	return (*SharedBoard)[Peg.x][Peg.y].isOwnerAPlayer();
}//end isOwnerAPlayer

bool CBoardManager::isOwnerLinkable(const MYPoint& Peg,
									ePlayer const player)
{
	return (*SharedBoard)[Peg.x][Peg.y].isOwnerLinkable(player);
}//end isOwnerLinkable

bool CBoardManager::isOwnerThis(const MYPoint& Peg,
								ePlayer const player)
{
	return (GetOwner(Peg) == player) ? true : false;
}//end isOwnerThis

ePlayer CBoardManager::GetOwner(const MYPoint& Peg)
{
	return ((*SharedBoard)[Peg.x][Peg.y].owner);
}//end GetOwner

bool SharedAStarData::isOwnerLinkable(ePlayer const player)
{
	if (owner == player || owner == LinkableByAny) {
		return true;
	}
	return false;
}//end isOwnerLinkable

bool SharedAStarData::isOwnerEnemy(ePlayer const player)
{
	if ((isOwnerAPlayer() == true) &&
		owner != player) {
		return true;
	}
	return false;
}//end isOwnerEnemy

bool SharedAStarData::isOwnerAPlayer()
{
	if (owner != NotOwnable &&
		owner != NOTAPLAYER &&
		owner != CurrentlyUnowned &&
		owner != LinkableByAny) {
		return true;
	}
	return false;
}//end isOwnerAPlayer

bool CBoardManager::isPegAvailable(const MYPoint& Peg)
{
	ePlayer owner = GetOwner(Peg);
	if (owner == CurrentlyUnowned || owner == LinkableByAny) {
		return true;
	}
	return false;
}//end isPegAvailable

bool CBoardManager::isDestBlocked(const MYPoint& Peg,
								  CDir const direction,
								  ePlayer const player)
{
	if (isPegValid(GetDestFromDir(Peg, direction), player)) {
		if ((*SharedBoard)[Peg.x][Peg.y].blockedDirs[direction] == 0) {
			return false;
		}
	}
	return true;
}//end isDestBlocked

bool CBoardManager::isDestBlocked(const MYPoint& Peg,
								  CDir const direction)
{
	if (isPegWithinBoard(GetDestFromDir(Peg, direction))) {
		if ((*SharedBoard)[Peg.x][Peg.y].blockedDirs[direction] == 0) {
			return false;
		}
	}
	return true;
}//end isDestBlocked

CPathReturn CBoardManager::isDestBlocked(const MYPoint& Peg,
										 const CJump& jump,
										 ePlayer const player)
{
	PERFORMANCE_MARKER
	CPathReturn returnValue;
	if (jump.jumpType == SingleJump) {
		returnValue.leftPath = isDestBlocked(Peg, jump.direction, player);
		returnValue.rightPath = returnValue.leftPath;
	}
	else {
		CPathDirs pathDirs = jump.GetPathDirs();
		MYPoint IntPeg = GetDestFromDir(Peg, pathDirs.leftDir);
		MYPoint DestPeg = GetDestFromDir(IntPeg, pathDirs.rightDir);
		bool DestPegValid = isPegValid(DestPeg, player);
		returnValue.leftPath = (DestPegValid == false
			|| isPegValid(IntPeg, player) == false
			|| isDestBlocked(Peg, pathDirs.leftDir, player) == true
			|| isDestBlocked(IntPeg, pathDirs.rightDir, player) == true);
		if (jump.IsDoubleStraight() == false) {
			MYPoint IntPeg = GetDestFromDir(Peg, pathDirs.rightDir);
			returnValue.rightPath = (DestPegValid == false
				|| isPegValid(IntPeg, player) == false
				|| isDestBlocked(Peg, pathDirs.rightDir, player) == true
				|| isDestBlocked(IntPeg, pathDirs.leftDir, player) == true);
		}
		else {
			returnValue.rightPath = returnValue.leftPath;
		}
		returnValue.andOr = AND;
	}
	return returnValue;
}//end isDestBlocked

bool CBoardManager::isPegValid(const MYPoint& Peg,
							   ePlayer const player)
{
	PERFORMANCE_MARKER
	if (isPegWithinBoard(Peg, player) == true) {
		if (isPegAvailable(Peg) == true
			|| GetOwner(Peg) == player
			|| player == AnyPlayer) {
			return true;
		}
	}
	return false;
}//isPegValid

bool CBoardManager::isLinkValid(const CLink& link,
								ePlayer const player)
{
	PERFORMANCE_MARKER
	if (isPegValid(link.startPeg, player) == true
		&& isPegValid(link.GetDestFromDir(), player) == true) {
		if (link.IsDouble() == false) {
			return true;
		}
		if (isPegValid(link.GetIntPeg(LEFT), player) == true) {
			return true;
		}
		return (link.IsDoubleStraight() == false
			&& isPegValid(link.GetIntPeg(RIGHT), player));
	}
	return false;
}//isLinkValid

bool CBoardManager::arePegsLinked(const MYPoint& Peg1,
								  const MYPoint& Peg2)
{
	int Peg1LinkGroup = GetLinkGroup(Peg1);
	if (Peg1LinkGroup != 0) {
		return (Peg1LinkGroup == GetLinkGroup(Peg2));
	}
	return false;
}//end arePegsLinked

bool CBoardManager::arePegsLinked(const CLink& link)
{
	return (arePegsLinked(link.startPeg, link.GetDestFromDir()));
}//end arePegsLinked

bool CBoardManager::isDestLinked(const MYPoint& Peg,
								 CDir const direction)
{
	return (*SharedBoard)[Peg.x][Peg.y].linkedDirs[direction];
}//end isDestLinked

bool CBoardManager::isDestLinked(const MYPoint& Peg,
								 CDir const direction,
								 ePlayer const player)
{
	player;
	return (*SharedBoard)[Peg.x][Peg.y].linkedDirs[direction];
}//end isDestLinked

CPathReturn CBoardManager::isDestLinked(const MYPoint& Peg,
										const CJump& jump,
										ePlayer const player)
{
	PERFORMANCE_MARKER
	CPathReturn returnValue;
	if (jump.jumpType == SingleJump) {
		returnValue.leftPath = isDestLinked(Peg, jump.direction, player);
		returnValue.rightPath = returnValue.leftPath;
	}
	else {
		CPathDirs pathDirs = jump.GetPathDirs();
		MYPoint IntPeg = GetDestFromDir(Peg, pathDirs.leftDir);
		returnValue.leftPath = (isPegWithinBoard(IntPeg)
							&& isDestLinked(Peg, pathDirs.leftDir, player)
							&& isDestLinked(IntPeg, pathDirs.rightDir, player));
		returnValue.rightPath = returnValue.leftPath;
		returnValue.andOr = OR;
		if (returnValue.leftPath == false && jump.IsDoubleStraight() == false) {
			IntPeg = GetDestFromDir(Peg, pathDirs.rightDir);
			returnValue.leftPath = (isPegWithinBoard(IntPeg)
								&& isDestLinked(Peg, pathDirs.rightDir, player)
								&& isDestLinked(IntPeg, pathDirs.leftDir, player));
		}
	}
	return returnValue;
}//end isDestLinked

void CBoardManager::addLink(const MYPoint& Peg,
							CDir const direction)
{
	PERFORMANCE_MARKER
	(*SharedBoard)[Peg.x][Peg.y].numLinks++;
	(*SharedBoard)[Peg.x][Peg.y].linkedDirs[direction] = true;
	CDir opposite = direction.GetOppositeDirection();
	MYPoint DestPeg = GetDestFromDir(Peg, direction);
	(*SharedBoard)[DestPeg.x][DestPeg.y].numLinks++;
	(*SharedBoard)[DestPeg.x][DestPeg.y].linkedDirs[opposite] = true;

	NineLinks nineLinks;
	GetNineLinks(CLink(Peg, CJump(direction)), nineLinks);
	for each (CLink link in nineLinks) {
		addBlock(link.startPeg, link.jump.direction);
	}

	int SourceGroup = GetLinkGroup(Peg);
	int DestGroup = GetLinkGroup(DestPeg);

	if (SourceGroup  && !DestGroup) {
		(LinkGroups[SourceGroup-1]).push_back(DestPeg);
		SetLinkGroup(DestPeg, SourceGroup);
	}
	else if (DestGroup && !SourceGroup) {
		(LinkGroups[DestGroup-1]).push_back(Peg);
		SetLinkGroup(Peg, DestGroup);
	}
	else if (!SourceGroup && !DestGroup) {
		int group = GetNextLinkGroup();
		SetLinkGroup(Peg, group);
		SetLinkGroup(DestPeg, group);
		LinkGroups[group-1].push_back(Peg);
		LinkGroups[group-1].push_back(DestPeg);
	}
	else if (SourceGroup != DestGroup) {
		for (list<MYPoint>::iterator iter = LinkGroups[DestGroup - 1].begin();
			iter != LinkGroups[DestGroup - 1].end(); ++iter) {
			LinkGroups[SourceGroup - 1].push_back(*iter);
			SetLinkGroup(*iter, SourceGroup);
		}
		LinkGroups[DestGroup - 1].clear();
	}
	return;
}//end addLink

int CBoardManager::GetNextLinkGroup()
{
	PERFORMANCE_MARKER
	vector<list<MYPoint>>::iterator iter = LinkGroups.begin();
	int group = 1;
	bool foundEmpty = false;
	for (; iter != LinkGroups.end(); ++iter, ++group) {
		if (iter->empty() == true) {
			foundEmpty = true;
			break;
		}
	}
	if (foundEmpty == false) {
		LinkGroups.push_back(list<MYPoint>());
	}
	return group;
}//end GetNextLinkGroup

void CBoardManager::removeLink(const MYPoint& Peg,
							   CDir const direction)
{
	PERFORMANCE_MARKER
	(*SharedBoard)[Peg.x][Peg.y].numLinks--;
	(*SharedBoard)[Peg.x][Peg.y].linkedDirs[direction] = false;
	CDir opposite = direction.GetOppositeDirection();
	MYPoint DestPeg = GetDestFromDir(Peg, direction);
	(*SharedBoard)[DestPeg.x][DestPeg.y].numLinks--;
	(*SharedBoard)[DestPeg.x][DestPeg.y].linkedDirs[opposite] = false;

	NineLinks nineLinks;
	GetNineLinks(CLink(Peg, CJump(direction)), nineLinks);
	for each (CLink link in nineLinks) {
		removeBlock(link.startPeg, link.jump.direction);
	}

	int SourceGroup = GetLinkGroup(Peg);
	int DestGroup = GetLinkGroup(DestPeg);
	if (doesPegHaveLinks(DestPeg) == false) {
		(LinkGroups[DestGroup-1]).remove(DestPeg);
		SetLinkGroup(DestPeg, 0);
	}
	if (doesPegHaveLinks(Peg) == false) {
		if (SourceGroup != 0) {
			(LinkGroups[SourceGroup-1]).remove(Peg);
			SetLinkGroup(Peg, 0);
		}
	}

	if (doesPegHaveLinks(Peg) == true
		&& doesPegHaveLinks(DestPeg) == true
		&& DestGroup == SourceGroup) {
		//both source and dest have links
		//both groups are connected, may need to be split apart
		list<MYPoint> sourceGroupList;
		BuildGroupList(Peg, sourceGroupList);

		//if they are not connected, and their groups are the same, they need to be split apart
		if (find(sourceGroupList.begin(), sourceGroupList.end(), DestPeg) == sourceGroupList.end()) {
			LinkGroups[SourceGroup-1] = sourceGroupList;

			list<MYPoint> destGroupList;
			BuildGroupList(DestPeg, destGroupList);
			int group = GetNextLinkGroup();
			LinkGroups[group-1] = destGroupList;
			for each (MYPoint point in destGroupList) {
				SetLinkGroup(point, group);
			}
		}
	}
	return;
}//end removeLink

void CBoardManager::BuildGroupList(const MYPoint& Peg,
								   list<MYPoint>& groupList)
{
	PERFORMANCE_MARKER
	groupList.push_back(Peg);
	for (CDir dir = leftUp; dir != NOTADIR; ++dir) {
		if (isDestLinked(Peg, dir) == true) {
			MYPoint Dest = GetDestFromDir(Peg, dir);
			if (find(groupList.begin(), groupList.end(), Dest) == groupList.end()) {
				BuildGroupList(Dest, groupList);
			}
		}
	}
	return;
}//end BuildGroupList

void CBoardManager::addBlock(const MYPoint& Peg,
							 CDir const direction)
{
	PERFORMANCE_MARKER
	if (isPegWithinBoard(GetDestFromDir(Peg, direction))) {
		(*SharedBoard)[Peg.x][Peg.y].blockedDirs[direction]++;
		CDir opposite = direction.GetOppositeDirection();
		MYPoint DestPeg = GetDestFromDir(Peg, direction);
		(*SharedBoard)[DestPeg.x][DestPeg.y].blockedDirs[opposite]++;
	}
	return;
}//end addBlock

void CBoardManager::removeBlock(const MYPoint& Peg,
								CDir const direction)
{
	PERFORMANCE_MARKER
	if (isPegWithinBoard(GetDestFromDir(Peg, direction))) {
		(*SharedBoard)[Peg.x][Peg.y].blockedDirs[direction]--;
		CDir opposite = direction.GetOppositeDirection();
		MYPoint DestPeg = GetDestFromDir(Peg, direction);
		(*SharedBoard)[DestPeg.x][DestPeg.y].blockedDirs[opposite]--;
		if ((*SharedBoard)[Peg.x][Peg.y].blockedDirs[direction] == false) {
			if (isOwnerAPlayer(Peg) == true) {
				ePlayer DestOwner = GetOwner(DestPeg);
				if (DestOwner == GetOwner(Peg)
					|| DestOwner == LinkableByAny) {
					addLink(Peg, direction);
				}
			}
		}
	}
	return;
}//end removeBlock

void CBoardManager::insertPeg(const MYPoint& Source,
							  ePlayer const player)
{
	(*SharedBoard)[Source.x][Source.y].owner = player;
	for (CDir direction = leftUp; direction != NOTADIR; ++direction) {
		if (isDestBlocked(Source, direction, player) == false) {
			MYPoint Dest = GetDestFromDir(Source, direction);
			if (isPegWithinBoard(Dest)) {
				if (isOwnerLinkable(Dest, player) == true) {
					addLink(Source, direction);
				}
			}
		}
	}
	GetPlayerPegList(player)->push_back(Source);
	return;
}//insertPeg

void CBoardManager::removePeg(const MYPoint& Source,
							  ePlayer const player)
{
	(*SharedBoard)[Source.x][Source.y].owner = (*SharedBoard)[Source.x][Source.y].originalOwner;
	for (CDir direction = leftUp; direction != NOTADIR; ++direction) {
		if (isDestLinked(Source, direction) == true) {
			removeLink(Source, direction);
		}
	}
	GetPlayerPegList(player)->pop_back();
	return;
}//removePeg

CPathReturn CBoardManager::isLinkWithinBoard(const CLink& link,
											 ePlayer const player)
{
	PERFORMANCE_MARKER
	CPathReturn returnPath;
	returnPath.leftPath = returnPath.rightPath = isPegWithinBoard(link.startPeg, player)
		&& isPegWithinBoard(link.GetDestFromDir(), player);
	if ((link.IsDouble() == true)
		&& (returnPath == true)) {
		returnPath.leftPath = returnPath.rightPath =
			returnPath.leftPath && isPegWithinBoard(link.GetIntPeg(LEFT), player);

		if (link.IsDoubleStraight() == false) {
			returnPath.rightPath = returnPath.rightPath
				&& isPegWithinBoard(link.GetIntPeg(RIGHT), player);
		}
	}
	return returnPath;
}//end isLinkWithinBoard

bool CBoardManager::isPegWithinBoard(const MYPoint& Source,
									 ePlayer const player)
{
	ValidSides validSides = GetValidSides(player);
	if (validSides.leftSide == false && Source.x == 0) {
		return false;
	}
	if (validSides.rightSide == false && Source.x == XBoardSize - 1) {
		return false;
	}
	if (validSides.topSide == false && Source.y == 0) {
		return false;
	}
	if (validSides.bottomSide == false && Source.y == YBoardSize - 1) {
		return false;
	}

	return (isPegWithinBoard(Source));
}//end isPegWithinBoard

bool CBoardManager::isPegOnSide(const MYPoint& Peg,
								eSides const Side)
{
	PERFORMANCE_MARKER
	switch (Side) {
		case LeftSide:
			return (Peg.x == 0 && !(Peg.y == 0 || Peg.y == YBoardSize - 1));
		case RightSide:
			return (Peg.x == XBoardSize - 1 && !(Peg.y == 0 || Peg.y == YBoardSize - 1));
		case TopSide:
			return (Peg.y == 0 && !(Peg.x == 0 || Peg.x == XBoardSize - 1));
		case BottomSide:
			return (Peg.y == YBoardSize - 1 && !(Peg.x == 0 || Peg.x == XBoardSize - 1));
		case TopAndBottom:
			return (isPegOnSide(Peg, TopSide) || isPegOnSide(Peg, BottomSide));
		case LeftAndRight:
			return (isPegOnSide(Peg, LeftSide) || isPegOnSide(Peg, RightSide));
		case AnySide:
			return (isPegOnSide(Peg, LeftAndRight) || isPegOnSide(Peg, TopAndBottom));
		default:
			return false;
	}
}//end isPegOnSide

bool CBoardManager::compareCoordToSide(const MYPoint& Peg,
									   eSides const DestSide)
{
	switch (DestSide)
	{
	case TopSide:
		return (Peg.y == 0 && (Peg.x > 0 && Peg.x < XBoardSize-1)) ? true : false;
	case BottomSide:
		return (Peg.y == YBoardSize-1 && (Peg.x > 0 && Peg.x < XBoardSize-1)) ? true : false;
	case LeftSide:
		return (Peg.x == 0 && (Peg.y > 0 && Peg.y < YBoardSize-1)) ? true : false;
	case RightSide:
		return (Peg.x == XBoardSize-1 && (Peg.y > 0 && Peg.y < YBoardSize-1)) ? true : false;
	case TopAndBottom:
		return (compareCoordToSide(Peg, TopSide) || compareCoordToSide(Peg, BottomSide));
	case LeftAndRight:
		return (compareCoordToSide(Peg, LeftSide) || compareCoordToSide(Peg, RightSide));
	case AnySide:
		return (compareCoordToSide(Peg, LeftAndRight) || compareCoordToSide(Peg, TopAndBottom));
	default:
		return false;
	};
}//end compareCoordToSide

ValidSides CBoardManager::GetValidSides(ePlayer const player)
{
	ValidSides validSides;
	validSides.leftSide = isSideValid(player, LeftSide);
	validSides.rightSide = isSideValid(player, RightSide);
	validSides.topSide = isSideValid(player, TopSide);
	validSides.bottomSide = isSideValid(player, BottomSide);
	return validSides;
}//end GetValidSides

bool CBoardManager::isSideValid(ePlayer const player,
								eSides const DestSide)
{
	if (player == PlayerRed ||
		player == ComputerRed) {
		if (DestSide == TopSide ||
			DestSide == BottomSide ||
			DestSide == TopAndBottom) {
			return true;
		}
	}
	else if (player == PlayerBlack || 
		player == ComputerBlack) {
		if (DestSide == LeftSide ||
			DestSide == RightSide ||
			DestSide == LeftAndRight) {
			return true;
		}
	}
	if (player == AnyPlayer) {
		return true;
	}
	if (DestSide == AnySide) {
		return true;
	}
	return false;
}//end isSideValid

int CBoardManager::GetLinkGroup(const MYPoint& Peg)
{
	return ((*SharedBoard)[Peg.x][Peg.y].linkGroup);
}//end GetLinkGroup

void CBoardManager::SetLinkGroup(const MYPoint& Peg,
								 int const linkGroup)
{
	(*SharedBoard)[Peg.x][Peg.y].linkGroup = static_cast<char>(linkGroup);
}//end SetLinkGroup

bool CBoardManager::doesPegHaveLinks(const MYPoint& Peg)
{
	if ((*SharedBoard)[Peg.x][Peg.y].numLinks > 0) {
		return true;
	}
	return false;
}//end doesPegHaveLinks

bool CBoardManager::isLinkWithinBoard(const CLink& link)
{
	if (isPegWithinBoard(link.startPeg) == true
		&& isPegWithinBoard(link.GetDestFromDir()) == true) {
		//no need to check intermediates, at least one is already within board
		return true;
	}
	return false;
}//end isLinkWithinBoard

bool CBoardManager::isPegWithinBoard(const MYPoint& Source)
{
	//check that it is within the board
	if ((Source.x >= 0 && Source.x <= XBoardSize-1) &&
		(Source.y >= 0 && Source.y <= YBoardSize-1)) {
		//check that its not in one of the 4 corners
		if ((Source.x == 0 && (Source.y == 0 || Source.y == YBoardSize-1)) ||
			(Source.x == XBoardSize-1 && (Source.y == 0 || Source.y == YBoardSize-1))) {
			return false;
		}
		else {
			return true;
		}
	}
	return false;
}//end isPegWithinBoard
int CBoardManager::GetAStarF(const MYPoint& Peg)
{
	return ((*pMainBoard)[Peg.x][Peg.y].AStarData.AStarF);
}//end GetAStarF

int CBoardManager::GetAStarG(const MYPoint& Peg)
{
	return ((*pMainBoard)[Peg.x][Peg.y].AStarData.AStarG);
}//end GetAStarG

int CBoardManager::GetAStarH(const MYPoint& Peg)
{
	return ((*pMainBoard)[Peg.x][Peg.y].AStarData.AStarH);
}//end GetAStarH

void CBoardManager::SetAStarF(const MYPoint& Peg,
							  int const F)
{
	(*pMainBoard)[Peg.x][Peg.y].AStarData.AStarF = F;
	return;
}//end SetAStarF

void CBoardManager::SetAStarG(const MYPoint& Peg,
							  int const G)
{
	(*pMainBoard)[Peg.x][Peg.y].AStarData.AStarG = G;
	return;
}//end SetAStarG

void CBoardManager::SetAStarH(const MYPoint& Peg,
							  int const H)
{
	(*pMainBoard)[Peg.x][Peg.y].AStarData.AStarH = H;
	return;
}//end SetAStarH

CLink CBoardManager::GetAStarLink(const MYPoint& ChildPeg)
{
	return (*pMainBoard)[ChildPeg.x][ChildPeg.y].AStarData.ParentLink;
}//end GetAStarLink

void CBoardManager::SetAStarLink(const MYPoint& ChildPeg,
								const CLink& ParentLink)
{
	(*pMainBoard)[ChildPeg.x][ChildPeg.y].AStarData.ParentLink = ParentLink;
	return;
}//end SetAStarLink

eAStar CBoardManager::GetAStarStatus(const MYPoint& Peg)
{
	return (*pMainBoard)[Peg.x][Peg.y].AStarStatus;
}//end GetAStarStatus

void CBoardManager::SetAStarStatus(const MYPoint& Peg,
								   eAStar const status)
{
	(*pMainBoard)[Peg.x][Peg.y].AStarStatus = status;
	return;
}//end SetAStarStatus
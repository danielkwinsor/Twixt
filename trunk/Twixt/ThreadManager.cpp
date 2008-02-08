
#include "stdafx.h"

using namespace std;

//These need to be global
boost::mutex			inputMutex;
boost::mutex			outputMutex;
boost::mutex			Thread1Mutex;
boost::mutex			Thread2Mutex;

bool ThreadedWorkChunk::BuildPathFromParts(ThreadedWorkChunk &otherPart)
{
	if (pathNumber == otherPart.pathNumber && pathNumber < 0) {
		if (topHeap.key != -1 && otherPart.topHeap.key != -1) {
			if (pathList.empty() == false) {
				pathNumber = -pathNumber;
				//TODO bugged
				this->StartPeg = this->pathList.front().GetDestFromDir();
				this->DestPeg = otherPart.pathList.front().GetDestFromDir();
				this->topHeap = HEAP<MYPoint>(this->StartPeg, this->topHeap.key + otherPart.topHeap.key);
				this->destSide = otherPart.destSide;
				//this->jumpStartData // probably don't need to set this
				this->pathList.MergePathList(otherPart.pathList);
				return true;
			}
		}
	}
	return false;
}//end BuildPathFromParts

CThreadManager::~CThreadManager()
{
	Destroy();
}//end dtor

void CThreadManager::Destroy()
{
	if (pAStarTrainingThread) {
		delete pAStarTrainingThread;
	}
	if (pAITrainingThread) {
		delete pAITrainingThread;
	}
	boost::mutex::scoped_lock inputLock(inputMutex);
	InputQueue.clear();
	if (pThread1) {
		delete pThread1;
		pThread1 = NULL;
	}
	if (pThread2) {
		delete pThread2;
		pThread2 = NULL;
	}
	ClearData();
	return;
}//end Destroy

void CThreadManager::ClearData()
{
	heap.clear();

	boost::mutex::scoped_lock outputLock(outputMutex);
	pathOutputs.clear();
	return;
}//end ClearData

MYPoint CThreadManager::GetBestPeg(list<ThreadedWorkChunk>* pCompletedWorkChunks)
{
<<<<<<< .mine
	list<ThreadedWorkChunk> completedWorkChunks;
	if (pCompletedWorkChunks == NULL) {
		pCompletedWorkChunks = &completedWorkChunks;
=======
	for (list<ThreadOutput>::iterator iter = pathOutputs.begin(); iter != pathOutputs.end(); ++iter) {
		if (iter->pathNumber > 0) {
			HEAP<MYPoint> wholePath = iter->topHeap;
			if (wholePath.key != -1) {
				heap.insertElement(wholePath.data, wholePath.key);
			}
		}
		else if (iter->pathNumber == 0) {
			continue;
		}
		else {
			HEAP<MYPoint> leftPathPart = iter->topHeap;
			++iter;
			for (list<ThreadOutput>::iterator compare = iter; compare != pathOutputs.end(); ++compare) {
				HEAP<MYPoint> rightPathPart = compare->topHeap;
				if (leftPathPart.data == rightPathPart.data) {
					//set it so we don't search for it again
					compare->pathNumber = 0;
					if (leftPathPart.key != -1 && rightPathPart.key != -1) {
						heap.insertElement(leftPathPart.data, leftPathPart.key + rightPathPart.key);
					}
					break;
				}
			}
		}
>>>>>>> .r9
	}
	OrderAndGroupWorkChunks(pCompletedWorkChunks);

	for (list<ThreadedWorkChunk>::iterator iter = pCompletedWorkChunks->begin(); iter != pCompletedWorkChunks->end(); ++iter) {
		heap.insertElement(iter->topHeap.data, iter->topHeap.key);
	}

#ifdef DEBUG
	ofstream file("BestPathPegs.txt");
	file << heap.size();
	for (CBinaryHeap<MYPoint>::Iterator iter = heap.begin(); iter != heap.end(); ++iter) {
		file << '\n' << (int)(iter->data.x) << '\t' << (int)(iter->data.y) << '\t' << (iter->key);
	}
#endif

	if (heap.size() != 0) {
		return heap.popTopHeap().data;
	}
	else {
		return MYPoint(0,0);
	}
}//end GetBestPeg

void CThreadManager::OrderAndGroupWorkChunks(std::list<ThreadedWorkChunk> *pCompletedWorkChunks)
{
	int pathNumber = 0;
	while (pathOutputs.empty() == false) {
		++pathNumber;
		for (list<ThreadedWorkChunk>::iterator iter = pathOutputs.begin(); iter != pathOutputs.end(); ++iter) {
			if (iter->pathNumber == pathNumber) {
				if (iter->topHeap.key != -1) {
					pCompletedWorkChunks->push_back(*iter);
				}
				iter = pathOutputs.erase(iter);
				break;
			}
			else if (iter->pathNumber == -pathNumber) {
				ThreadedWorkChunk wholePath = *iter;
				iter = pathOutputs.erase(iter);
				for (list<ThreadedWorkChunk>::iterator compare = iter; compare != pathOutputs.end(); ++compare) {
					if (iter->pathNumber == compare->pathNumber) {
						if (wholePath.topHeap.key != -1 && compare->topHeap.key != -1) {
							if (wholePath.BuildPathFromParts(*compare) == true) {
								pCompletedWorkChunks->push_back(wholePath);
							}
						}
						iter = compare = pathOutputs.erase(compare);
						break;
					}
				}
				break;
			}
		}
	}
	return;
}//end OrderAndGroupWorkChunks

bool CThreadManager::WaitTillDone()
{
	for (;;) {
		boost::mutex::scoped_lock inputLock(inputMutex);
		if (InputQueue.empty() == true) {
			//must lock all thread locks before those threads lock an output
			boost::mutex::scoped_lock thread1Lock(Thread1Mutex);
			boost::mutex::scoped_lock thread2Lock(Thread2Mutex);

			boost::mutex::scoped_lock outputLock(outputMutex);
			threadsAreBusy = false;
			return true;
		}
		inputLock.unlock();
		Sleep(1);
	}
}//end WaitTillDone

ThreadedWorkChunk::ThreadedWorkChunk(int xSize, int ySize, MYPoint StartPeg, MYPoint DestPeg, eSides destSide, ePlayer player, bool jumpStart, JumpStartData jumpStartData, bool completeSearch, int pathNumber, bool buildPath, ePlayer currentPlayer)
{
	ThreadedWorkChunk::xSize = xSize;
	ThreadedWorkChunk::ySize = ySize;
	ThreadedWorkChunk::StartPeg = StartPeg;
	ThreadedWorkChunk::DestPeg = DestPeg;
	ThreadedWorkChunk::destSide = destSide;
	ThreadedWorkChunk::player = player;
	ThreadedWorkChunk::completeSearch = completeSearch;
	ThreadedWorkChunk::jumpStart = jumpStart;
	ThreadedWorkChunk::jumpStartData = jumpStartData;
	ThreadedWorkChunk::pathNumber = pathNumber;
	ThreadedWorkChunk::buildPath = buildPath;
	ThreadedWorkChunk::currentPlayer = currentPlayer;

	topHeap = HEAP<MYPoint, int>();
	return;
}//end ctor

CThreadManager::CThreadManager()
{
	pThread1 = NULL;
	pThread2 = NULL;
	pAStarTrainingThread = NULL;
	pAITrainingThread = NULL;
}//end ctor

bool CThreadManager::isBusy()
{
	return threadsAreBusy;
}//end isBusy

void CThreadManager::Init(SharedAStarData (*SharedBoard)[MAXBOARDSIZE][MAXBOARDSIZE],
						  int const numThreads,
						  int const XBoardSize,
						  int const YBoardSize)
{
	maxThreads = numThreads;
	threadsAreBusy = false;
	if (maxThreads >= 1) {
		if (pThread1) delete pThread1;
		pThread1 = new boost::thread(boost::bind(&ExecuteThread, SharedBoard,
			this, &Thread1Mutex, XBoardSize, YBoardSize));
	}
	if (maxThreads >= 2) {
		if (pThread2) delete pThread2;
		pThread2 = new boost::thread(boost::bind(&ExecuteThread, SharedBoard,
			this, &Thread2Mutex, XBoardSize, YBoardSize));
	}
	return;
}//end Init

void CThreadManager::StartTrainingAStarWeights(void (*pTrainingFunction)(CMainWindow*), CMainWindow* pMainWindow)
{
	currentlyTrainingAStarWeights = true;
	if (pAStarTrainingThread == NULL) {
		pAStarTrainingThread = new boost::thread(boost::bind(pTrainingFunction, pMainWindow));
	}
}

void CThreadManager::StartTrainingAIWeights(void (*pTrainingFunction)(CMainWindow*), CMainWindow* pMainWindow)
{
	currentlyTrainingAIWeights = true;
	if (pAITrainingThread == NULL) {
		pAITrainingThread = new boost::thread(boost::bind(pTrainingFunction, pMainWindow));
	}
}

void CThreadManager::StopTrainingAStarWeights()
{
	currentlyTrainingAStarWeights = false;
}

void CThreadManager::StopTrainingAIWeights()
{
	currentlyTrainingAIWeights = false;
}

void CThreadManager::PushAStarData(ThreadedWorkChunk const workChunk)
{
	boost::mutex::scoped_lock lock(inputMutex);
	InputQueue.push_back(workChunk);
	threadsAreBusy = true;
	return;
}//end PushAStarData

void ExecuteThread(SharedAStarData (*SharedBoard)[MAXBOARDSIZE][MAXBOARDSIZE],
				   CThreadManager* pThreadManager,
				   boost::mutex* pThreadLock,
				   int const XBoardSize,
				   int const YBoardSize)
{
	AStarPathfinder AStar(SharedBoard, XBoardSize, YBoardSize);
	vector<ThreadedWorkChunk>* pInputQueue = &(pThreadManager->InputQueue);
	for(;;) {
		bool wait = true;
		boost::mutex::scoped_lock inputLock(inputMutex);
		if (pInputQueue->empty() == false) {
			ThreadedWorkChunk workChunk = pInputQueue->back();
			pInputQueue->pop_back();
			boost::mutex::scoped_lock threadLock(*pThreadLock);
			inputLock.unlock();
			AStar.ResetAStarList();
			AStar.SetBoardSize(workChunk.xSize, workChunk.ySize);
			AStar.currentPlayer = workChunk.currentPlayer;

			if (workChunk.jumpStart) {
				AStar.JumpStartAStar(workChunk.jumpStartData);
			}
			workChunk.topHeap = AStar.AStar(workChunk.StartPeg, workChunk.DestPeg,
				workChunk.player, workChunk.destSide, workChunk.completeSearch);

			if (workChunk.buildPath == true) {
				if (workChunk.topHeap.key != -1) {//only build a path if a path was found!
					workChunk.pathList.BuildPathList(workChunk.topHeap.data,
						workChunk.jumpStartData.startSide, workChunk.StartPeg, AStar);
				}
			}
			//can't sort by dest peg, must sort by start peg
			workChunk.topHeap.data = workChunk.StartPeg;

			boost::mutex::scoped_lock outputLock(outputMutex);
			pThreadManager->pathOutputs.push_back(workChunk);
			wait = false;
		}
		else {
			inputLock.unlock();
		}

		if (wait == true) {
			Sleep(1);
		}
	}
}//end ExecuteThread

#include "stdafx.h"

using namespace std;

//These need to be global
boost::mutex			inputMutex;
boost::mutex			outputMutex;
boost::mutex			Thread1Mutex;
boost::mutex			Thread2Mutex;

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

MYPoint CThreadManager::GetBestPeg()
{
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
	}


#ifdef DEBUG
	ofstream file("BestPathPegs.txt");
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

ThreadInput::ThreadInput(int xSize, int ySize, MYPoint StartPeg, MYPoint DestPeg, eSides destSide, ePlayer player, bool jumpStart, JumpStartData jumpStartData, bool completeSearch, int outputNum, bool buildPath, ePlayer currentPlayer)
{
	ThreadInput::xSize = xSize;
	ThreadInput::ySize = ySize;
	ThreadInput::StartPeg = StartPeg;
	ThreadInput::DestPeg = DestPeg;
	ThreadInput::destSide = destSide;
	ThreadInput::player = player;
	ThreadInput::completeSearch = completeSearch;
	ThreadInput::jumpStart = jumpStart;
	ThreadInput::jumpStartData = jumpStartData;
	ThreadInput::outputNum = outputNum;
	ThreadInput::buildPath = buildPath;
	ThreadInput::currentPlayer = currentPlayer;
	return;
}//end ctor

ThreadOutput::ThreadOutput(HEAP<MYPoint> const topHeap,
						   bool const buildPath,
						   int const pathNumber)
{
	ThreadOutput::pathNumber = pathNumber;
	ThreadOutput::topHeap = topHeap;
	ThreadOutput::buildPath = buildPath;
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

void CThreadManager::PushAStarData(ThreadInput const input)
{
	boost::mutex::scoped_lock lock(inputMutex);
	InputQueue.push_back(input);
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
	vector<ThreadInput>* pInputQueue = &(pThreadManager->InputQueue);
	for(;;) {
		bool wait = true;
		boost::mutex::scoped_lock inputLock(inputMutex);
		if (pInputQueue->empty() == false) {
			ThreadInput input = pInputQueue->back();
			pInputQueue->pop_back();
			boost::mutex::scoped_lock threadLock(*pThreadLock);
			inputLock.unlock();
			AStar.ResetAStarList();
			AStar.SetBoardSize(input.xSize, input.ySize);
			AStar.currentPlayer = input.currentPlayer;

			if (input.jumpStart) {
				AStar.JumpStartAStar(input.jumpStartData);
			}
			HEAP<MYPoint> topHeap = AStar.AStar(input.StartPeg, input.DestPeg,
				input.player, input.destSide, input.completeSearch);

			ThreadOutput threadOutput(topHeap, input.buildPath, input.outputNum);
			if (input.buildPath == true) {
				if (topHeap.key != -1) {//only build a path if a path was found!
					threadOutput.pathList.BuildPathList(topHeap.data,
						input.jumpStartData.startSide, input.StartPeg, AStar);
				}
			}
			else {
				threadOutput.topHeap.data = input.StartPeg;
			}

			boost::mutex::scoped_lock outputLock(outputMutex);
			pThreadManager->pathOutputs.push_back(threadOutput);
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
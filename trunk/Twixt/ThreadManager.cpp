
#include "stdafx.h"

using namespace std;

//These need to be global
boost::mutex			inputMutex;
boost::mutex			output1Mutex;
boost::mutex			output2Mutex;
boost::mutex			Thread1Mutex;
boost::mutex			Thread2Mutex;

CThreadManager::~CThreadManager()
{
	Destroy();
}//end dtor

void CThreadManager::Destroy()
{
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

	boost::mutex::scoped_lock output1Lock(output1Mutex);
	Output1.clear();
	output1Lock.unlock();

	boost::mutex::scoped_lock output2Lock(output2Mutex);
	Output2.clear();
	return;
}//end ClearData

MYPoint CThreadManager::GetBestPeg()
{
	for (vector<ThreadOutput>::iterator iter = Output1.begin();
		iter != Output1.end(); ++iter) {
		HEAP<MYPoint> data1 = iter->topHeap;
		bool found = false;
		for (list<ThreadOutput>::iterator compare = Output2.begin();
			compare != Output2.end(); ++compare) {
			HEAP<MYPoint> data2 = compare->topHeap;
			if (data1.data == data2.data) {
				found = true;
				Output2.erase(compare);
				if (data1.key != -1 && data2.key != -1) {
					heap.insertElement(data1.data, data1.key + data2.key);
				}
				break;
			}
		}
		if (found == false) {
			if (data1.key != -1) {
				heap.insertElement(data1.data, data1.key);
			}
		}
	}
	for (list<ThreadOutput>::iterator compare = Output2.begin();
		compare != Output2.end(); ++compare) {
		if (compare->topHeap.key != -1) {
			heap.insertElement(compare->topHeap.data, compare->topHeap.key);
		}
	}

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

			boost::mutex::scoped_lock output1Lock(output1Mutex);
			boost::mutex::scoped_lock output2Lock(output2Mutex);
			threadsAreBusy = false;
			return true;
		}
		inputLock.unlock();
		Sleep(1);
	}
}//end WaitTillDone

ThreadInput::ThreadInput(MYPoint StartPeg, MYPoint DestPeg, eSides destSide, ePlayer player, bool jumpStart, JumpStartData jumpStartData, bool completeSearch, int outputNum, bool buildPath, ePlayer currentPlayer)
{
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
						   bool const buildPath)
{
	ThreadOutput::topHeap = topHeap;
	ThreadOutput::buildPath = buildPath;
	return;
}//end ctor

CThreadManager::CThreadManager()
{
	pThread1 = NULL;
	pThread2 = NULL;
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
		pThread1 = new boost::thread(boost::bind(&ExecuteThread, SharedBoard,
			this, &Thread1Mutex, XBoardSize, YBoardSize));
	}
	if (maxThreads >= 2) {
		pThread2 = new boost::thread(boost::bind(&ExecuteThread, SharedBoard,
			this, &Thread2Mutex, XBoardSize, YBoardSize));
	}
	return;
}//end Init

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
			AStar.currentPlayer = input.currentPlayer;

			if (input.jumpStart) {
				AStar.JumpStartAStar(input.jumpStartData);
			}
			HEAP<MYPoint> topHeap = AStar.AStar(input.StartPeg, input.DestPeg,
				input.player, input.destSide, input.completeSearch);

			ThreadOutput threadOutput(topHeap, input.buildPath);
			if (input.buildPath == true) {
				if (topHeap.key != -1) {//only build a path if a path was found!
					threadOutput.pathList.BuildPathList(topHeap.data,
						input.jumpStartData.startSide, input.StartPeg, AStar);
				}
			}
			else {
				threadOutput.topHeap.data = input.StartPeg;
			}

			if (input.outputNum == 1) {
				boost::mutex::scoped_lock output1Lock(output1Mutex);
				pThreadManager->Output1.push_back(threadOutput);
			}
			else {
				boost::mutex::scoped_lock output2Lock(output2Mutex);
				pThreadManager->Output2.push_back(threadOutput);
			}
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
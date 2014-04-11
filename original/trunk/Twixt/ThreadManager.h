
#ifndef THREADMANAGER_H
#define THREADMANAGER_H

class CMainWindow;

class ThreadedWorkChunk
{
public:
	ThreadedWorkChunk(){return;};
	ThreadedWorkChunk(int xSize, int ySize, MYPoint StartPeg, MYPoint DestPeg, eSides destSide, ePlayer player, bool jumpStart, JumpStartData jumpStartData, bool completeSearch, int pathNumber, bool buildPath, ePlayer currentPlayer);

	bool		BuildPathFromParts(ThreadedWorkChunk& otherPart);

	//input:
	int			xSize;
	int			ySize;
	MYPoint		StartPeg;
	MYPoint		DestPeg;
	eSides		destSide;
	ePlayer		player;
	bool		jumpStart;
	JumpStartData jumpStartData;
	bool		completeSearch;
	int			pathNumber;
	bool		buildPath;
	ePlayer		currentPlayer;

	//output:
	HEAP<MYPoint>	topHeap;
	CPath			pathList;
};

class CThreadManager
{
public:
	CThreadManager			();
	~CThreadManager			();

	void	StartTrainingAStarWeights(void (*pTrainingFunction)(CMainWindow*), CMainWindow* pMainWindow);
	void	StopTrainingAStarWeights();

	void	StartTrainingAIWeights(void (*pTrainingFunction)(CMainWindow*), CMainWindow* pMainWindow);
	void	StopTrainingAIWeights();

	void	Init			(SharedAStarData (*SharedBoard)[MAXBOARDSIZE][MAXBOARDSIZE],
							int const numThreads,
							int const XBoardSize,
							int const YBoardSize);

	void	Destroy			();

	void	ClearData		();

	void	PushAStarData	(ThreadedWorkChunk const workChunk);

	bool	WaitTillDone	();

	MYPoint	GetBestPeg		(std::list<ThreadedWorkChunk>* pCompletedWorkChunks = NULL);

	void	OrderAndGroupWorkChunks(std::list<ThreadedWorkChunk>* pCompletedWorkChunks = NULL);

	bool	isBusy			();


	//shared data
	vector<ThreadedWorkChunk>	InputQueue;
	list<ThreadedWorkChunk>		pathOutputs;
	bool						threadsAreBusy;

private:
	int						maxThreads;
	boost::thread*			pThread1;
	boost::thread*			pThread2;
	boost::thread*			pAStarTrainingThread;
	boost::thread*			pAITrainingThread;
	CBinaryHeap<MYPoint>	heap;
};

void ExecuteThread(SharedAStarData (*SharedBoard)[MAXBOARDSIZE][MAXBOARDSIZE],
				   CThreadManager* pThreadManager,
				   boost::mutex* pThreadLock,
				   int const XBoardSize,
				   int const YBoardSize);

#endif

#ifndef THREADMANAGER_H
#define THREADMANAGER_H

class CMainWindow;

class ThreadInput
{
public:
	ThreadInput(){return;};
	ThreadInput(int xSize, int ySize, MYPoint StartPeg, MYPoint DestPeg, eSides destSide, ePlayer player, bool jumpStart, JumpStartData jumpStartData, bool completeSearch, int outputNum, bool buildPath, ePlayer currentPlayer);
	int			xSize;
	int			ySize;
	MYPoint		StartPeg;
	MYPoint		DestPeg;
	eSides		destSide;
	ePlayer		player;
	bool		jumpStart;
	JumpStartData jumpStartData;
	bool		completeSearch;
	int			outputNum;
	bool		buildPath;
	ePlayer		currentPlayer;
};

class ThreadOutput
{
public:
	ThreadOutput	();
	ThreadOutput	(HEAP<MYPoint> const topHeap,
					bool const buildPath);

	bool			buildPath;
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

	void	PushAStarData	(ThreadInput const input);

	bool	WaitTillDone	();

	MYPoint	GetBestPeg		();

	bool	isBusy			();


	//shared data
	vector<ThreadInput>		InputQueue;
	vector<ThreadOutput>	Output1;
	list<ThreadOutput>		Output2;
	bool					threadsAreBusy;

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
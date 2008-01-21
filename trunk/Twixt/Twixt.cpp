
#include "stdafx.h"

CTwixtGame TwixtGame;
bool currentlyTrainingAStarWeights;
bool currentlyTrainingAIWeights;

BOOL CTwixtGame::InitInstance ()
{
    m_pMainWnd = new CMainWindow;
    m_pMainWnd->ShowWindow (m_nCmdShow);
    m_pMainWnd->UpdateWindow ();
    return TRUE;
}//end InitInstance

BEGIN_MESSAGE_MAP (CMainWindow, CFrameWnd)
    ON_WM_PAINT ()
	ON_WM_KEYDOWN ()
	ON_WM_LBUTTONDOWN ()
	ON_WM_RBUTTONDOWN ()
	ON_COMMAND (ID_GAME_NEW, OnGameNew)
	ON_COMMAND (ID_GAME_LOAD, OnGameLoad)
	ON_COMMAND (ID_GAME_SAVE, OnGameSave)
	ON_COMMAND (ID_GAME_SAVEAS, OnGameSaveAs)
	ON_COMMAND (ID_SCEN_LOAD, OnScenLoad)
	ON_COMMAND (ID_EXIT_APP, OnExitApp)
	ON_COMMAND (ID_WINDOW_DEFAULT, OnWindowDefault)
	ON_COMMAND (ID_WINDOW_BOARD, OnWindowBoard)
	ON_COMMAND (ID_WINDOW_SCREEN, OnWindowScreen)
	ON_COMMAND_RANGE (ID_SHOWF, ID_SHOW_NEWEST, OnShow)
END_MESSAGE_MAP ()

BEGIN_MESSAGE_MAP(CDialogNewGame, CDialog)
	ON_BN_CLICKED(IDOK, OnOK)
	ON_BN_CLICKED(IDD_DEFAULT, OnDefault)
END_MESSAGE_MAP()

CMainWindow::CMainWindow()
{
	Create (NULL, _T("Twixt Beta v0.5"), WS_OVERLAPPEDWINDOW);
	CreatePens();
	InitDebugSettings();
	InitGameData();

	XBoardSize = gameData.XBoardSize;
	YBoardSize = gameData.YBoardSize;
	//numThreads = gameData.numThreads;
	numThreads = 2;

	CDir test = leftUp;
	test++;
	test++;
	++test;
	++test;

	CMenu menu;
	menu.LoadMenu (IDR_MENU1);
	SetMenu (&menu);
	menu.Detach ();

	currentlyTrainingAStarWeights = false;
	currentlyTrainingAIWeights = false;
	pThreadManager = new CThreadManager;
	pMainAI = new AILogic(&MainBoard, pThreadManager, XBoardSize, YBoardSize, Dif_Medium);

	StartNewGame(XBoardSize, YBoardSize, numThreads);


	int profileType = 2;
	if (profileType == 0) {
		DoTurn();
	}
	else if (profileType == 1) {
	}
	else if (profileType == 2) {
		ofstream file("loadedhistory.txt");
		file.flush();
	}
	else if (profileType == 3) {
		int iterations = 2;
		pMainAI->insertPeg(MYPoint(3,12), ComputerRed);
		pMainAI->insertPeg(MYPoint(3,18), ComputerRed);
		pMainAI->insertPeg(MYPoint(3,20), ComputerRed);
		pMainAI->insertPeg(MYPoint(5,5), ComputerRed);
		pMainAI->insertPeg(MYPoint(5,7), ComputerRed);
		pMainAI->insertPeg(MYPoint(7,15), ComputerRed);
		pMainAI->insertPeg(MYPoint(9,13), ComputerRed);
		pMainAI->insertPeg(MYPoint(10,1), ComputerRed);
		pMainAI->insertPeg(MYPoint(10,9), ComputerRed);
		pMainAI->insertPeg(MYPoint(11,16), ComputerRed);
		pMainAI->insertPeg(MYPoint(12,8), ComputerRed);
		pMainAI->insertPeg(MYPoint(12,10), ComputerRed);
		pMainAI->insertPeg(MYPoint(13,8), ComputerRed);
		pMainAI->insertPeg(MYPoint(14,1), ComputerRed);
		pMainAI->insertPeg(MYPoint(14,10), ComputerRed);
		pMainAI->insertPeg(MYPoint(14,15), ComputerRed);
		pMainAI->insertPeg(MYPoint(15,11), ComputerRed);
		pMainAI->insertPeg(MYPoint(15,15), ComputerRed);
		pMainAI->insertPeg(MYPoint(15,21), ComputerRed);
		pMainAI->insertPeg(MYPoint(16,9), ComputerRed);
		pMainAI->insertPeg(MYPoint(16,11), ComputerRed);
		pMainAI->insertPeg(MYPoint(17,3), ComputerRed);
		pMainAI->insertPeg(MYPoint(17,10), ComputerRed);
		pMainAI->insertPeg(MYPoint(19,1), ComputerRed);
		pMainAI->insertPeg(MYPoint(20,5), ComputerRed);
		pMainAI->insertPeg(MYPoint(20,20), ComputerRed);
		pMainAI->insertPeg(MYPoint(21,15), ComputerRed);
		pMainAI->insertPeg(MYPoint(22,12), ComputerRed);


		pMainAI->insertPeg(MYPoint(2,11), PlayerBlack);
		pMainAI->insertPeg(MYPoint(3,2), PlayerBlack);
		pMainAI->insertPeg(MYPoint(4,8), PlayerBlack);
		pMainAI->insertPeg(MYPoint(5,6), PlayerBlack);
		pMainAI->insertPeg(MYPoint(6,17), PlayerBlack);
		pMainAI->insertPeg(MYPoint(7,5), PlayerBlack);
		pMainAI->insertPeg(MYPoint(8,20), PlayerBlack);
		pMainAI->insertPeg(MYPoint(9,1), PlayerBlack);
		pMainAI->insertPeg(MYPoint(10,13), PlayerBlack);
		pMainAI->insertPeg(MYPoint(11,11), PlayerBlack);
		pMainAI->insertPeg(MYPoint(12,15), PlayerBlack);
		pMainAI->insertPeg(MYPoint(12,12), PlayerBlack);
		pMainAI->insertPeg(MYPoint(13,3), PlayerBlack);
		pMainAI->insertPeg(MYPoint(14,5), PlayerBlack);
		pMainAI->insertPeg(MYPoint(14,6), PlayerBlack);
		pMainAI->insertPeg(MYPoint(14,11), PlayerBlack);
		pMainAI->insertPeg(MYPoint(14,19), PlayerBlack);
		pMainAI->insertPeg(MYPoint(15,5), PlayerBlack);
		pMainAI->insertPeg(MYPoint(15,22), PlayerBlack);
		pMainAI->insertPeg(MYPoint(16,1), PlayerBlack);
		pMainAI->insertPeg(MYPoint(16,3), PlayerBlack);
		pMainAI->insertPeg(MYPoint(16,5), PlayerBlack);
		pMainAI->insertPeg(MYPoint(18,11), PlayerBlack);
		pMainAI->insertPeg(MYPoint(19,10), PlayerBlack);
		pMainAI->insertPeg(MYPoint(20,10), PlayerBlack);
		pMainAI->insertPeg(MYPoint(21,9), PlayerBlack);
		pMainAI->insertPeg(MYPoint(21,13), PlayerBlack);
		pMainAI->insertPeg(MYPoint(22,7), PlayerBlack);
		
		unsigned int highStart;
		unsigned int lowStart;
		unsigned int highEnd;
		unsigned int lowEnd;
		
	__asm {
		rdtsc	;
		mov		[highStart], edx;
		mov		[lowStart], eax;
		}
		ePlayer player = ComputerRed;
		eSides startSide;
		eSides destSide;
		MYPoint DestPeg;
		MYPoint StartPeg;
		vector<MYPoint>* pPegList;
		for (int x = 0; x < iterations; ++x) {
			if (x % 2 == 0) {
				player = ComputerRed;
			}
			else {
				player = PlayerBlack;
			}
			pMainAI->GetStartData(player, StartPeg, DestPeg, startSide, destSide, &pPegList);
			pMainAI->currentPlayer = player;
			MYPoint nullPeg;
			vector<int> LinkGroupList;
			bool startSearched = false;
			bool destSearched = false;
			for (vector<MYPoint>::iterator iter = pPegList->begin(); iter != pPegList->end(); ++iter) {
				MYPoint Peg = *iter;
				int linkGroup = pMainAI->GetLinkGroup(Peg);
				bool add = true;
				if (linkGroup != 0) {
					//see if the peg is linked to a peg already searched
					for (vector<int>::iterator iter = LinkGroupList.begin();
						iter != LinkGroupList.end(); ++iter) {
						if (linkGroup == *iter) {
							add = false;
							break;
						}
					}
					if (add == true) {
						//make sure the linked pegs are not searched
						LinkGroupList.push_back(linkGroup);
					}
				}
				if (add == true) {
					//find the paths from this peg to the 2 sides
					if (Peg == StartPeg) {
						startSearched = true;
					}
					else if (Peg == DestPeg) {
						destSearched = true;
					}

					pMainAI->ResetAStarList();
					pMainAI->AStar(Peg, DestPeg, player, destSide, true);
					pMainAI->ResetAStarList();
					pMainAI->AStar(Peg, StartPeg, player, startSide, true);
				}
			}
		}

	__asm {
		rdtsc	;
		mov		[highEnd], edx;
		mov		[lowEnd], eax;
		}
		unsigned int time = highEnd - highStart;
		unsigned int time2 = lowEnd - lowStart;
		if (lowStart > lowEnd) {
			time -= 1;
		}

		if (iterations) {
			HEAP<MYPoint> topHeap;
			CPath path;
			vector<MYPoint> pegs;
			pMainAI->ResetAStarList();
			topHeap = pMainAI->AStar(StartPeg, DestPeg, player, destSide, true);
			pegs.push_back(topHeap.data);

			int key = topHeap.key;
			if (key != -1) {
				while (key == topHeap.key && pMainAI->OpenHeap.size()) {
					HEAP<MYPoint> element = pMainAI->OpenHeap.popTopHeap();
					key = element.key;
					pegs.push_back(element.data);
				}
				path.BuildPathList(topHeap.data, startSide, StartPeg, *pMainAI);
			}

			ofstream file("debug.txt");
			for (CPath::iterator iter = path.begin(); iter != path.end(); ++iter) {
				MYPoint Dest = iter->GetDestFromDir();
				file << '\n' << iter->startPeg.x << ' ' << iter->startPeg.y
					<< " - " << Dest.x << ' ' << Dest.y;
			}
			file << "\n\n\n\n";
			for (vector<MYPoint>::iterator iter = pegs.begin(); iter != pegs.end(); ++iter) {
				file << '\n' << iter->x << ' ' << iter->y;
			}
			file << "\n\n\n\n" << pMainAI->OpenHeap.size() << ' ' << pMainAI->ClosedList.size();
		}

		ofstream benchmark("benchmark.txt");
		benchmark<<time<<'\n'<<time2;

		std::ofstream myfile;
		myfile.open("profiler.txt");
		PerfManager::instance()->log(myfile);
		myfile.close();
	}
	else if (profileType == 4) {
		int iterations = 500000;
		unsigned int highStart;
		unsigned int lowStart;
		unsigned int highEnd;
		unsigned int lowEnd;

		vector<int> random;
		vector<int> edit;
		for (int x = 0; x < 100; ++x) {
			random.push_back(rand());
			edit.push_back(rand());
		}
		CBinaryHeap<int> randomHeap(100);
		
	__asm {
		rdtsc	;
		mov		[highStart], edx;
		mov		[lowStart], eax;
		}

		register int x;
		for (; iterations > 0; --iterations) {
			for (x = 0; x < 100; ++x) {
				randomHeap.insertElement(random[x], random[x]);
			}
			for (x = 0; x < 100; ++x) {
				//randomHeap.editElement(random[x], edit[x]);
			}
			for (x = 0; x < 100; ++x) {
				randomHeap.popTopHeap();
			}
		}


	__asm {
		rdtsc	;
		mov		[highEnd], edx;
		mov		[lowEnd], eax;
		}
		unsigned int time = highEnd - highStart;
		unsigned int time2 = lowEnd - lowStart;
		if (lowStart > lowEnd) {
			time -= 1;
		}
		ofstream benchmark("benchmark.txt");
		benchmark<<time<<'\n'<<time2<<"\n\n";

		std::ofstream myfile;
		myfile.open("profiler.txt");
		PerfManager::instance()->log(myfile);
		myfile.close();
	}
	return;
}//end ctor

void CMainWindow::LoadSavedHistory(int number,
								   ePlayer& player,
								   ePlayer& opponent,
								   std::vector<CPeg>& pegsToInsert,
								   std::vector<CSolution>& solutions)
{
	std::string filename;
	if (number == -1) {
		filename = "history.txt";
	}
	else if (number == 0) {
		filename = "Copy of history.txt";
	}
	else {
		filename = "Copy (";
		char buffer[32] = {0};
		_itoa_s(number, buffer, 10);
		filename += buffer;
		filename += ") of history.txt";
	}

	player = PlayerRed;
	opponent = ComputerBlack;

	ePlayer loadedPlayer;
	bool firstPlayerLoaded = false;
	bool secondPlayerLoaded = false;
	ifstream file(filename.c_str());
	int playerInt;
	MYPoint Peg;
	while (file.good()) {
		int x;
		int y;
		file >> x >> y >> playerInt;
		Peg.x = (char)x;
		Peg.y = (char)y;
		loadedPlayer = static_cast<ePlayer>(playerInt);
		if (Peg.x < 0 || Peg.y < 0) {
			pegsToInsert.pop_back();
		}
		else {
			if (firstPlayerLoaded == false) {
				firstPlayerLoaded = true;
				player = loadedPlayer;
			}
			else if (secondPlayerLoaded == false) {
				secondPlayerLoaded = true;
				opponent = loadedPlayer;
			}
			pegsToInsert.push_back(CPeg(Peg, loadedPlayer));
		}
		char temp[128];
		file.getline(temp, 128);
		if (std::string(temp) == std::string(" end") || std::string(temp) == std::string(" END")) {
			while (file.good()) {
				int x;
				int y;
				float solutionWeight;
				file >> x >> y >> solutionWeight;
				solutions.push_back(CSolution(MYPoint(x, y), solutionWeight));
			}
		}
	}
	return;
}//end LoadSavedHistory

void CMainWindow::StartNewGame(int const XBoardSize,
							   int const YBoardSize,
							   int const numThreads)
{
	pThreadManager->Init(&MainBoard, numThreads, XBoardSize, YBoardSize);
	pMainAI->Init(XBoardSize, YBoardSize, gameData.difficulty, &MainBoard);
	pMainAI->LoadAIWeights();
	pMainAI->LoadAStarWeights();

	ofstream file("history.txt");
	file.flush();

	lastPeg = MYPoint(0,0);
	ChangeWindowSize();
	RePaint();
	return;
}//end StartNewGame

CMainWindow::~CMainWindow ()
{
	delete pMainAI;
	delete pThreadManager;
	pMainAI = NULL;
	pThreadManager = NULL;
	return;
}//end dtor

MYPoint CMainWindow::GetPegFromText(int const xCoord,
								   char const yChar)
{
	int x = xCoord-1;
	switch (yChar) {
	case 'A':
		return MYPoint(x,0);
	case 'B':
		return MYPoint(x,1);
	case 'C':
		return MYPoint(x,2);
	case 'D':
		return MYPoint(x,3);
	case 'E':
		return MYPoint(x,4);
	case 'F':
		return MYPoint(x,5);
	case 'G':
		return MYPoint(x,6);
	case 'H':
		return MYPoint(x,7);
	case 'I':
		return MYPoint(x,8);
	case 'J':
		return MYPoint(x,9);
	case 'K':
		return MYPoint(x,10);
	case 'L':
		return MYPoint(x,11);
	default:
		return MYPoint(0,0);
	}
}//end

MYPoint CMainWindow::GetPegFromText(char const xChar,
								   int const yCoord)
{
	int y = yCoord-1;
	switch (xChar) {
	case 'A':
		return MYPoint(0,y);
	case 'B':
		return MYPoint(1,y);
	case 'C':
		return MYPoint(2,y);
	case 'D':
		return MYPoint(3,y);
	case 'E':
		return MYPoint(4,y);
	case 'F':
		return MYPoint(5,y);
	case 'G':
		return MYPoint(6,y);
	case 'H':
		return MYPoint(7,y);
	case 'I':
		return MYPoint(8,y);
	case 'J':
		return MYPoint(9,y);
	case 'K':
		return MYPoint(10,y);
	case 'L':
		return MYPoint(11,y);
	default:
		return MYPoint(0,y);
	}
}//end

void CMainWindow::LoadTestCase(int testCase,
							   ePlayer& player,
							   ePlayer& opponent,
							   std::vector<CPeg>& pegsToInsert,
							   std::vector<CSolution>& solutions)
{
	char numbers = 0;
	bool numbersFirst = true;
	bool firstPlayerAssigned = false;
	int xCoord = 0;
	char yChar = 0;
	char xChar = 0;
	int yCoord = 0;

	char inputPlayer = NOTAPLAYER;
	ePlayer startingPlayer = NOTAPLAYER;
	player = NOTAPLAYER;
	opponent = NOTAPLAYER;
	string name("test case ");
	char buffer[32] = {0};
	_itoa_s(testCase, buffer, 10);
	name += buffer;
	name += ".txt";
	ifstream file(name.c_str());
	file>>numbers;
	if (numbers == 'T' || numbers == 't') {
		numbersFirst = true;
	}
	else {
		numbersFirst = false;
	}
	MYPoint Solution;
	MYPoint Dest;
	MYPoint Peg;
	while (file.good()) {
		if (numbersFirst == true) {
			file>>xCoord;
			file>>yChar;
			Peg = GetPegFromText(xCoord,yChar);
		}
		else {
			file>>xChar;
			file>>yCoord;
			Peg = GetPegFromText(xChar,yCoord);
		}
		file>>inputPlayer;
		switch (inputPlayer) {
		case 'W':
			player = ComputerRed;
			break;
		case 'B':
			player = ComputerBlack;
			break;
		}
		if (firstPlayerAssigned == false) {
			firstPlayerAssigned = true;
			startingPlayer = player;
		}
		pegsToInsert.push_back(CPeg(Peg, player));
		char end[128];
		file.getline(end, 128);
		if (std::string(end) == std::string(" END") || std::string(end) == std::string(" end")) {
			while(file.good()) {
				float solutionWeight;
				if (numbersFirst == true) {
					file>>xCoord;
					file>>yChar;
					file>>solutionWeight;
					Solution = GetPegFromText(xCoord,yChar);
				}
				else {
					file>>xChar;
					file>>yCoord;
					file>>solutionWeight;
					Solution = GetPegFromText(xChar,yCoord);
				}
				solutions.push_back(CSolution(Solution, solutionWeight));
				char temp;
				file.getline(&temp, 1);
			}
		}
	}

	if (startingPlayer == ComputerRed) {
		player = ComputerRed;
		opponent = ComputerBlack;
	}
	else {
		player = ComputerBlack;
		opponent = ComputerRed;
	}

	return;
}//end LoadTestCase

void CMainWindow::ViewTestCase(int testCase)
{
	historyPegs.clear();
	historyIndex = 0;
	std::vector<CSolution> solutions;
	ePlayer player;
	ePlayer opponent;
	char numbers = 0;
	bool numbersFirst = true;
	bool firstPlayerAssigned = false;
	int xCoord = 0;
	char yChar = 0;
	char xChar = 0;
	int yCoord = 0;

	char inputPlayer = NOTAPLAYER;
	ePlayer startingPlayer = NOTAPLAYER;
	player = NOTAPLAYER;
	opponent = NOTAPLAYER;
	string name("test case ");
	char buffer[32] = {0};
	_itoa_s(testCase, buffer, 10);
	name += buffer;
	name += ".txt";
	ifstream file(name.c_str());
	file>>numbers;
	if (numbers == 'T' || numbers == 't') {
		numbersFirst = true;
	}
	else {
		numbersFirst = false;
	}
	MYPoint Solution;
	MYPoint Dest(0,0);
	MYPoint Peg;
	while (file.good()) {
		if (numbersFirst == true) {
			file>>xCoord;
			file>>yChar;
			Peg = GetPegFromText(xCoord,yChar);
		}
		else {
			file>>xChar;
			file>>yCoord;
			Peg = GetPegFromText(xChar,yCoord);
		}
		file>>inputPlayer;
		switch (inputPlayer) {
		case 'W':
			player = ComputerRed;
			break;
		case 'B':
			player = ComputerBlack;
			break;
		}
		if (firstPlayerAssigned == false) {
			firstPlayerAssigned = true;
			startingPlayer = player;
		}
		historyPegs.push_back(CPeg(Peg, player));
		char end[128];
		file.getline(end, 128);
		if (std::string(end) == std::string(" END") || std::string(end) == std::string(" end")) {
			while(file.good()) {
				float solutionWeight;
				if (numbersFirst == true) {
					file>>xCoord;
					file>>yChar;
					file>>solutionWeight;
					Solution = GetPegFromText(xCoord,yChar);
				}
				else {
					file>>xChar;
					file>>yCoord;
					file>>solutionWeight;
					Solution = GetPegFromText(xChar,yCoord);
				}
				solutions.push_back(CSolution(Solution, solutionWeight));
				char temp;
				file.getline(&temp, 1);
			}
		}
	}

	if (startingPlayer == ComputerRed) {
		player = ComputerRed;
		opponent = ComputerBlack;
	}
	else {
		player = ComputerBlack;
		opponent = ComputerRed;
	}

	if (historyPegs.empty() == true || solutions.empty() == true) {
		pMainAI->Init(12, 12, Dif_Hard, &MainBoard);
		RePaint();
		return;
	}

	ExecuteAITestCase(12, player, opponent, historyPegs, solutions, Dest);
	RePaint();

	bool destInserted = false;
	std::vector<CPeg> pegsToDrawSpecial;
	for each (CSolution solution in solutions) {
		if (solution.solution == Dest) {
			pegsToDrawSpecial.push_back(CPeg(solution.solution, Green));
			destInserted = true;
		}
		else {
			pegsToDrawSpecial.push_back(CPeg(solution.solution, Blue));
		}
	}
	if (destInserted == false && Dest != MYPoint(0,0)) {
		pegsToDrawSpecial.push_back(CPeg(Dest, Yellow));
	}
	DrawDebug(&pegsToDrawSpecial);

	historyIndex = historyPegs.size();

	return;
}//end ViewTestCase

void CMainWindow::ViewSavedHistory(int number)
{
	historyPegs.clear();
	historyIndex = 0;
	std::vector<CSolution> solutions;
	ePlayer player;
	ePlayer opponent;
	ePlayer loadedPlayer = NOTAPLAYER;
	player = NOTAPLAYER;
	opponent = NOTAPLAYER;

	bool firstPlayerLoaded = false;
	bool secondPlayerLoaded = false;
	int playerInt;
	MYPoint Solution;
	MYPoint Dest(0,0);
	MYPoint Peg;

	std::string filename;
	if (number == -1) {
		filename = "history.txt";
	}
	else if (number == 0) {
		filename = "Copy of history.txt";
	}
	else {
		filename = "Copy (";
		char buffer[32] = {0};
		_itoa_s(number, buffer, 10);
		filename += buffer;
		filename += ") of history.txt";
	}
	ifstream file(filename.c_str());
	while (file.good()) {
		int x;
		int y;
		file >> x >> y >> playerInt;
		Peg.x = (char)x;
		Peg.y = (char)y;
		loadedPlayer = static_cast<ePlayer>(playerInt);
		if (Peg.x < 0 || Peg.y < 0) {
			historyPegs.pop_back();
		}
		else {
			if (firstPlayerLoaded == false) {
				firstPlayerLoaded = true;
				player = loadedPlayer;
			}
			else if (secondPlayerLoaded == false) {
				secondPlayerLoaded = true;
				opponent = loadedPlayer;
			}
			historyPegs.push_back(CPeg(Peg, loadedPlayer));
		}
		char temp[128];
		file.getline(temp, 128);
		if (std::string(temp) == std::string(" end") || std::string(temp) == std::string(" END")) {
			while (file.good()) {
				int x;
				int y;
				float solutionWeight;
				file >> x >> y >> solutionWeight;
				solutions.push_back(CSolution(MYPoint(x, y), solutionWeight));
				char temp;
				file.getline(&temp, 1);
			}
		}
	}

	if (historyPegs.empty() == true || solutions.empty() == true) {
		pMainAI->Init(24, 24, Dif_Hard, &MainBoard);
		RePaint();
		return;
	}

	ExecuteAITestCase(24, player, opponent, historyPegs, solutions, Dest);
	RePaint();

	bool destInserted = false;
	std::vector<CPeg> pegsToDrawSpecial;
	for each (CSolution solution in solutions) {
		if (solution.solution == Dest) {
			pegsToDrawSpecial.push_back(CPeg(solution.solution, Green));
			destInserted = true;
		}
		else {
			pegsToDrawSpecial.push_back(CPeg(solution.solution, Blue));
		}
	}
	if (destInserted == false && Dest != MYPoint(0,0)) {
		pegsToDrawSpecial.push_back(CPeg(Dest, Yellow));
	}
	DrawDebug(&pegsToDrawSpecial);

	historyIndex = historyPegs.size();

	return;
}//end ViewSavedHistory

void CMainWindow::ExecuteAITestCase(int sizeOfBoard,
									ePlayer player,
									ePlayer opponent,
									std::vector<CPeg>& pegsToInsert,
									std::vector<CSolution>& solutions,
									MYPoint& Dest)
{
	if (pegsToInsert.empty() == false && solutions.empty() == false) {
		pMainAI->Init(sizeOfBoard, sizeOfBoard, Dif_Hard, &MainBoard);
		XBoardSize = sizeOfBoard;
		YBoardSize = sizeOfBoard;
		pMainAI->SetBoardSize(XBoardSize, YBoardSize);
		gameData.firstPlayer = player;
		gameData.secondPlayer = opponent;

		for each (CPeg peg in pegsToInsert) {
			pMainAI->insertPeg(peg.peg, peg.player);
		}

		pMainAI->DoTurnAndEval(&Dest, player, opponent, solutions);
	}
}

void CMainWindow::ExecuteAStarTestCase(int sizeOfBoard,
										ePlayer player,
										ePlayer opponent,
										std::vector<CPeg>& pegsToInsert,
										std::vector<CSolution>& solutions)
{
	if (pegsToInsert.empty() == false && solutions.empty() == false) {
		pMainAI->Init(sizeOfBoard, sizeOfBoard, Dif_Hard, &MainBoard);
		XBoardSize = sizeOfBoard;
		YBoardSize = sizeOfBoard;
		pMainAI->SetBoardSize(XBoardSize, YBoardSize);
		gameData.firstPlayer = player;
		gameData.secondPlayer = opponent;

		for each (CPeg peg in pegsToInsert) {
			pMainAI->insertPeg(peg.peg, peg.player);
		}

		pMainAI->FindPathAndEval(player, solutions);
	}
}


#define NUM_TEST_CASES 60
#define NUM_HISTORIES 25

void TrainAIWeights(CMainWindow* pMainWindow)
{
	while (currentlyTrainingAIWeights == false) {
		Sleep(100);
	}
	int iterations = 0;
	ePlayer player;
	ePlayer opponent;
	std::vector<CPeg> pegsToInsert;
	std::vector<CSolution> solutions;
	MYPoint Dest;
	
	unsigned int random;
	__asm {
		rdtsc	;
		mov		[random], edx;
		mov		[random], eax;
		}
	srand(random);
	for (;;) {
		while (currentlyTrainingAIWeights == false) {
			Sleep(100);
		}
		++iterations;
		pMainWindow->pMainAI->currentWeightsScore = 0.0f;

		//do all of the test cases
		for (int cases = 1; cases <= NUM_TEST_CASES; ++cases) {
			pegsToInsert.clear();
			solutions.clear();
			pMainWindow->LoadTestCase(cases, player, opponent, pegsToInsert, solutions);
			pMainWindow->ExecuteAITestCase(12, player, opponent, pegsToInsert, solutions, Dest);
		}

		//do all of the stored histories
		for (int histories = 1; histories <= NUM_HISTORIES; ++histories) {
			pegsToInsert.clear();
			solutions.clear();
			pMainWindow->LoadSavedHistory(histories, player, opponent, pegsToInsert, solutions);
			pMainWindow->ExecuteAITestCase(24, player, opponent, pegsToInsert, solutions, Dest);
		}

		pMainWindow->pMainAI->currentAIWeightsScore = pMainWindow->pMainAI->currentWeightsScore;
		pMainWindow->pMainAI->SaveAIWeights();
		pMainWindow->pMainAI->PerturbAIWeights();//comes AFTER we have tested what we loaded
		ofstream iters("AITrainingIterations.txt");
		iters << iterations;
		iters.close();
	}
	return;
}//end TrainAIWeights

void TrainAStarWeights(CMainWindow* pMainWindow)
{
	while (currentlyTrainingAStarWeights == false) {
		Sleep(100);
	}
	pMainWindow->RetestAStarWeights();

	int todaysIterations = 0;
	int allIterations = 0;
	ePlayer player;
	ePlayer opponent;
	std::vector<CPeg> pegsToInsert;
	std::vector<CSolution> solutions;
	unsigned int random;
	__asm {
		rdtsc	;
		mov		[random], edx;
		mov		[random], eax;
		}
	srand(random);

	for (;;) {
		while (currentlyTrainingAStarWeights == false) {
			Sleep(100);
		}
		pMainWindow->pMainAI->currentWeightsScore = 0.0f;

		//do all of the test cases
		for (int cases = 1; cases <= NUM_TEST_CASES; ++cases) {
			pegsToInsert.clear();
			solutions.clear();
			pMainWindow->LoadTestCase(cases, player, opponent, pegsToInsert, solutions);
			pMainWindow->ExecuteAStarTestCase(12, player, opponent, pegsToInsert, solutions);
		}

		//do all of the stored histories
		for (int histories = 1; histories <= NUM_HISTORIES; ++histories) {
			pegsToInsert.clear();
			solutions.clear();
			pMainWindow->LoadSavedHistory(histories, player, opponent, pegsToInsert, solutions);
			pMainWindow->ExecuteAStarTestCase(24, player, opponent, pegsToInsert, solutions);
		}

		pMainWindow->pMainAI->currentAStarWeightsScore = pMainWindow->pMainAI->currentWeightsScore;
		pMainWindow->pMainAI->SaveAStarWeights();
		pMainWindow->pMainAI->PerturbAStarWeights();//comes AFTER we have tested what we loaded
		fstream iters("AStarTrainingIterations.txt");
		iters >> allIterations;
		iters.close();
		iters.open("AStarTrainingIterations.txt", ios::out);
		iters << allIterations+1 << "\tTotal Iterations";
		iters << '\n' << ++todaysIterations << "\tToday's Iterations";
		iters.close();
	}
	return;
}//end TrainAStarWeights

void CMainWindow::SaveHistory(bool const skipLastEntry)
{
	ePlayer firstPlayer = gameData.firstPlayer;
	ePlayer secondPlayer = gameData.secondPlayer;
	std::vector<MYPoint>* pFirstPlayerPegs = pMainAI->GetPlayerPegList(firstPlayer);
	std::vector<MYPoint>* pSecondPlayerPegs = pMainAI->GetPlayerPegList(secondPlayer);
	if (pFirstPlayerPegs->empty() == true && pSecondPlayerPegs->empty() == true) {
		return;
	}

	int index = 0;
	std::string filename;
	do {
		++index;
		filename = "Copy (";
		char buffer[32] = {0};
		_itoa_s(index, buffer, 10);
		filename += buffer;
		filename += ") of history.txt";

		//mimic ios::noreplace
		std::ifstream history(filename.c_str());
		if (!history) {
			//file doesn't exist, we will create it next
			break;
		}
		else {
			//file already exists, so continue
			history.close();
		}
	} while (index);

	std::ofstream history(filename.c_str());

	bool skipLastFirstPlayerPeg = (skipLastEntry == true && pFirstPlayerPegs->size() > pSecondPlayerPegs->size());
	bool skipLastSecondPlayerPeg = (skipLastEntry == true && pFirstPlayerPegs->size() == pSecondPlayerPegs->size());
	for (index = 0; index < pFirstPlayerPegs->size(); ++index) {
		if (skipLastFirstPlayerPeg == true && index == pFirstPlayerPegs->size() - 1) {
			break;
		}
		else {
			history<<'\n'<<(int)(*pFirstPlayerPegs)[index].x<<' '<<(int)(*pFirstPlayerPegs)[index].y<<' '<<firstPlayer;
		}
		if (skipLastSecondPlayerPeg == true && index == pSecondPlayerPegs->size() - 1) {
			break;
		}
		else {
			history<<'\n'<<(int)(*pSecondPlayerPegs)[index].x<<' '<<(int)(*pSecondPlayerPegs)[index].y<<' '<<secondPlayer;
		}
	}
	history<<" END";

	return;
}//end SaveHistory

void CMainWindow::RetestAStarWeights()
{
	ePlayer player;
	ePlayer opponent;
	std::vector<CPeg> pegsToInsert;
	std::vector<CSolution> solutions;

	std::vector<std::vector<int>> weights;
	pMainAI->LoadAStarWeightsFromBackup(weights);

	for (int numWeights = 0; numWeights != weights.size(); ++numWeights) {
		pMainAI->currentWeightsScore = 0.0f;
		pMainAI->SetAStarLinkWeight(weights[numWeights][0]);
		pMainAI->SetAStarBlockWeight(weights[numWeights][1]);
		pMainAI->SetAStarDoubleSetupWeight(weights[numWeights][2]);

		//do all of the test cases
		for (int cases = 1; cases <= NUM_TEST_CASES; ++cases) {
			pegsToInsert.clear();
			solutions.clear();
			LoadTestCase(cases, player, opponent, pegsToInsert, solutions);
			ExecuteAStarTestCase(12, player, opponent, pegsToInsert, solutions);
		}

		//do all of the stored histories
		for (int histories = 1; histories <= NUM_HISTORIES; ++histories) {
			pegsToInsert.clear();
			solutions.clear();
			LoadSavedHistory(histories, player, opponent, pegsToInsert, solutions);
			ExecuteAStarTestCase(24, player, opponent, pegsToInsert, solutions);
		}

		pMainAI->currentAStarWeightsScore = pMainAI->currentWeightsScore;
		weights[numWeights].push_back(pMainAI->currentAStarWeightsScore);
		ofstream iters("AStarRetestingIterations.txt");
		iters << numWeights+1 << " / " << weights.size();
		iters.close();
	}
	ofstream iters("AStarRetestingIterations.txt");
	iters << "done";
	iters.close();

	//get best
	pMainAI->bestAStarWeightsScore = 0;
	for (int numWeights = 0; numWeights != weights.size(); ++numWeights) {
		if (weights[numWeights][3] > pMainAI->bestAStarWeightsScore) {
			pMainAI->SetAStarLinkWeight(weights[numWeights][0]);
			pMainAI->SetAStarBlockWeight(weights[numWeights][1]);
			pMainAI->SetAStarDoubleSetupWeight(weights[numWeights][2]);
			pMainAI->bestAStarWeightsScore = weights[numWeights][3];
		}
	}
	pMainAI->currentAStarWeightsScore = pMainAI->bestAStarWeightsScore;

	//prune really sucky ones
	for (int numWeights = 0; numWeights != weights.size(); ++numWeights) {
		if ((weights[numWeights][3] * 2) < pMainAI->bestAStarWeightsScore) {
			weights[numWeights] = weights[weights.size()-1];
			weights.pop_back();
		}
	}

	pMainAI->SaveAStarWeightsToBackup(weights);
	pMainAI->bestAStarWeightsScore = 0;
	pMainAI->SaveAStarWeights();
	pMainAI->LoadAStarWeights();
	return;
}//end RetestAStarWeights

bool CMainWindow::GetBoardCoordFromMouse(MYPoint* Source,
										 const CPoint& mousePoint)
{
	MYPoint peg(mousePoint.x % gridMulti, mousePoint.y % gridMulti);

	//make sure it falls close enough within a peg's circle
	if ((peg.x >= pegUpper-1 && peg.x <= pegLower+1) &&
		(peg.y >= pegUpper-1 && peg.y <= pegLower+1)) {

		//get the peg coord
		peg = MYPoint(mousePoint.x / gridMulti, mousePoint.y / gridMulti);
		if (pMainAI->isPegWithinBoard(peg) == true) {
			*Source = peg;
			return true;
		}
	}
	return false;
}//end GetBoardCoordFromMouse

void CMainWindow::GetPenAndBrush(CPen **Pen,
								 CBrush **Brush,
								 ePlayer const player)
{
	switch (player) {
	case PlayerRed:
	case ComputerRed:
		*Pen = &redPen;
		*Brush = &redBrush;
		break;
	case PlayerBlack:
	case ComputerBlack:
		*Pen = &blackPen;
		*Brush = &blackBrush;
		break;
	case Green:
		*Pen = &greenPen;
		*Brush = &greenBrush;
		break;
	case Yellow:
		*Pen = &yellowPen;
		*Brush = &yellowBrush;
		break;

	case Blue:
	default:
		*Pen = &bluePen;
		*Brush = &blueBrush;
		break;
	}

	return;
}//end GetPenAndBrush

void CMainWindow::OnKeyDown(UINT nChar, UINT nRepeatCount, UINT nFlags)
{
	static int viewCase = 1;
	static int history = 1;
	bool shiftKeyDown = ::GetKeyState(VK_SHIFT) < 0;

	if (currentlyTrainingAStarWeights == true || currentlyTrainingAIWeights == true) {
		if (currentlyTrainingAStarWeights) {
			switch (nChar) {
				case 'x': case 'X':
					pThreadManager->StopTrainingAStarWeights();
			}
		}
		if (currentlyTrainingAIWeights) {
			switch (nChar) {
				case 'x': case 'X':
					pThreadManager->StopTrainingAIWeights();
			}
		}


		//if we are training weights, only accept this input!!!!!!!!!
		return;
	}

	switch (nChar) {
		case 'g': case 'G'://save a good history
			SaveHistory(true);
			break;

		case 'f': case 'F'://forward in history
			if (historyPegs.size() && historyIndex < historyPegs.size()) {
				MYPoint Peg = historyPegs[historyIndex].peg;
				if (Peg.x < 0 || Peg.y < 0) {
					pMainAI->removePeg(Peg, historyPegs[historyIndex].player);
				}
				else {
					pMainAI->insertPeg(Peg, historyPegs[historyIndex].player);
				}
				++historyIndex;
				RePaint();
			}
			break;

		case 'b': case 'B'://back in history
			if (historyPegs.size() && historyIndex > 0) {
				--historyIndex;
				MYPoint Peg = historyPegs[historyIndex].peg;
				if (Peg.x < 0 || Peg.y < 0) {
					pMainAI->insertPeg(Peg, historyPegs[historyIndex].player);
				}
				else {
					pMainAI->removePeg(Peg, historyPegs[historyIndex].player);
				}
				RePaint();
			}
			break;

		case 'i': case 'I': pThreadManager->StartTrainingAIWeights(&TrainAIWeights, this); break;
		case 's': case 'S': pThreadManager->StartTrainingAStarWeights(&TrainAStarWeights, this); break;
		case VK_LEFT: shiftKeyDown ? history -= 10 : history -= 1; break;
		case VK_RIGHT: shiftKeyDown ? history += 10 : history += 1; break;
		case VK_UP: shiftKeyDown ? viewCase += 10 : viewCase += 1; break;
		case VK_DOWN: shiftKeyDown ? viewCase -= 10 : viewCase -= 1; break;
	}

	switch (nChar) {
		case VK_LEFT:
		case VK_RIGHT:
			if (history < -1) {
				history = -1;
			}
			else if (history > NUM_HISTORIES) {
				history = NUM_HISTORIES;
			}
			ViewSavedHistory(history);
			break;
		case VK_UP:
		case VK_DOWN:
			if (viewCase < 1) {
				viewCase = 1;
			}
			else if (viewCase > NUM_TEST_CASES) {
				viewCase = NUM_TEST_CASES;
			}
			ViewTestCase(viewCase);
			break;
	}
	return;
}

void CMainWindow::OnLButtonDown (UINT nFlags, CPoint mousePoint)
{
	if (pThreadManager->isBusy() == true) {
		//don't process another turn if the computer is still calculating

		//err doesn't work, needs to be fixed
		return;
	}
	if (gameData.gameWon == true) {
		return;
	}

	nFlags;
	MYPoint Source(0,0);
	if (GetBoardCoordFromMouse(&Source, mousePoint) == false) {
		return;
	}

	ePlayer thisPlayer = gameData.currentPlayer;
	if (pMainAI->isPegWithinBoard(Source, thisPlayer) == true
		&& pMainAI->isPegAvailable(Source) == true) {
		InsertPeg(Source, thisPlayer);
	}
	return;
}//end OnLButtonDown

void CMainWindow::OnRButtonDown (UINT nFlags, CPoint mousePoint)
{
	nFlags;
	mousePoint;
	ViewTestCase(1);

	if (0) {
	//if (gameData.currentTurn >= gameData.maxPlayers) {
		ePlayer currentPlayer = gameData.currentPlayer;
		//make sure the turn goes back to the current player instead of
		//making the computer do its turn all over again
		do {
			DecrementTurn();
			RemoveLastPeg(gameData.currentPlayer);
		} while (currentPlayer != gameData.currentPlayer);
		pMainAI->UndoTurn();
		gameData.gameWon = false;
		RePaint();
	}
	return;
}//end OnRButtonDown

void CMainWindow::InsertPeg(const MYPoint& Source,
							ePlayer const player)
{
	ofstream file;
	if (debugSettings.debugLoadHistory == false) {
		file.open("history.txt", ios::app);
	}
	else {
		file.open("debughistory.txt", ios::app);
	}
	file<<(int)Source.x<<' '<<(int)Source.y<<' '<<player<<'\n';
	file.close();

	if (player == PlayerRed || player == PlayerBlack) {
		gameData.recentlySaved = false;
	}
	CPen *Pen = 0;
	CBrush *Brush = 0;
	GetPenAndBrush(&Pen, &Brush, player);
	pMainAI->insertPeg(Source, player);
	DrawPegAndLinks(Source, Pen, Brush, player);
	lastPeg = Source;
	bool won = pMainAI->CheckForWin(player);
	if (won == true) {
		OnGameWon(player);
	}
	else {
		IncrementTurn();
		DoTurn();
		RePaint();
	}
	return;
}//end InsertPeg

void CMainWindow::RemoveLastPeg(ePlayer const player)
{
	gameData.recentlySaved = false;
	vector<MYPoint>* pPegs = pMainAI->GetPlayerPegList(player);
	lastPeg = pPegs->back();
	pMainAI->removePeg(lastPeg, player);
	ofstream file;
	if (debugSettings.debugLoadHistory == false) {
		file.open("history.txt", ios::app);
	}
	else {
		file.open("debughistory.txt", ios::app);
	}
	file<<'\n'<<-(int)(lastPeg.x)<<' '<<-(int)(lastPeg.y)<<' '<<player;
	if (pPegs->empty() == false) {
		lastPeg = pPegs->back();
	}
	else {
		lastPeg = MYPoint(0,0);
	}
	RePaint();
	return;
}//end InsertPeg

void CMainWindow::OnPaint ()
{
	ChangeWindowSize();
	CPaintDC dc (this);
	int x = 0;
	int y = 0;
	CRect rect;
	GetClientRect (&rect);
	dc.FillRect(rect, &backgroundBrush);

	//draw the empty pegs in the center, and the left and right edges
	dc.SelectObject(lightGray);
	for (x = 1; x < XBoardSize-1; ++x) {
		for (y = 0; y < YBoardSize; ++y) {
			dc.Ellipse (x*gridMulti+pegUpper, y*gridMulti+pegUpper,
						x*gridMulti+pegLower, y*gridMulti+pegLower);
		}
	}

	//draw the empty pegs on the top and bottom edges
	for (y = 1; y < YBoardSize-1; ++y) {
		dc.Ellipse (pegUpper, y*gridMulti+pegUpper,
					0*gridMulti+pegLower, y*gridMulti+pegLower);
		dc.Ellipse ((XBoardSize-1)*gridMulti+pegUpper, y*gridMulti+pegUpper,
					(XBoardSize-1)*gridMulti+pegLower, y*gridMulti+pegLower);
	}

	//draw the grid lines
	for (y = 1; y < YBoardSize; ++y) {
		dc.MoveTo(0, y*gridMulti);
		dc.LineTo(XBoardSize*gridMulti, y*gridMulti);
	}
	for (x = 1; x < XBoardSize; ++x) {
		dc.MoveTo(x*gridMulti, 0);
		dc.LineTo(x*gridMulti, YBoardSize*gridMulti);
	}
	//draw the grid lines at the edges
	dc.MoveTo(0, gridMulti);
	dc.LineTo(0, (YBoardSize-1) * gridMulti);
	dc.MoveTo((XBoardSize) * gridMulti, gridMulti);
	dc.LineTo((XBoardSize) * gridMulti, (YBoardSize-1) * gridMulti);
	dc.MoveTo(gridMulti, 0);
	dc.LineTo((XBoardSize-1) * gridMulti, 0);
	dc.MoveTo(gridMulti, (YBoardSize) * gridMulti);
	dc.LineTo((XBoardSize-1) * gridMulti, (YBoardSize) * gridMulti);

	//draw black edges
	dc.SelectObject(blackThick);
	dc.MoveTo(gridMulti, gridMulti);
	dc.LineTo(gridMulti, (YBoardSize-1)*gridMulti);
	dc.MoveTo((XBoardSize-1)*gridMulti, gridMulti);
	dc.LineTo((XBoardSize-1)*gridMulti, (YBoardSize-1)*gridMulti);

	//draw red edges
	dc.SelectObject(redThick);
	dc.MoveTo(gridMulti, gridMulti);
	dc.LineTo((XBoardSize-1)*gridMulti, gridMulti);
	dc.MoveTo(gridMulti, (YBoardSize-1)*gridMulti);
	dc.LineTo((XBoardSize-1)*gridMulti, (YBoardSize-1)*gridMulti);

	//draw all the player's pegs
	ePlayer tempPlayer = gameData.firstPlayer;
	DrawPlayerPegs(tempPlayer, &redPen, &redBrush);

	tempPlayer = gameData.secondPlayer;
	DrawPlayerPegs(tempPlayer, &blackPen, &blackBrush);

	DrawDebug();
	return;
}//end OnPaint

void CMainWindow::RePaint ()
{
	ChangeWindowSize();
	CClientDC dc (this);
	int x = 0;
	int y = 0;
	CRect rect;
	GetClientRect (&rect);
	dc.FillRect(rect, &backgroundBrush);

	//draw the empty pegs in the center, and the left and right edges
	dc.SelectObject(lightGray);
	for (x = 1; x < XBoardSize-1; ++x) {
		for (y = 0; y < YBoardSize; ++y) {
			dc.Ellipse (x*gridMulti+pegUpper, y*gridMulti+pegUpper,
						x*gridMulti+pegLower, y*gridMulti+pegLower);
		}
	}

	//draw the empty pegs on the top and bottom edges
	for (y = 1; y < YBoardSize-1; ++y) {
		dc.Ellipse (pegUpper, y*gridMulti+pegUpper,
					0*gridMulti+pegLower, y*gridMulti+pegLower);
		dc.Ellipse ((XBoardSize-1)*gridMulti+pegUpper, y*gridMulti+pegUpper,
					(XBoardSize-1)*gridMulti+pegLower, y*gridMulti+pegLower);
	}

	//draw the grid lines
	for (y = 1; y < YBoardSize; ++y) {
		dc.MoveTo(0, y*gridMulti);
		dc.LineTo(XBoardSize*gridMulti, y*gridMulti);
	}
	for (x = 1; x < XBoardSize; ++x) {
		dc.MoveTo(x*gridMulti, 0);
		dc.LineTo(x*gridMulti, YBoardSize*gridMulti);
	}
	//draw the grid lines at the edges
	dc.MoveTo(0, gridMulti);
	dc.LineTo(0, (YBoardSize-1) * gridMulti);
	dc.MoveTo((XBoardSize) * gridMulti, gridMulti);
	dc.LineTo((XBoardSize) * gridMulti, (YBoardSize-1) * gridMulti);
	dc.MoveTo(gridMulti, 0);
	dc.LineTo((XBoardSize-1) * gridMulti, 0);
	dc.MoveTo(gridMulti, (YBoardSize) * gridMulti);
	dc.LineTo((XBoardSize-1) * gridMulti, (YBoardSize) * gridMulti);

	//draw black edges
	dc.SelectObject(blackThick);
	dc.MoveTo(gridMulti, gridMulti);
	dc.LineTo(gridMulti, (YBoardSize-1)*gridMulti);
	dc.MoveTo((XBoardSize-1)*gridMulti, gridMulti);
	dc.LineTo((XBoardSize-1)*gridMulti, (YBoardSize-1)*gridMulti);

	//draw red edges
	dc.SelectObject(redThick);
	dc.MoveTo(gridMulti, gridMulti);
	dc.LineTo((XBoardSize-1)*gridMulti, gridMulti);
	dc.MoveTo(gridMulti, (YBoardSize-1)*gridMulti);
	dc.LineTo((XBoardSize-1)*gridMulti, (YBoardSize-1)*gridMulti);

	//draw all the player's pegs
	ePlayer tempPlayer = gameData.firstPlayer;
	DrawPlayerPegs(tempPlayer, &redPen, &redBrush);

	tempPlayer = gameData.secondPlayer;
	DrawPlayerPegs(tempPlayer, &blackPen, &blackBrush);

	DrawDebug();

	return;
}//end RePaint

void CMainWindow::DrawPegAndLinks(const MYPoint& Source,
								  CPen *Pen,
								  CBrush *Brush,
								  ePlayer const player)
{
	CClientDC dc (this);
	dc.SelectObject(*Pen);
	dc.SelectObject(*Brush);
	dc.Ellipse ((Source.x * gridMulti) + pegUpper,
				(Source.y * gridMulti) + pegUpper,
				(Source.x * gridMulti) + pegLower,
				(Source.y * gridMulti) + pegLower);
	if (pMainAI->doesPegHaveLinks(Source) == true) {
		if (debugSettings.showLinks) {
			for (CDir direction = leftUp; direction != NOTADIR; ++direction) {
				DrawLinks(Source, Pen, Brush, player, direction);
			}
		}
	}
	return;
}//end DrawPegAndLinks

void CMainWindow::DrawLinks(const MYPoint& Source,
							CPen *Pen,
							CBrush *Brush,
							ePlayer const player,
							CDir const direction)
{
	if ((pMainAI->isDestLinked(Source, CJump(direction), player) == true) && 
		(pMainAI->isPegWithinBoard(GetDestFromDir(Source, direction)) == true)) {
		MYPoint Dest = GetDestFromDir(Source, direction);
		if (pMainAI->isOwnerThis(Dest, player) == true) {
			CClientDC dc (this);
			dc.SelectObject(*Pen);
			dc.SelectObject(*Brush);
			dc.MoveTo((Source.x * gridMulti) + pegPoint,
					(Source.y * gridMulti) + pegPoint);
			dc.LineTo((Dest.x * gridMulti) + pegPoint,
					(Dest.y * gridMulti) + pegPoint);
		}
	}
	return;
}//end DrawLinks

void CMainWindow::DrawBestPath(const MYPoint& LastPeg)
{
	CLink parentLink = pMainAI->GetAStarLink(LastPeg);
	while (parentLink.startPeg != MYPoint(0,0)) {
		DrawParentLink(parentLink.GetDestFromDir(), &greenPen, &greenBrush);
		parentLink = pMainAI->GetAStarLink(parentLink.startPeg);
	}
	return;
}//end DrawBestPath

void CMainWindow::DrawDebug(std::vector<CPeg>* pPegsToDrawSpecial)
{
	CClientDC dc (this);
	if (debugSettings.showSearched == true) {
		dc.SelectObject(bluePen);
		dc.SelectObject(blueBrush);
		for each (MYPoint peg in pMainAI->ClosedList) {
			dc.Ellipse ((peg.x * gridMulti) + pegUpper + 2,
						(peg.y * gridMulti) + pegUpper + 2,
						(peg.x * gridMulti) + (pegLower - 2),
						(peg.y * gridMulti) + (pegLower - 2));
		}
	}
	if (debugSettings.showNewest == true) {
		if (lastPeg != MYPoint(0,0)) {
			dc.SelectObject(greenPen);
			dc.SelectObject(greenBrush);
			dc.Ellipse ((lastPeg.x * gridMulti) + pegUpper + 2,
						(lastPeg.y * gridMulti) + pegUpper + 2,
						(lastPeg.x * gridMulti) + (pegLower - 2),
						(lastPeg.y * gridMulti) + (pegLower - 2));
		}
	}
	if (debugSettings.showParent == true) {
		for (int x = 0; x < XBoardSize; x++) {
			for (int y = 0; y < YBoardSize; y++) {
				if ((pMainAI->GetAStarLink(MYPoint(x, y))).startPeg != MYPoint(0,0)) {
					DrawParentLink(MYPoint(x, y), &bluePen, &blueBrush);
				}
			}
		}
	}
	if (debugSettings.showBestPath == true) {
		if (pMainAI->ClosedList.empty() == false) {
			DrawBestPath(pMainAI->ClosedList.back());
		}
	}

	if (pPegsToDrawSpecial) {
		for each (CPeg peg in *pPegsToDrawSpecial) {
			CPen *Pen = 0;
			CBrush *Brush = 0;
			GetPenAndBrush(&Pen, &Brush, peg.player);
			dc.SelectObject(*Pen);
			dc.SelectObject(*Brush);
			dc.Ellipse ((peg.peg.x * gridMulti) + pegUpper + 2,
						(peg.peg.y * gridMulti) + pegUpper + 2,
						(peg.peg.x * gridMulti) + (pegLower - 2),
						(peg.peg.y * gridMulti) + (pegLower - 2));
		}
	}
	return;
}//end DrawDebug

void CMainWindow::DrawParentLink(const MYPoint& Source,
								 CPen* pen,
								 CBrush* brush)
{
	MYPoint Dest = (pMainAI->GetAStarLink(Source)).startPeg;

	CClientDC dc (this);
	dc.SelectObject(pen);
	dc.SelectObject(brush);
	dc.MoveTo((Source.x * gridMulti) + pegPoint,
			(Source.y * gridMulti) + pegPoint);
	dc.LineTo(((Source.x + Dest.x) * gridMulti / 2) + pegPoint,
			((Source.y + Dest.y) * gridMulti / 2) + pegPoint);
	return;
}//end DrawParentLink

void CMainWindow::ChangeWindowSize()
{
	if (gameData.windowSize == Window_DefaultSize) {
		gridMulti = 30;
		pegUpper = 9;
		pegLower = 20;
		pegPoint = 15;
	}
	else if (gameData.windowSize == Window_BoardToWindow) {
		CClientDC dc (this);
		CRect rect;
		GetClientRect (&rect);
		if ((rect.bottom - rect.top) / YBoardSize >= (rect.right - rect.left) / XBoardSize) {
			gridMulti = (int) ((rect.right - rect.left) / XBoardSize);
		}
		else {
			gridMulti = (int) ((rect.bottom - rect.top) / YBoardSize);
		}
		pegUpper = (int) ((gridMulti * (3.0 / 10.0)) - 1.0);
		pegLower = (int) ((gridMulti * (7.0 / 10.0)) + 1.0);
		pegPoint = (int) (gridMulti / 2);
	}
	else if (gameData.windowSize == Window_BoardToScreen) {
		CClientDC dc (this);
		if ((dc.GetDeviceCaps(HORZRES) == 1024) &&
			(dc.GetDeviceCaps(VERTRES) == 768)) {
			if (XBoardSize >= YBoardSize) {
				gridMulti = (int) (30.0 * (24.0 / XBoardSize));
				pegUpper = (int) (10.0 * (24.0 / XBoardSize) - 1.0);
				pegLower = (int) (20.0 * (24.0 / XBoardSize) + 1.0);
				pegPoint = (int) (15.0 * (24.0 / XBoardSize));
			}
			else {
				gridMulti = (int) (30.0 * (24.0 / YBoardSize));
				pegUpper = (int) (10.0 * (24.0 / YBoardSize) - 1.0);
				pegLower = (int) (20.0 * (24.0 / YBoardSize) + 1.0);
				pegPoint = (int) (15.0 * (24.0 / YBoardSize));
			}
		}
		else {
			if (XBoardSize >= YBoardSize) {
				gridMulti = (int) ((dc.GetDeviceCaps(VERTRES) / XBoardSize) - 1);
			}
			else {
				gridMulti = (int) ((dc.GetDeviceCaps(VERTRES) / YBoardSize) - 1);
			}
			pegPoint = (int) (gridMulti / 2);
			pegUpper = (int) ((gridMulti * (3.0 / 10.0)) - 1.0);
			pegLower = (int) ((gridMulti * (7.0 / 10.0)) + 1.0);
		}
	}
	return;
}//end ChangeWindowSize

void CMainWindow::DrawPlayerPegs(ePlayer const player,
								 CPen *Pen,
								 CBrush *Brush)
{
	for (int x = 0; x < XBoardSize; ++x) {
		for (int y = 0; y < YBoardSize; ++y) {
			if (pMainAI->isOwnerThis(MYPoint(x,y), player) == true) {
				DrawPegAndLinks(MYPoint(x,y), Pen, Brush, player);
			}
		}
	}
	return;
}//end DrawPlayerPegs

void CMainWindow::InitDebugSettings()
{
	debugSettings.showLinks = true;
	debugSettings.showNewest = true;
	debugSettings.showBestPath = false;
	debugSettings.showSearched = false;
	debugSettings.showParent = false;
	debugSettings.showAStarF = false;
	debugSettings.showAStarG = false;
	debugSettings.showAStarH = false;
	debugSettings.debugLoadHistory = false;
	return;
}//end InitDebugSettings

void CMainWindow::InitGameData()
{
	gameData.XBoardSize = DEFAULTBOARDSIZE;
	gameData.YBoardSize = DEFAULTBOARDSIZE;
	gameData.numThreads = DEFAULTNUMTHREADS;
	gameData.difficulty = DEFAULTDIFFICULTY;
	gameData.currentTurn = 0;
	gameData.maxPlayers = 2;
	//gameData.firstPlayer = PlayerRed;
	//gameData.secondPlayer = ComputerBlack;
	gameData.firstPlayer = ComputerRed;
	gameData.secondPlayer = PlayerBlack;
	gameData.currentPlayer = gameData.firstPlayer;
	gameData.recentlySaved = true;
	gameData.gameWon = false;
	gameData.windowSize = Window_DefaultSize;
	return;
}//end InitgameData

ePlayer CMainWindow::GetOpponent(ePlayer const player)
{
	if (gameData.firstPlayer == player) {
		return gameData.secondPlayer;
	}
	else if (gameData.secondPlayer == player) {
		return gameData.firstPlayer;
	}
	else {
		return NOTAPLAYER;
	}
}//end GetOpponent

void CMainWindow::CreatePens()
{
	redPen.CreatePen (0, 1, 255);
	redBrush.CreateSolidBrush (255);
	redThick.CreatePen (0, 3, 255);
	blackPen.CreatePen (0, 1, RGB(0, 0, 0));
	blackBrush.CreateSolidBrush (0);
	blackThick.CreatePen (0, 3, 1);
	lightGray.CreateSolidBrush (RGB(240, 240, 240));
	bluePen.CreatePen (0, 1, RGB(0, 0, 255));
	blueBrush.CreateSolidBrush (RGB(0, 0, 255));
	greenPen.CreatePen (0, 1, RGB(0, 255, 0));
	greenBrush.CreateSolidBrush (RGB(0, 255, 0));
	yellowPen.CreatePen (0, 1, RGB(255, 255, 0));
	yellowBrush.CreateSolidBrush (RGB(255, 255, 0));
	backgroundBrush.CreateSolidBrush (RGB(255, 255, 255));
	return;
}//end CreatePens

void CMainWindow::IncrementTurn()
{
	gameData.currentTurn++;
	int nextPlayerTurn = gameData.currentTurn % gameData.maxPlayers;
	switch (nextPlayerTurn)
	{
	case 0:
		gameData.currentPlayer = gameData.firstPlayer;
		break;
	case 1:
		gameData.currentPlayer = gameData.secondPlayer;
		break;
	default:
		gameData.currentPlayer = NOTAPLAYER;
	}

	return;
}//end IncrementTurn

void CMainWindow::DoTurn()
{
	ePlayer currentPlayer = gameData.currentPlayer;
	MYPoint Dest;
	switch (currentPlayer)
	{
	case PlayerRed:
	case PlayerBlack:
		break;
	case ComputerRed:
	case ComputerBlack:
		//if (gameData.currentTurn == 0 && debugSettings.debugLoadHistory == false) {
		//	pMainAI->DoFirstTurn(&Dest, currentPlayer);
		//}
		//else {
			pMainAI->DoTurn(&Dest, currentPlayer, GetOpponent(currentPlayer));
		//}
		InsertPeg(Dest, currentPlayer);
		break;
	default:
		break;
	}
	return;
}//end DoTurn

void CMainWindow::DecrementTurn()
{
	ASSERT(gameData.currentTurn > 0);
	gameData.recentlySaved = false;
	gameData.currentTurn--;
	int currentPlayerTurn = gameData.currentTurn % gameData.maxPlayers;
	switch (currentPlayerTurn)
	{
	case 0:
		gameData.currentPlayer = gameData.firstPlayer;
		break;
	case 1:
		gameData.currentPlayer = gameData.secondPlayer;
		break;
	default:
		gameData.currentPlayer = NOTAPLAYER;
	}
	return;
}//end DecrementTurn

void CMainWindow::OnExitApp ()
{
	PostMessage (WM_CLOSE, 0, 0);
}
void CMainWindow::OnGameNew ()
{
	if (gameData.recentlySaved == true) {
		CDialogNewGame newGame;
		if (newGame.DoModal() == IDOK) {
			InitGameData();
			XBoardSize = YBoardSize = newGame.size;
			numThreads = newGame.numThreads;
			gameData.difficulty = newGame.difficulty;

			//do players etc
			if (newGame.redGoesFirst == true) {
				if (newGame.computerIsRed == true) {
					gameData.firstPlayer = ComputerRed;
				}
				else {
					gameData.firstPlayer = PlayerRed;
				}
				if (newGame.computerIsBlack == true) {
					gameData.secondPlayer = ComputerBlack;
				}
				else {
					gameData.secondPlayer = PlayerBlack;
				}
			}
			else {
				if (newGame.computerIsBlack == true) {
					gameData.firstPlayer = ComputerBlack;
				}
				else {
					gameData.firstPlayer = PlayerBlack;
				}
				if (newGame.computerIsRed == true) {
					gameData.secondPlayer = ComputerRed;
				}
				else {
					gameData.secondPlayer = PlayerRed;
				}
			}
			gameData.currentPlayer = gameData.firstPlayer;
			StartNewGame(XBoardSize, YBoardSize, numThreads);
			DoTurn();
		}
	}
	else {
		CDialogNotRecentlySaved CDNRS;
		int nResult;
		nResult = CDNRS.DoModal();
		if (nResult == IDOK) {
			//save game
		}
		else if (nResult == IDCANCEL) {
			gameData.recentlySaved = true;
			OnGameNew();
		}
	}
}
void CMainWindow::OnScenLoad ()
{
	OnGameLoad();
	return;
}

void CMainWindow::OnGameLoad ()
{
	FILE* fpLoad;
	fopen_s(&fpLoad, "SaveGame.tsg", "rb");
	if (fpLoad == NULL) {
		return;
	}

	fread(&gameData, sizeof(GameData), 1, fpLoad);
	fread(&debugSettings, sizeof(DebugSettings), 1, fpLoad);

	StartNewGame(gameData.XBoardSize, gameData.YBoardSize, gameData.numThreads);

	int sizeFirstPlayerPegs;
	int sizeSecondPlayerPegs;
	fread(&sizeFirstPlayerPegs, sizeof(int), 1, fpLoad);
	fread(&sizeSecondPlayerPegs, sizeof(int), 1, fpLoad);

	vector<MYPoint> firstPlayerPegs;
	vector<MYPoint> secondPlayerPegs;
	MYPoint point;
	for (int x = 0; x < sizeFirstPlayerPegs; ++x) {
		fread(&point, sizeof(MYPoint), 1, fpLoad);
		firstPlayerPegs.push_back(point);
	}
	for (int x = 0; x < sizeSecondPlayerPegs; ++x) {
		fread(&point, sizeof(MYPoint), 1, fpLoad);
		secondPlayerPegs.push_back(point);
	}

	for (int x = 0; x < sizeSecondPlayerPegs; ++x) {
		pMainAI->insertPeg(firstPlayerPegs[x], gameData.firstPlayer);
		pMainAI->insertPeg(secondPlayerPegs[x], gameData.secondPlayer);
	}
	if (sizeSecondPlayerPegs < sizeFirstPlayerPegs) {
		pMainAI->insertPeg(firstPlayerPegs.back(), gameData.firstPlayer);
	}

	fclose(fpLoad);
	DoTurn();
	return;
}
void CMainWindow::OnGameSave ()
{
	FILE* fpSave;
	fopen_s(&fpSave, "SaveGame.tsg", "wb");
	if (fpSave == NULL) {
		return;
	}

	fwrite(&gameData, sizeof(GameData), 1, fpSave);
	fwrite(&debugSettings, sizeof(DebugSettings), 1, fpSave);

	vector<MYPoint>* pFirstPlayerPegs = pMainAI->GetPlayerPegList(gameData.firstPlayer);
	vector<MYPoint>* pSecondPlayerPegs = pMainAI->GetPlayerPegList(gameData.secondPlayer);

	int size = pFirstPlayerPegs->size();
	fwrite(&size, sizeof(int), 1, fpSave);
	size = pSecondPlayerPegs->size();
	fwrite(&size, sizeof(int), 1, fpSave);

	MYPoint point;
	for each (MYPoint point in *pFirstPlayerPegs) {
		fwrite(&point, sizeof(MYPoint), 1, fpSave);
	}

	for each (MYPoint point in *pSecondPlayerPegs) {
		fwrite(&point, sizeof(MYPoint), 1, fpSave);
	}

	fclose(fpSave);
	return;
}
void CMainWindow::OnGameSaveAs ()
{
	OnGameSave();
	return;
}
void CMainWindow::OnGameWon(ePlayer const player)
{
	gameData.recentlySaved = true;
	gameData.gameWon = true;
	if (player == PlayerRed || player == ComputerRed) {
		CDialogRedWon redWon;
		if (redWon.DoModal() == IDOK) {
			OnGameNew();
		}
	}
	else {
		CDialogBlackWon blackWon;
		if (blackWon.DoModal() == IDOK) {
			OnGameNew();
		}
	}
	return;
}
void CMainWindow::OnWindowDefault()
{
	CMenu* pMenu = GetMenu ();
	pMenu->CheckMenuItem (ID_WINDOW_DEFAULT + gameData.windowSize, MF_UNCHECKED);
	gameData.windowSize = Window_DefaultSize;
	pMenu->CheckMenuItem (ID_WINDOW_DEFAULT + gameData.windowSize, MF_CHECKED);
	ChangeWindowSize();
	RePaint ();
}
void CMainWindow::OnWindowBoard()
{
	CMenu* pMenu = GetMenu ();
	pMenu->CheckMenuItem (ID_WINDOW_DEFAULT + gameData.windowSize, MF_UNCHECKED);
	gameData.windowSize = Window_BoardToWindow;
	pMenu->CheckMenuItem (ID_WINDOW_DEFAULT + gameData.windowSize, MF_CHECKED);
	ChangeWindowSize();
	RePaint ();
}
void CMainWindow::OnWindowScreen()
{
	CMenu* pMenu = GetMenu ();
	pMenu->CheckMenuItem (ID_WINDOW_DEFAULT + gameData.windowSize, MF_UNCHECKED);
	gameData.windowSize = Window_BoardToScreen;
	pMenu->CheckMenuItem (ID_WINDOW_DEFAULT + gameData.windowSize, MF_CHECKED);
	ChangeWindowSize();
	RePaint ();
}

void CDialogNewGame::OnOK() 
{
	size = GetDlgItemInt(IDC_EDITSIZE);
	numThreads = GetDlgItemInt(IDC_NUMTHREADS);
	CString string;
	GetDlgItemTextA(IDC_DIFFICULTY, string);

	if (string == CString("Hard")) {
		difficulty = Dif_Hard;
	}
	else if (string == CString("Medium")) {
		difficulty = Dif_Medium;
	}
	else {
		difficulty = Dif_Easy;
	}

	if (size < 12) {
		size = 12;
	}
	else if (size > MAXBOARDSIZE) {
		size = MAXBOARDSIZE;
	}

	if (numThreads < 1) {
		numThreads = 1;
	}
	else if (numThreads > 16) {
		numThreads = 16;
	}

	if (GetCheckedRadioButton(IDC_RADIO1, IDC_RADIO2) == IDC_RADIO2)
		computerIsRed = true;
	else
		computerIsRed = false;
	if (GetCheckedRadioButton(IDC_RADIO3, IDC_RADIO4) == IDC_RADIO4)
		computerIsBlack = true;
	else
		computerIsBlack = false;

	if (GetCheckedRadioButton(IDC_RADIO5, IDC_RADIO6) == IDC_RADIO5)
		redGoesFirst = true;
	else
		redGoesFirst = false;

	CDialog::OnOK();
}

void CDialogNewGame::OnDefault() 
{
	size = DEFAULTBOARDSIZE;
	SetDlgItemInt(IDC_EDITSIZE, size);
	numThreads = DEFAULTNUMTHREADS;
	SetDlgItemInt(IDC_NUMTHREADS, numThreads);
	CheckDlgButton(IDC_RADIO1, MF_CHECKED);
	CheckDlgButton(IDC_RADIO2, MF_UNCHECKED);
	CheckDlgButton(IDC_RADIO3, MF_UNCHECKED);
	CheckDlgButton(IDC_RADIO4, MF_CHECKED);
	CheckDlgButton(IDC_RADIO5, MF_CHECKED);
	CheckDlgButton(IDC_RADIO6, MF_UNCHECKED);
	CComboBox* pDifficulty = (CComboBox*) GetDlgItem(IDC_DIFFICULTY);
	pDifficulty->SelectString(0, _T("Medium"));
}

BOOL CDialogNewGame::OnInitDialog() 
{
	//TODO fix bug
	CDialog::OnInitDialog();
	SetDlgItemInt(IDC_EDITSIZE, size);
	SetDlgItemInt(IDC_NUMTHREADS, numThreads);
	CheckDlgButton(IDC_RADIO1, MF_CHECKED);
	CheckDlgButton(IDC_RADIO4, MF_CHECKED);
	CheckDlgButton(IDC_RADIO5, MF_CHECKED);
	CComboBox* pDifficulty = (CComboBox*) GetDlgItem(IDC_DIFFICULTY);
	pDifficulty->AddString(_T("Easy"));
	pDifficulty->AddString(_T("Medium"));
	pDifficulty->AddString(_T("Hard"));
	pDifficulty->SelectString(0, _T("Medium"));
	return TRUE;
}

CDialogNotRecentlySaved::CDialogNotRecentlySaved(CWnd* pParent /*=NULL*/)
: CDialog(IDD_NOT_RECENTLY_SAVED, pParent){}

CDialogRedWon::CDialogRedWon(CWnd* pParent)
: CDialog(IDD_REDWON, pParent)
{
	return;
}

CDialogBlackWon::CDialogBlackWon(CWnd* pParent)
: CDialog(IDD_BLACKWON, pParent)
{
	return;
}

CDialogNewGame::CDialogNewGame(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_OPTION, pParent)
{
	size = DEFAULTBOARDSIZE;
	numThreads = DEFAULTNUMTHREADS;
	OnInitDialog();
}


void CMainWindow::OnShow (UINT nID)
{
	//most of these are no longer valid since the multithreaded
	//ai thrashes the stored data
	CMenu* pMenu = GetMenu();
	bool* pSetting;
	switch (nID) {
	case ID_SHOWF:
		pSetting = &debugSettings.showAStarF;
		break;
	case ID_SHOWG:
		pSetting = &debugSettings.showAStarG;
		break;
	case ID_SHOWH:
		pSetting = &debugSettings.showAStarH;
		break;
	case ID_SHOW_PARENT:
		pSetting = &debugSettings.showParent;
		break;
	case ID_SHOW_LINKS:
		pSetting = &debugSettings.showLinks;
		break;
	case ID_SHOW_SEARCHED:
		pSetting = &debugSettings.showSearched;
		break;
	case ID_SHOW_NEWEST:
		pSetting = &debugSettings.showNewest;
		break;
	case ID_SHOW_BEST_PATH:
		pSetting = &debugSettings.showBestPath;
		break;
	default:
		return;
	}
	if (*pSetting == true) {
		*pSetting = false;
		pMenu->CheckMenuItem (nID, MF_UNCHECKED);
	}
	else {
		*pSetting = true;
		pMenu->CheckMenuItem (nID, MF_CHECKED);
	}
	RePaint();
}


	

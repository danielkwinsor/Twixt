
#ifndef NEW_TWIXT_H
#define NEW_TWIXT_H

#include "stdafx.h"

class CMainWindow;
void	TrainAStarWeights	(CMainWindow* pMainWindow);
void	TrainAIWeights		(CMainWindow* pMainWindow);

extern bool currentlyTrainingAStarWeights;
extern bool currentlyTrainingAIWeights;

class CTwixtGame : public CWinApp
{
public:
    virtual BOOL InitInstance ();

private:

};

class CMainWindow : public CFrameWnd
{
public:
	friend void TrainAStarWeights(CMainWindow* pMainWindow);
	friend void TrainAIWeights(CMainWindow* pMainWindow);
private:
	AILogic*			pMainAI;
	CThreadManager*		pThreadManager;

public:
    CMainWindow			();
    ~CMainWindow		();
	SharedAStarData			MainBoard[MAXBOARDSIZE][MAXBOARDSIZE];

protected:
    afx_msg void OnPaint ();
    afx_msg void OnShow (UINT nID);
    afx_msg void OnExitApp ();
    afx_msg void OnGameNew ();
    afx_msg void OnGameLoad ();
    afx_msg void OnScenLoad ();
    afx_msg void OnGameSave ();
    afx_msg void OnGameSaveAs ();
    afx_msg void OnWindowDefault ();
    afx_msg void OnWindowBoard ();
    afx_msg void OnWindowScreen ();
	afx_msg void OnKeyDown (UINT nChar, UINT nRepeatCount, UINT nFlags);
	afx_msg void OnLButtonDown (UINT nFlags, CPoint mousePoint);
	afx_msg void OnRButtonDown (UINT nFlags, CPoint mousePoint);
	afx_msg BOOL OnEraseBkgnd( CDC * );
    DECLARE_MESSAGE_MAP ()

	void	OnGameWon	(ePlayer const player);

private:
	int XBoardSize;
	int YBoardSize;
	int	gridMulti;
	int	pegUpper;
	int	pegLower;
	int	pegPoint;
	int testCasesCorrect;
	int numThreads;

	DebugSettings	debugSettings;
	GameData		gameData;

	MYPoint lastPeg;
	CPen redPen;
	CBrush redBrush;
	CPen blackPen;
	CBrush blackBrush;
	CPen greenPen;
	CBrush greenBrush;
	CPen redThick;
	CPen blackThick;
	CBrush lightGray;
	CPen bluePen;
	CBrush blueBrush;
	CPen yellowPen;
	CBrush yellowBrush;
	CBrush backgroundBrush;

	//for viewing history
	std::vector<CPeg>	historyPegs;
	int					historyIndex;


	void	StartNewGame		(int const XBoardSize,
								int const YBoardSize,
								int const numThreads);

	void	InsertPeg			(const MYPoint& Source,
								ePlayer const player);

	void	RemoveLastPeg		(ePlayer const player);

	void	DrawPlayerPegs		(ePlayer const player,
								CPen *Pen,
								CBrush *Brush);

	void	DrawPegAndLinks		(const MYPoint& Source,
								CPen *Pen,
								CBrush *Brush,
								ePlayer const player);

	void	DrawLinks			(const MYPoint& Source,
								CPen *Pen,
								CBrush *Brush,
								ePlayer const player,
								CDir const direction);

	void	DrawBestPath		(const MYPoint& LastPeg);

	void	DrawDebug			(std::vector<CPeg>* pPegsToDrawSpecial = 0);
	
	void	DrawParentLink		(const MYPoint& Source,
								CPen* pen,
								CBrush* brush);

	void	DrawAllSearchArea	();

	void	ChangeWindowSize	();

	bool	GetBoardCoordFromMouse	(MYPoint* Source,
									const CPoint& mousePoint);

	void	GetPenAndBrush		(CPen **Pen,
								CBrush **Brush,
								ePlayer const player);

	void	RePaint				();

	ePlayer GetOpponent			(ePlayer const player);
	void	InitDebugSettings	();
	void	InitGameData		();
	void	CreatePens			();
	void	IncrementTurn		();
	void	DecrementTurn		();
	void	DoTurn				();

	void	SaveHistory			(bool const skipLastEntry);

	void	RetestAStarWeights	();
	void	RetestAIWeights		();

	void	ViewTestCase		(int testCase);
	void	ViewSavedHistory	(int number);

	void	ExecuteAITestCase	(int sizeOfBoard,
								ePlayer player,
								ePlayer opponent,
								std::vector<CPeg>& pegsToInsert,
								std::vector<CSolution>& solutions,
								MYPoint& Dest);

	void	ExecuteAStarTestCase(int sizeOfBoard,
								ePlayer player,
								ePlayer opponent,
								std::vector<CPeg>& pegsToInsert,
								std::vector<CSolution>& solutions);


	void	LoadTestCase		(int testCase,
								ePlayer& player,
								ePlayer& opponent,
								std::vector<CPeg>& pegsToInsert,
								std::vector<CSolution>& solutions);

	void	LoadSavedHistory	(int number,
								ePlayer& player,
								ePlayer& opponent,
								std::vector<CPeg>& pegsToInsert,
								std::vector<CSolution>& solutions);

	MYPoint	GetPegFromText		(int const x,
								char const y);

	MYPoint	GetPegFromText		(char const x,
								int const y);
};

class CDialogForgotSave : public CDialog
{
public:
};

class CDialogNewGame : public CDialog
{
public:
	CDialogNewGame(CWnd* pParent = NULL);   // standard constructor

	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnDefault();

	int		size;
	int		numThreads;
	eDifficulty	difficulty;
	bool	computerIsRed;
	bool	computerIsBlack;
	bool	redGoesFirst;

protected:
	DECLARE_MESSAGE_MAP()
};

class CDialogRedWon : public CDialog
{
public:
	CDialogRedWon	(CWnd* pParent = NULL);
};

class CDialogBlackWon : public CDialog
{
public:
	CDialogBlackWon	(CWnd* pParent = NULL);
};

class CDialogNotRecentlySaved : public CDialog
{
public:
	CDialogNotRecentlySaved(CWnd* pParent = NULL);   // standard constructor
};


#endif

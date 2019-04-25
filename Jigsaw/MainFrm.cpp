
// MainFrm.cpp: CMainFrame 类的实现
//

#include "stdafx.h"
#include "Jigsaw.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CMainFrame 构造/析构

CMainFrame::CMainFrame() noexcept
{
#define MY_STYLE (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | FWS_ADDTOTITLE)
	//创建窗口
	Create(NULL, _T("拼图游戏"), MY_STYLE, CRect(0, 0, GAME_WIN_W, GAME_WIN_H));
	//设置客户区大小
	{															//获得整个屏幕大小的方法
		HDC hDC = ::GetDC(HWND(NULL));							//	得到屏幕DC  
		int screenWidth = ::GetDeviceCaps(hDC, HORZRES);		//	宽  
		int screenHeight = ::GetDeviceCaps(hDC, VERTRES);       //	高   
		::ReleaseDC(HWND(NULL), hDC);							//	释放DC
		RECT rcFrame = { (screenWidth - m_iWidth) / 2 ,(screenHeight - m_iHeight) / 2 ,		//计算边框大小，并设置
			(screenWidth + m_iWidth) / 2 ,
			(screenHeight + m_iHeight) / 2 };
		MoveWindow(&rcFrame, TRUE);		//调用WindowsAPI设置窗口位置和大小
	}
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	gameStep = false;
	SetTimer(ETimerIdGameLoop, 0, NULL);		//启动定时器每次都会进入游戏帧处理
	m_game.SetHandle(GetSafeHwnd());			//设置游戏主窗口句柄

	return 0;
}

void CMainFrame::OnTimer(UINT_PTR nIDEvent) {
	switch (nIDEvent)
	{
	case ETimerIdGameLoop: {
		//static DWORD dwLastUpdate = GetTickCount();
		//if (GetTickCount() - dwLastUpdate >= 10) {		//限制帧数
		m_game.EnterFrame(GetTickCount());
		//dwLastUpdate = GetTickCount();
		//}
		}
	default:
		break;
	}
	CFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::OnMouseMove(UINT nFlags, CPoint point) {
	m_game.OnMouseMove(nFlags, point);
	CFrameWnd::OnMouseMove(nFlags, point);
}

void CMainFrame::OnLButtonUp(UINT nFlags, CPoint point) {
	m_game.OnLButtonUp(nFlags, point);
	CFrameWnd::OnLButtonUp(nFlags, point);
}
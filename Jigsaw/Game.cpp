#include "stdafx.h"
#include "Game.h"

Game::Game()
{
}


Game::~Game()
{
}

//设置输出窗口的句柄
void Game::SetHandle(HWND hWnd) {
	m_hWnd = hWnd;
}

//进入游戏帧
bool Game::EnterFrame(DWORD dwTime) {
	GameDraw();
	return false;
}

void Game::OnMouseMove(UINT nFlags, CPoint point) {	//处理鼠标移动事件
	if (gameStep) {
		m_gameRun.OnMouseMove(nFlags, point);
	}
	else {
		m_gameMenu.OnMouseMove(nFlags, point);
	}
}

void Game::OnLButtonUp(UINT nFlags, CPoint point) {	//处理左键抬起事件
	if (gameStep) {
		m_gameRun.OnLButtonUp(nFlags, point);
	}
	else {
		m_gameRun.randPicture();
		m_gameMenu.OnLButtonUp(nFlags, point);
	}
}

//游戏绘图
void Game::GameDraw() {
	//客户区大小
	HDC hdc = ::GetDC(m_hWnd);
	CRect rc;
	GetClientRect(m_hWnd, &rc);

	CDC *dc = CClientDC::FromHandle(hdc);

	CDC m_dcMemory;		//双缓冲绘图用
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(dc, rc.Width(), rc.Height());
	m_dcMemory.CreateCompatibleDC(dc);
	CBitmap *pOldBitmap = m_dcMemory.SelectObject(&bmp);

	Graphics gh(m_dcMemory.GetSafeHdc());	//构造对象
	gh.Clear(Color::White);					//清除背景
	gh.ResetClip();

	//画入内存
	if (!gameStep) {
		m_gameMenu.Draw(gh);
	}
	else {
		m_gameRun.Draw(gh);
	}
	DrawFps(gh);

	//复制到屏幕
	::BitBlt(hdc, 0, 0, rc.Width(), rc.Height(),
		m_dcMemory.GetSafeHdc(), 0, 0, SRCCOPY);
	dc->DeleteDC();		//释放
	return;
}

void Game::DrawFps(Graphics &gh) {
	static int fps = 0;				//定义静态变量，每次进入函数时保存上次的值
	m_fps++;						//记录已经画了多少帧
	static DWORD dwLast = GetTickCount();	//记录上次输出FPS的时间
	if (GetTickCount() - dwLast >= 1000) {	//判断时间是否超过1秒，如果超过，输出FPS
		fps = m_fps;
		m_fps = 0;	//清零，方便对帧进行重新记数
		dwLast = GetTickCount();//记录本次输出的时间
	}

	//输出FPS
	{
		//将FPS格式化到字符串
		CString s;
		s.Format(_T("FPS:%d"), fps);

		SolidBrush brush(Color(0xFF, 0x00, 0x00));	//创建红色画刷
		Gdiplus::Font font(_T("宋体"), 10.0);		//创建输出的字体

		CRect rc;
		::GetClientRect(m_hWnd, &rc);		//获得输出窗口的大小，用来定位文字的输出位置

		//在右上角显示
		PointF origin(static_cast<float>(rc.right - 50),
			static_cast<float>(rc.top + 2));

		gh.DrawString(s.GetString(), -1, &font, origin, &brush);	//输出文字
	}
}
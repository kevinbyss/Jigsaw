#pragma once

#include "GameMenu.h"
#include "GameRun.h"

class Game
{
public:
	Game();
	~Game();

	void SetHandle(HWND hWnd);			//设置输出窗口的句柄

	bool EnterFrame(DWORD dwTimer);		//进入游戏帧

	void OnMouseMove(UINT nFlags, CPoint point);	//处理鼠标移动事件

	void OnLButtonUp(UINT nFlags, CPoint point);	//处理左键抬起事件

	void GameDraw();
private:
	HWND m_hWnd;	//窗口

	int m_fps{ 0 }; //记录游戏每秒多少帧

	GameMenu m_gameMenu;
	GameRun m_gameRun;
private:
	//输出FPS
	void DrawFps(Graphics &gh);


};


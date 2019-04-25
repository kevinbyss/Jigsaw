#pragma once

#include "GameMenu.h"
#include "GameRun.h"

class Game
{
public:
	Game();
	~Game();

	void SetHandle(HWND hWnd);			//����������ڵľ��

	bool EnterFrame(DWORD dwTimer);		//������Ϸ֡

	void OnMouseMove(UINT nFlags, CPoint point);	//��������ƶ��¼�

	void OnLButtonUp(UINT nFlags, CPoint point);	//�������̧���¼�

	void GameDraw();
private:
	HWND m_hWnd;	//����

	int m_fps{ 0 }; //��¼��Ϸÿ�����֡

	GameMenu m_gameMenu;
	GameRun m_gameRun;
private:
	//���FPS
	void DrawFps(Graphics &gh);


};


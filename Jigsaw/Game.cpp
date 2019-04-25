#include "stdafx.h"
#include "Game.h"

Game::Game()
{
}


Game::~Game()
{
}

//����������ڵľ��
void Game::SetHandle(HWND hWnd) {
	m_hWnd = hWnd;
}

//������Ϸ֡
bool Game::EnterFrame(DWORD dwTime) {
	GameDraw();
	return false;
}

void Game::OnMouseMove(UINT nFlags, CPoint point) {	//��������ƶ��¼�
	if (gameStep) {
		m_gameRun.OnMouseMove(nFlags, point);
	}
	else {
		m_gameMenu.OnMouseMove(nFlags, point);
	}
}

void Game::OnLButtonUp(UINT nFlags, CPoint point) {	//�������̧���¼�
	if (gameStep) {
		m_gameRun.OnLButtonUp(nFlags, point);
	}
	else {
		m_gameRun.randPicture();
		m_gameMenu.OnLButtonUp(nFlags, point);
	}
}

//��Ϸ��ͼ
void Game::GameDraw() {
	//�ͻ�����С
	HDC hdc = ::GetDC(m_hWnd);
	CRect rc;
	GetClientRect(m_hWnd, &rc);

	CDC *dc = CClientDC::FromHandle(hdc);

	CDC m_dcMemory;		//˫�����ͼ��
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(dc, rc.Width(), rc.Height());
	m_dcMemory.CreateCompatibleDC(dc);
	CBitmap *pOldBitmap = m_dcMemory.SelectObject(&bmp);

	Graphics gh(m_dcMemory.GetSafeHdc());	//�������
	gh.Clear(Color::White);					//�������
	gh.ResetClip();

	//�����ڴ�
	if (!gameStep) {
		m_gameMenu.Draw(gh);
	}
	else {
		m_gameRun.Draw(gh);
	}
	DrawFps(gh);

	//���Ƶ���Ļ
	::BitBlt(hdc, 0, 0, rc.Width(), rc.Height(),
		m_dcMemory.GetSafeHdc(), 0, 0, SRCCOPY);
	dc->DeleteDC();		//�ͷ�
	return;
}

void Game::DrawFps(Graphics &gh) {
	static int fps = 0;				//���徲̬������ÿ�ν��뺯��ʱ�����ϴε�ֵ
	m_fps++;						//��¼�Ѿ����˶���֡
	static DWORD dwLast = GetTickCount();	//��¼�ϴ����FPS��ʱ��
	if (GetTickCount() - dwLast >= 1000) {	//�ж�ʱ���Ƿ񳬹�1�룬������������FPS
		fps = m_fps;
		m_fps = 0;	//���㣬�����֡�������¼���
		dwLast = GetTickCount();//��¼���������ʱ��
	}

	//���FPS
	{
		//��FPS��ʽ�����ַ���
		CString s;
		s.Format(_T("FPS:%d"), fps);

		SolidBrush brush(Color(0xFF, 0x00, 0x00));	//������ɫ��ˢ
		Gdiplus::Font font(_T("����"), 10.0);		//�������������

		CRect rc;
		::GetClientRect(m_hWnd, &rc);		//���������ڵĴ�С��������λ���ֵ����λ��

		//�����Ͻ���ʾ
		PointF origin(static_cast<float>(rc.right - 50),
			static_cast<float>(rc.top + 2));

		gh.DrawString(s.GetString(), -1, &font, origin, &brush);	//�������
	}
}
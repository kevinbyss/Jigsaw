#include "stdafx.h"
#include "GameMenu.h"


GameMenu::GameMenu()
{
	background = Image::FromFile(_T("./img/background.png"));
	for (int i = 0; i < 4; i++) {		//初始化图片和位置
		TCHAR path[MAX_PATH];
		_stprintf_s(path, _T("./img/Menu_%d.png"), i);
		menuImage[i] = Image::FromFile(path);
		if (i == 0 || i == 1) { menuRect[i] = RectF((REAL)((GAME_WIN_W - 230) / 2), (REAL)((GAME_WIN_H - 50) / 2), 200, 50); }
		if (i == 2 || i == 3) { menuRect[i] = RectF((REAL)((GAME_WIN_W - 230) / 2), (REAL)((GAME_WIN_H - 50) / 2) + 70, 200, 50); }
	}
	mouseMove[0] = false;
	mouseMove[1] = false;
}


GameMenu::~GameMenu()
{
}

void GameMenu::Draw(Graphics &gh) {	//绘制背景和菜单
	gh.DrawImage(background, 0, 0, GAME_WIN_W, GAME_WIN_H);
	if (mouseMove[0]) {
		gh.DrawImage(menuImage[1], menuRect[1]);
	}
	else {
		gh.DrawImage(menuImage[0], menuRect[0]);
	}
	if (mouseMove[1]) {
		gh.DrawImage(menuImage[3], menuRect[3]);
	}
	else {
		gh.DrawImage(menuImage[2], menuRect[2]);
	}
}
void GameMenu::OnMouseMove(UINT nFlags, CPoint point) {	//处理鼠标移动事件
	PointF pt(static_cast<float>(point.x), static_cast<float>(point.y));
	if (menuRect[0].Contains(pt)) {
		mouseMove[0] = true;
	}
	else {
		mouseMove[0] = false;
	}
	if (menuRect[2].Contains(pt)) {
		mouseMove[1] = true;
	}
	else {
		mouseMove[1] = false;
	}
}

void GameMenu::OnLButtonUp(UINT nFlags, CPoint point) {	//处理左键抬起事件
	PointF pt(static_cast<float>(point.x), static_cast<float>(point.y));
	if (!gameStep) {
		if (menuRect[0].Contains(pt)) {
			gameStep = true;
		}
		if (menuRect[2].Contains(pt)) {
			exit(0);
		}
	}
}
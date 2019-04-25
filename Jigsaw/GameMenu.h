#pragma once
class GameMenu
{
public:
	GameMenu();
	~GameMenu();

public:
	void Draw(Graphics &gh);	//绘制背景和菜单

	void OnMouseMove(UINT nFlags, CPoint point);	//处理鼠标移动事件

	void OnLButtonUp(UINT nFlags, CPoint point);	//处理左键抬起事件

private:
	Image *menuImage[4];
	Image *background;
	RectF menuRect[4];
	bool mouseMove[2];
};


#pragma once
class GameRun
{
public:
	GameRun();
	~GameRun();

public:
	void Draw(Graphics &gh);	//绘制背景和图片

	void OnMouseMove(UINT nFlags, CPoint point);	//处理鼠标移动事件

	void OnLButtonUp(UINT nFlags, CPoint point);	//处理左键抬起事件

	void changePic(Point target1, Point target2);		//交换两个图片的所有信息

	bool GameWin();		//游戏判断结束并处理

	void randPicture();		//将图片随机排序
private:
	Image *picture[3][3];
	RectF picRect[3][3];
	bool inPicture[3][3];
	bool isEmpty[3][3];
	int picIndex[3][3];
	Image *run_back;
	Image *frame;
	Image *returnMenu1;
	Image *returnMenu2;
	Image *masterPic;
	bool inReturnMenu;
};


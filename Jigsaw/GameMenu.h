#pragma once
class GameMenu
{
public:
	GameMenu();
	~GameMenu();

public:
	void Draw(Graphics &gh);	//���Ʊ����Ͳ˵�

	void OnMouseMove(UINT nFlags, CPoint point);	//��������ƶ��¼�

	void OnLButtonUp(UINT nFlags, CPoint point);	//�������̧���¼�

private:
	Image *menuImage[4];
	Image *background;
	RectF menuRect[4];
	bool mouseMove[2];
};


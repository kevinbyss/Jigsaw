#pragma once
class GameRun
{
public:
	GameRun();
	~GameRun();

public:
	void Draw(Graphics &gh);	//���Ʊ�����ͼƬ

	void OnMouseMove(UINT nFlags, CPoint point);	//��������ƶ��¼�

	void OnLButtonUp(UINT nFlags, CPoint point);	//�������̧���¼�

	void changePic(Point target1, Point target2);		//��������ͼƬ��������Ϣ

	bool GameWin();		//��Ϸ�жϽ���������

	void randPicture();		//��ͼƬ�������
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


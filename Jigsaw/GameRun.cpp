#include "stdafx.h"
#include "GameRun.h"


GameRun::GameRun()
{
	frame = Image::FromFile(_T("./img/frame.png"));
	Image *imgPtr = Image::FromFile(_T("./img/picture.png"));
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			Bitmap *tempMap = new Bitmap(132, 132);	//创建可供绘制的位图
			Graphics *tempgh = Graphics::FromImage(tempMap);		//构造绘制对象
			if (!(i == 2 && j == 2)) {
				tempgh->DrawImage(imgPtr, 0, 0, (i * 132), (j * 132), 132, 132, Unit::UnitPixel);		//将图片裁剪绘制于内存
				isEmpty[i][j] = false;
			}
			else {
				isEmpty[i][j] = true;
			}
			picture[i][j] = tempMap;
			picRect[i][j] = RectF((i * 132) + 77, (j * 132) + 65, 132, 132);
			inPicture[i][j] = false;
			picIndex[i][j] = i * 10 + j;
		}
	}
	randPicture();
	inPicture[0][0] = true;
	run_back = Image::FromFile(_T("./img/run_back.png"));
	returnMenu1 = Image::FromFile(_T("./img/return_0.png"));
	returnMenu2 = Image::FromFile(_T("./img/return_1.png"));
	masterPic = Image::FromFile(_T("./img/picture.png"));
	inReturnMenu = false;
}


GameRun::~GameRun()
{
}

void GameRun::Draw(Graphics &gh) {	//绘制背景和图片
	gh.DrawImage(run_back, 0, 0, GAME_WIN_W, GAME_WIN_H);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			gh.DrawImage(picture[i][j], picRect[i][j]);
			if (inPicture[i][j]) {
				gh.DrawImage(frame, picRect[i][j]);
			}
		}
	}
	RectF rcReturn(520, 400, 200, 50);
	if (inReturnMenu) {
		gh.DrawImage(returnMenu2, rcReturn);
	}
	else {
		gh.DrawImage(returnMenu1, rcReturn);
	}
	RectF rcMasterPic(520, 100, 200, 200);
	gh.DrawImage(masterPic, rcMasterPic);
}

void GameRun::OnMouseMove(UINT nFlags, CPoint point) {	//处理鼠标移动事件
	PointF pt(static_cast<float>(point.x), static_cast<float>(point.y));
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (picRect[i][j].Contains(pt)) {
				inPicture[i][j] = true;
			}
			else {
				inPicture[i][j] = false;
			}
		}
	}
	RectF rcReturn(520, 400, 200, 50);
	if (rcReturn.Contains(pt)) {
		inReturnMenu = true;
	}
	else {
		inReturnMenu = false;
	}
}

void GameRun::OnLButtonUp(UINT nFlags, CPoint point) {	//处理左键抬起事件
	PointF pt(static_cast<float>(point.x), static_cast<float>(point.y));
	Point target1, target2;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (picRect[i][j].Contains(pt)) {
				target1.X = i;
				target1.Y = j;
				switch (i * 10 + j)
				{
				case 0:
					if (isEmpty[1][0]) {
						target2.X = 1;
						target2.Y = 0;
						changePic(target1, target2);
					}
					if (isEmpty[0][1]) {
						target2.X = 0;
						target2.Y = 1;
						changePic(target1, target2);
					}
					break;
				case 10:
					if (isEmpty[0][0]) {
						target2.X = 0;
						target2.Y = 0;
						changePic(target1, target2);
					}
					if (isEmpty[2][0]) {
						target2.X = 2;
						target2.Y = 0;
						changePic(target1, target2);
					}
					if (isEmpty[1][1]) {
						target2.X = 1;
						target2.Y = 1;
						changePic(target1, target2);
					}
					break;
				case 20:
					if (isEmpty[1][0]) {
						target2.X = 1;
						target2.Y = 0;
						changePic(target1, target2);
					}
					if (isEmpty[2][1]) {
						target2.X = 2;
						target2.Y = 1;
						changePic(target1, target2);
					}
					break;
				case 1:
					if (isEmpty[0][0]) {
						target2.X = 0;
						target2.Y = 0;
						changePic(target1, target2);
					}
					if (isEmpty[1][1]) {
						target2.X = 1;
						target2.Y = 1;
						changePic(target1, target2);
					}
					if (isEmpty[0][2]) {
						target2.X = 0;
						target2.Y = 2;
						changePic(target1, target2);
					}
					break;
				case 11:
					if (isEmpty[1][0]) {
						target2.X = 1;
						target2.Y = 0;
						changePic(target1, target2);
					}
					if (isEmpty[0][1]) {
						target2.X = 0;
						target2.Y = 1;
						changePic(target1, target2);
					}
					if (isEmpty[2][1]) {
						target2.X = 2;
						target2.Y = 1;
						changePic(target1, target2);
					}
					if (isEmpty[1][2]) {
						target2.X = 1;
						target2.Y = 2;
						changePic(target1, target2);
					}
					break;
				case 21:
					if (isEmpty[2][0]) {
						target2.X = 2;
						target2.Y = 0;
						changePic(target1, target2);
					}
					if (isEmpty[1][1]) {
						target2.X = 1;
						target2.Y = 1;
						changePic(target1, target2);
					}
					if (isEmpty[2][2]) {
						target2.X = 2;
						target2.Y = 2;
						changePic(target1, target2);
					}
					break;
				case 2:
					if (isEmpty[0][1]) {
						target2.X = 0;
						target2.Y = 1;
						changePic(target1, target2);
					}
					if (isEmpty[1][2]) {
						target2.X = 1;
						target2.Y = 2;
						changePic(target1, target2);
					}
					break;
				case 12:
					if (isEmpty[0][2]) {
						target2.X = 0;
						target2.Y = 2;
						changePic(target1, target2);
					}
					if (isEmpty[1][1]) {
						target2.X = 1;
						target2.Y = 1;
						changePic(target1, target2);
					}
					if (isEmpty[2][2]) {
						target2.X = 2;
						target2.Y = 2;
						changePic(target1, target2);
					}
					break;
				case 22:
					if (isEmpty[2][1]) {
						target2.X = 2;
						target2.Y = 1;
						changePic(target1, target2);
					}
					if (isEmpty[1][2]) {
						target2.X = 1;
						target2.Y = 2;
						changePic(target1, target2);
					}
					break;
				default:
					break;
				}
			}
		}
	}
	RectF rcReturn(520, 400, 200, 50);
	if (rcReturn.Contains(pt)) {
		gameStep = false;
	}
	if (GameWin() && nFlags != 10000) {
		AfxMessageBox(_T("恭喜！拼图完成！"));
		gameStep = false;
	}
}

void GameRun::changePic(Point target1, Point target2) {
	Image *tempImage = picture[target1.X][target1.Y];
	picture[target1.X][target1.Y] = picture[target2.X][target2.Y];
	picture[target2.X][target2.Y] = tempImage;
	int tempIndex = picIndex[target1.X][target1.Y];
	picIndex[target1.X][target1.Y] = picIndex[target2.X][target2.Y];
	picIndex[target2.X][target2.Y] = tempIndex;
	bool tempBool = isEmpty[target1.X][target1.Y];
	isEmpty[target1.X][target1.Y] = isEmpty[target2.X][target2.Y];
	isEmpty[target2.X][target2.Y] = tempBool;
}

bool GameRun::GameWin() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (picIndex[i][j] != i * 10 + j) return false;
		}
	}
	return true;
}

void GameRun::randPicture() {
	srand(GetTickCount());
	/* 此方法随机结果有约1/2的几率出现无法还原的排序
	Point target1, target2;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			target1.X = i;
			target1.Y = j;
			target2.X = rand() % 3;
			target2.Y = rand() % 3;
			changePic(target1, target2);
		}
	}*/
	CPoint clickPoint[9];
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			clickPoint[i * 3 + j].x = picRect[i][j].X + 10;
			clickPoint[i * 3 + j].y = picRect[i][j].Y + 10;
		}
	}
	UINT temp = 10000;
	for (int times = 0; times < 500; times++) {
		int clickN = rand() % 9;
		OnLButtonUp(temp, clickPoint[clickN]);
	}
}
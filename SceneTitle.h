#pragma once

#include "DxLib.h"
#include "vector.h"
#include "singleton.h"
#include "scene.h"

class title :public singleton<title>, public BaseScene
{
public:
	int backGh, darkGh, lanthanumGh, playerGh, stringGh, fireGh, textWindowGh;
	vector2 bPos1, bPos2;//背景の位置
	vector2 pPos, lPos, fPos;//プレイヤー、ランタン、炎の位置
	vector2 triPos;//三角形画像の位置
	int animCnt,questionState,select;
	float speed;
	bool startFlg, soundFlg;
	char questionFlg;
	static int triangleGh;
	static int buttonSe;
	title();
	void Init();
	void unInit() {};
	void Update();
	void Draw();
	void Debug() ;

	//void initTitle();
	//void drawTitle();
	//void updateTitle();
	void pushStartButton();
	void changeSpeed();
	void question();
};

void questionSelect(TCHAR *FormatString1, ...);
int questionCheckButton();
extern int yourColor;
extern bool tutorialFlg;

//タイトルのインスタンスのポインタを返す
#define pTitleInstance (title::getInstance())
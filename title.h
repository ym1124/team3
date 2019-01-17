#pragma once
#include "DxLib.h"
#include "vector.h"
#include "singleton.h"
#include "scene.h"

class title:public singleton<title>
{
public:
	int backGh, darkGh,lanthanumGh,playerGh,stringGh,fireGh;
	vector2 bPos1, bPos2;//背景の位置
	vector2 pPos, lPos, fPos;//プレイヤー、ランタン、炎の位置
	int animCnt;
	bool startFlg;
	title();
	void initTitle();
	void drawTitle();
	void updateTitle();
	void pushStartButton();
};

//タイトルのインスタンスのポインタを返す
#define pTitleInstance (title::getInstance())
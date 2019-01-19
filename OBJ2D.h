#pragma once
#include "DxLib.h"
#include "common.h"
#include "vector.h"

#include "light.h"

class OBJ2D;
typedef void(*MOVER)(OBJ2D *obj);

class animator
{
public:
	vector2 pos;
	int texture;
	int animCnt;
	int sheetsNum;
	int speed;
	int srcX;
	int srcY;
	int sizeX;
	int sizeY;
	animator();
	//描画関数
	//アニメーション枚数、描画フレーム数、画像の切り取り位置x、画像の切り取り位置y、アニメーション画像の幅、アニメーション画像の高さ
	virtual void setTextureInfo(int sheetsNum = 1, int speed = 1, int srcX = 0, int srcY = 0, int sizeX = 0, int sizeY = 0);
	virtual void draw(bool animationFlg = false);
};

class OBJ2D:public animator
{
public:
	OBJ2D();
	void clear();
	MOVER mover;
	virtual void update();
	virtual void setObject(vector2 pos)=0;
};


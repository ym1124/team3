#pragma once
#include "DxLib.h"
#include "vector.h"

#define LIGHT_MARGINE_X 60
#define LIGHT_MARGINE_Y 55

class torch
{
public:
	vector2 pos;
	int torchAnimCnt;
	bool isAlive;
	static int torchGh;
	torch(vector2 pos);
	void drawTorch();
	void setTorch();
	void updateTorch();
};

class torchLight//トーチに灯すlight
{
public:
	vector2 pos;
	vector2 sway;
	//トーチ自身の番号
	int number;
	bool isAlive;
	torch *t;
	//全体の合計本数
	static int sum;
	static int lightGh;
	static bool setFlg;
	//引数付きコンストラクタで対象の松明を規定
	torchLight(torch *t);
	void initLight();
	void moveLight();
	void drawLight();
	void updateLight();
	void swayLight();
};

torchLight* getLightPointertes(int num);

//template <typename T>
//void setLight(T temp, light *lig)
#pragma once
#include "DxLib.h"
#include "common.h"
#include "Player.h"
#include "vector.h"
#include "YSDBG.h"

#define LIGHT_MARGINE_X 60
#define LIGHT_MARGINE_Y 55

class torch
{
public:
	vector2 pos;
	int number;
	int torchAnimCnt;
	bool isAlive;
	static int fireGh,torchGh;
	static int sumNumber;
	torch(vector2 pos);
	void drawTorch();
	void drawTorchAll();
	virtual void setTorch();
	void updateTorch();
	void hitCheck();
};

class lanthanum
{
public:
	vector2 pos;
	int number;
	int lanthanumAnimCnt;
	bool isAlive;
	static int fireGh, lanthanumGh;
	static int sumNumber;
	lanthanum(/*vector2 pos*/);
	void drawLanthanum();
	void drawLanthanumAll();
	void moveLanthanum();
	void updateLanthanum();
};

extern lanthanum lanthanum1;

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
	virtual void moveLight();
	virtual void drawLight();
	void updateLight();
	void swayLight();
};

class playerLight :public torchLight
{
public:
	int lanthanumGh;
	lanthanum* l;
	playerLight();
	void moveLight();
	void drawLight();
};

//template <typename T>
//void setLight(T temp, light *lig)

void moveLightTes();
playerLight* getPlTorchPointerTes();
torchLight* getLightPointertes(int num);
void updateAllTorchLight();
void drawAlltorch();
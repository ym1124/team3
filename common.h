#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <time.h>
#include <math.h>
#include <memory>
#include <vector>
#include <algorithm>


#define PI	(3.141592f)

//--------------------------------
//	定数
//--------------------------------
#define SCREEN_WIDTH (1280)
#define SCREEN_HEIGHT (720)


struct Color
{
	unsigned int White;
	unsigned int Black;
	unsigned int Red;
	unsigned int Green;
	unsigned int Blue;
	unsigned int Yellow;

	Color();
};

extern Color color;
extern bool gameexit;
extern int framerate;
extern bool debugFlg;

void InputKey();
void InputJoypad();
void InputAllKey();
int checkHiddenCommand();
double ToRadian(double deg);

//--------------------------------
//	マクロ関数
//--------------------------------

/* ==========  入力関係（トリガー）  ========== */
// キー入力
extern int key[256]; // 0:入力されていない 1:入力された瞬間 2:入力されている
extern int keyall;
extern int PAD1;
extern bool slow_flg;

/* ==========  角度変換用  ========== */
//#define ToRadian(x) FromDgreeToRadian(x)
#define ToDegree(x) XMConvertToDegrees(x)


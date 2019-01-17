////////////////////////////////////////////////////////
//
//			BG.cpp	マップチップ(Dxライブラリ版)
//
////////////////////////////////////////////////////////
/*	実装の仕方(19/01/12記)
※要インクルード DxLib.h
YSDBG.h をインクルードする。
bg.init();//毎フレーム、ダメ
bg.update();
bg.draw(); 置く。

場合によっては変数名を変えます
*/


//UnresoledMergeConflict
#pragma once
#include"DxLib.h"
#include "YSDBG.h"
#include "common.h"
#include "vector.h"
#include <assert.h>
////////////////////////
//	定数
////////////////////////
#define SCALE_BG (1.0f)//チップのスケール
#define SCALE_BG_X SCALE_BG
#define SCALE_BG_Y SCALE_BG
//TODO スクリーンのサイズ確認
//#define SCREEN_WIDTH (600)
//#define SCREEN_HEIGHT (400)

const  vector2 WORLD_SIZE = vector2(CHIP_SIZE*SCALE_BG_X*CHIP_NUMX, CHIP_SIZE*SCALE_BG_Y*CHIP_NUMY);
const  vector2 WINDOW_SIZE = vector2(SCREEN_WIDTH, SCREEN_HEIGHT);
const vector2 BG_SCALE(SCALE_BG_X, SCALE_BG_Y);
////////////////////////
//	変数(実体)
////////////////////////
//BGsystem bg;
int chipHandle[CHIP_NUMX*CHIP_NUMY];

vector2 camera_pos;	//world座標			//実際に画面に描画されるやつのあれ
vector2 world_pos;	//not				//ステージ全体に於けるポジション
vector2 screen_pos;	//not				//画面上のポジション
bool suitti = true;	//debug

bool kb_Z, kbPrev_Z;
////////////////////////
//	プロトタイプ宣言
////////////////////////
//debug
bool Suittingu(bool &suitti);
void Draw_Zephyranthes(int chipindex, int i, int j);
void Draw_Physalis(int chipindex, int i, int j, vector2 scale);
void DrawModiGraph_WrapedScale(const vector2 &pos, const vector2 &scale, const int &grHandle, const int &TransFlag);
void CameraMove();
//////////////////////////////////////////////////////////////////
#define $	(51)

int chip_data[CHIP_NUMX][CHIP_NUMY] =
{
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0,0,0,0,0,0,0,0},//64*64
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,1,2,3,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,1,2,3,0,0,1,2,3,0,0,0 },
	{ 1,2,2,2,2,2,2,2,2,2,2,3,0,0,0},
	{ 0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0 },
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
	{0},
};
#undef $

//int chip_data2[CHIP_NUMX][CHIP_NUMY] =
//{
//{	 1, 2, 3, 4, 5, 6, 7, 8, 9,10},
//{	11,12,13,14,15,16,17,18,19,20},
//{	21,22,23,24,25,26,27,28,29,30},
//{	31,32,33,34,35,36,37,38,39,40},
//{	41,42,43,44,45,46,47,48,49,50},
//{	51,52,53,54,55,56,57,58,59,60},
//{	61,62,63,64,65,66,67,68,69,70},
//{	71,72,73,74,75,76,77,78,79,80},
//{	81,82,83,84,85,86,87,88,89,90},
//{	91,92,93,94,95,96,97,98,99,100},
//};

///////////////////////////////////////////////////////////////

///////////////////////////////////////
//
//		初期化するところ
//
///////////////////////////////////////
void BGsystem::init()
{
	camera_pos = vector2(0.0f, 0.0f);
	LoadDivGraph("resource/image/mapchip.png",
		CHIP_NUMX*CHIP_NUMY, CHIP_DIV_X, CHIP_DIV_Y, CHIP_SIZE, CHIP_SIZE, chipHandle);

	for (auto &it : chipHandle)
	{
		if (it == -1)
			assert("チップハンドル-1");
	}

}
///////////////////////////////////////
//
//		更新するところ
//
///////////////////////////////////////

void BGsystem::update()
{
	kb_Z = CheckHitKey(KEY_INPUT_Z);//今フレームの入力状態を確認




	//DEBUG////
	if (kb_Z && !kbPrev_Z)
		Suittingu(suitti);
	///////////
	CameraMove();

	//DEBUG
	if (CheckHitKey(KEY_INPUT_ESCAPE))
		exit(true);

	kbPrev_Z = kb_Z;//前フレームの入力状態を更新
}

///////////////////////////////////////
//
//		描画するところ
//
///////////////////////////////////////
void BGsystem::draw()
{
	static int backGh = LoadGraph("resource/image/gameBack.png", false);
	DrawGraph(0, 0, backGh, true);
	for (int i = 0; i < 20; i++)//y
	{
		for (int j = 0; j < 20; j++)//x
		{
			int chipIndex;//チップインなんとかさん
			chipIndex = chip_data[i][j];

			//描画関数
			if (chipHandle[i*CHIP_NUMY + j] == -1)
				exit(false);

			Draw_Physalis(chipIndex, i, j, BG_SCALE);
			//if (suitti)
			//	Draw_Zephyranthes(chipIndex, i, j);//初期
				//else

		}//_for
	}//_for
}





///////////////////////////////////////
//
//		その他するところ
//
///////////////////////////////////////
//カメラの移動関数
void CameraMove()
{


	//以下カメラに関する///////////////////////
	//カメラ操作
	{
		if (CheckHitKey(KEY_INPUT_W))
			camera_pos.y -= 2;
		if (CheckHitKey(KEY_INPUT_S))
			camera_pos.y += 2;
		if (CheckHitKey(KEY_INPUT_A))
			camera_pos.x -= 2;
		if (CheckHitKey(KEY_INPUT_D))
			camera_pos.x += 2;
	}


	//カメラの移動制限
	{
		if (camera_pos.x < 0)
			camera_pos.x = 0;
		if (camera_pos.x > WORLD_SIZE.x - WINDOW_SIZE.x)
			camera_pos.x = WORLD_SIZE.x - WINDOW_SIZE.x;
		if (camera_pos.y < 0)
			camera_pos.y = 0;
		if (camera_pos.y > WORLD_SIZE.y - WINDOW_SIZE.y)
			camera_pos.y = WORLD_SIZE.y - WINDOW_SIZE.y;
	}

	///////////////////////////////////////
}

//DEBUG
//スイッチング関数(Z)
bool Suittingu(bool &suitti)//スイッチング作用をする関数
{
	switch (suitti)
	{
	case true:
		suitti = false;
		return false;
		break;

	case false:
		suitti = true;
		return true;
		break;
	}

}

//マップチップの描画_試作1号機(ゼフィランサス)
void Draw_Zephyranthes(int chipindex, int i, int j)
{
	int tempHandle = chipHandle[chipindex];
	DrawGraph(64 * j - camera_pos.x, 64 * i - camera_pos.y, tempHandle, false);
}

//マップチップの描画_試作2号機(サイサリス)
void Draw_Physalis(int chipindex, int i, int j, vector2 scale)
{
	//int tempHandle = chipHandle[chipindex];
	DrawModiGraph_WrapedScale(vector2(CHIP_SIZE*scale.x * j - camera_pos.x, CHIP_SIZE*scale.y * i - camera_pos.y), scale, chipHandle[chipindex], TRUE);
}


//DrawModiGraph関数のラップ関数//スケールによる拡大縮小ができるダケ。あとvector2に対応

//pos=描画する基点（左上）, scale , あとは一緒
void DrawModiGraph_WrapedScale(const vector2 &pos, const vector2 &scale, const int &grHandle, const int &TransFlag)
{
	//2,3,4 //R=right,L=left,T=top,B=bottom
	vector2 posRT = vector2(pos.x + (CHIP_SIZE*scale.x), pos.y);
	vector2 posRB = vector2(pos.x + (CHIP_SIZE*scale.x), pos.y + (CHIP_SIZE*scale.y));
	vector2 posLB = vector2(pos.x, pos.y + (CHIP_SIZE*scale.y));

	DrawModiGraph(static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(posRT.x), static_cast<int>(posRT.y),
		static_cast<int>(posRB.x), static_cast<int>(posRB.y), static_cast<int>(posLB.x), static_cast<int>(posLB.y), grHandle, TransFlag);
}






;;;;;;;;;
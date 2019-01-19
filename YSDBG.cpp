//////////////////////////////////////////////////////////
////
////			BG.cpp	マップチップ(Dxライブラリ版)
////
//////////////////////////////////////////////////////////
///*	実装の仕方(19/01/12記)
//※要インクルード DxLib.h
//YSDBG.h をインクルードする。
//bg.init();//毎フレーム、ダメ
//bg.update();
//bg.draw(); 置く。
//
//場合によっては変数名を変えます
//*/


//UnresoledMergeConflict
#include"DxLib.h"
#include "YSDBG.h"
#include "common.h"
#include "vector.h"
#include <assert.h>
////////////////////////
//	定数
////////////////////////
//画像シリーズ
#define SCALE_BG (1.0f)//チップのスケール
#define SCALE_BG_X SCALE_BG
#define SCALE_BG_Y SCALE_BG

const vector2 WORLD_SIZE = vector2(CHIP_SIZE*SCALE_BG_X*CHIP_NUMX, CHIP_SIZE*SCALE_BG_Y*CHIP_NUMY);//描画するワールドのサイズ
const vector2 WINDOW_SIZE = vector2(SCREEN_WIDTH, SCREEN_HEIGHT);//ウィンドウサイズ
const vector2 BG_SCALE(SCALE_BG_X, SCALE_BG_Y);//スケール
const vector2 CHIPS_SIZE(CHIP_SIZE_X, CHIP_SIZE_Y);//画像サイズ
												   ////////////////////////
												   //	変数(実体)
												   ////////////////////////
												   //BGsystem bg;//実体
int chipHandle[CHIP_DIV_X*CHIP_DIV_Y];//画像を収めるハンドル

vector2 camera_pos;	//world座標			//実際に画面に描画されるやつのあれ
					//vector2 world_pos;	//not				//ステージ全体に於けるポジション
					//vector2 screen_pos;	//not				//画面上のポジション

					//DEBUG suitti Z
bool suitti = true;
bool kb_Z, kbPrev_Z;
bool kb_Spc, kbPrev_Spc;

////////////////////////
//	プロトタイプ宣言
////////////////////////
//DEBUG
bool Suittingu(bool &suitti);

void Draw_Zephyranthes(int chipindex, int i, int j);
void Draw_Physalis(int chipindex, int i, int j, vector2 scale);
void DrawModiGraph_WrapedScale(const vector2 &pos, const vector2 &scale, const int &grHandle, const int &TransFlag);
void DrawModiGraph_Wraped(const vector2 &pos, const vector2 &size, const vector2 &scale, const int &grHandle, const int &TransFlag);
//////////////////////////////////////////////////////////////////
//プログラムで読むやつ
int  chipData[CHIP_NUMY][CHIP_NUMX] = { 0 };
//ステージデータ

#define $	(51)

int chip_data[CHIP_NUMY][CHIP_NUMX] =
{
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0,0,0,0,0,0,0,0 },//64*64
	{ 0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,1,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,1,2,3,0,0,1,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 1,2,2,2,2,2,2,2,2,2,2,3,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0 },
	{ 0 },
	{ 0 },
	{ 0 },
	{ 0 },
	{ 0 },
	{ 0 },
	{ 0 },
};
#undef $

static int chip_data0[CHIP_NUMY][CHIP_NUMX] =
{
	{ 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11 },
	{ 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11 },
	{ 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11 },
	{ 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11 },
	{ 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11 },
	{ 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11 },
	{ 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11 },
	{ 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11 },
	{ 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11 },
	{ 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11 },
	{ 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11 },
	{ 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11 },
	{ 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11 },
	{ 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11 },
	{ 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11 },
	{ 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11 },
	{ 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11 },
	{ 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11 },
	{ 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11 },
	{ 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11 },
};
static int chip_data1[CHIP_NUMY][CHIP_NUMX] =
{
	{ 20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20 },
	{ 20,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,20 },
	{ 20,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,20 },
	{ 20,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,20 },
	{ 20,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,20 },
	{ 20,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,20 },
	{ 20,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,20 },
	{ 20,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,20 },
	{ 20,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,20 },
	{ 20,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,20 },
	{ 20,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,20 },
	{ 20,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,20 },
	{ 20,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,20 },
	{ 20,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,20 },
	{ 20,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,20 },
	{ 20,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,20 },
	{ 20,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,20 },
	{ 20,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,20 },
	{ 20,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,75,20 },
	{ 20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20 },
};

//データの入れ物
int *chipData_Box[] = { &chip_data0[0][0] , &chip_data1[0][0], };
///////////////////////////////////////////////////////////////

///////////////////////////////////////
//
//		初期化するところ
//
///////////////////////////////////////
void BGsystem::init()
{
	static bool initSW = false;
	//一回だけ
	if (!initSW)
	{
		camera_pos = vector2(0.0f, 0.0f);
		LoadDivGraph("resource/image/mapchip.png",
			CHIP_DIV_X*CHIP_DIV_Y, CHIP_DIV_X, CHIP_DIV_Y, CHIP_SIZE_X, CHIP_SIZE_Y, chipHandle);
		//ハンドル検査
		for (auto &it : chipHandle)
		{
			if (it == -1)
				assert("チップハンドル-1");
		}
		initSW = true;

		//TODO chipData
		//最初のステージのチップデータ
		//int *tempChip_data = 0;
		//tempChip_data= chipData_Box[0];
		for (int i = 0; i < CHIP_NUMY; i++)
		{
			std::memmove(chipData[i], chip_data[i], CHIP_NUMX * sizeof(int));
		}
	}
}
///////////////////////////////////////
//
//		更新するところ
//
///////////////////////////////////////
int camera_ChipPosX, camera_ChipPosY;
const int WINDOW_SIZE_CHIP_X = SCREEN_WIDTH / (CHIP_SIZE_X * SCALE_BG_X);
const int WINDOW_SIZE_CHIP_Y = SCREEN_HEIGHT / (CHIP_SIZE_Y * SCALE_BG_Y);

void BGsystem::update()
{
	//DEBUG keyinput
	//kb_Z = CheckHitKey(KEY_INPUT_Z);//今フレームの入力状態を確認
	//kb_Spc = CheckHitKey(KEY_INPUT_SPACE);
	//DEBUG Zスイッチ
	//if (kb_Z && !kbPrev_Z)
	//	Suittingu(suitti);

	///////////
	camera_ChipPosX = camera_pos.x / (CHIP_SIZE_X * SCALE_BG_X);
	camera_ChipPosY = camera_pos.y / (CHIP_SIZE_Y * SCALE_BG_Y);

	//DEBUG 強制終了処理
	//if (CheckHitKey(KEY_INPUT_ESCAPE))
	//{
	//	exit(true);
	//}

	//DEBUG 文字をだすところ
	//clsDx();
	//printfDx("campos(x:%.1f,y%.1f)\n", camera_pos.x, camera_pos.y);

	//DEBUG keyinput//前フレームの入力状態を更新
	//kbPrev_Z = kb_Z;
	//kbPrev_Spc = kb_Spc;
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
	DrawGraph(1280, 0, backGh, true);
	DrawGraph(2560, 0, backGh, true);
	for (int i = 0; i < 20; i++)//y
	{
		for (int j = 0; j < 20; j++)//x
		{
			int chipIndex;//チップインなんとかさん
			chipIndex = chip_data[i][j];

			//描画関数
			Draw_Physalis(chipIndex, i, j, BG_SCALE);
		}//_for
	}//_for

}


///////////////////////////////////////
//
//		その他するところ
//
///////////////////////////////////////
vector2 Convert_WorldToWindow(vector2 &pos)
{
	return vector2(pos.x - camera_pos.x, pos.y - camera_pos.y);
}


//チップハンドル内の画像を全消去します.
void BGsystem::RereaseChipHandle()
{
	for (auto &it : chipHandle)
	{
		DeleteGraph(it);
	}
}



//カメラの移動関数
void CameraMove(vector2 plpos)
{
	vector2 plposPrev = plpos;
	vector2 posGap;

	////DEBUG カメラ
	//const static int CAM_SPEED = 2;
	//int bairitu;
	//{
	//	if (CheckHitKey(KEY_INPUT_LSHIFT))bairitu = 4;
	//	else bairitu = 1;

	//	if (CheckHitKey(KEY_INPUT_W))
	//		camera_pos.y -= CAM_SPEED*bairitu;
	//	if (CheckHitKey(KEY_INPUT_S))
	//		camera_pos.y += CAM_SPEED*bairitu;
	//	if (CheckHitKey(KEY_INPUT_A))
	//		camera_pos.x -= CAM_SPEED*bairitu;
	//	if (CheckHitKey(KEY_INPUT_D))
	//		camera_pos.x += CAM_SPEED*bairitu;
	//}

	vector2 wndPos = Convert_WorldToWindow(plpos);
	const static vector2 SCREEN_MERGIN(128 * 2, 72 * 2);
	//{
	//	//誤差を計算
	//	posGap.x = wndPos.x - posGap.x;
	//	posGap.y = wndPos.y - posGap.y;

	//	camera_pos += posGap;
	//}


	//カメラの移動
	{
		if (wndPos.x <  0 + SCREEN_MERGIN.x)
		{
			camera_pos.x -= (0 + SCREEN_MERGIN.x) - wndPos.x;
		}
		if (WINDOW_SIZE.x - SCREEN_MERGIN.x < wndPos.x)
		{
			camera_pos.x += wndPos.x - WINDOW_SIZE.x + SCREEN_MERGIN.x;
		}

		if (wndPos.y < (0 + SCREEN_MERGIN.y))
		{
			camera_pos.y -= wndPos.y + (0 + SCREEN_MERGIN.y);
		}
		if (WINDOW_SIZE.y - (SCREEN_MERGIN.y) < wndPos.y)
		{
			camera_pos.y += wndPos.y - (WINDOW_SIZE.y - SCREEN_MERGIN.y);
		}

	}


	//DEBUG 文字をだすところ
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
	clsDx();
	printfDx("campos(x:%.1f,y%.1f)\n", camera_pos.x, camera_pos.y);
	///////////////////////////////////////
	plposPrev = plpos;//前フレームの位置をコピー
}

//DEBUG suittingu
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
	if (chipindex >= CHIP_DIV_X*CHIP_DIV_Y)chipindex = 0;
	int tempHandle = chipHandle[chipindex];
	DrawModiGraph_Wraped(vector2(CHIP_SIZE_X*scale.x * j - camera_pos.x, CHIP_SIZE_Y*scale.y * i - camera_pos.y), CHIPS_SIZE, scale, tempHandle, TRUE);

}

//DrawModiGraph関数のラップ関数//スケールによる拡大縮小ができるダケ。あとvector2に対応
//pos=描画する基点（左上）, scale , あとは一緒
void DrawModiGraph_WrapedScale(const vector2 &pos, const vector2 &scale, const int &grHandle, const int &TransFlag)
{
	//2,3,4 //R=right,L=left,T=top,B=bottom
	vector2 posRT(pos.x + (CHIP_SIZE_X*scale.x), pos.y);
	vector2 posRB(pos.x + (CHIP_SIZE_X*scale.x), pos.y + (CHIP_SIZE_Y*scale.y));
	vector2 posLB(pos.x, pos.y + (CHIP_SIZE_Y*scale.y));

	//vector2 posRT = vector2(pos.x + (CHIP_SIZE_X*scale.x), pos.y);
	//vector2 posRB = vector2(pos.x + (CHIP_SIZE_X*scale.x), pos.y + (CHIP_SIZE_Y*scale.y));
	//vector2 posLB = vector2(pos.x, pos.y + (CHIP_SIZE_Y*scale.y));
	DrawModiGraph(static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(posRT.x), static_cast<int>(posRT.y),
		static_cast<int>(posRB.x), static_cast<int>(posRB.y), static_cast<int>(posLB.x), static_cast<int>(posLB.y), grHandle, TransFlag);
}
void DrawModiGraph_Wraped(const vector2 &pos, const vector2 &size, const vector2 &scale, const int &grHandle, const int &TransFlag)
{
	//2,3,4 //R=right,L=left,T=top,B=bottom
	vector2 posRT(pos.x + (size.x*scale.x), pos.y);
	vector2 posRB(pos.x + (size.x*scale.x), pos.y + (size.y*scale.y));
	vector2 posLB(pos.x, pos.y + (size.y*scale.y));

	DrawModiGraph(static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(posRT.x), static_cast<int>(posRT.y),
		static_cast<int>(posRB.x), static_cast<int>(posRB.y), static_cast<int>(posLB.x), static_cast<int>(posLB.y), grHandle, TransFlag);
}



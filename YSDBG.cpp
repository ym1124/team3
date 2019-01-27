//////////////////////////////////////////////////////////
////
////			BG.cpp	マップチップ(Dxライブラリ版)
////
//////////////////////////////////////////////////////////


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

const vector2 WORLD_SIZE = vector2(CHIP_SIZE*SCALE_BG_X*CHIP_NUMX, CHIP_SIZE*SCALE_BG_Y*CHIP_NUMY);//描画するワールドのサイズ
const vector2 WINDOW_SIZE = vector2(SCREEN_WIDTH, SCREEN_HEIGHT);//ウィンドウサイズ
const vector2 BG_SCALE(SCALE_BG_X, SCALE_BG_Y);//スケール
const vector2 CHIPS_SIZE(CHIP_SIZE_X, CHIP_SIZE_Y);//画像サイズ
////////////////////////
//	変数(実体)
////////////////////////
BGsystem background;//実体
int chipHandle[CHIP_DIV_X*CHIP_DIV_Y];//画像を収めるハンドル
int backHandle;

vector2 camera_pos;		//world座標			//実際に画面に描画されるやつのあれ
//vector2 world_pos;	//not				//ステージ全体に於けるポジション
//vector2 screen_pos;	//not				//画面上のポジション


////////////////////////
//	プロトタイプ宣言
////////////////////////

void Draw_Physalis(int chipindex, int i, int j, vector2 scale);
void DrawModiGraph_Wraped(const vector2 &pos, const vector2 &size, const vector2 &scale, const int &grHandle, const int &TransFlag);
void CameraMove(vector2 plpos);
void StageData_Copy(int *chipDataArr[], int const* originalData[], vector2 stageSize);

//////////////////////////////////////////////////////////////////

//プログラムで読むやつ
//＿人人人人人人人人人人＿//
//＞　これを使います!＜	  //
//￣Y^Y^Y^Y^Y^Y^Y^Y^Y￣//
int chip_data[CHIP_NUMY][CHIP_NUMX];

//以下、当分ステージデータ
static int stage_data0[CHIP_NUMY][CHIP_NUMX] =
{
	{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},
};

static int stage_data1[CHIP_NUMY][CHIP_NUMX] =
{
	{ 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },//64*64
	{ 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 6, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 6, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 6, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0,12,11,11,11,11,13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, },
	{ 6, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 6, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, },
	{ 6, 0, 0, 0, 0, 0, 2, 2, 0, 0, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 6, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 6, 0, 0, 0, 0, 0, 0, 0, 0, 7,10, 6, 0, 0, 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 5, 2, 2, 2, 3, 0, 0, 1, 2, 4,10, 5, 2, 2, 4,10, 5, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 1, 2, 2, 2, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
};
static int stage_data2[CHIP_NUMY][CHIP_NUMX] =
{
	{ 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },//64*64
	{ 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 6, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 6, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 6, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0,12,11,11,11,11,13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, },
	{ 6, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 6, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, },
	{ 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 6, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 6, 0, 0, 0, 0, 0, 0, 0, 0, 7,10, 6, 0, 0, 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 5, 2, 2, 2, 3, 0, 0, 1, 2, 4,10, 5, 2, 2, 4,10, 5, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 1, 2, 2, 2, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
};
static int stage_data3[CHIP_NUMY][CHIP_NUMX] =
{
	{ 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },//64*64
	{ 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 6, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 6, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 6, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0,12,11,11,11,11,13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, },
	{ 6, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 6, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, },
	{ 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 6, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 6, 0, 0, 0, 0, 0, 0, 0, 0, 7,10, 6, 0, 0, 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 5, 2, 2, 2, 3, 0, 0, 1, 2, 4,10, 5, 2, 2, 4,10, 5, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 1, 2, 2, 2, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
};

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
		backHandle = LoadGraph("resource/image/Back.png");

		//ハンドル検査
		for (int it : chipHandle)
		{
			if (it == -1)
				assert(!"チップハンドル-1");
		}
		initSW = true;

		for (int i = 0; i < CHIP_NUMY; i++)
		{
			std::memmove(chip_data[i], stage_data1[i], CHIP_NUMX * sizeof(int));
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

	///////////
	//CameraMove();
	camera_ChipPosX = camera_pos.x / (CHIP_SIZE_X * SCALE_BG_X);
	camera_ChipPosY = camera_pos.y / (CHIP_SIZE_Y * SCALE_BG_Y);

	//DEBUG ステージ変更
	if (CheckHitKey(KEY_INPUT_1))SelectStage(1);
	if (CheckHitKey(KEY_INPUT_2))SelectStage(2);
	if (CheckHitKey(KEY_INPUT_3))SelectStage(3);

	//DEBUG 強制終了処理
	if (CheckHitKey(KEY_INPUT_ESCAPE))
	{
		exit(true);
	}

}

///////////////////////////////////////
//
//		描画するところ
//
///////////////////////////////////////
#define BG_SCROLL (2) //小さいほど早くなる
void BGsystem::draw()
{
	//背景描画
	{
		//左上
		DrawGraph(
			(static_cast<int>(camera_pos.x / -BG_SCROLL) % SCREEN_WIDTH),
			(static_cast<int>(camera_pos.y / -BG_SCROLL) % SCREEN_HEIGHT),
			backHandle, TRUE);
		//右上
		DrawGraph(
			(static_cast<int>(camera_pos.x / -BG_SCROLL) % SCREEN_WIDTH) + SCREEN_WIDTH,
			(static_cast<int>(camera_pos.y / -BG_SCROLL) % SCREEN_HEIGHT),
			backHandle, TRUE);
		//左下
		DrawGraph(
			(static_cast<int>(camera_pos.x / -BG_SCROLL) % SCREEN_WIDTH),
			(static_cast<int>(camera_pos.y / -BG_SCROLL) % SCREEN_HEIGHT) + SCREEN_HEIGHT,
			backHandle, TRUE);
		//右下
		DrawGraph(
			(static_cast<int>(camera_pos.x / -BG_SCROLL) % SCREEN_WIDTH) + SCREEN_WIDTH,
			(static_cast<int>(camera_pos.y / -BG_SCROLL) % SCREEN_HEIGHT) + SCREEN_HEIGHT,
			backHandle, TRUE);
	}

	//マップチップ描画
	int chipIndex;//チップインなんとかさん
	const static int CHIP_DRAW_MERGIN = 2;//画面外に余分に描画する分
	for (int i = camera_ChipPosY; i < camera_ChipPosY + WINDOW_SIZE_CHIP_Y + CHIP_DRAW_MERGIN; i++)//y
	{
		for (int j = camera_ChipPosX; j < camera_ChipPosX + WINDOW_SIZE_CHIP_X + CHIP_DRAW_MERGIN; j++)//x
		{
			chipIndex = chip_data[i][j];
			//描画関数
			Draw_Physalis(chipIndex, i, j, BG_SCALE);
		}//_for
	}//_for

	{
		//いじりましたbyYSD
		static int black = 0;
		if (!black)
			black = LoadGraph("resource/image/black.png", false);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 155);
		DrawGraph(0, 0, black, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void SelectStage(int stageNo)
{
	//TODO ステージ変える関数
	switch (stageNo)
	{
	case 0:
		//とりあえずなし
		break;
	case 1:
		//ステージ1
		//TODO chipData
		/*配列にマップチップの中身を代入*/
		for (int i = 0; i < CHIP_NUMY; i++)
		{
			std::memmove(chip_data[i], stage_data1[i], CHIP_NUMX * sizeof(int));
		}
		break;
	case 2:
		//ステージ2
		for (int i = 0; i < CHIP_NUMY; i++)
		{
			std::memmove(chip_data[i], stage_data2[i], CHIP_NUMX * sizeof(int));
		}
		break;
	case 3:
		for (int i = 0; i < CHIP_NUMY; i++)
		{
			std::memmove(chip_data[i], stage_data3[i], CHIP_NUMX * sizeof(int));
		}
		break;
	default:
		break;
	}
}

//第一が入れ物、第二がデータ
void StageData_Copy(int *chipDataArr[], int const *originalData[], vector2 stageSize)
{
	//TODO chipData
	/*配列にマップチップの中身を代入*/
	for (int i = 0; i < stageSize.y; i++)
	{
		std::memmove(chipDataArr[i], originalData[i], stageSize.x * sizeof(int));
	}
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
void BGsystem::ReleaseChipHandle()
{
	for (auto &it : chipHandle)
	{
		DeleteGraph(it);
	}
}

/*画面サイズは1280*720*/
#define SCROLL_MERGIN_X (620)//((SCREEN_WIDTH/10) * 4)
#define SCROLL_MERGIN_Y (250)//((SCREEN_HEIGHT/10) * 3)
#define SCROLL_MERGIN_TOP //UNDONE あとで考える
//カメラの移動関数
void CameraMove(vector2 plpos)
{
	vector2 wndPos = Convert_WorldToWindow(plpos);
	const static vector2 SCREEN_MERGIN(SCROLL_MERGIN_X, SCROLL_MERGIN_Y);
	constexpr static float SPEED_MAX_X = 7.0f;//
	constexpr static float SPEED_MAX_Y = 12.0f;
	static vector2 scrollSP(0, 0);

	const static float SCROLL_SPEED_X = (2.0f);
	const static float SCROLL_SPEED_Y = 2.0f;
	//const static float SCROLL_ACCEL = 1.0f;
	static vector2 prev_plpos;//一つ前のフレームのplpos
	static vector2 plSpeed;
	plSpeed = vector2(plpos.x - prev_plpos.x, plpos.y - prev_plpos.y);
	static vector2 cam_moveAmount;
	int ScrollState = 0;//0普通　1高速　2高速->減速

	//画面外にいるかどうか
	if (!(0 < wndPos.x&&wndPos.x < SCREEN_WIDTH && 0 < wndPos.y&&wndPos.y < SCREEN_HEIGHT))
		ScrollState = 1;

	//スクロールの開始条件
	//条件画面内
	if (ScrollState == 0)//外に行ってない(フラグ萎え萎え)
	{
		//x
		if (wndPos.x < 0 + SCREEN_MERGIN.x)
		{
			cam_moveAmount.x -= SCROLL_SPEED_X;
		}
		else
		{
			cam_moveAmount.x += SCROLL_SPEED_X;
		}
		if (WINDOW_SIZE.x - SCREEN_MERGIN.x < wndPos.x)
		{
			cam_moveAmount.x += SCROLL_SPEED_X;
		}
		else
		{
			cam_moveAmount.x -= SCROLL_SPEED_X;
		}

		//y
		if (wndPos.y < (0 + SCREEN_MERGIN.y))
		{
			cam_moveAmount.y -= SCROLL_SPEED_Y;
		}
		else
		{
			cam_moveAmount.y += SCROLL_SPEED_Y;
		}
		if (WINDOW_SIZE.y - SCREEN_MERGIN.y < wndPos.y)
		{
			cam_moveAmount.y += SCROLL_SPEED_Y;
		}
		else
		{
			cam_moveAmount.y -= SCROLL_SPEED_Y;
		}


		//速度が上限以上にならないようにする場所
		{
			//x
			if (cam_moveAmount.x > SPEED_MAX_X)
				cam_moveAmount.x = SPEED_MAX_X;
			else if (cam_moveAmount.x < -SPEED_MAX_X)
				cam_moveAmount.x = -SPEED_MAX_X;
			//y
			if (cam_moveAmount.y > SPEED_MAX_Y)
				cam_moveAmount.y = SPEED_MAX_Y;
			else if (cam_moveAmount.y < -SPEED_MAX_Y)
				cam_moveAmount.y = -SPEED_MAX_Y;
		}

	}
	else if (ScrollState == 1)//外行ってる(フラグビンビン)
	{
		//TODO 画面外処理
		//x
		if (wndPos.x < 0 + SCREEN_MERGIN.x)
		{
			cam_moveAmount.x -= SCROLL_SPEED_X;
		}
		else
		{
			cam_moveAmount.x += SCROLL_SPEED_X;
		}
		if (WINDOW_SIZE.x - SCREEN_MERGIN.x < wndPos.x)
		{
			cam_moveAmount.x += SCROLL_SPEED_X;
		}
		else
		{
			cam_moveAmount.x -= SCROLL_SPEED_X;
		}

		//y
		if (wndPos.y < (0 + SCREEN_MERGIN.y))
		{
			cam_moveAmount.y -= SCROLL_SPEED_Y;
		}
		else
		{
			cam_moveAmount.y += SCROLL_SPEED_Y;
		}
		if (WINDOW_SIZE.y - SCREEN_MERGIN.y < wndPos.y)
		{
			cam_moveAmount.y += SCROLL_SPEED_Y;
		}
		else
		{
			cam_moveAmount.y -= SCROLL_SPEED_Y;
		}

		//速度が上限以上にならないようにする場所
		{
			//x
			if (cam_moveAmount.x > SPEED_MAX_X * 3)
				cam_moveAmount.x = SPEED_MAX_X * 3;
			else if (cam_moveAmount.x < -SPEED_MAX_X * 3)
				cam_moveAmount.x = -SPEED_MAX_X * 3;
			//y
			if (cam_moveAmount.y > SPEED_MAX_Y * 3)
				cam_moveAmount.y = SPEED_MAX_Y * 3;
			else if (cam_moveAmount.y < -SPEED_MAX_Y * 3)
				cam_moveAmount.y = -SPEED_MAX_Y * 3;

			//プレイヤーがウィンドウ付近に接近時//(改変)
			//if (0 - 200 < wndPos.x&&wndPos.x < SCREEN_WIDTH + 200 && 0 - 150 < wndPos.y&&wndPos.y < SCREEN_HEIGHT - 150)
			if (std::fabsf(cam_moveAmount.x) >= SPEED_MAX_X * 3 && std::fabsf(cam_moveAmount.y) >= SPEED_MAX_Y * 3)
				ScrollState = 2;

		}
	}
	else if (ScrollState == 2)
	{
		cam_moveAmount.x -= 0.1;
		cam_moveAmount.y -= 0.1;

		if (std::fabsf(cam_moveAmount.x) <= SPEED_MAX_X  && std::fabsf(cam_moveAmount.y) <= SPEED_MAX_Y)
			ScrollState = 0;


		//速度が上限以上にならないようにする場所
		{
			//x
			if (cam_moveAmount.x > SPEED_MAX_X * 5)
				cam_moveAmount.x = SPEED_MAX_X * 5;
			else if (cam_moveAmount.x < -SPEED_MAX_X * 5)
				cam_moveAmount.x = -SPEED_MAX_X * 5;
			//y
			if (cam_moveAmount.y > SPEED_MAX_Y * 5)
				cam_moveAmount.y = SPEED_MAX_Y * 5;
			else if (cam_moveAmount.y < -SPEED_MAX_Y * 5)
				cam_moveAmount.y = -SPEED_MAX_Y * 5;
		}
	}
	//微速になったときに調節するとこ
	{
		//x
		if (1.0f <= cam_moveAmount.x)
		{
			cam_moveAmount.x -= 0.5f;
			if (cam_moveAmount.x < 0)
				cam_moveAmount.x = 0.0f;
		}
		else if (cam_moveAmount.x <= -1.0f)
		{
			cam_moveAmount.x += 0.5f;
			if (cam_moveAmount.x > 0.0f)
				cam_moveAmount.x = 0.0f;
		}
		if (-1.0f < cam_moveAmount.x && cam_moveAmount.x < 1.0f)
		{
			cam_moveAmount.x = 0;
		}
		//y
		if (1.0f <= cam_moveAmount.y)
		{
			cam_moveAmount.y -= 0.5f;
			if (cam_moveAmount.y < 0)
				cam_moveAmount.y = 0.0f;
		}
		else if (cam_moveAmount.y <= -1.0f)
		{
			cam_moveAmount.y += 0.5f;
			if (cam_moveAmount.y > 0.0f)
				cam_moveAmount.y = 0.0f;
		}
		if (-1.0f < cam_moveAmount.y && cam_moveAmount.y < 1.0f)
		{
			cam_moveAmount.y = 0;
		}
	}


	camera_pos += cam_moveAmount;
	prev_plpos = plpos;
	static vector2 prev_cam_moveAmout;
	prev_cam_moveAmout = cam_moveAmount;





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

	////DEBUG 文字をだすところ
	clsDx();
	printfDx("campos(x:%.1f,y%.1f)\n", camera_pos.x, camera_pos.y);
	printfDx("cam_amount(x:%.1f,y%.1f)\n", cam_moveAmount.x, cam_moveAmount.y);
	printfDx("pl_speed(x:%.1f,y%.1f)", plSpeed.x, plSpeed.y);
	///////////////////////////////////////
}


//マップチップの描画_試作1号機(ゼフィランサス)
//消去済み

//マップチップの描画_試作2号機(サイサリス)
void Draw_Physalis(int chipindex, int i, int j, vector2 scale)
{
	if (chipindex >= CHIP_DIV_X*CHIP_DIV_Y)chipindex = 0;
	else if (chipindex < 0) chipindex = 0;
	int tempHandle = chipHandle[chipindex];
	DrawModiGraph_Wraped(vector2(CHIP_SIZE_X*scale.x * j - camera_pos.x, CHIP_SIZE_Y*scale.y * i - camera_pos.y
	), CHIPS_SIZE, scale, tempHandle, TRUE);
}

//DrawModiGraph関数のラップ関数//スケールによる拡大縮小ができるダケ。あとvector2に対応
//pos=描画する基点（左上）, scale , あとは一緒
void DrawModiGraph_Wraped
(const vector2 &pos, const vector2 &size, const vector2 &scale,
	const int &grHandle, const int &TransFlag)
{
	//2,3,4 //R=right,L=left,T=top,B=bottom
	vector2 posRT(pos.x + (size.x*scale.x), pos.y);
	vector2 posRB(pos.x + (size.x*scale.x), pos.y + (size.y*scale.y));
	vector2 posLB(pos.x, pos.y + (size.y*scale.y));

	DrawModiGraph(static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(posRT.x), static_cast<int>(posRT.y),
		static_cast<int>(posRB.x), static_cast<int>(posRB.y), static_cast<int>(posLB.x), static_cast<int>(posLB.y), grHandle, TransFlag);
}

void Reset_CameraPos_YSD(vector2 resetPos)
{
	camera_pos = vector2(resetPos.x - WINDOW_SIZE.x, resetPos.y - WINDOW_SIZE.y);
}


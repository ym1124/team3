#pragma once
////////////////////////////////////////////////////////
//
//			BG.h	マップチップ
//
////////////////////////////////////////////////////////
#include "vector.h"
#define CHIP_NUMX (60) //チップ配列の数x
#define CHIP_NUMY (20) //チップ配列の数y
//TODO 最終画像に合わせた変更
#define CHIP_DIV_X (10)//画像の区切りの数x
#define CHIP_DIV_Y (10)//画像の区切りの数y
#define CHIP_SIZE (64) //画像の1区切りの大きさ
#define CHIP_SIZE_X CHIP_SIZE
#define CHIP_SIZE_Y CHIP_SIZE
extern vector2 camera_pos;
extern const vector2 WORLD_SIZE;
extern const vector2 WINDOW_SIZE;
extern int chip_data[CHIP_NUMY][CHIP_NUMX];

class BGsystem
{
private:

public:
	void init();
	void update();
	void draw();
	//void uninit();//作る？
	void ReleaseChipHandle();
};
//extern BGsystem bg;
void DrawModiGraph_Wraped(const vector2 &pos, const vector2 &size, const vector2 &scale, const int &grHandle, const int &TransFlag);
vector2 Convert_WorldToWindow(vector2 &pos);
void CameraMove(vector2 plpos);
void SelectStage(int stageNo);//ステージ変更用関数
void Reset_CameraPos_YSD(vector2 resetPos);//引数の位置を中心とする位置にカメラを移動

extern BGsystem background;//実体

enum TR_ATTR
{
	TR_NONE = -1,   // -1:何もなし
	ALL_BLOCK,      //  0:四方ブロック
	UPPER_BLOCK,    //  1:上だけブロック
	HASHIGO,        //  2:はしご
	PASSSOUL,		//	3:魂だけ通れる
	SPIKE,			//	4:とげ
};

const TR_ATTR terrainAttr[CHIP_DIV_Y][CHIP_DIV_X] = {
	{ TR_ATTR::TR_NONE,   TR_ATTR::ALL_BLOCK,   TR_ATTR::ALL_BLOCK,   TR_ATTR::ALL_BLOCK,   TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK, },
	{ TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK,	TR_ATTR::ALL_BLOCK,		TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK, },
	{ TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK,     TR_ATTR::UPPER_BLOCK,     TR_ATTR::PASSSOUL,     TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE, TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK, },
	{ TR_ATTR::TR_NONE,     TR_ATTR::TR_NONE,     TR_ATTR::TR_NONE,     TR_ATTR::TR_NONE,     TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE, TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK, },
};




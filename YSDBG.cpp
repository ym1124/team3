//////////////////////////////////////////////////////////
////
////			BG.cpp	�}�b�v�`�b�v(Dx���C�u������)
////
//////////////////////////////////////////////////////////


//UnresoledMergeConflict
#include"DxLib.h"
#include "YSDBG.h"
#include "common.h"
#include "vector.h"
#include <assert.h>
////////////////////////
//	�萔
////////////////////////
#define SCALE_BG (1.0f)//�`�b�v�̃X�P�[��
#define SCALE_BG_X SCALE_BG
#define SCALE_BG_Y SCALE_BG

const vector2 WORLD_SIZE = vector2(CHIP_SIZE*SCALE_BG_X*CHIP_NUMX, CHIP_SIZE*SCALE_BG_Y*CHIP_NUMY);//�`�悷�郏�[���h�̃T�C�Y
const vector2 WINDOW_SIZE = vector2(SCREEN_WIDTH, SCREEN_HEIGHT);//�E�B���h�E�T�C�Y
const vector2 BG_SCALE(SCALE_BG_X, SCALE_BG_Y);//�X�P�[��
const vector2 CHIPS_SIZE(CHIP_SIZE_X, CHIP_SIZE_Y);//�摜�T�C�Y
////////////////////////
//	�ϐ�(����)
////////////////////////
//BGsystem bg;//����
int chipHandle[CHIP_DIV_X*CHIP_DIV_Y];//�摜�����߂�n���h��
int backHandle;

vector2 camera_pos;		//world���W			//���ۂɉ�ʂɕ`�悳����̂���
//vector2 world_pos;	//not				//�X�e�[�W�S�̂ɉ�����|�W�V����
//vector2 screen_pos;	//not				//��ʏ�̃|�W�V����

//DEBUG suitti Z
bool suitti = true;
bool kb_Z, kbPrev_Z;
bool kb_Spc, kbPrev_Spc;

////////////////////////
//	�v���g�^�C�v�錾
////////////////////////
//DEBUG
bool Suittingu(bool &suitti);

void Draw_Physalis(int chipindex, int i, int j, vector2 scale);
void DrawModiGraph_Wraped(const vector2 &pos, const vector2 &size, const vector2 &scale, const int &grHandle, const int &TransFlag);
void CameraMove(vector2 plpos);
//////////////////////////////////////////////////////////////////
//�v���O�����œǂނ��
int  chipData[CHIP_NUMY][CHIP_NUMX] = { 0 };
//�X�e�[�W�f�[�^

#define $	(2)

int chip_data[CHIP_NUMY][CHIP_NUMX] =
{
	{ 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },//64*64
	{ 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,12,11,11,11,11,13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, },
	{ 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, },
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
#undef $

static int chip_data0[CHIP_NUMY][CHIP_NUMX] =
{
	{ 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },//64*64
	{ 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,12,11,11,11,11,13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 6, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 6, 0, 0, 0, 0, 0, 0, 0, 0, 7,10, 6, 0, 0, 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 5, 2, 2, 2, 3, 0, 0, 1, 2, 4,10, 5, 2, 2, 4,10, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 1, 2, 2, 2, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },

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

//�f�[�^�̓��ꕨ�������ᔠ
int *chipData_Box[] = { &chip_data0[0][0] , &chip_data1[0][0], };//���ʎg���
///////////////////////////////////////////////////////////////

///////////////////////////////////////
//
//		����������Ƃ���
//
///////////////////////////////////////
void BGsystem::init()
{
	static bool initSW = false;
	//��񂾂�
	if (!initSW)
	{
		camera_pos = vector2(0.0f, 0.0f);
		LoadDivGraph("resource/image/mapchip.png",
			CHIP_DIV_X*CHIP_DIV_Y, CHIP_DIV_X, CHIP_DIV_Y, CHIP_SIZE_X, CHIP_SIZE_Y, chipHandle);
		backHandle = LoadGraph("resource/image/Back.png");

		//�n���h������
		for (int it : chipHandle)
		{
			if (it == -1)
				assert(!"�`�b�v�n���h��-1");
		}
		initSW = true;

		//TODO chipData
		//�ŏ��̃X�e�[�W�̃`�b�v�f�[�^
		//int *tempChip_data = 0;
		//tempChip_data= chipData_Box[0];
		/*�z��Ƀ}�b�v�`�b�v�̒��g����*/
		for (int i = 0; i < CHIP_NUMY; i++)
		{
			std::memmove(chipData[i], chip_data[i], CHIP_NUMX * sizeof(int));
		}
	}
}
///////////////////////////////////////
//
//		�X�V����Ƃ���
//
///////////////////////////////////////
int camera_ChipPosX, camera_ChipPosY;
const int WINDOW_SIZE_CHIP_X = SCREEN_WIDTH / (CHIP_SIZE_X * SCALE_BG_X);
const int WINDOW_SIZE_CHIP_Y = SCREEN_HEIGHT / (CHIP_SIZE_Y * SCALE_BG_Y);

void BGsystem::update()
{
	//DEBUG keyinput
	//kb_Z = CheckHitKey(KEY_INPUT_Z);//���t���[���̓��͏�Ԃ��m�F
	//kb_Spc = CheckHitKey(KEY_INPUT_SPACE);
	//DEBUG Z�X�C�b�`
	//if (kb_Z && !kbPrev_Z)
	//	Suittingu(suitti);

	///////////
	//CameraMove();
	camera_ChipPosX = camera_pos.x / (CHIP_SIZE_X * SCALE_BG_X);
	camera_ChipPosY = camera_pos.y / (CHIP_SIZE_Y * SCALE_BG_Y);

	//DEBUG �����I������
	if (CheckHitKey(KEY_INPUT_ESCAPE))
	{
		exit(true);
	}

	//DEBUG keyinput//�O�t���[���̓��͏�Ԃ��X�V
	//kbPrev_Z = kb_Z;
	//kbPrev_Spc = kb_Spc;
}

///////////////////////////////////////
//
//		�`�悷��Ƃ���
//
///////////////////////////////////////
#define BG_SCROLL (2) //�������قǑ����Ȃ�
void BGsystem::draw()
{
	//�w�i�`��
	{
		//����
		DrawGraph(
			(static_cast<int>(camera_pos.x / -BG_SCROLL) % SCREEN_WIDTH),
			(static_cast<int>(camera_pos.y / -BG_SCROLL) % SCREEN_HEIGHT),
			backHandle, TRUE);
		//�E��
		DrawGraph(
			(static_cast<int>(camera_pos.x / -BG_SCROLL) % SCREEN_WIDTH) + SCREEN_WIDTH,
			(static_cast<int>(camera_pos.y / -BG_SCROLL) % SCREEN_HEIGHT),
			backHandle, TRUE);
		//����
		DrawGraph(
			(static_cast<int>(camera_pos.x / -BG_SCROLL) % SCREEN_WIDTH),
			(static_cast<int>(camera_pos.y / -BG_SCROLL) % SCREEN_HEIGHT) + SCREEN_HEIGHT,
			backHandle, TRUE);
		//�E��
		DrawGraph(
			(static_cast<int>(camera_pos.x / -BG_SCROLL) % SCREEN_WIDTH) + SCREEN_WIDTH,
			(static_cast<int>(camera_pos.y / -BG_SCROLL) % SCREEN_HEIGHT) + SCREEN_HEIGHT,
			backHandle, TRUE);
	}

	//�}�b�v�`�b�v�`��
	int chipIndex;//�`�b�v�C���Ȃ�Ƃ�����
	const static int CHIP_DRAW_MERGIN = 2;//��ʊO�ɗ]���ɕ`�悷�镪
	for (int i = camera_ChipPosY; i < camera_ChipPosY + WINDOW_SIZE_CHIP_Y + CHIP_DRAW_MERGIN; i++)//y
	{
		for (int j = camera_ChipPosX; j < camera_ChipPosX + WINDOW_SIZE_CHIP_X + CHIP_DRAW_MERGIN; j++)//x
		{
			chipIndex = chipData[i][j];
			//�`��֐�
			Draw_Physalis(chipIndex, i, j, BG_SCALE);
		}//_for
	}//_for

	{
		//������܂���byYSD
		static int black = 0;
		if (!black)
			black = LoadGraph("resource/image/black.png", false);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 155);
		DrawGraph(0, 0, black, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}


///////////////////////////////////////
//
//		���̑�����Ƃ���
//
///////////////////////////////////////

vector2 Convert_WorldToWindow(vector2 &pos)
{
	return vector2(pos.x - camera_pos.x, pos.y - camera_pos.y);
}

//�`�b�v�n���h�����̉摜��S�������܂�.
void BGsystem::ReleaseChipHandle()
{
	for (auto &it : chipHandle)
	{
		DeleteGraph(it);
	}
}

/*��ʃT�C�Y��1280*720*/
#define SCROLL_MERGIN_X (620)//((SCREEN_WIDTH/10) * 4)
#define SCROLL_MERGIN_Y (300)//((SCREEN_HEIGHT/10) * 3)
#define SCROLL_MERGIN_TOP //UNDONE ���Ƃōl����
//�J�����̈ړ��֐�
void CameraMove(vector2 plpos)
{

	vector2 wndPos = Convert_WorldToWindow(plpos);
	const static vector2 SCREEN_MERGIN(SCROLL_MERGIN_X, SCROLL_MERGIN_Y);
	constexpr static float SPEED_MAX_X = 7.0f;//
	constexpr static float SPEED_MAX_Y = 12.0f;
	static vector2 scrollSP(0, 0);
	//�J�����̈ړ�
#if  0

		//�X�N���[���}�[�W���O�ɏo���Ƃ��ɂ��̕������J�������ړ�
	if (wndPos.x < 0 + SCREEN_MERGIN.x)
	{
		camera_pos.x -= (0 + SCREEN_MERGIN.x) - wndPos.x;
	}
	if (WINDOW_SIZE.x - SCREEN_MERGIN.x < wndPos.x)
	{
		camera_pos.x += wndPos.x - WINDOW_SIZE.x + SCREEN_MERGIN.x;
	}

	if (wndPos.y < (0 + SCREEN_MERGIN.y))
	{
		camera_pos.y -= (0 + SCREEN_MERGIN.y) - wndPos.y;
	}
	if (WINDOW_SIZE.y - SCREEN_MERGIN.y < wndPos.y)
	{
		camera_pos.y += wndPos.y - WINDOW_SIZE.y + SCREEN_MERGIN.y;
	}

#elif 0//��ݸ�݂���

		//�v���C���[�̈ʒu��ێ����A�X�s�[�h�����o�A���̃X�s�[�h�̕������J�������ړ�������B

	const static float SCROLL_SPEED_X = (2.0f);
	const static float SCROLL_SPEED_Y = 2.0f;
	const static float SCROLL_ACCEL = 1.0f;
	static vector2 prev_plpos;//��O�̃t���[����plpos
	static vector2 plSpeed;
	plSpeed = vector2(wndPos.x - prev_plpos.x, wndPos.y - prev_plpos.y);
	static vector2 cam_moveAmount;
	//�X�N���[���̊J�n����
	//x
	{
		if (wndPos.x < 0 + SCREEN_MERGIN.x)
		{
			cam_moveAmount.x -= SCROLL_SPEED_X;
		}
		else
		{
			cam_moveAmount.x++;
		}
		if (WINDOW_SIZE.x - SCREEN_MERGIN.x < wndPos.x)
		{
			cam_moveAmount.x += SCROLL_SPEED_X;
		}
		else
		{
			cam_moveAmount.x--;
		}

		//y
		if (wndPos.y < (0 + SCREEN_MERGIN.y))
		{
			cam_moveAmount.y -= SCROLL_SPEED_Y;
		}
		else
		{
			cam_moveAmount.y += 0.5f;
		}
		if (WINDOW_SIZE.y - SCREEN_MERGIN.y < wndPos.y)
		{
			cam_moveAmount.y += SCROLL_SPEED_Y;
		}
		else
		{
			cam_moveAmount.y -= 0.5f;
		}
	}
	//���x������ȏ�ɂȂ�Ȃ��悤�ɂ���ꏊ
	//if (cam_moveAmount.x)
	{
		if (cam_moveAmount.x > SPEED_MAX_X)
		{
			cam_moveAmount.x = SPEED_MAX_X;
		}
		else if (cam_moveAmount.x < -SPEED_MAX_X)
		{
			cam_moveAmount.x = -SPEED_MAX_X;
		}

		if (cam_moveAmount.y > SPEED_MAX_Y)
		{
			cam_moveAmount.y = SPEED_MAX_Y;
		}
		else if (cam_moveAmount.y < -SPEED_MAX_Y)
		{
			cam_moveAmount.y = -SPEED_MAX_Y;
		}
	}


	//�����ɂȂ����Ƃ��ɒ��߂���Ƃ�
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

#elif 1

//�v���C���[�̈ʒu��ێ����A�X�s�[�h�����o�A���̃X�s�[�h�̕������J�������ړ�������B

	const static float SCROLL_SPEED_X = (2.0f);
	const static float SCROLL_SPEED_Y = 2.0f;
	//const static float SCROLL_ACCEL = 1.0f;
	static vector2 prev_plpos;//��O�̃t���[����plpos
	static vector2 plSpeed;
	plSpeed = vector2(plpos.x - prev_plpos.x, plpos.y - prev_plpos.y);
	static vector2 cam_moveAmount;

	//�X�N���[���̊J�n����
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
			//cam_moveAmount.y += SCROLL_SPEED_Y;
		}
		if (WINDOW_SIZE.y - SCREEN_MERGIN.y < wndPos.y)
		{
			cam_moveAmount.y += SCROLL_SPEED_Y;
		}
		else
		{
			//cam_moveAmount.y -= SCROLL_SPEED_Y;
		}
	}
	//���x������ȏ�ɂȂ�Ȃ��悤�ɂ���ꏊ
	{
		if (cam_moveAmount.x > SPEED_MAX_X)
		{
			cam_moveAmount.x = SPEED_MAX_X;
		}
		else if (cam_moveAmount.x < -SPEED_MAX_X)
		{
			cam_moveAmount.x = -SPEED_MAX_X;
		}

		if (cam_moveAmount.y > SPEED_MAX_Y)
		{
			cam_moveAmount.y = SPEED_MAX_Y;
		}
		else if (cam_moveAmount.y < -SPEED_MAX_Y)
		{
			cam_moveAmount.y = -SPEED_MAX_Y;
		}
	}

	//�����ɂȂ����Ƃ��ɒ��߂���Ƃ�
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

#elif 1
	//�J�����ƃv���C���[�̍����v�Z�B�v���C���[���^�񒆂ɗ���悤�ɉ����B
	//speed, speedMAX, accela, 
	//��ʐ^��

#endif //  0



	//�J�����̈ړ�����
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

	////DEBUG �����������Ƃ���
	clsDx();
	printfDx("campos(x:%.1f,y%.1f)\n", camera_pos.x, camera_pos.y);
	printfDx("cam_amount(x:%.1f,y%.1f)\n", cam_moveAmount.x, cam_moveAmount.y);
	printfDx("pl_speed(x:%.1f,y%.1f)", plSpeed.x, plSpeed.y);
	///////////////////////////////////////
}

//DEBUG suittingu
//�X�C�b�`���O�֐�(Z)
bool Suittingu(bool &suitti)//�X�C�b�`���O��p������֐�
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

//�}�b�v�`�b�v�̕`��_����1���@(�[�t�B�����T�X)
//�v�斕���ς�

//�}�b�v�`�b�v�̕`��_����2���@(�T�C�T���X)
void Draw_Physalis(int chipindex, int i, int j, vector2 scale)
{
	if (chipindex >= CHIP_DIV_X*CHIP_DIV_Y)chipindex = 0;
	else if (chipindex < 0) chipindex = 0;
	int tempHandle = chipHandle[chipindex];
	DrawModiGraph_Wraped(vector2(CHIP_SIZE_X*scale.x * j - camera_pos.x, CHIP_SIZE_Y*scale.y * i - camera_pos.y
		), CHIPS_SIZE, scale, tempHandle, TRUE);
}

//DrawModiGraph�֐��̃��b�v�֐�//�X�P�[���ɂ��g��k�����ł���_�P�B����vector2�ɑΉ�
//pos=�`�悷���_�i����j, scale , ���Ƃ͈ꏏ
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



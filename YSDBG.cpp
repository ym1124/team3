////////////////////////////////////////////////////////
//
//			BG.cpp	�}�b�v�`�b�v(Dx���C�u������)
//
////////////////////////////////////////////////////////
/*	�����̎d��(19/01/12�L)
���v�C���N���[�h DxLib.h
YSDBG.h ���C���N���[�h����B
bg.init();//���t���[���A�_��
bg.update();
bg.draw(); �u���B

�ꍇ�ɂ���Ă͕ϐ�����ς��܂�
*/


//UnresoledMergeConflict
#pragma once
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
//TODO �X�N���[���̃T�C�Y�m�F
//#define SCREEN_WIDTH (600)
//#define SCREEN_HEIGHT (400)

const  vector2 WORLD_SIZE = vector2(CHIP_SIZE*SCALE_BG_X*CHIP_NUMX, CHIP_SIZE*SCALE_BG_Y*CHIP_NUMY);
const  vector2 WINDOW_SIZE = vector2(SCREEN_WIDTH, SCREEN_HEIGHT);
const vector2 BG_SCALE(SCALE_BG_X, SCALE_BG_Y);
////////////////////////
//	�ϐ�(����)
////////////////////////
//BGsystem bg;
int chipHandle[CHIP_NUMX*CHIP_NUMY];

vector2 camera_pos;	//world���W			//���ۂɉ�ʂɕ`�悳����̂���
vector2 world_pos;	//not				//�X�e�[�W�S�̂ɉ�����|�W�V����
vector2 screen_pos;	//not				//��ʏ�̃|�W�V����
bool suitti = true;	//debug

bool kb_Z, kbPrev_Z;
////////////////////////
//	�v���g�^�C�v�錾
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
//		����������Ƃ���
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
			assert("�`�b�v�n���h��-1");
	}

}
///////////////////////////////////////
//
//		�X�V����Ƃ���
//
///////////////////////////////////////

void BGsystem::update()
{
	kb_Z = CheckHitKey(KEY_INPUT_Z);//���t���[���̓��͏�Ԃ��m�F




	//DEBUG////
	if (kb_Z && !kbPrev_Z)
		Suittingu(suitti);
	///////////
	CameraMove();

	//DEBUG
	if (CheckHitKey(KEY_INPUT_ESCAPE))
		exit(true);

	kbPrev_Z = kb_Z;//�O�t���[���̓��͏�Ԃ��X�V
}

///////////////////////////////////////
//
//		�`�悷��Ƃ���
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
			int chipIndex;//�`�b�v�C���Ȃ�Ƃ�����
			chipIndex = chip_data[i][j];

			//�`��֐�
			if (chipHandle[i*CHIP_NUMY + j] == -1)
				exit(false);

			Draw_Physalis(chipIndex, i, j, BG_SCALE);
			//if (suitti)
			//	Draw_Zephyranthes(chipIndex, i, j);//����
				//else

		}//_for
	}//_for
}





///////////////////////////////////////
//
//		���̑�����Ƃ���
//
///////////////////////////////////////
//�J�����̈ړ��֐�
void CameraMove()
{


	//�ȉ��J�����Ɋւ���///////////////////////
	//�J��������
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

	///////////////////////////////////////
}

//DEBUG
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
void Draw_Zephyranthes(int chipindex, int i, int j)
{
	int tempHandle = chipHandle[chipindex];
	DrawGraph(64 * j - camera_pos.x, 64 * i - camera_pos.y, tempHandle, false);
}

//�}�b�v�`�b�v�̕`��_����2���@(�T�C�T���X)
void Draw_Physalis(int chipindex, int i, int j, vector2 scale)
{
	//int tempHandle = chipHandle[chipindex];
	DrawModiGraph_WrapedScale(vector2(CHIP_SIZE*scale.x * j - camera_pos.x, CHIP_SIZE*scale.y * i - camera_pos.y), scale, chipHandle[chipindex], TRUE);
}


//DrawModiGraph�֐��̃��b�v�֐�//�X�P�[���ɂ��g��k�����ł���_�P�B����vector2�ɑΉ�

//pos=�`�悷���_�i����j, scale , ���Ƃ͈ꏏ
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
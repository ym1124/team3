//////////////////////////////////////////////////////////
////
////			BG.cpp	�}�b�v�`�b�v(Dx���C�u������)
////
//////////////////////////////////////////////////////////
///*	�����̎d��(19/01/12�L)
//���v�C���N���[�h DxLib.h
//YSDBG.h ���C���N���[�h����B
//bg.init();//���t���[���A�_��
//bg.update();
//bg.draw(); �u���B
//
//�ꍇ�ɂ���Ă͕ϐ�����ς��܂�
//*/


//UnresoledMergeConflict
#include"DxLib.h"
#include "YSDBG.h"
#include "common.h"
#include "vector.h"
#include <assert.h>
////////////////////////
//	�萔
////////////////////////
//�摜�V���[�Y
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

vector2 camera_pos;	//world���W			//���ۂɉ�ʂɕ`�悳����̂���
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

void Draw_Zephyranthes(int chipindex, int i, int j);
void Draw_Physalis(int chipindex, int i, int j, vector2 scale);
void DrawModiGraph_WrapedScale(const vector2 &pos, const vector2 &scale, const int &grHandle, const int &TransFlag);
void DrawModiGraph_Wraped(const vector2 &pos, const vector2 &size, const vector2 &scale, const int &grHandle, const int &TransFlag);
//////////////////////////////////////////////////////////////////
//�v���O�����œǂނ��
int  chipData[CHIP_NUMY][CHIP_NUMX] = { 0 };
//�X�e�[�W�f�[�^

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

//�f�[�^�̓��ꕨ
int *chipData_Box[] = { &chip_data0[0][0] , &chip_data1[0][0], };
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
		//�n���h������
		for (auto &it : chipHandle)
		{
			if (it == -1)
				assert("�`�b�v�n���h��-1");
		}
		initSW = true;

		//TODO chipData
		//�ŏ��̃X�e�[�W�̃`�b�v�f�[�^
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
	camera_ChipPosX = camera_pos.x / (CHIP_SIZE_X * SCALE_BG_X);
	camera_ChipPosY = camera_pos.y / (CHIP_SIZE_Y * SCALE_BG_Y);

	//DEBUG �����I������
	//if (CheckHitKey(KEY_INPUT_ESCAPE))
	//{
	//	exit(true);
	//}

	//DEBUG �����������Ƃ���
	//clsDx();
	//printfDx("campos(x:%.1f,y%.1f)\n", camera_pos.x, camera_pos.y);

	//DEBUG keyinput//�O�t���[���̓��͏�Ԃ��X�V
	//kbPrev_Z = kb_Z;
	//kbPrev_Spc = kb_Spc;
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
	DrawGraph(1280, 0, backGh, true);
	DrawGraph(2560, 0, backGh, true);
	for (int i = 0; i < 20; i++)//y
	{
		for (int j = 0; j < 20; j++)//x
		{
			int chipIndex;//�`�b�v�C���Ȃ�Ƃ�����
			chipIndex = chip_data[i][j];

			//�`��֐�
			Draw_Physalis(chipIndex, i, j, BG_SCALE);
		}//_for
	}//_for

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
void BGsystem::RereaseChipHandle()
{
	for (auto &it : chipHandle)
	{
		DeleteGraph(it);
	}
}



//�J�����̈ړ��֐�
void CameraMove(vector2 plpos)
{
	vector2 plposPrev = plpos;
	vector2 posGap;

	////DEBUG �J����
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
	//	//�덷���v�Z
	//	posGap.x = wndPos.x - posGap.x;
	//	posGap.y = wndPos.y - posGap.y;

	//	camera_pos += posGap;
	//}


	//�J�����̈ړ�
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


	//DEBUG �����������Ƃ���
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
	clsDx();
	printfDx("campos(x:%.1f,y%.1f)\n", camera_pos.x, camera_pos.y);
	///////////////////////////////////////
	plposPrev = plpos;//�O�t���[���̈ʒu���R�s�[
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
void Draw_Zephyranthes(int chipindex, int i, int j)
{
	int tempHandle = chipHandle[chipindex];
	DrawGraph(64 * j - camera_pos.x, 64 * i - camera_pos.y, tempHandle, false);
}
//�}�b�v�`�b�v�̕`��_����2���@(�T�C�T���X)
void Draw_Physalis(int chipindex, int i, int j, vector2 scale)
{
	if (chipindex >= CHIP_DIV_X*CHIP_DIV_Y)chipindex = 0;
	int tempHandle = chipHandle[chipindex];
	DrawModiGraph_Wraped(vector2(CHIP_SIZE_X*scale.x * j - camera_pos.x, CHIP_SIZE_Y*scale.y * i - camera_pos.y), CHIPS_SIZE, scale, tempHandle, TRUE);

}

//DrawModiGraph�֐��̃��b�v�֐�//�X�P�[���ɂ��g��k�����ł���_�P�B����vector2�ɑΉ�
//pos=�`�悷���_�i����j, scale , ���Ƃ͈ꏏ
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



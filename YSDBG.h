#pragma once
////////////////////////////////////////////////////////
//
//			BG.h	�}�b�v�`�b�v
//
////////////////////////////////////////////////////////
#include "vector.h"
#define CHIP_NUMX (60) //�`�b�v�z��̐�x
#define CHIP_NUMY (20) //�`�b�v�z��̐�y
//TODO �ŏI�摜�ɍ��킹���ύX
#define CHIP_DIV_X (10)//�摜�̋�؂�̐�x
#define CHIP_DIV_Y (10)//�摜�̋�؂�̐�y
#define CHIP_SIZE (64) //�摜��1��؂�̑傫��
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
	//void uninit();//���H
	void ReleaseChipHandle();
};
//extern BGsystem bg;
void DrawModiGraph_Wraped(const vector2 &pos, const vector2 &size, const vector2 &scale, const int &grHandle, const int &TransFlag);
vector2 Convert_WorldToWindow(vector2 &pos);
void CameraMove(vector2 plpos);
void SelectStage(int stageNo);//�X�e�[�W�ύX�p�֐�
void Reset_CameraPos_YSD(vector2 resetPos);//�����̈ʒu�𒆐S�Ƃ���ʒu�ɃJ�������ړ�

extern BGsystem background;//����

enum TR_ATTR
{
	TR_NONE = -1,   // -1:�����Ȃ�
	ALL_BLOCK,      //  0:�l���u���b�N
	UPPER_BLOCK,    //  1:�ゾ���u���b�N
	HASHIGO,        //  2:�͂���
	PASSSOUL,		//	3:�������ʂ��
	SPIKE,			//	4:�Ƃ�
};

const TR_ATTR terrainAttr[CHIP_DIV_Y][CHIP_DIV_X] = {
	{ TR_ATTR::TR_NONE,   TR_ATTR::ALL_BLOCK,   TR_ATTR::ALL_BLOCK,   TR_ATTR::ALL_BLOCK,   TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK, },
	{ TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK,	TR_ATTR::ALL_BLOCK,		TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK, },
	{ TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK,     TR_ATTR::UPPER_BLOCK,     TR_ATTR::PASSSOUL,     TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE, TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK, },
	{ TR_ATTR::TR_NONE,     TR_ATTR::TR_NONE,     TR_ATTR::TR_NONE,     TR_ATTR::TR_NONE,     TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE, TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK, },
};




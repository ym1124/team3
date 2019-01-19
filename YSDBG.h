#pragma once
////////////////////////////////////////////////////////
//
//			BG.h	�}�b�v�`�b�v
//
////////////////////////////////////////////////////////
#include "vector.h"
#define CHIP_NUMX (60) //�`�b�v�z��̐�x
#define CHIP_NUMY (20) //�`�b�v�z��̐�y
#define CHIP_DIV_X (10)//�摜�̋�؂�̐�x
#define CHIP_DIV_Y (10)//�摜�̋�؂�̐�y
#define CHIP_SIZE (64) //�摜��1��؂�̑傫��
#define CHIP_SIZE_X CHIP_SIZE
#define CHIP_SIZE_Y CHIP_SIZE


class BGsystem
{
private:

public:

	void init();
	void update();
	void draw();
	//void uninit();//���H
	void RereaseChipHandle();
};
//extern BGsystem bg;

extern int chip_data[CHIP_NUMY][CHIP_NUMX];
extern vector2 camera_pos;
void DrawModiGraph_Wraped(const vector2 &pos, const vector2 &size, const vector2 &scale, const int &grHandle, const int &TransFlag);
void CameraMove(vector2 plpos);

enum TR_ATTR
{
	TR_NONE = -1,   // -1:�����Ȃ�
	ALL_BLOCK,      //  0:�l���u���b�N
	UPPER_BLOCK,    //  1:�ゾ���u���b�N
	HASHIGO,        //  2:�͂���
};

const TR_ATTR terrainAttr[CHIP_DIV_X][CHIP_DIV_Y] = {
	{ TR_ATTR::TR_NONE,   TR_ATTR::ALL_BLOCK,   TR_ATTR::ALL_BLOCK,   TR_ATTR::ALL_BLOCK,   TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK, },
	{ TR_ATTR::UPPER_BLOCK, TR_ATTR::UPPER_BLOCK, TR_ATTR::UPPER_BLOCK, TR_ATTR::UPPER_BLOCK, TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE, },
	{ TR_ATTR::HASHIGO,     TR_ATTR::HASHIGO,     TR_ATTR::TR_NONE,     TR_ATTR::TR_NONE,     TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE, },
	{ TR_ATTR::TR_NONE,     TR_ATTR::TR_NONE,     TR_ATTR::TR_NONE,     TR_ATTR::TR_NONE,     TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE, },
};




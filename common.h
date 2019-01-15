#ifndef _COMMON_H_
#define	_COMMON_H_

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
//	�萔
//--------------------------------
#define SCREEN_WIDTH (1440)
#define SCREEN_HEIGHT (810)


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
double ToRadian(double deg);

//--------------------------------
//	�}�N���֐�
//--------------------------------

/* ==========  ���͊֌W�i�g���K�[�j  ========== */
// �L�[����
extern int key[256]; // 0:���͂���Ă��Ȃ� 1:���͂��ꂽ�u�� 2:���͂���Ă���
extern int keyall;
extern int PAD1;
extern bool slow_flg;

/* ==========  �p�x�ϊ��p  ========== */
//#define ToRadian(x) FromDgreeToRadian(x)
#define ToDegree(x) XMConvertToDegrees(x)

#endif // !_COMMON_H_
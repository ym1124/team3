#pragma once
#include "DxLib.h"
#include "common.h"
#include "vector.h"

#include "light.h"

class OBJ2D;
typedef void(*MOVER)(OBJ2D *obj);

class animator
{
public:
	vector2 pos;
	int texture;
	int animCnt;
	int sheetsNum;
	int speed;
	int srcX;
	int srcY;
	int sizeX;
	int sizeY;
	animator();
	//�`��֐�
	//�A�j���[�V���������A�`��t���[�����A�摜�̐؂���ʒux�A�摜�̐؂���ʒuy�A�A�j���[�V�����摜�̕��A�A�j���[�V�����摜�̍���
	virtual void setTextureInfo(int sheetsNum = 1, int speed = 1, int srcX = 0, int srcY = 0, int sizeX = 0, int sizeY = 0);
	virtual void draw(bool animationFlg = false);
};

class OBJ2D:public animator
{
public:
	OBJ2D();
	void clear();
	MOVER mover;
	virtual void update();
	virtual void setObject(vector2 pos)=0;
};


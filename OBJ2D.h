#pragma once
#include "DxLib.h"
#include "common.h"
#include "vector.h"

#include "light.h"

class OBJ2D;
typedef void(*MOVER)(OBJ2D *obj);

class OBJ2D
{
public:
	vector2 pos;
	int texture;
	bool setFlg;

	OBJ2D();
	void clear();
	MOVER mover;
	virtual void update();
	virtual void draw();
	virtual void setObject(vector2 pos)=0;
};

void testMove(OBJ2D *obj);

//class OBJ2DManager
//{
//public:
//	OBJ2D objs[5];
//	void init();			// �����ݒ�
//	void update();			// �X�V����
//	void draw();			// �`�揈��
//
//	OBJ2D* searchSet(MOVER mover, D3DXVECTOR2 pos);	// OBJ�̒ǉ�
////private:
////	virtual int getSize() = 0;
//}
#include "Collision.h"
#include "YSDBG.h"
#include "myFunc.h"
#include <assert.h>

int getData(int map[CHIP_NUMY][CHIP_NUMX], float x, float y)
{
	int divX = static_cast<int>(x) >> 6;      // x�����̃C���f�b�N�X
	int divY = static_cast<int>(y) >> 6;      // y�����̃C���f�b�N�X
	return map[divY][divX];
}

int getTerrainAttr(float x, float y)
{
	int index = getData(chip_data, x, y);

	// �C���f�b�N�X��-1�ł����TR_NONE��Ԃ�
	if (index < 0 || index>CHIP_DIV_X*CHIP_DIV_Y) return -1;

	// x�����̃C���f�b�N�X
	int remX = index % CHIP_DIV_X;

	// y�����̃C���f�b�N�X
	int divY = index / CHIP_DIV_Y;

	// �Y���͈̔̓`�F�b�N
	//assert(remX >= 0 && remX < CHIP_DIV_X);
	//assert(divY >= 0 && divY < CHIP_DIV_Y);

	// ���^�[��
	return terrainAttr[divY][remX];
}


bool isUpperQuater(float y)
{
	return wrap(static_cast<int>(y), 0, CHIP_SIZE) < CHIP_SIZE >> 2;
}

bool isHitDown(float x, float y)
{
	switch (getTerrainAttr(x, y))
	{
	case TR_ATTR::TR_NONE:return false;
		break;
	}
	return true;
}

bool isHitAll(float x, float y)
{
	switch (getTerrainAttr(x, y))
	{
	case TR_ATTR::TR_NONE:return false;
		break;
	}
	return true;
}

//--------------------------------
//  �������ɕǂɂ߂荞��ł��邩�ǂ����𔻒�
//--------------------------------
bool isFloor(float x, float y, float width)
{
	for (; width > 0; width -= CHIP_SIZE)               // width��CHIP_SIZE�����炵�Ă���
	{
		if (isHitDown(x - width, y)) return true;       // ���[����
		if (isHitDown(x + width, y)) return true;       // �E�[����
	}
	return isHitDown(x, y);                             // �Ō�ɐ^�񒆂Ŕ���
}

//�V��
bool isCeiling(float x, float y, float width)
{
	for (; width > 0; width -= CHIP_SIZE)
	{
		if (isHitAll(x, y))return true;
		if (isHitAll(x, y))return true;
	}
	return false;
}


bool isWall(float x, float y, float height)
{
	for (; height > 0; height -= CHIP_SIZE)
	{
		if (isHitAll(x, y))return true;
	}
	return false;
}


//--------------------------------
//  �������ɂ߂荞��ł����ꍇ�Ay���W���C������
//--------------------------------
void mapHoseiDown(BaseObject* obj)
{
	static constexpr float ADJUST_Y = 0.125f;
	float y = obj->getPos(false);                          // �킩��₷���������߂�������y�ɑ��
	y -= wrap(y, 0.0f, static_cast<float>(CHIP_SIZE));  // 0.0f����CHIP_SIZE�܂ł̊Ԃ����b�v�A���E���h������
	obj->setPosY(y - ADJUST_Y);                     // ������������
	obj->setSpeedY((std::min)(obj->getSpeed(false), 0.0f));      // �n�ʂɂ��������̂ő��x���~�܂�
}


void mapHoseiUp(BaseObject* obj)
{
	static constexpr float ADJUST_Y = 0.125f;
	float y = obj->getPos(false) - obj->getSize(false);
	y -= wrap(static_cast<int>(obj->getSize(false)), -32, 0);
	y += obj->getSize(false);
	if (obj->getSpeed(false) < 0)obj->setSpeedY(0.0f);
}


void mapHoseiRight(BaseObject* obj)
{
	static constexpr float ADJUST_X = 0.125f;
	float x = obj->getPos(true) + obj->getSize(true);
	x -= wrap(x, 0.0f, static_cast<float>(CHIP_SIZE));
	obj->setPosX(x - obj->getSize(true) - ADJUST_X);
	obj->setSpeedX(0.0f);
}


void mapHoseiLeft(BaseObject* obj)
{
	static constexpr float ADJUST_X = 0.125f;
	float x = obj->getPos(true) - obj->getSize(true);
	x -= wrap(x, -(static_cast<float>(CHIP_SIZE)), 0.0f);
	obj->setPosX(x + obj->getSize(true) + ADJUST_X);
	obj->setSpeedX(0.0f);
}

void mapHoseiDown(OBJ2D* obj)
{
	static constexpr float ADJUST_Y = 0.125f;
	float y = obj->pos.y;                          // �킩��₷���������߂�������y�ɑ��
	y -= wrap(y, 0.0f, static_cast<float>(CHIP_SIZE));  // 0.0f����CHIP_SIZE�܂ł̊Ԃ����b�v�A���E���h������
	obj->pos.y = (y - ADJUST_Y);                     // ������������
	obj->accel.y = (std::min)(obj->accel.y, 0.0f);      // �n�ʂɂ��������̂ő��x���~�܂�
}


void mapHoseiUp(OBJ2D* obj)
{
	static constexpr float ADJUST_Y = 0.125f;
	float y = obj->pos.y - obj->sizeY;
	y -= wrap(static_cast<int>(obj->sizeY), -32, 0);
	y += obj->sizeY;
	if (obj->accel.y < 0)obj->accel.y = (0.0f);
}


void mapHoseiRight(OBJ2D* obj)
{
	static constexpr float ADJUST_X = 0.125f;
	float x = obj->pos.x + obj->sizeX;
	x -= wrap(x, 0.0f, static_cast<float>(CHIP_SIZE));
	obj->pos.x = x - obj->sizeX - ADJUST_X;
	obj->accel.x = 0.0f;
}


void mapHoseiLeft(OBJ2D* obj)
{
	static constexpr float ADJUST_X = 0.125f;
	float x = obj->pos.x - obj->sizeX;
	x -= wrap(x, -(static_cast<float>(CHIP_SIZE)), 0.0f);
	obj->pos.x = x + obj->sizeX + ADJUST_X;
	obj->accel.x = 0.0f;
}
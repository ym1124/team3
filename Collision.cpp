#include "Collision.h"
#include "YSDBG.h"
#include "myFunc.h"
#include <assert.h>

int getData(int map[CHIP_NUMY][CHIP_NUMX], float x, float y)
{
	int divX = static_cast<int>(x) >> 6;      // x方向のインデックス
	int divY = static_cast<int>(y) >> 6;      // y方向のインデックス
	return map[divY][divX];
}

int getTerrainAttr(float x, float y)
{
	int index = getData(chip_data, x, y);

	// インデックスが-1であればTR_NONEを返す
	if (index < 0 || index>CHIP_DIV_X*CHIP_DIV_Y) return -1;

	// x方向のインデックス
	int remX = index % CHIP_DIV_X;

	// y方向のインデックス
	int divY = index / CHIP_DIV_Y;

	// 添字の範囲チェック
	//assert(remX >= 0 && remX < CHIP_DIV_X);
	//assert(divY >= 0 && divY < CHIP_DIV_Y);

	// リターン
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
//  下方向に壁にめり込んでいるかどうかを判定
//--------------------------------
bool isFloor(float x, float y, float width)
{
	for (; width > 0; width -= CHIP_SIZE)               // widthをCHIP_SIZE分減らしていく
	{
		if (isHitDown(x - width, y)) return true;       // 左端から
		if (isHitDown(x + width, y)) return true;       // 右端から
	}
	return isHitDown(x, y);                             // 最後に真ん中で判定
}

//天井
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
//  下方向にめり込んでいた場合、y座標を修正する
//--------------------------------
void mapHoseiDown(BaseObject* obj)
{
	static constexpr float ADJUST_Y = 0.125f;
	float y = obj->getPos(false);                          // わかりやすく書くためいったんyに代入
	y -= wrap(y, 0.0f, static_cast<float>(CHIP_SIZE));  // 0.0fからCHIP_SIZEまでの間をラップアラウンドさせる
	obj->setPosY(y - ADJUST_Y);                     // 少し浮かせる
	obj->setSpeedY((std::min)(obj->getSpeed(false), 0.0f));      // 地面にあたったので速度が止まる
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
	float y = obj->pos.y;                          // わかりやすく書くためいったんyに代入
	y -= wrap(y, 0.0f, static_cast<float>(CHIP_SIZE));  // 0.0fからCHIP_SIZEまでの間をラップアラウンドさせる
	obj->pos.y = (y - ADJUST_Y);                     // 少し浮かせる
	obj->accel.y = (std::min)(obj->accel.y, 0.0f);      // 地面にあたったので速度が止まる
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
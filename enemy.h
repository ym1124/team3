#pragma once
#include "DxLib.h"
#include "vector.h"

class enemy
{
public:
	vector2 pos;
	static int enemyGh;
	enemy();
	void initEnemy();
	void moveEnemy();
	void drawEnemy();
};
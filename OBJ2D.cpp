#include "OBJ2D.h"

OBJ2D::OBJ2D()
{
	clear();
}

void OBJ2D::clear()
{
	texture = 0;
	pos = vector2(0, 0);
	mover = nullptr;
}

void OBJ2D::update()
{
	//関数ポインタに入力された関数の実行
	mover(this);
}

void OBJ2D::draw()
{
	//画像が入っていれば描画
	if (texture)
		DrawGraph(pos.x, pos.y, texture, true);
	//画像が入っていなければ停止
	//assert(!texture);
}

void OBJ2D::setObject(vector2 pos)
{
}

void testMove(OBJ2D *obj)
{
	if (key[KEY_INPUT_RIGHT]  >1)
		obj->pos.x++;
	if (key[KEY_INPUT_LEFT] > 1)
		obj->pos.x--;
	if (key[KEY_INPUT_UP] >1)
		obj->pos.y--;
	if (key[KEY_INPUT_DOWN] >1)
		obj->pos.y++;
}
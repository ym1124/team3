#include "OBJ2D.h"

OBJ2D::OBJ2D():animator()
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

void OBJ2D::setObject(vector2 pos)
{
}

animator::animator()
{
	texture = 0;
}

void animator::setTextureInfo(int sheetsNum, int speed, int srcX, int srcY, int sizeX, int sizeY)
{
	this->sheetsNum = sheetsNum;
	this->speed = speed;
	this->srcX = srcX;
	this->srcY = srcY;
	this->sizeX = sizeX;
	this->sizeY = sizeY;
}

void animator::draw(bool animationFlg)
{
	//画像が入っていれば描画(アニメーション無し)
	if (!animationFlg)
	{
		if (texture)
			DrawGraph(pos.x - camera_pos.x, pos.y - camera_pos.y, texture, true);
	}
	//画像が入っていれば描画(アニメーション有り)
	if (animationFlg)
	{
		if (texture)
		{
			animCnt++;
			DrawRectGraph(pos.x - camera_pos.x, pos.y - camera_pos.y, srcX + (animCnt / speed%sheetsNum*sizeX), srcY, sizeX, sizeY, texture, true);
		}
	}
	//画像が入っていなければ停止
	//assert(!texture);
}
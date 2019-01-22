#include "OBJ2D.h"

OBJ2D::OBJ2D():animator()
{
	clear();
}

void OBJ2D::clear()
{
	texture = nullptr;
	pos = vector2(0, 0);
	mover = nullptr;
	sheetsNum = 0;
	speed = 0;
	srcX = 0;
	srcY = 0;
	sizeX = 0;
	sizeY = 0;
}

void OBJ2D::update()
{
	//関数ポインタに入力された関数の実行
	mover(this);
}

//位置、画像、移動関数を設定
void OBJ2D::setObject(vector2 pos, int *texture, MOVER mover)
{
	this->pos = pos;
	this->texture = texture;
	this->mover = mover;
}

animator::animator()
{
	texture = 0;
}

//画像情報の設定
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
		if (texture!=nullptr)
			DrawRectGraph(pos.x - camera_pos.x, pos.y - camera_pos.y, srcX, srcY, sizeX, sizeY, *texture, true);
	}
	//画像が入っていれば描画(アニメーション有り)
	if (animationFlg)
	{
		if (texture != nullptr)
		{
			animCnt++;
			DrawRectGraph(pos.x - camera_pos.x, pos.y - camera_pos.y, srcX + (animCnt / speed%sheetsNum*sizeX), srcY, sizeX, sizeY, *texture, true);
		}
	}
	//画像が入っていなければ停止
	//assert(!texture);
}
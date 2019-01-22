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
	//�֐��|�C���^�ɓ��͂��ꂽ�֐��̎��s
	mover(this);
}

//�ʒu�A�摜�A�ړ��֐���ݒ�
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

//�摜���̐ݒ�
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
	//�摜�������Ă���Ε`��(�A�j���[�V��������)
	if (!animationFlg)
	{
		if (texture!=nullptr)
			DrawRectGraph(pos.x - camera_pos.x, pos.y - camera_pos.y, srcX, srcY, sizeX, sizeY, *texture, true);
	}
	//�摜�������Ă���Ε`��(�A�j���[�V�����L��)
	if (animationFlg)
	{
		if (texture != nullptr)
		{
			animCnt++;
			DrawRectGraph(pos.x - camera_pos.x, pos.y - camera_pos.y, srcX + (animCnt / speed%sheetsNum*sizeX), srcY, sizeX, sizeY, *texture, true);
		}
	}
	//�摜�������Ă��Ȃ���Β�~
	//assert(!texture);
}
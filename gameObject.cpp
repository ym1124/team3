#include "gameObject.h"

Lanthanum Lanthanums[LANTHANUM_MAX];

void Lanthanumfire::setObjectTemp(vector2 pos)
{
	if (!texture)
	{
		setObject(pos, &lanthanum::fireGh, LanthanumMove);//update����ɂ��̏������Ȃ��ƃ_���I
		setTextureInfo(15, 10, 0, 0, 100, 100);//�摜���ݒ肵�Ă���
	}
}

Lanthanum::Lanthanum() :OBJ2D()
{
}

void Lanthanum::setObjectTemp(vector2 pos)
{
	if (!texture)
	{
		setObject(pos, &lanthanum::lanthanumGh, LanthanumMove);//mover��nullptr���ƃG���[�ł�̂�Update���O�ōs��
		setTextureInfo();//�摜���ݒ肵�Ă���
	}
	f.setObjectTemp(pos);
}

void LanthanumMove(OBJ2D *obj)
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

//�e���v���[�g������?
void LanthanumsUpdate()
{
	for (auto &it : Lanthanums)
	{
		it.update();
		it.f.update();
	}
}

void LanthanumsDraw()
{
	for (auto &it : Lanthanums)
	{
		it.draw();
		it.f.draw(true);
	}
}


void LanthanumsSetObject()
{
	Lanthanums[0].setObjectTemp(vector2(700, 700));
	Lanthanums[1].setObjectTemp(vector2(100,100));
	Lanthanums[2].setObjectTemp(vector2(200, 100));
	Lanthanums[3].setObjectTemp(vector2(300, 100));
	Lanthanums[4].setObjectTemp(vector2(400, 100));
	Lanthanums[5].setObjectTemp(vector2(500, 100));
	Lanthanums[6].setObjectTemp(vector2(600, 100));
	Lanthanums[7].setObjectTemp(vector2(700, 100));
	Lanthanums[8].setObjectTemp(vector2(800, 100));
	Lanthanums[9].setObjectTemp(vector2(900, 100));
	Lanthanums[10].setObjectTemp(vector2(100, 400));
	Lanthanums[11].setObjectTemp(vector2(200, 400));
	Lanthanums[12].setObjectTemp(vector2(300, 400));
	Lanthanums[13].setObjectTemp(vector2(400, 400));
	Lanthanums[14].setObjectTemp(vector2(500, 400));
	Lanthanums[15].setObjectTemp(vector2(550, 400));
	Lanthanums[16].setObjectTemp(vector2(600, 400));
	Lanthanums[17].setObjectTemp(vector2(650, 400));
	Lanthanums[18].setObjectTemp(vector2(700, 400));
	Lanthanums[19].setObjectTemp(vector2(750, 400));
}

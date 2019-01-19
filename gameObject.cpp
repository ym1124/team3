#include "gameObject.h"

Lanthanum Lanthanums[20];

void Lanthanumfire::setObject(vector2 pos)
{
	if (!texture)
	{
		this->pos = pos;
		texture = lanthanum::fireGh;
		mover = LanthanumMove;//updateより先にこの処理しないとダメ！
		setTextureInfo(15, 10, 0, 0, 100, 100);//画像情報設定しておく
	}
}

Lanthanum::Lanthanum() :OBJ2D()
{
	
}

void Lanthanum::setObject(vector2 pos)
{
	if (!texture)
	{
		this->pos = pos;
		texture = lanthanum::lanthanumGh;
		mover = LanthanumMove;//updateより先にこの処理しないとダメ！
		setTextureInfo(15, 10, 0, 0, 100, 100);//画像情報設定しておく
	}
	f.setObject(pos);
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

//テンプレート化する
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
	Lanthanums[1].setObject(vector2(100,100));
	Lanthanums[2].setObject(vector2(200, 200));
	Lanthanums[3].setObject(vector2(300, 300));
	Lanthanums[4].setObject(vector2(400, 400));
	Lanthanums[5].setObject(vector2(500, 500));
	Lanthanums[6].setObject(vector2(600, 600));
	Lanthanums[7].setObject(vector2(700, 700));
	Lanthanums[8].setObject(vector2(700, 700));
	Lanthanums[9].setObject(vector2(700, 700));
	Lanthanums[10].setObject(vector2(700, 700));
	Lanthanums[11].setObject(vector2(700, 700));
	Lanthanums[12].setObject(vector2(700, 700));
	Lanthanums[13].setObject(vector2(700, 700));
	Lanthanums[14].setObject(vector2(700, 700));
	Lanthanums[15].setObject(vector2(700, 700));
	Lanthanums[16].setObject(vector2(700, 700));
	Lanthanums[17].setObject(vector2(700, 700));
	Lanthanums[18].setObject(vector2(700, 700));
	Lanthanums[19].setObject(vector2(700, 700));
	Lanthanums[0].setObject(vector2(700, 700));

}

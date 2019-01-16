#include "gameObject.h"

Lanthanum testLanthanum1;

Lanthanum::Lanthanum() :OBJ2D()
{
	
}

void Lanthanum::setObject(vector2 pos)
{
	if (!setFlg)
	{
		this->pos = pos;
		texture = lanthanum::lanthanumGh;
		mover = testMove;//updateより先にこの処理しないとダメ！
		setFlg = true;
	}
}


#include "gameObject.h"

Lanthanum testLanthanum1;

Lanthanum::Lanthanum() :OBJ2D()
{
	
}

void Lanthanum::setObject(vector2 pos)
{
	if (!texture)
	{
		this->pos = pos;
		texture = lanthanum::lanthanumGh;
		mover = testMove;//update����ɂ��̏������Ȃ��ƃ_���I
	}
}


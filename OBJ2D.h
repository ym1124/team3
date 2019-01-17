#pragma once
#include "DxLib.h"
#include "common.h"
#include "vector.h"

#include "light.h"

class OBJ2D;
typedef void(*MOVER)(OBJ2D *obj);

class OBJ2D
{
public:
	vector2 pos;
	int texture;

	OBJ2D();
	void clear();
	MOVER mover;
	virtual void update();
	virtual void draw();
	virtual void setObject(vector2 pos)=0;
};

void testMove(OBJ2D *obj);
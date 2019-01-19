#pragma once
#include "DxLib.h"
#include "OBJ2D.h"

class Lanthanumfire :public OBJ2D
{
public:
	void setObject(vector2 pos);
};

class Lanthanum:public OBJ2D
{
public:
	Lanthanum();
	Lanthanumfire f;
	void setObject(vector2 pos);
};
extern Lanthanum Lanthanums[20];
void LanthanumMove(OBJ2D *obj);
void LanthanumsUpdate();
void LanthanumsDraw();
void LanthanumsSetObject();
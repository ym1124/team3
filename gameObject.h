#pragma once
#include "DxLib.h"
#include "OBJ2D.h"
#include "template.h"

const int LANTHANUM_MAX = 20;

class Lanthanumfire :public OBJ2D
{
public:
	void setObjectTemp(vector2 pos);
};

class Lanthanum:public OBJ2D
{
public:
	Lanthanum();
	Lanthanumfire f;
	void setObjectTemp(vector2 pos);
};
extern Lanthanum Lanthanums[LANTHANUM_MAX];
void LanthanumMove(OBJ2D *obj);
void LanthanumsUpdate();
void LanthanumsDraw();
void LanthanumsSetObject();
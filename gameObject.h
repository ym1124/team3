#pragma once
#include "DxLib.h"
#include "OBJ2D.h"
#include "Player.h"

//************�萔***************//
const int LANTHANUM_MAX = 20;
const int WOODENBOX_MAX = 10;
const int SKELETON_MAX = 5;
const int SIGNBORDLEFT_MAX = 2;
//************����***************//
extern int objGh1;

void loadObjectGraphics();

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
void noMove(OBJ2D *obj);
//�V�Ղ牻
//void LanthanumsUpdate();
//void LanthanumsDraw();
void LanthanumsSetObject();

class woodenbox:public OBJ2D
{
public:
	woodenbox();
	void setObjectTemp(vector2 pos);
};
extern woodenbox woodenboxs[WOODENBOX_MAX];
void possessionMove(OBJ2D *obj);
void woodenboxSetObject();

class skeleton :public OBJ2D
{
public:
	skeleton();
	void setObjectTemp(vector2 pos);
};
extern skeleton skeletons[SKELETON_MAX];
void skeletonSetObject();

class signbordleft :public OBJ2D
{
public:
	signbordleft();
	void setObjectTemp(vector2 pos);
};
extern signbordleft signbordlefts[SIGNBORDLEFT_MAX];        
void signbordleftSetObject();


//***********All�n**************//
void gameObjectSetAll();
void gameObjectUpdateAll();
void gameObjectDrawAll();
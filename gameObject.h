#pragma once
#include "DxLib.h"
#include "OBJ2D.h"
#include "Player.h"

//************íËêî***************//
const int LANTHANUM_MAX = 20;
const int WOODENBOX_MAX = 10;
const int SKELETON_MAX = 5;
const int SIGNBORDLEFT_MAX = 2;
const int BIGLANTHANUM_MAX = 5;
const int IRONBAR_MAX = 5;
//************é¿ëÃ***************//
extern int objGh1;

void loadObjectGraphics();

class Lanthanumfire :public OBJ2D
{
public:
	void setObjectTemp(vector2 pos);
};

class Lanthanum :public OBJ2D
{
public:
	Lanthanum();
	Lanthanumfire f;
	void setObjectTemp(vector2 pos);
};
extern Lanthanum Lanthanums[LANTHANUM_MAX];
void noMove(OBJ2D *obj);
//ìVÇ’ÇÁâª
//void LanthanumsUpdate();
//void LanthanumsDraw();
void LanthanumsSetObject();

class woodenbox :public OBJ2D
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

class bigLanthanum :public OBJ2D
{
public:
	bigLanthanum();
	void setObjectTemp(vector2 pos);
};
extern bigLanthanum bigLanthanums[BIGLANTHANUM_MAX];
void bigLanthanumSetObject();

class bigLanthanumFire :public OBJ2D
{
public:
	static bool inSoulFlg;
	bigLanthanumFire();
	void setObjectTemp(vector2 pos);
};
extern bigLanthanumFire bigLanthanumFire1;
void bigLanthanumFireSetObject();
void serchInsoulLanthanum(OBJ2D *obj);

class ironbar : public OBJ2D
{
public:
	ironbar();
	void setObjectTemp(vector2 pos);
};
extern ironbar ironbars[IRONBAR_MAX];
void ironbarSetObject();

//***********Allån**************//
void gameObjectSetAll();
void gameObjectUpdateAll();
void gameObjectDrawAll();
#include "gameObject.h"

int objGh1;
Lanthanum Lanthanums[LANTHANUM_MAX];
woodenbox woodenboxs[WOODENBOX_MAX];
skeleton skeletons[SKELETON_MAX];
signbordleft signbordlefts[SIGNBORDLEFT_MAX];

void loadObjectGraphics()
{
	if (!objGh1)
	{
		objGh1 = LoadGraph("resource/image/objGh1.png", false);
	}
}

//****************************ランタン****************************
void Lanthanumfire::setObjectTemp(vector2 pos)
{
	if (!texture)
	{
		setObject(pos, &lanthanum::fireGh, noMove);//updateより先にこの処理しないとダメ！
		setTextureInfo(15, 20, 0, 0, 100, 100);//画像情報設定しておく
	}
}

Lanthanum::Lanthanum() :OBJ2D()
{
}

void Lanthanum::setObjectTemp(vector2 pos)
{
	if (!texture)
	{
		setObject(pos, &lanthanum::lanthanumGh, noMove);//moverがnullptrだとエラーでるのでUpdateより前で行う
		setTextureInfo(0,0,0,0,100,100);//画像情報設定しておく
	}
	f.setObjectTemp(pos);
}

void noMove(OBJ2D *obj)
{
}

//テンプレート化した
//void LanthanumsUpdate()
//{
//	for (auto &it : Lanthanums)
//	{
//		it.update();
//		it.f.update();
//	}
//}

//void LanthanumsDraw()
//{
//	for (auto &it : Lanthanums)
//	{
//		it.draw();
//		it.f.draw(true);
//	}
//}


void LanthanumsSetObject()
{
	Lanthanums[0].setObjectTemp(vector2(700, 200));
	Lanthanums[1].setObjectTemp(vector2(100,300));
	Lanthanums[2].setObjectTemp(vector2(500, 300));
	Lanthanums[3].setObjectTemp(vector2(900, 300));
	Lanthanums[4].setObjectTemp(vector2(1300, 300));
	Lanthanums[5].setObjectTemp(vector2(1700, 300));
	Lanthanums[6].setObjectTemp(vector2(2100, 300));
	Lanthanums[7].setObjectTemp(vector2(2500, 300));
	Lanthanums[8].setObjectTemp(vector2(2900, 300));
	Lanthanums[9].setObjectTemp(vector2(3300, 300));
	Lanthanums[10].setObjectTemp(vector2(100, 500));
	Lanthanums[11].setObjectTemp(vector2(500, 500));
	Lanthanums[12].setObjectTemp(vector2(900, 500));
	Lanthanums[13].setObjectTemp(vector2(1300, 500));
	Lanthanums[14].setObjectTemp(vector2(1700, 500));
	Lanthanums[15].setObjectTemp(vector2(2100, 500));
	Lanthanums[16].setObjectTemp(vector2(2500, 500));
	Lanthanums[17].setObjectTemp(vector2(2900, 500));
	Lanthanums[18].setObjectTemp(vector2(3300, 500));
	Lanthanums[19].setObjectTemp(vector2(3700, 500));
}


void possessionMove(OBJ2D *obj)
{

}

//********************木箱*************************************
woodenbox::woodenbox() :OBJ2D()
{
}

void woodenbox::setObjectTemp(vector2 pos)
{
	if (!texture)
	{
		setObject(pos, &objGh1, possessionMove);//moverがnullptrだとエラーでるのでUpdateより前で行う
		setTextureInfo(0,0,0,0,48,48);//画像情報設定しておく
	}
}

void woodenboxSetObject()
{
	woodenboxs[0].setObjectTemp(vector2(3*CHIP_SIZE, 9 * CHIP_SIZE+16));
	woodenboxs[1].setObjectTemp(vector2(20 * CHIP_SIZE, 9 * CHIP_SIZE+16));
	woodenboxs[2].setObjectTemp(vector2(15 * CHIP_SIZE, 9 * CHIP_SIZE+16));
	woodenboxs[3].setObjectTemp(vector2(21 * CHIP_SIZE, 9 * CHIP_SIZE+16));
	woodenboxs[4].setObjectTemp(vector2(29 * CHIP_SIZE, 9 * CHIP_SIZE+16));
	woodenboxs[5].setObjectTemp(vector2(33 * CHIP_SIZE, 9 * CHIP_SIZE+16));
	woodenboxs[6].setObjectTemp(vector2(810, 9 * CHIP_SIZE+16));
	woodenboxs[7].setObjectTemp(vector2(45 * CHIP_SIZE, 9 * CHIP_SIZE + 16));
	woodenboxs[8].setObjectTemp(vector2(51 * CHIP_SIZE, 9 * CHIP_SIZE + 16));
	woodenboxs[9].setObjectTemp(vector2(60 * CHIP_SIZE, 9 * CHIP_SIZE + 16));
}

//**********************スケルトン**************************************

skeleton::skeleton() :OBJ2D()
{
}

void skeleton::setObjectTemp(vector2 pos)
{
	if (!texture)
	{
		setObject(pos, &objGh1, noMove);//moverがnullptrだとエラーでるのでUpdateより前で行う
		setTextureInfo(0, 0, 0, 220, 25, 25);//画像情報設定しておく
	}
}

void skeletonsSetObject()
{
	skeletons[0].setObjectTemp(vector2(13*CHIP_SIZE, 9* CHIP_SIZE+39));
	skeletons[1].setObjectTemp(vector2(11*CHIP_SIZE, 9* CHIP_SIZE+39));
	skeletons[2].setObjectTemp(vector2(810, 9* CHIP_SIZE+39));
	skeletons[3].setObjectTemp(vector2(114, 9* CHIP_SIZE+39));
	skeletons[4].setObjectTemp(vector2(514, 9* CHIP_SIZE+39));
}

//*************************標識***************************
signbordleft::signbordleft() :OBJ2D()
{
}

void signbordleft::setObjectTemp(vector2 pos)
{
	if (!texture)
	{
		setObject(pos, &objGh1, possessionMove);//moverがnullptrだとエラーでるのでUpdateより前で行う
		setTextureInfo(0, 0, 0, 92, 64, 64);//画像情報設定しておく
	}
}

void signbordleftSetObject()
{
	signbordlefts[0].setObjectTemp(vector2(190, CHIP_SIZE*9));
	signbordlefts[1].setObjectTemp(vector2(560, CHIP_SIZE * 9));
}




//*********All系************//
void gameObjectSetAll()
{
	loadObjectGraphics();
	signbordleftSetObject();
	woodenboxSetObject();
	LanthanumsSetObject();
	skeletonsSetObject();
}
void gameObjectUpdateAll()
{
	updateLanthanums(Lanthanums, LANTHANUM_MAX);
	tempGameObjectUpdate(woodenboxs, WOODENBOX_MAX);
	tempGameObjectUpdate(signbordlefts, SIGNBORDLEFT_MAX);
	tempGameObjectUpdate(skeletons, SKELETON_MAX);
}

void gameObjectDrawAll()
{
	drawLanthanums(Lanthanums, LANTHANUM_MAX);
	tempGameObjectDraw(woodenboxs, WOODENBOX_MAX, false);
	tempGameObjectDraw(signbordlefts, SIGNBORDLEFT_MAX, false);
	tempGameObjectDraw(skeletons, SKELETON_MAX, false);
}
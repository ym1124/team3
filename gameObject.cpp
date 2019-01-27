#include "gameObject.h"
#include "Collision.h"

int objGh1;
bool bigLanthanumFire::inSoulFlg = false;
Lanthanum Lanthanums[LANTHANUM_MAX];
woodenbox woodenboxs[WOODENBOX_MAX];
skeleton skeletons[SKELETON_MAX];
signbordleft signbordlefts[SIGNBORDLEFT_MAX];
bigLanthanum bigLanthanums[BIGLANTHANUM_MAX];
bigLanthanumFire bigLanthanumFire1;
ironbar ironbars[IRONBAR_MAX];

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
		setTextureInfo(0, 0, 0, 0, 100, 100);//画像情報設定しておく
	}
	f.setObjectTemp(vector2(pos.x, pos.y));
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
	Lanthanums[1].setObjectTemp(vector2(100, 300));
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
	static constexpr float SPEED_MAX_Y = 12.0f;
	static constexpr float GRAVITY = 0.7f;
	//static constexpr float GROUND_POS = 700.0f;

	static bool hit[WOODENBOX_MAX][WOODENBOX_MAX] = { false };
	int num = 0;
	for (int j = 0; j < WOODENBOX_MAX; j++)
	{
		if (obj != &woodenboxs[j])continue;
		num = j;
		break;
	}
	for (int i = 0; i < WOODENBOX_MAX; i++)
	{
		if (obj->pos.x < (woodenboxs[i].pos.x + woodenboxs[i].sizeX*0.5f) && obj->pos.x >(woodenboxs[i].pos.x - woodenboxs[i].sizeX*0.5f))
		{
			if (hit[num][i] && !isHitObject(obj, &woodenboxs[i]))
			{
				objHoseiDown(obj);
				break;
			}
		}
		hit[num][i] = isHitObject(obj, &woodenboxs[i]);
	}

	obj->accel.y += GRAVITY;
	if (obj->accel.y >= SPEED_MAX_Y)
	{
		obj->accel.y = SPEED_MAX_Y;
	}
	obj->old.y = obj->pos.y;
	obj->pos.y += obj->accel.y;
	obj->delta.y = obj->old.y - obj->pos.y;


	if (obj->delta.y < 0)
	{
		if (isFloor(obj->pos.x, obj->pos.y, 15))
		{
			mapHoseiDown(obj);
		}
	}
	if (obj->delta.y > 0)
	{
		if (isCeiling(obj->pos.x, obj->pos.y - 50, 15))
		{
			mapHoseiUp(obj);
		}
	}


	if (controlPL == PLcon::BOX)
	{
		if (!obj->inSoul)return;
		Player *pl = &player;
		obj->pos.x = pl->pl_S->getPos(true);
		obj->pos.y = pl->pl_S->getPos(false);
	}

	if (obj->delta.x > 0)
	{
		if (isWall(obj->pos.x + 15, obj->pos.y, 50))
		{
			mapHoseiRight(obj);
		}
	}
	if (obj->delta.x < 0)
	{
		if (isWall(obj->pos.x - 15, obj->pos.y, 50))
		{
			mapHoseiLeft(obj);
		}
	}
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
		setTextureInfo(0, 0, 0, 0, 48, 48);//画像情報設定しておく
	}
}

void woodenboxSetObject()
{
	woodenboxs[0].setObjectTemp(vector2(3 * CHIP_SIZE, 9 * CHIP_SIZE + 16));
	woodenboxs[1].setObjectTemp(vector2(20 * CHIP_SIZE, 9 * CHIP_SIZE + 16));
	woodenboxs[2].setObjectTemp(vector2(15 * CHIP_SIZE, 9 * CHIP_SIZE + 16));
	woodenboxs[3].setObjectTemp(vector2(21 * CHIP_SIZE, 9 * CHIP_SIZE + 16));
	woodenboxs[4].setObjectTemp(vector2(29 * CHIP_SIZE, 9 * CHIP_SIZE + 16));
	woodenboxs[5].setObjectTemp(vector2(33 * CHIP_SIZE, 9 * CHIP_SIZE + 16));
	woodenboxs[6].setObjectTemp(vector2(810, 9 * CHIP_SIZE + 16));
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
	skeletons[0].setObjectTemp(vector2(13 * CHIP_SIZE, 9 * CHIP_SIZE + 39));
	skeletons[1].setObjectTemp(vector2(11 * CHIP_SIZE, 9 * CHIP_SIZE + 39));
	skeletons[2].setObjectTemp(vector2(810, 9 * CHIP_SIZE + 39));
	skeletons[3].setObjectTemp(vector2(114, 9 * CHIP_SIZE + 39));
	skeletons[4].setObjectTemp(vector2(514, 9 * CHIP_SIZE + 39));
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
	signbordlefts[0].setObjectTemp(vector2(190, CHIP_SIZE * 9));
	signbordlefts[1].setObjectTemp(vector2(560, CHIP_SIZE * 9));
}

//*************************でかランタン***************************
bigLanthanum::bigLanthanum() :OBJ2D()
{
}

void bigLanthanum::setObjectTemp(vector2 pos)
{
	if (!texture)
	{
		setObject(pos, &objGh1, noMove);//moverがnullptrだとエラーでるのでUpdateより前で行う
		setTextureInfo(0, 0, 0, 48, 32, 44);//画像情報設定しておく
	}
}

void bigLanthanumSetObject()
{
	bigLanthanums[0].setObjectTemp(vector2(290, CHIP_SIZE * 5));
	bigLanthanums[1].setObjectTemp(vector2(490, CHIP_SIZE * 5));
	bigLanthanums[2].setObjectTemp(vector2(690, CHIP_SIZE * 5));
	bigLanthanums[3].setObjectTemp(vector2(890, CHIP_SIZE * 5));
	bigLanthanums[4].setObjectTemp(vector2(1090, CHIP_SIZE * 5));
}

//**************でかランタンの炎***********************//
bigLanthanumFire::bigLanthanumFire() :OBJ2D()
{
}

void bigLanthanumFire::setObjectTemp(vector2 pos)
{
	if (!texture)
	{
		setObject(pos, &torch::fireGh, serchInsoulLanthanum);//moverがnullptrだとエラーでるのでUpdateより前で行う
		setTextureInfo(10, 64/*加算合成の数だけ下げる*/, 0, 200, 100, 100);//画像情報設定しておく
	}
}

//入ってるランタンに炎を灯す
void serchInsoulLanthanum(OBJ2D *obj)
{
	bigLanthanumFire::inSoulFlg = false;
	for (auto &it : bigLanthanums)
	{
		if (it.inSoul)
		{
			obj->pos = vector2(it.pos.x+2,it.pos.y+23);
			bigLanthanumFire::inSoulFlg = true;
			break;
		}
	}
}

void bigLanthanumFireSetObject()
{
	bigLanthanumFire1.setObjectTemp(vector2(290, CHIP_SIZE * 5));
}

//*************鉄格子*******************//
ironbar::ironbar() :OBJ2D()
{
}

void ironbar::setObjectTemp(vector2 pos)
{
	if (!texture)
	{
		setObject(pos, &objGh1, noMove);//moverがnullptrだとエラーでるのでUpdateより前で行う
		setTextureInfo(0, 0, 0, 245, 32, 64);//画像情報設定しておく
	}
}

void ironbarSetObject()
{
	ironbars[0].setObjectTemp(vector2(690, CHIP_SIZE * 15));
	ironbars[1].setObjectTemp(vector2(790, CHIP_SIZE * 15));
	ironbars[2].setObjectTemp(vector2(890, CHIP_SIZE * 15));
	ironbars[3].setObjectTemp(vector2(990, CHIP_SIZE * 15));
	ironbars[4].setObjectTemp(vector2(1090, CHIP_SIZE * 15));
}

//*********All系************//
void gameObjectSetAll()
{
	//loadObjectGraphics();
	signbordleftSetObject();
	woodenboxSetObject();
	LanthanumsSetObject();
	skeletonsSetObject();
	bigLanthanumSetObject();
	bigLanthanumFireSetObject();
	ironbarSetObject();
}
void gameObjectUpdateAll()
{
	updateLanthanums(Lanthanums, LANTHANUM_MAX);
	tempGameObjectUpdate(woodenboxs, WOODENBOX_MAX);
	tempGameObjectUpdate(signbordlefts, SIGNBORDLEFT_MAX);
	tempGameObjectUpdate(skeletons, SKELETON_MAX);
	tempGameObjectUpdate(&bigLanthanumFire1, 1);
	tempGameObjectUpdate(bigLanthanums, BIGLANTHANUM_MAX);
	tempGameObjectUpdate(ironbars, IRONBAR_MAX);
}

void gameObjectDrawAll()
{
	drawLanthanums(Lanthanums, LANTHANUM_MAX);
	tempGameObjectDraw(woodenboxs, WOODENBOX_MAX, false);
	tempGameObjectDraw(signbordlefts, SIGNBORDLEFT_MAX, false);
	tempGameObjectDraw(skeletons, SKELETON_MAX, false);
	//加算合成
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	if(bigLanthanumFire::inSoulFlg)tempGameObjectDraw(&bigLanthanumFire1, 1,true);
	if (bigLanthanumFire::inSoulFlg)tempGameObjectDraw(&bigLanthanumFire1, 1, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	tempGameObjectDraw(bigLanthanums, BIGLANTHANUM_MAX, false);
	tempGameObjectDraw(ironbars, IRONBAR_MAX, false);
}
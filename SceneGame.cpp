

#include "DxLib.h"
#include "common.h"
#include "SceneGame.h"
#include "gameObject.h"
#include "light.h"


void SceneGame::Update()
{
	pl->Update();

	bg->update();
	gameObjectUpdateAll();
	updateAllTorchLight(bg, pl);
	getPlTorchPointerTes()->updateLight(bg, pl);
}

void SceneGame::Draw()
{
	//‹P“xέ’θ
	SetDrawBright(155, 155, 155);
	bg->draw();
	gameObjectDrawAll();
	pl->Draw();
	//‹P“xέ’θ
	SetDrawBright(255, 255, 255);
	//•‰ζ–Κ•`‰ζ
	static int b;
	if (b == 0)
		b = LoadGraph("resource/image/black.png");
	//155‚ΕγY—ν‚Ι“―‰»‚·‚ι
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 105);
	DrawGraph(0, 0, b, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	drawAlltorch();
	getPlTorchPointerTes()->moveLight(pl);
	getPlTorchPointerTes()->t->updateTorch();
	getPlTorchPointerTes()->drawLight(pl);
	updateAllTorchLight(bg, pl);
}

SceneGame::SceneGame()
{
	pl = &player;
	bg = &background;
	gameObjectSetAll();
	lanthanum::initLanthanum();
	getPlTorchPointerTes()->initLight();
}

SceneGame::~SceneGame()
{

}

void SceneGame::Debug()
{

}

void SceneGame::Init()
{
	bg->init();

	pl->Init();
}

void SceneGame::unInit()
{

}
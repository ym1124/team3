

#include "DxLib.h"
#include "common.h"
#include "SceneGame.h"
#include "gameObject.h"
#include "light.h"

void SceneGame::Update()
{
	pl->Update();

	bg->update();

	updateAllTorchLight(bg, pl);
	getPlTorchPointerTes()->updateLight(bg, pl);
	LanthanumsUpdate();
}

void SceneGame::Draw()
{
	//‹P“xέ’θ
	SetDrawBright(125, 125, 125);
	bg->draw();

	pl->Draw();
	//‹P“xέ’θ
	SetDrawBright(255, 255, 255);
	//•‰ζ–Κ•`‰ζ
	static int b;
	if (b == 0)
		b = LoadGraph("resource/image/black.png");
	//155‚ΕγY—ν‚Ι“―‰»‚·‚ι
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 155);
	DrawGraph(0, 0, b, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	drawAlltorch();
	getPlTorchPointerTes()->moveLight(pl);
	getPlTorchPointerTes()->t->updateTorch();
	getPlTorchPointerTes()->drawLight(pl);
	updateAllTorchLight(bg, pl);
	LanthanumsDraw();
}

SceneGame::SceneGame()
{
	pl = new Player();
	bg = new BGsystem();

	lanthanum::initLanthanum();
	LanthanumsSetObject();
	getPlTorchPointerTes()->initLight();
}

SceneGame::~SceneGame()
{
	delete pl;
	delete bg;
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
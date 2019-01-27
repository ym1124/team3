

#include "DxLib.h"
#include "common.h"
#include "SceneGame.h"
#include "gameObject.h"
#include "light.h"
#include "YSDPause.h"


void SceneGame::Update()
{
	if (pause.Get_PauseState()) { pause.Update(); return; }
	if (key[pauseKey = KEY_INPUT_9] == 1)pause.PauseMode_On();

	pl->Update();

	//CameraMove(vector2(pl->pl_S->getPos(true), pl->pl_S->getPos(false)));

	bg->update();
	gameObjectUpdateAll();
	updateAllTorchLight(bg, pl);
	getPlTorchPointerTes()->updateLight(bg, pl);

	//ƒfƒoƒbƒO—p************************************
	if (key[KEY_INPUT_C] == 1)
		sceneManager::changeScene(sceneManager::CLEAR);
	//********************************************
}

void SceneGame::Draw()
{
	//‹P“xÝ’è
	SetDrawBright(155, 155, 155);
	bg->draw();
	gameObjectDrawAll();
	pl->Draw();
	//‹P“xÝ’è
	SetDrawBright(255, 255, 255);
	//•‰æ–Ê•`‰æ
	static int b;
	if (b == 0)
		b = LoadGraph("resource/image/black.png");
	//155‚ÅãY—í‚É“¯‰»‚·‚é
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 105);
	DrawGraph(0, 0, b, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	drawAlltorch();
	getPlTorchPointerTes()->moveLight(pl);
	getPlTorchPointerTes()->t->updateTorch();
	getPlTorchPointerTes()->drawLight(pl);
	updateAllTorchLight(bg, pl);

	pause.draw();
}

SceneGame::SceneGame()
{
	pl = &player;
	bg = &background;
	gameObjectSetAll();
	lanthanum::initLanthanum();
	getPlTorchPointerTes()->initLight();
	loadObjectGraphics();
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

	pause.Init();
}

void SceneGame::unInit()
{

}
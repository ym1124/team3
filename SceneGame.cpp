#include "DxLib.h"
#include "common.h"
#include "SceneGame.h"
#include "gameObject.h"
#include "light.h"

void SceneGame::Update()
{
	pl->Update();

	bg->update();

	updateAllTorchLight(bg,pl);
	getPlTorchPointerTes()->updateLight(bg,pl);
	testLanthanum1.update();
}

void SceneGame::Draw()
{
	//�P�x�ݒ�
	SetDrawBright(125, 125, 125);
	bg->draw();

	pl->Draw();
	//�P�x�ݒ�
	SetDrawBright(255, 255, 255);
	//����ʕ`��
	static int b;
	if (b == 0)
		b = LoadGraph("resource/image/black.png");
	//155���Y��ɓ�������
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 155);
	DrawGraph(0, 0, b, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	drawAlltorch();
	getPlTorchPointerTes()->moveLight(pl);
	getPlTorchPointerTes()->t->updateTorch();
	getPlTorchPointerTes()->drawLight(pl);
	testLanthanum1.draw();
	updateAllTorchLight(bg,pl);
}

SceneGame::SceneGame()
{
	pl = new Player();
	bg = new BGsystem();
	
	testLanthanum1.setObject(vector2(100, 100));
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
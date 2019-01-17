#pragma once
#include "scene.h"

class Player;

titleScene tsc;

scene::scene(): nowscene(TITLE)
{

}

void scene::sceneManager()
{
	switch (nowscene)
	{
	case TITLE:
		doTitleScene();
		break;
	case PLAY:
		doPlayScene();
		break;
	}
}

void scene::doTitleScene()
{
	tsc.initTitle();
	tsc.drawTitle();
	tsc.updateTitle();
}

void scene::doPlayScene()
{
	//この順番でやること
	pTitleInstance->drawTitle();
	pTitleInstance->updateTitle();
}

void titleScene::drawTitle()
{
	//SetDrawBright(122, 122, 122);
	//static int a = LoadGraph("resource/image/haikei.png", true);
	//DrawGraph(0, 0, a, true);
	//後で消す
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Lを押してね！！！！");
}

void titleScene::initTitle()
{

}

void titleScene::updateTitle()
{
	//色調調整
	/*bg.init();
	bg.update();
	bg.draw();*/
	//後で変える
	static int a;
	if(a==0)
	a = LoadGraph("resource/image/tempBack.png", true);
	DrawGraph(0, 0, a, true);
	//黒画面描画
	static int b;
	if(b==0)
	b = LoadGraph("resource/image/black.png");
	//155で綺麗に同化する
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 155);
	DrawGraph(0, 0, b, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//
	updateAllTorchLight();
	pl.Draw();
	pl.Update();
	drawAlltorch();
	//lanthanum1.updateLanthanum();
	/*getPlTorchPointerTes()->drawLight();
	getPlTorchPointerTes()->moveLight();*/
	testLanthanum1.setObject(vector2(100, 100));
	getPlTorchPointerTes()->updateLight();
	testLanthanum1.update();
	testLanthanum1.draw();

	if (key[KEY_INPUT_S] == 1)
		sc.nowscene = PLAY;
}
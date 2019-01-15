#pragma once
#include "scene.h"

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
		//doPlayScene();
		break;
	}
}

void scene::doTitleScene()
{
	tsc.initTitle();
	tsc.drawTitle();
	tsc.updateTitle();
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
	updateAllTorchLight();

	drawAlltorch();

	//lanthanum1.updateLanthanum();
	/*getPlTorchPointerTes()->drawLight();
	getPlTorchPointerTes()->moveLight();*/
	getPlTorchPointerTes()->updateLight();
}
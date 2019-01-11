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
	tsc.drawTitle();
	tsc.initTitle();
	tsc.updateTitle();
}

void titleScene::drawTitle()
{
	//SetDrawBright(122, 122, 122);
	//static int a = LoadGraph("resource/image/haikei.png", true);
	//DrawGraph(0, 0, a, true);
}

void titleScene::initTitle()
{

}

void titleScene::updateTitle()
{
	getLightPointertes(1)->updateLight();
	getLightPointertes(2)->updateLight();
}
#pragma once
#include "DxLib.h"
#include "Player.h"
#include "light.h"
#include "common.h"

enum { TITLE, PLAY, OVER, CLEAR,TUTORIAL };
class scene
{
public:
	int nowscene;
	scene();
	void sceneManager();
	void doTitleScene();
};

class titleScene
{
public:
	void initTitle();
	void drawTitle();
	void updateTitle();
};

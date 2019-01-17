#pragma once
#include "DxLib.h"
#include "Player.h"
#include "light.h"
#include "common.h"
#include "gameObject.h"
#include "title.h"

enum { TITLE, PLAY, OVER, CLEAR,TUTORIAL };
class scene
{
public:
	int nowscene;
	scene();
	void sceneManager();
	void doTitleScene();
	void doPlayScene();
};

extern scene sc;

class titleScene
{
public:
	void initTitle();
	void drawTitle();
	void updateTitle();
};

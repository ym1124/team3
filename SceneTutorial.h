#pragma once

#include "scene.h"
#include "Player.h"
#include "YSDBG.h"
#include "template.h"
#include "Collision.h"
#include "common.h"
#include "SceneTitle.h"
#include "gameObject.h"

class SceneTutorial : public BaseScene
{
public:
	int state,deray,select;
	int tutorialTextGh;
	vector2 triPos;
	BGsystem bg;
	Player pl;
	SceneTutorial();
	~SceneTutorial();
	void Init();
	void Update();
	void Draw();
	void Debug();
	void unInit();

	void tutorialGuide();
};

extern woodenbox box;
void boxSetObject();
#pragma once

#include "scene.h"
#include "Player.h"
#include "YSDBG.h"

class SceneGame : public BaseScene
{
public:
	SceneGame();
	~SceneGame();
	void Init();
	void unInit();
	void Update();
	void Draw();
	void Debug();

private:
	BGsystem *bg;
	Player *pl;
};
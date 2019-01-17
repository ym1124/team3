#pragma once

#include "scene.h"
#include "Player.h"


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

public:
	BGsystem *bg;
	Player *pl;
};
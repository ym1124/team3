#pragma once

#include "DxLib.h"
#include "Player.h"
#include "gameObject.h"
#include "singleton.h"

class SceneClear :public BaseScene,public singleton<SceneClear>
{
public:
	int clearGh, backGh, playerGh,lanthanumGh,fireGh, lightGh,endingGh,endingStringGh;
	int buttonSe = LoadSoundMem("resource/sound/titleButton.mp3");
	int animCnt,lightPower, lightCnt;
	int yColor;
	float speed,lightX, lightY;
	bool soundFlg,startFlg,lightFlg;
	vector2 bPos;//�w�i�̈ʒu
	vector2 pPos, lPos, fPos;//�v���C���[�A�����^���A���̈ʒu
	SceneClear();
	~SceneClear();
	void Init();
	void Update();
	void Draw();
	void Debug();
	void unInit();
	void pushStartButton();
};
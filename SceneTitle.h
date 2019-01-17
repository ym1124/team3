#pragma once

//#include "scene.h"
//
//class SceneTitle : public BaseScene
//{
//public:
//	SceneTitle();
//	void Init();
//	void unInit();
//	void Update();
//	void Draw();
//	void Debug();
//};

#include "DxLib.h"
#include "vector.h"
#include "singleton.h"
#include "scene.h"

class title :public singleton<title>, public BaseScene
{
public:
	int backGh, darkGh, lanthanumGh, playerGh, stringGh, fireGh;
	vector2 bPos1, bPos2;//�w�i�̈ʒu
	vector2 pPos, lPos, fPos;//�v���C���[�A�����^���A���̈ʒu
	int animCnt;
	bool startFlg;
	title();
	void Init();
	void unInit() {};
	void Update();
	void Draw();
	void Debug() ;

	//void initTitle();
	//void drawTitle();
	//void updateTitle();
	void pushStartButton();
};

//�^�C�g���̃C���X�^���X�̃|�C���^��Ԃ�
#define pTitleInstance (title::getInstance())
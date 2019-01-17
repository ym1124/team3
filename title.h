#pragma once
#include "DxLib.h"
#include "vector.h"
#include "singleton.h"
#include "scene.h"

class title:public singleton<title>
{
public:
	int backGh, darkGh,lanthanumGh,playerGh,stringGh,fireGh;
	vector2 bPos1, bPos2;//�w�i�̈ʒu
	vector2 pPos, lPos, fPos;//�v���C���[�A�����^���A���̈ʒu
	int animCnt;
	bool startFlg;
	title();
	void initTitle();
	void drawTitle();
	void updateTitle();
	void pushStartButton();
};

//�^�C�g���̃C���X�^���X�̃|�C���^��Ԃ�
#define pTitleInstance (title::getInstance())
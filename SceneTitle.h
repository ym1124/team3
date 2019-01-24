#pragma once

#include "DxLib.h"
#include "vector.h"
#include "singleton.h"
#include "scene.h"

class title :public singleton<title>, public BaseScene
{
public:
	int backGh, darkGh, lanthanumGh, playerGh, stringGh, fireGh, textWindowGh;
	vector2 bPos1, bPos2;//�w�i�̈ʒu
	vector2 pPos, lPos, fPos;//�v���C���[�A�����^���A���̈ʒu
	vector2 triPos;//�O�p�`�摜�̈ʒu
	int animCnt,questionState,select;
	float speed;
	bool startFlg, soundFlg;
	char questionFlg;
	static int triangleGh;
	static int buttonSe;
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
	void changeSpeed();
	void question();
};

void questionSelect(TCHAR *FormatString1, ...);
int questionCheckButton();
extern int yourColor;
extern bool tutorialFlg;

//�^�C�g���̃C���X�^���X�̃|�C���^��Ԃ�
#define pTitleInstance (title::getInstance())
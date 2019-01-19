
#include "SceneTitle.h"
#include "common.h"
#include "scene.h"

title::title()
{
	Init();
}

//������
void title::Init()
{
	//�摜�ǂݍ���
	darkGh = LoadGraph("resource/image/titleLightCircle.png", false);
	backGh = LoadGraph("resource/image/titleBack.png", false);
	lanthanumGh = LoadGraph("resource/image/titleLanthanum.png", false);
	fireGh = LoadGraph("resource/image/titleFire.png", false);
	playerGh = LoadGraph("resource/image/titlePlayer.png", false);
	stringGh = LoadGraph("resource/image/titleString.png", false);
	animCnt = 0;
	speed = 0.5;
	startFlg = false;
	soundFlg = false;
	bPos1 = vector2(0.0f, 0.0f);
	bPos2 = vector2(1280.f, 0.0f);
	pPos = vector2(500, 528);
	lPos = vector2(560, 557);
	fPos = vector2(558, 573);
}

//�X�V
void title::Update()
{
	//BGM�Đ�
	if (!soundFlg)
	{
		//��ƒ��Ȃ̂Ő؂��Ă܂�
		//PlaySoundFile("resource/sound/title.mp3", DX_PLAYTYPE_LOOP);
		soundFlg = true;
	}
	//�v���C���[�̕��������ύX
	changeSpeed();
	pPos.x += speed;
	//�v���C���[�ƃ����^���̈ʒu����
	lPos = vector2(pPos.x + 60, pPos.y + 29);
	fPos = vector2(pPos.x + 58, pPos.y + 45);
	//�w�i�ړ�����
	bPos1.x--;
	if (bPos1.x < -1280)
		bPos1.x = 0;
	bPos2.x--;
	if (bPos2.x < 0)
		bPos2.x = 1280;
	//�X�^�[�g�{�^���������ꂽ��
	if (key[KEY_INPUT_SPACE] == 1)
		startFlg = true;
	pushStartButton();
}

//�`��
void title::Draw()
{
	//�B���R�}���h(�����^���̉��̐F���ς��)
	static int state;
	state = checkHiddenCommand();
	//�A�j���[�V�����J�E���g���Z
	animCnt++;
	//�P�x�ݒ�
	SetDrawBright(255, 255, 255);
	//�w�i�u���b�N�`��
	DrawGraph(bPos1.x, bPos1.y, backGh, true);
	DrawGraph(bPos2.x, bPos2.y, backGh, true);
	//�v���C���[�`��
	if (state >3)
	{
		SetDrawBlendMode(DX_BLENDMODE_INVSRC,255);
		DrawRectGraph(pPos.x, pPos.y, 128 * (animCnt / 6 % 6), 0, 128, 128, playerGh, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else DrawRectGraph(pPos.x, pPos.y, 128 * (animCnt / 6 % 6), 0, 128, 128, playerGh, true);
	//�����^���̉��`��
	DrawRectGraph(fPos.x, fPos.y, 100 * (animCnt / 6 % 10), 100 * (state % 4), 100, 100, fireGh, true);
	//�����^���`��
	DrawGraph(lPos.x, lPos.y, lanthanumGh, true);
	//�Èŕ`��
	DrawGraph(0, 0, darkGh, true);
	//�����`��
	DrawGraph(-30, 0, stringGh, true);
	//�P�x�Đݒ�
	SetDrawBright(142, 142, 142);
}

//�X�^�[�g�{�^���������ꂽ��
void title::pushStartButton()
{
	if (startFlg)
	{
		speed = 2.0f;
		//�E�Ɉړ�����
		pPos.x += speed;
		//�V�[���J�ڏ���
		if (pPos.x > 920)
		{
			sceneManager::changeScene(sceneManager::GAME);
			//BGM��~
			StopSoundFile();
			soundFlg = false;
		}
	}
}

void title::changeSpeed()
{
	if (!startFlg)
	{
		if (pPos.x < 380)
			speed = 0.5f;
		if (pPos.x > 700)
			speed = -0.5f;
	}
}

void title::Debug()
{
	DrawFormatString(0, 0, color.Yellow, "Timer:%d///////////////////////////////////", timer);
}

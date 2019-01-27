#include "SceneClear.h"

SceneClear::SceneClear()
{
	Init();
}

SceneClear::~SceneClear()
{
}

void SceneClear::unInit()
{
}

//������
void SceneClear::Init()
{
	//�摜�ǂݍ���
	backGh = LoadGraph("resource/image/endingbackground.png", false);
	playerGh = LoadGraph("resource/image/endingCharacter193.192.png", false);
	lanthanumGh =LoadGraph("resource/image/endingLanthanum32.92.png", false);
	fireGh = LoadGraph("resource/image/endingFire.png", false);
	lightGh = LoadGraph("resource/image/endlight.png", false);
	endingGh = LoadGraph("resource/image/gameclear.png", false);
	endingStringGh = LoadGraph("resource/image/endingString.png", false);
	buttonSe = LoadSoundMem("resource/sound/titleButton.mp3");
	animCnt = 0;
	lightPower = 150;
	speed = 1.2f;
	lightX = 0;
	lightY = 0;
	lightCnt = 0;
	soundFlg = false;
	startFlg = false;
	lightFlg = false;
	bPos = vector2(0, 00);
	pPos = vector2(0, 410);
	switch (yourColor)
	{
	case 3:
	case 4:
		yColor = 0;
		break;
	case 1:
	case 2:
		yColor = 1;
		break;
	case 0:
		yColor = 2;
		break;
	case -1:
	case -2:
		yColor = 3;
		break;
	case -3:
	case -4:
		yColor = 4;
		break;
	}
}

//�X�V
void SceneClear::Update()
{
	//BGM�Đ�
	if (!soundFlg)
	{
		//��ƒ��Ȃ̂Ő؂��Ă܂�
		PlaySoundFile("resource/sound/014.ogg", DX_PLAYTYPE_LOOP);
		soundFlg = true;
	}
	//�v���C���[�̕��������ύX
	pPos.x += speed;
	//�v���C���[�ƃ����^���̈ʒu����
	lPos = vector2(pPos.x + 143, pPos.y + 45);
	fPos = vector2(pPos.x + 110, pPos.y + 50);
	//���C�g�̋���
	if (!lightFlg)
	{
		lightPower--;
		if (lightPower < 50)
			lightFlg = true;
	}
	if (lightFlg)
	{
		lightPower++;
		if (lightPower > 230)
			lightFlg = false;
	}
	pushStartButton();
	//�X�^�[�g�{�^���������ꂽ��
	if ((key[KEY_INPUT_SPACE] == 1 || key[KEY_INPUT_A] == 1 && !startFlg) || (pPos.x>1280 && !startFlg))
	{
		startFlg = true;
		animCnt = 0;
	}
}

//�`��
void SceneClear::Draw()
{
	//�A�j���[�V�����J�E���g���Z
	animCnt++;
	if (!startFlg)
	{
		//�P�x�ݒ�
		SetDrawBright(255, 255, 255);
		//�w�i�u���b�N�`��
		DrawGraph(bPos.x, bPos.y, backGh, true);
		//�v���C���[�`��
		DrawRectGraph(pPos.x, pPos.y, 193 * (animCnt / 6 % 6), 0, 193, 192, playerGh, true);
		//�����^���̉��`��
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		DrawRectGraph(fPos.x, fPos.y, 100 * (animCnt / 6 % 32), 100 * yColor, 100, 100, fireGh, true);
		DrawRectGraph(fPos.x, fPos.y, 100 * (animCnt / 6 % 32), 100 * yColor, 100, 100, fireGh, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		//�����^���`��
		DrawGraph(lPos.x, lPos.y, lanthanumGh, true);
		//���`��
		lightCnt++;
		if (lightCnt / 50 % 2 == 0)
			lightX += 0.2f;
		if (lightCnt / 50 % 2 == 1)
			lightX -= 0.2f;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
		DrawGraph(lightX, lightY, lightGh, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else
	{
		DrawGraph(0, 0, endingGh, true);
		DrawRectGraph(0, 0, 0, 0, animCnt * 2, 780, endingStringGh, true);
		int pos = animCnt * 2 - 30;
		if (pos > 977)
			pos = 977;
		if (pos > 180)
		{
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
			DrawRectGraph(pos, 440, 100 * (animCnt / 6 % 32), 100 * yColor, 100, 100, fireGh, true);//�v���C���[�̉��ɍ��킹��ق����������A�N�₩�ȉ���������
			DrawRectGraph(pos, 440, 100 * (animCnt / 6 % 32), 100 * yColor, 100, 100, fireGh, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		//**************�X�^�[�g��ʂŁuC�L�[�������ƁE�E�E�E�v���ē��ꂽ���I�I***********//
	}
}
void SceneClear::pushStartButton()
{
	if (startFlg)
	{
		if (key[KEY_INPUT_SPACE] == 1 || key[KEY_INPUT_A] == 1)
		{
			sceneManager::changeScene(sceneManager::TITLE);
			//BGM��~
			StopSoundFile();
			soundFlg = false;
		}
	}
}


void SceneClear::Debug() {}
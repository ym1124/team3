
#include "SceneTitle.h"
#include "common.h"
#include "scene.h"

int title::buttonSe;
int yourColor = 0;
static int sCnt = 0;

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
	textWindowGh= LoadGraph("resource/image/textwindow.png", false);
	buttonSe = LoadSoundMem("resource/sound/titleButton.mp3");
	animCnt = 0;
	questionState = 0;
	yourColor = 0;
	speed = 0.5;
	startFlg = false;
	soundFlg = false;
	questionFlg = false;
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
		PlaySoundFile("resource/sound/title.mp3", DX_PLAYTYPE_LOOP);
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
	question();
}

//�`��
void title::Draw()
{
	if (!questionFlg)
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
		if (state > 3)
		{
			SetDrawBlendMode(DX_BLENDMODE_INVSRC, 255);
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
	}
	else
	{

	}
	//�P�x�Đݒ�
	//SetDrawBright(142, 142, 142);
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
			questionFlg = true;
			if (questionState == 6)
			{
				sceneManager::changeScene(sceneManager::GAME);
				//BGM��~
				StopSoundFile();
				soundFlg = false;
			}
		}
	}
}

void title::question()
{
	if (questionFlg)
	{
		static int x = rand() % 7 - 3;
		static int y = rand() % 7 - 3;
		sCnt++;
		if (sCnt % 3 == 0)
		{
			x = rand() % 7 - 3;
			y = rand() % 7 - 3;
		}
		int q1 = 0;
		int q2 = 0;
		int q3 = 0;
		int q4 = 0;
		DrawGraph(-80+(x*-1), 80+(y*-1), textWindowGh, true);
		switch (questionState)
		{
		case 0:
			ChangeFont("PixelMplus10", DX_CHARSET_DEFAULT);
			SetFontSize(50);
			DrawFormatString(220+x, 350+y, GetColor(255, 255, 255), "������������m���⃒�s���}�X");
			if (key[KEY_INPUT_SPACE] == 1)
			{
				questionState++;
				PlaySoundMem(buttonSe, DX_PLAYTYPE_BACK);
			}
			break;
		case 1:
			SetFontSize(40);
			DrawFormatString(300+x, 270+y, GetColor(255, 255, 255), "���i�^���D���i�̃n�H");
			SetFontSize(30);
			questionSelect("","1.�R����", "2.�܃E��", "3.���Ȃ���_");
			SetFontSize(20);
			q1 = questionCheckButton();
			switch (q1)
			{
			case 1:
					questionState++;
					yourColor--;
				break;
			case 2:
					questionState++;
				break;
			case 3:
					questionState++;
					yourColor++;
				break;
			}
			break;
		case 2:
			SetFontSize(40);
			DrawFormatString(300 + x, 270 + y, GetColor(255, 255, 255), "�A�Ȃ��K�����C�Ȃ̃n�H");
			SetFontSize(30);
			questionSelect("", "1.�Z������", "2.�Z���C", "3.������");
			SetFontSize(20);
			q2 = questionCheckButton();
			switch (q2)
			{
			case 1:
				questionState++;
				yourColor++;
				break;
			case 2:
				questionState++;
				break;
			case 3:
				questionState++;
				yourColor--;
				break;
			}
			break;
		case 3:
			SetFontSize(40);
			DrawFormatString(300 + x, 270 + y, GetColor(255, 255, 255), "�A�ȃ^�����x���̃n�H");
			SetFontSize(30);
			questionSelect("", "1.������", "2.���i��", "3.�C�̂�");
			SetFontSize(20);
			q3 = questionCheckButton();
			switch (q3)
			{
			case 1:
				questionState++;
				break;
			case 2:
				questionState++;
				yourColor--;
				break;
			case 3:
				questionState++;
				yourColor++;
				break;
			}
			break;
		case 4:
			SetFontSize(40);
			DrawFormatString(300 + x, 270 + y, GetColor(255, 255, 255), "���i�^���z�����̃n�H");
			SetFontSize(30);
			questionSelect("", "1.�Ђƃf", "2.�N���", "3.������");
			SetFontSize(20);
			q4 = questionCheckButton();
			switch (q4)
			{
			case 1:
				questionState++;
				break;
			case 2:
				questionState++;
				yourColor--;
				break;
			case 3:
				questionState++;
				yourColor++;
				break;
			}
			break;
		case 5:
			switch (yourColor)
			{
			case 3:
			case 4:
				SetFontSize(50);
				DrawFormatString(200 + x, 360 + y, GetColor(255, 255, 255), "���i�^�̉��͔R�����l�ȏ����i�u���J�v");
				if (key[KEY_INPUT_SPACE] == 1)
				{
					questionState++;
					ChangeFont("���C���I");
					PlaySoundMem(buttonSe, DX_PLAYTYPE_BACK);
				}
				break;
			case 2:
			case 1:
				SetFontSize(50);
				DrawFormatString(210 + x, 360 + y, GetColor(255, 255, 255), "���i�^�̉��͏��V���b���u�����W�v");
				if (key[KEY_INPUT_SPACE] == 1)
				{
					questionState++;
					ChangeFont("���C���I");
					PlaySoundMem(buttonSe, DX_PLAYTYPE_BACK);
				}
				break;
			case 0:
				SetFontSize(50);
				DrawFormatString(210 + x, 360 + y, GetColor(255, 255, 255), "���i�^�̉��͖����m�u�~���C���v");
				if (key[KEY_INPUT_SPACE] == 1)
				{
					questionState++;
					ChangeFont("���C���I");
					PlaySoundMem(buttonSe, DX_PLAYTYPE_BACK);
				}
				break;
			case -1:
			case -2:
				SetFontSize(50);
				DrawFormatString(220 + x, 360 + y, GetColor(255, 255, 255), "���܃G�̉��͗���_�u�����v");
				if (key[KEY_INPUT_SPACE] == 1)
				{
					questionState++;
					ChangeFont("���C���I");
					PlaySoundMem(buttonSe, DX_PLAYTYPE_BACK);
				}
				break;
			case -3:
			case -4:
				SetFontSize(50);
				DrawFormatString(210 + x, 360 + y, GetColor(255, 255, 255), "���܃G�̉��͕��b�^�u�ރ����L�v");//�s���N�̓��_
				if (key[KEY_INPUT_SPACE] == 1)
				{
					questionState++;
					ChangeFont("���C���I");
					PlaySoundMem(buttonSe, DX_PLAYTYPE_BACK);
				}
				break;
			}
		}
	}
}

//����̓��e���
void questionSelect(TCHAR *FormatString1, ...)
{
	static int x = rand() % 7 - 3;
	static int y = rand() % 7 - 3;
	va_list arg;
	va_start(arg, FormatString1);
	for (int cnt = 0; cnt < sizeof(arg)-1; cnt++)
	{
		if (sCnt % 3 == 0)
		{
			x = rand() % 7 - 3;
			y = rand() % 7 - 3;
		}
		DrawFormatString(300+x, 50*cnt+350+y, GetColor(255, 255, 255), va_arg(arg, TCHAR*));
	}
	va_end(arg);
}

int questionCheckButton()
{
	int select = 0;
	if (key[KEY_INPUT_1] == 1)
	{
		select = 1;
		PlaySoundMem(title::buttonSe, DX_PLAYTYPE_BACK);
		return select;
	}
	if (key[KEY_INPUT_2] == 1)
	{
		select = 2;
		PlaySoundMem(title::buttonSe, DX_PLAYTYPE_BACK);
		return select;
	}
	if (key[KEY_INPUT_3] == 1)
	{
		select = 3;
		PlaySoundMem(title::buttonSe, DX_PLAYTYPE_BACK);
		return select;
	}
	return 0;
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

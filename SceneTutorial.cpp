#include "SceneTutorial.h"

woodenbox box;

SceneTutorial::SceneTutorial()
{
	state = 0;
	select = 1;
	triPos = vector2(430, 505);
	deray = 60;
}

SceneTutorial::~SceneTutorial()
{
}

void SceneTutorial::Draw()
{
	bg.draw();
	box.draw();
	pl.Draw();
	tutorialGuide();
}

void SceneTutorial::Update()
{
	box.update();
	if (state != 4)
	{
		pl.Update();
		bg.update();
	}
	if (state== 5)
		sceneManager::changeScene(sceneManager::TITLE);
}

void SceneTutorial::Init()
{
	tutorialFlg = false;
	pl.Init();
	bg.init();
	tutorialTextGh = LoadGraph("resource/image/tutorialText.png", false);
	boxSetObject();
}

void SceneTutorial::unInit()
{
}

void SceneTutorial::Debug()
{
}

void SceneTutorial::tutorialGuide()
{
	if (select == 1)
		triPos = vector2(430, 505);
	else if(select==2)
		triPos = vector2(630, 505);
	switch (state)
	{
	case 0://ジャンプチェック
		if (controlPL == BODY && pl.pl_b->onGround && key[KEY_INPUT_SPACE] == 1)
		{
			deray = 100;
			state++;
		}
		break;
	case 1:
		deray--;
		if (deray < 0)
			state++;
		break;
	case 2://幽体化チェック
		if (controlPL == BODY && key[KEY_INPUT_Z] == 1)
		{
			deray = 100;
			state++;
		}
		break;
	case 3:
		deray--;
		if (deray < 0)
			state++;
		break;
	//case 4://憑依チェック
	//	if (controlPL==BOX)
	//	{
	//		deray = 100;
	//		state++;
	//	}
	//	break;
	//case 5:
	//	deray--;
	//	if (deray < 0)
	//		state++;
	//	break;
	case 4:
		if (key[KEY_INPUT_LEFT] == 1)
		{
			select = 1;
			PlaySoundMem(title::buttonSe, DX_PLAYTYPE_BACK);
		}
		else if (key[KEY_INPUT_RIGHT] == 1)
		{
			select = 2;
			PlaySoundMem(title::buttonSe, DX_PLAYTYPE_BACK);
		}
		ChangeFont("PixelMplus10");
		SetFontSize(40);
		DrawFormatString(350, 350, GetColor(255, 255, 255), "チゆーとリあルを終了シますカ？");
		DrawGraph(triPos.x, triPos.y, title::triangleGh, true);
		SetFontSize(30);
		DrawFormatString(450, 500, GetColor(255, 255, 255), "ウん！");
		SetFontSize(30);
		DrawFormatString(650, 500, GetColor(255, 255, 255), "いヤダ！");
		if (select == 1 && key[KEY_INPUT_SPACE] == 1)
			state++;
		if (select == 2 && key[KEY_INPUT_SPACE] == 1)
			state = 0;
		break;
	}
	DrawRectGraph(pl.pl_b->getPos(true) - camera_pos.x, pl.pl_b->getPos(false) - camera_pos.y - 100, 0, (60 * state), 60, 60, tutorialTextGh, true);
}

void boxSetObject()
{
	loadObjectGraphics();
	box.setObjectTemp(vector2(3 * CHIP_SIZE, 9 * CHIP_SIZE + 16));
}
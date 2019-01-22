
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

//初期化
void title::Init()
{
	//画像読み込み
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

//更新
void title::Update()
{
	//BGM再生
	if (!soundFlg)
	{
		//作業中なので切ってます
		PlaySoundFile("resource/sound/title.mp3", DX_PLAYTYPE_LOOP);
		soundFlg = true;
	}
	//プレイヤーの歩く速さ変更
	changeSpeed();
	pPos.x += speed;
	//プレイヤーとランタンの位置同期
	lPos = vector2(pPos.x + 60, pPos.y + 29);
	fPos = vector2(pPos.x + 58, pPos.y + 45);
	//背景移動処理
	bPos1.x--;
	if (bPos1.x < -1280)
		bPos1.x = 0;
	bPos2.x--;
	if (bPos2.x < 0)
		bPos2.x = 1280;
	//スタートボタンが押されたら
	if (key[KEY_INPUT_SPACE] == 1)
		startFlg = true;
	pushStartButton();
	question();
}

//描画
void title::Draw()
{
	if (!questionFlg)
	{
		//隠しコマンド(ランタンの炎の色が変わる)
		static int state;
		state = checkHiddenCommand();
		//アニメーションカウント加算
		animCnt++;
		//輝度設定
		SetDrawBright(255, 255, 255);
		//背景ブロック描画
		DrawGraph(bPos1.x, bPos1.y, backGh, true);
		DrawGraph(bPos2.x, bPos2.y, backGh, true);
		//プレイヤー描画
		if (state > 3)
		{
			SetDrawBlendMode(DX_BLENDMODE_INVSRC, 255);
			DrawRectGraph(pPos.x, pPos.y, 128 * (animCnt / 6 % 6), 0, 128, 128, playerGh, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		else DrawRectGraph(pPos.x, pPos.y, 128 * (animCnt / 6 % 6), 0, 128, 128, playerGh, true);
		//ランタンの炎描画
		DrawRectGraph(fPos.x, fPos.y, 100 * (animCnt / 6 % 10), 100 * (state % 4), 100, 100, fireGh, true);
		//ランタン描画
		DrawGraph(lPos.x, lPos.y, lanthanumGh, true);
		//暗闇描画
		DrawGraph(0, 0, darkGh, true);
		//文字描画
		DrawGraph(-30, 0, stringGh, true);
	}
	else
	{

	}
	//輝度再設定
	//SetDrawBright(142, 142, 142);
}

//スタートボタンが押されたら
void title::pushStartButton()
{
	if (startFlg)
	{
		speed = 2.0f;
		//右に移動処理
		pPos.x += speed;
		//シーン遷移条件
		if (pPos.x > 920)
		{
			questionFlg = true;
			if (questionState == 6)
			{
				sceneManager::changeScene(sceneManager::GAME);
				//BGM停止
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
			DrawFormatString(220+x, 350+y, GetColor(255, 255, 255), "こレかラ幾つかノ質問ヲ行いマス");
			if (key[KEY_INPUT_SPACE] == 1)
			{
				questionState++;
				PlaySoundMem(buttonSe, DX_PLAYTYPE_BACK);
			}
			break;
		case 1:
			SetFontSize(40);
			DrawFormatString(300+x, 270+y, GetColor(255, 255, 255), "あナタが好きナのハ？");
			SetFontSize(30);
			questionSelect("","1.コあら", "2.まウす", "3.あなこんダ");
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
			DrawFormatString(300 + x, 270 + y, GetColor(255, 255, 255), "アなたガきライなのハ？");
			SetFontSize(30);
			questionSelect("", "1.センそう", "2.セかイ", "3.ヤさい");
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
			DrawFormatString(300 + x, 270 + y, GetColor(255, 255, 255), "アなタがたベルのハ？");
			SetFontSize(30);
			questionSelect("", "1.メだま", "2.あナた", "3.イのち");
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
			DrawFormatString(300 + x, 270 + y, GetColor(255, 255, 255), "あナタがホしいのハ？");
			SetFontSize(30);
			questionSelect("", "1.ひとデ", "2.クるま", "3.しレん");
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
				DrawFormatString(200 + x, 360 + y, GetColor(255, 255, 255), "あナタの炎は燃えル様な純粋ナ「あカ」");
				if (key[KEY_INPUT_SPACE] == 1)
				{
					questionState++;
					ChangeFont("メイリオ");
					PlaySoundMem(buttonSe, DX_PLAYTYPE_BACK);
				}
				break;
			case 2:
			case 1:
				SetFontSize(50);
				DrawFormatString(210 + x, 360 + y, GetColor(255, 255, 255), "あナタの炎は少シ濁ッた「ヲれんジ」");
				if (key[KEY_INPUT_SPACE] == 1)
				{
					questionState++;
					ChangeFont("メイリオ");
					PlaySoundMem(buttonSe, DX_PLAYTYPE_BACK);
				}
				break;
			case 0:
				SetFontSize(50);
				DrawFormatString(210 + x, 360 + y, GetColor(255, 255, 255), "あナタの炎は無個性ノ「ミずイロ」");
				if (key[KEY_INPUT_SPACE] == 1)
				{
					questionState++;
					ChangeFont("メイリオ");
					PlaySoundMem(buttonSe, DX_PLAYTYPE_BACK);
				}
				break;
			case -1:
			case -2:
				SetFontSize(50);
				DrawFormatString(220 + x, 360 + y, GetColor(255, 255, 255), "ヲまエの炎は淀んダ「あヲ」");
				if (key[KEY_INPUT_SPACE] == 1)
				{
					questionState++;
					ChangeFont("メイリオ");
					PlaySoundMem(buttonSe, DX_PLAYTYPE_BACK);
				}
				break;
			case -3:
			case -4:
				SetFontSize(50);
				DrawFormatString(210 + x, 360 + y, GetColor(255, 255, 255), "ヲまエの炎は腐ッタ「むラさキ」");//ピンクはヤダ
				if (key[KEY_INPUT_SPACE] == 1)
				{
					questionState++;
					ChangeFont("メイリオ");
					PlaySoundMem(buttonSe, DX_PLAYTYPE_BACK);
				}
				break;
			}
		}
	}
}

//質問の内容作る
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

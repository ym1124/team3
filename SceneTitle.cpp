
#include "SceneTitle.h"
#include "common.h"
#include "scene.h"

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

//更新
void title::Update()
{
	//BGM再生
	if (!soundFlg)
	{
		//作業中なので切ってます
		//PlaySoundFile("resource/sound/title.mp3", DX_PLAYTYPE_LOOP);
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
}

//描画
void title::Draw()
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
	if (state >3)
	{
		SetDrawBlendMode(DX_BLENDMODE_INVSRC,255);
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
	//輝度再設定
	SetDrawBright(142, 142, 142);
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
			sceneManager::changeScene(sceneManager::GAME);
			//BGM停止
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


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
	darkGh = LoadGraph("resource/image/titleLightCircle.png", false);
	backGh = LoadGraph("resource/image/titleBack.png", false);
	lanthanumGh = LoadGraph("resource/image/titleLanthanum.png", false);
	fireGh = LoadGraph("resource/image/titleFire.png", false);
	playerGh = LoadGraph("resource/image/titlePlayer.png", false);
	stringGh = LoadGraph("resource/image/titleString.png", false);
	animCnt = 0;
	startFlg = false;
	bPos1 = vector2(0.0f, 0.0f);
	bPos2 = vector2(1280.f, 0.0f);
	pPos = vector2(500, 528);
	lPos = vector2(560, 557);
	fPos = vector2(558, 573);
}

//更新
void title::Update()
{
	//背景移動処理
	bPos1.x--;
	if (bPos1.x < -1280)
		bPos1.x = 0;
	bPos2.x--;
	if (bPos2.x < 0)
		bPos2.x = 1280;
	//スタートボタンが押されたら
	if (key[KEY_INPUT_S] == 1)
		startFlg = true;
	pushStartButton();
}

//描画
void title::Draw()
{
	//アニメーションカウント加算
	animCnt++;
	//輝度設定
	SetDrawBright(255, 255, 255);
	//背景ブロック描画
	DrawGraph(bPos1.x, bPos1.y, backGh, true);
	DrawGraph(bPos2.x, bPos2.y, backGh, true);
	//プレイヤー描画
	DrawRectGraph(pPos.x, pPos.y, 128 * (animCnt / 6 % 6), 0, 128, 128, playerGh, true);
	//隠しコマンド(ランタンの炎の色が変わる)
	static int state;
	state = checkHiddenCommand();
	//ランタンの炎描画
	DrawRectGraph(fPos.x, fPos.y, 100 * (animCnt / 6 % 15), 100 * state, 100, 100, fireGh, true);
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
		//右に移動処理
		pPos.x += 2;
		lPos.x += 2;
		fPos.x += 2;
		//シーン遷移条件
		if (pPos.x > 1000)
		{
			sceneManager::changeScene(sceneManager::GAME);
		}
	}
}

void title::Debug()
{
	DrawFormatString(0, 0, color.Yellow, "Timer:%d///////////////////////////////////", timer);
}

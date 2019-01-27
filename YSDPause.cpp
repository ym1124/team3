//////////////////////////////////////////////////////////
////
////			Pause.cpp
////
//////////////////////////////////////////////////////////
#include "DxLib.h"
#include "YSDPause.h"
#include "common.h"
#include "vector.h"

PauseClass pause;
int frameHandle;//ポーズ枠の画像ハンドル
int cursorHandle = 0, blackback = 0;//画像ハンドルズ
int pauseKey;//どのキーでオプションを開いたかを見る
bool kb_pausekey, kbprev_pausekey;

//vector2 frameSize;

const enum//選択項目の名前
{
	BACK_GAME, RESTART, TO_TITLE,
	LAST_NOTHING/*✝意味を持たない最後のシルシ✝*/
};

//初期化関数
void PauseClass::Init()//はじめに一回だけ
{
	pauseState = false;
	//frameHandle = LoadGraph("resource/image/pause_frame_test.png");
	frameHandle = LoadGraph("resource/image/textwindow.png");
	blackback = LoadGraph("resource/image/black.png");
	chosenItem = 0;
	return;
}

//更新関数
void PauseClass::Update()
{
	//外部(SceneGame::Update())にPauseMode_On
	//スイッチOn!!!!
	{//実装パート//
		if (!timer)//最初に一回だけ
		{
			cursorHandle = LoadGraph("resource/image/triangle.png");
		}

		//項目選択
		{
			if (key[KEY_INPUT_DOWN] == 1)//下押した瞬間
			{
				chosenItem++;
				PlaySoundFile("resource/sound/titleButton.mp3", DX_PLAYTYPE_BACK);
			}
			if (key[KEY_INPUT_UP] == 1)//上押した瞬間
			{
				chosenItem--;
				PlaySoundFile("resource/sound/titleButton.mp3", DX_PLAYTYPE_BACK);
			}

			if (key[pauseKey] == 1)//ポーズキーと同じキーを押したとき
			{
				PlaySoundFile("resource/sound/titleButton.mp3", DX_PLAYTYPE_BACK);
				PauseMode_Off();
			};

			//想定外(範囲外)の値になった時は
			if (chosenItem < 0) { chosenItem = LAST_NOTHING - 1; }
			if (chosenItem >= LAST_NOTHING) { chosenItem = 0; }
		}

		//選択中の項目を決定
		if (key[KEY_INPUT_SPACE] || key[KEY_INPUT_A])
		{

			//イジるのは...
			//こ↑こ↓
			switch (chosenItem)
			{
			case BACK_GAME:
				PauseMode_Off();
				break;
			case TO_TITLE:
				//TODO シーン切り替え
				PlaySoundFile("resource/sound/titleButton.mp3", DX_PLAYTYPE_BACK);
				break;
			case RESTART:
				//TODO リスタート
				PlaySoundFile("resource/sound/titleButton.mp3", DX_PLAYTYPE_BACK);
				break;
				//増やしたらここに
			//case :
			default:
				//何もしない
				break;
			}//switch
		}//if(決定押したとき)


		timer++;
		return;
	}
}


char *itemName[LAST_NOTHING] = { "げえムに戻ル","リすたート","タイとルに戻ル", };
//const vector2 cursor(180 + 250, 0);
//描画関数
void PauseClass::draw()
{
	//定数
	const static int MOJIICHI_Y(300);	//一行目の位置
	const static int GAP_Y(20);	//項目の行間
	const static int FONT_SIZE(40);	//フォントサイズ
	const static int FRAME_MGN_L(115);	//オプション枠の左辺位置
	const static int OPTN_MGN_L(400);	//オプション枠左端から文字表示し始めまでのあいだ

	if (pauseState)
	{
		SetDrawBright(255, 255, 255);

		//枠
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 170);
		DrawExtendGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, blackback, TRUE);//薄い真っ黒
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

		DrawGraph(FRAME_MGN_L, 120, frameHandle, TRUE);
		//文字	//定数ばっかはむしろ見づらくない？なくなくなくなくない？
		//PAUSE文字
		ChangeFont("PixelMplus12", DX_CHARSET_DEFAULT);
		SetFontSize(FONT_SIZE + 30);
		DrawString(415, 180, "- P A U S E -", GetColor(255, 255, 255));
		//選択項目
		ChangeFont("PixelMplus10", DX_CHARSET_DEFAULT);
		SetFontSize(FONT_SIZE);
		DrawString(523/*FRAME_MGN_L + OPTN_MGN_L*/, MOJIICHI_Y + (FONT_SIZE + GAP_Y) * 1, itemName[0], GetColor(255, 255, 255));
		DrawString(523, MOJIICHI_Y + (FONT_SIZE + GAP_Y) * 2, itemName[1], GetColor(255, 255, 255));
		DrawString(523, MOJIICHI_Y + (FONT_SIZE + GAP_Y) * 3, itemName[2], GetColor(255, 255, 255));
		//カーソル
		DrawGraph(FRAME_MGN_L + OPTN_MGN_L - FONT_SIZE, MOJIICHI_Y + (FONT_SIZE + GAP_Y)*(chosenItem + 1) + 10, cursorHandle, TRUE);
		//	);
	}
	return;
}

//////////以下、つかってくだちい//////////

//ポーズ起動関数
void PauseClass::PauseMode_On()
{
	pauseState = true;
	PlaySoundFile("resource/sound/titleButton.mp3", DX_PLAYTYPE_BACK);
}
//ポーズ完了関数（Pause::Update関数内にて使用）
void PauseClass::PauseMode_Off()
{
	pauseState = false;
	PlaySoundFile("resource/sound/titleButton.mp3", DX_PLAYTYPE_BACK);
}
//ポーズ確認関数（if()の条件に使用）
bool PauseClass::Get_PauseState()
{
	return pauseState;
}

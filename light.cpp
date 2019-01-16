#include "light.h"

int torchLight::lightGh;
int torch::fireGh, torch::torchGh;
int torchLight::sum = 0;
int torch::sumNumber = 0;
bool torchLight::setFlg = false;
int lanthanum::fireGh, lanthanum::lanthanumGh,lanthanum::sumNumber=0;

//配列で書き直す説
//t10はプレイヤーの炎
torch t1(vector2(30, 30)), t2(vector2(230, 30)), t3(vector2(430, 30)), t4(vector2(30, 230)), t5(vector2(230, 230)), t6(vector2(430, 230)), t7(vector2(30, 430)), t8(vector2(230, 430)), t9(vector2(430, 430)), t10(vector2(0, 0));
torchLight light1(&t1), light2(&t2), light3(&t3), light4(&t4), light5(&t5), light6(&t6), light7(&t7), light8(&t8), light9(&t9);
playerLight plLight;
lanthanum lanthanum1;

torch::torch(vector2 pos) :pos(pos), torchAnimCnt(0), isAlive(false)
{
	torch::sumNumber++;
	number = sumNumber;
}

void torch::setTorch()
{
	static bool onceFlg = false;
	if (!onceFlg)
	{
		torch::fireGh = LoadGraph("resource/image/fire.png", true);
		torch::torchGh = LoadGraph("resource/image/torch.png", true);
		onceFlg = true;
	}
}

void torch::hitCheck()
{
	//当たり判定
	if (plLight.pos.x + 40 > pos.x + 40 && plLight.pos.x + 40 < pos.x + 55 && plLight.pos.y + 60 > pos.y + 50 && plLight.pos.y + 60 < pos.y + 70)
		isAlive = true;
}

void torch::drawTorch()
{
	//プレイヤーの炎じゃないなら松明部分描画する
	if (number != plLight.t->number)
		DrawGraph(pos.x + 47, pos.y + 64, torch::torchGh, true);
	//デバッグ用
	DrawLine(pos.x + 40, pos.y + 50, pos.x + 55, pos.y + 50, GetColor(255, 0, 0));
	DrawLine(pos.x + 40, pos.y + 50, pos.x + 40, pos.y + 70, GetColor(255, 0, 0));
	DrawLine(pos.x + 40, pos.y + 70, pos.x + 55, pos.y + 70, GetColor(255, 0, 0));
	DrawLine(pos.x + 55, pos.y + 50, pos.x + 55, pos.y + 70, GetColor(255, 0, 0));
}

void torch::drawTorchAll()
{
	if (isAlive)
	{
		torchAnimCnt++;
		DrawRectGraph(pos.x, pos.y, 100 * (torchAnimCnt / 6 % 10), 0, 100, 100, torch::fireGh, true);
	}
	drawTorch();
}

void torch::updateTorch()
{
	setTorch();
	hitCheck();
}

torchLight::torchLight(torch *t)
{
	sway = vector2(0, 0);
	torchLight::sum++;
	number = sum;
	this->t = t;//&tだとバグるのはなぜ？
	pos = t->pos;
	//pos = vector2(0, 400);
	isAlive = false;
}

void torchLight::initLight()
{
	if (!torchLight::setFlg)
	{
		//後で場所変える
		torchLight::lightGh = LoadGraph("resource/image/lightcircle.png", true);
		torchLight::setFlg = true;
	}

	//デバッグ用画像切り替え
	if (CheckHitKey(KEY_INPUT_C))
	{
		static int i = 0;
		for (i = 2; i < 11; i++)
		{
			if (key[i] == 1)
				break;
		}
		switch (i)
		{
		case 2:
			torchLight::lightGh = LoadGraph("resource/image/10.png", true);
			break;
		case 3:
			torchLight::lightGh = LoadGraph("resource/image/20.png", true);
			break;
		case 4:
			torchLight::lightGh = LoadGraph("resource/image/30.png", true);
			break;
		case 5:
			torchLight::lightGh = LoadGraph("resource/image/40.png", true);
			break;
		case 6:
			torchLight::lightGh = LoadGraph("resource/image/50.png", true);
			break;
		case 7:
			torchLight::lightGh = LoadGraph("resource/image/60.png", true);
			break;
		case 8:
			torchLight::lightGh = LoadGraph("resource/image/70.png", true);
			break;
		case 9:
			torchLight::lightGh = LoadGraph("resource/image/80.png", true);
			break;
		}
	}

	if (!isAlive&&t->isAlive)
	{
		//点火する
		isAlive = true;
	}

}

void torchLight::moveLight()
{
	//後で変える
	t->updateTorch();
	if (isAlive)
	{
		//描画する位置取得
		pos = t->pos;

		////デバッグ用
		//if (CheckHitKey(KEY_INPUT_RIGHT))
		//	t->pos.x++;
		//if (CheckHitKey(KEY_INPUT_LEFT))
		//	t->pos.x--;
		//if (CheckHitKey(KEY_INPUT_UP))
		//	t->pos.y--;
		//if (CheckHitKey(KEY_INPUT_DOWN))
		//	t->pos.y++;
	}
}

void torchLight::drawLight()
{
	if (isAlive)
	{
		//輝度設定
		SetDrawBright(255, 255, 255);
		//デバッグ用描画範囲表示
		//DrawBox(t->pos.x - LIGHT_MARGINE_X, t->pos.y - LIGHT_MARGINE_Y, t->pos.x + 200 - LIGHT_MARGINE_X, t->pos.y + 200 - LIGHT_MARGINE_Y, GetColor(255, 255, 255), false);
		//描画範囲指定
		SetDrawArea(t->pos.x - LIGHT_MARGINE_X, t->pos.y - LIGHT_MARGINE_Y, t->pos.x + 200 - LIGHT_MARGINE_X, t->pos.y + 200 - LIGHT_MARGINE_Y);
		//背景画像の描画//後で変える
		static int a = LoadGraph("resource/image/tempBack.png", true);
		DrawGraph(0, 0, a, true);
		//bg.draw();
		//松明描画
		t->drawTorchAll();
		//プレイヤー松明
		//plTorch.drawLight();
		//プレイヤーランタン
		plLight.l->drawLanthanumAll();
		//プレイヤー描画
		pl.Draw();
		//アルファブレンド設定
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,155);
		//円形画像を描画
		DrawGraph(t->pos.x - LIGHT_MARGINE_X + sway.x, t->pos.y - LIGHT_MARGINE_Y + sway.y, torchLight::lightGh, true);
		//アルファブレンド設定
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		//輝度再設定
		//SetDrawBright(142, 132, 132);
		//描画範囲設定解除
		SetDrawAreaFull();
	}
}

void torchLight::updateLight()
{
	t->updateTorch();
	initLight();
	moveLight();
	drawLight();
}

//コンストラクタ
playerLight::playerLight() :torchLight(&t10)
{
	isAlive = true;
	l = &lanthanum1;
	l->isAlive = true;
}

void playerLight::moveLight()
{
	//プレイヤーの炎移動//マージンで位置調整
	pos.x = pl.getBodyPos(true);
	pos.y = pl.getBodyPos(false);
}

void playerLight::drawLight()
{
	if (isAlive)
	{
		//デバッグ用当たり判定ボックス
		DrawBox(pos.x + 40, pos.y + 60, pos.x + 45, pos.y + 65, GetColor(0, 0, 255), false);
		//プレイヤー松明描画
		/*DrawGraph(t->pos.x, t->pos.y, pTorchGh, true);*/
		//t->drawTorchAll();
		//ランタン部分描画
		l->updateLanthanum();
		//輝度再設定
		SetDrawBright(142, 142, 142);//いい感じになる(142,142,142)
	}
}

//template<typename T>
//void setLight(T temp, light *lig)
//{
//	lig->pos = temp.pos;
//	lig->updateLight();
//}

lanthanum::lanthanum(/*vector2 pos*/) /*:pos(pos)*/
{
	lanthanum::sumNumber++;
	number = lanthanum::sumNumber;
	pos.x=pl.getBodyPos(true);
	pos.y = pl.getBodyPos(false);
}

//ランタン部分のみ描画
void lanthanum::drawLanthanum()
{
	static bool onceFlg = false;
	if (!onceFlg)
	{
		lanthanum::fireGh = LoadGraph("resource/image/lanthanumfire.png");
		lanthanum::lanthanumGh = LoadGraph("resource/image/playerlanthanum.png");
		onceFlg = true;
	}
	DrawGraph(pos.x, pos.y, lanthanum::lanthanumGh, true);
}

//ランタンの炎まで描画
void lanthanum::drawLanthanumAll()
{
	lanthanumAnimCnt++;
	DrawRectGraph(pos.x, pos.y, (lanthanumAnimCnt/12%15) * 100, 0, 100, 100, lanthanum::fireGh, true);
	drawLanthanum();
}

//ランタンの移動
void lanthanum::moveLanthanum()
{
	//プレイヤーポジション取得
	pos.x = pl.getBodyPos(true);
	pos.y = pl.getBodyPos(false);
}

void lanthanum::updateLanthanum()
{
	drawLanthanumAll();
	moveLanthanum();
}

//************要修正関数のコーナー**************//

void torchLight::swayLight()
{
	//炎の揺れ//カクカクなる
	sway.x = rand() % 8 - 4;
	sway.y = rand() % 8 - 4;
}

torchLight* getLightPointertes(int num)
{
	switch (num)
	{
	case 1:
		return &light1;
		break;
	case 2:
		return &light2;
		break;
	case 3:
		return &light3;
		break;
	case 4:
		return &light4;
		break;
	case 5:
		return &light5;
		break;
	case 6:
		return &light6;
		break;
	case 7:
		return &light7;
		break;
	case 8:
		return &light8;
		break;
	case 9:
		return &light9;
		break;
	}
}

playerLight* getPlTorchPointerTes()
{
	return &plLight;
}

void updateAllTorchLight()
{
	//点火したライトの描画系
	light1.updateLight();
	light2.updateLight();
	light3.updateLight();
	light4.updateLight();
	light5.updateLight();
	light6.updateLight();
	light7.updateLight();
	light8.updateLight();
	light9.updateLight();
}

void drawAlltorch()
{
	//松明部分のみの描画
	t1.drawTorch();
	t2.drawTorch();
	t2.drawTorch();
	t3.drawTorch();
	t4.drawTorch();
	t5.drawTorch();
	t6.drawTorch();
	t7.drawTorch();
	t8.drawTorch();
	t9.drawTorch();
}
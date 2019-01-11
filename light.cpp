#include "light.h"

int torchLight::lightGh;
int torch::torchGh;
int torchLight::sum = 0;
bool torchLight::setFlg = false;

torch t1(vector2(30, 30)), t2(vector2(230, 230));
torchLight light1(&t1), light2(&t2);


torch::torch(vector2 pos) :pos(pos),torchAnimCnt(0)
{

}

void torch::drawTorch()
{
	torchAnimCnt++;
	DrawRectGraph(pos.x, pos.y, 100 * (torchAnimCnt/6%10), 0, 100, 100, torch::torchGh, true);
}

torchLight::torchLight(torch *t)
{
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
		torch::torchGh = LoadGraph("resource/image/taimatu.png", true);
	}

	if (!isAlive/*&&点火する条件*/)
	{
		//点火する
		isAlive = true;
	}
}

void torchLight::moveLight()
{
	if (isAlive)
	{
		//描画する位置取得
		//pos = this->t->pos;

		//デバッグ用
		if (CheckHitKey(KEY_INPUT_RIGHT))
			pos.x++;
		if (CheckHitKey(KEY_INPUT_LEFT))
			pos.x--;
		if (CheckHitKey(KEY_INPUT_UP))
			pos.y--;
		if (CheckHitKey(KEY_INPUT_DOWN))
			pos.y++;
	}
}

void torchLight::drawLight()
{
	if (isAlive)
	{
		//輝度設定
		SetDrawBright(255, 255, 255);
		//デバッグ用描画範囲表示
		DrawBox(pos.x - LIGHT_MARGINE_X, pos.y - LIGHT_MARGINE_Y, pos.x + 200 - LIGHT_MARGINE_X, pos.y + 200 - LIGHT_MARGINE_Y,GetColor(255,255,255),false);
		//描画範囲指定
		SetDrawArea(pos.x - LIGHT_MARGINE_X, pos.y - LIGHT_MARGINE_Y, pos.x + 200 - LIGHT_MARGINE_X, pos.y + 200 - LIGHT_MARGINE_Y);
		//背景画像の描画//後で変える
		static int a = LoadGraph("resource/image/haikei.png", true);
		//if(number==1)
		DrawGraph(0, 0, a, true);
		//松明描画
		t->drawTorch();
		//円形画像を描画
		DrawGraph(pos.x - LIGHT_MARGINE_X, pos.y - LIGHT_MARGINE_Y, torchLight::lightGh, true);
		//輝度再設定
		SetDrawBright(122, 122, 122);
		//描画範囲設定解除
		SetDrawAreaFull();
	}
}

void torchLight::updateLight()
{
	initLight();
	moveLight();
	drawLight();
}

//template<typename T>
//void setLight(T temp, light *lig)
//{
//	lig->pos = temp.pos;
//	lig->updateLight();
//}

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
	}
}
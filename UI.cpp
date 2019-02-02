#include "UI.h"
#include "light.h"
#include "YSDBG.h"
#include "gameObject.h"
int UI::Graph;
int UI::Graph2;
int UI::string;
int UI::maxnum;

UI MTIui;
stageString stst;

void UI::Update()
{
	maxnum = torch::maxnum - torchLight::maxnum;
	parsent = player.pl_S->soultime/3;

	canSoul = false;

	{
		static int prev;
		if (prev != maxnum)
		{
			torchFlg = true;
			prev = maxnum;
		}
	}

	if (controlPL == PLcon::SOUL)
	{
		for (int i = 0; i < WOODENBOX_MAX; i++)
		{
			woodenbox *box = woodenboxs;

			if (fabs(box[i].pos.x - player.pl_S->getPos(true)) < 50)
			{
				if (fabs(box[i].pos.y - player.pl_S->getPos(false)) < 50)
				{
					canSoul = true;
					break;
				}
			}
		}

		for (int i = 0; i < BIGLANTHANUM_MAX; i++)
		{
			bigLanthanum *Blump = bigLanthanums;
			if (fabs(Blump[i].pos.x - player.pl_S->getPos(true)) < 70)
			{
				if (fabs(Blump[i].pos.y - player.pl_S->getPos(false)) < 70)
				{
					canSoul = true;
					break;
				}
			}
		}
	}

	DrawUpdate();
}

void UI::Draw()
{
	DrawRectGraphF(50, 550, 0, 110, 162, 192, Graph, TRUE);

	DrawRectGraphF(155, 672, 30 * wk[UI::SMLNUM].aFrame, 0, 30, 43, Graph, TRUE);
	DrawRectGraphF(125, 672, 30 * wk[UI::SMLNUM].aLine, 0, 30, 43, Graph, TRUE);

	DrawRectGraphF(55, 510, 40 * wk[UI::BIGNUM].aFrame, 43, 40, 67, Graph, TRUE);
	if (wk[UI::BIGNUM].aLine != 0)DrawRectGraphF(10, 510, 40 * wk[UI::BIGNUM].aLine, 43, 40, 67, Graph, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	DrawRectRotaGraphF(155, 550, wk[UI::FIRE].aFrame * 100,yColor * 100, 100, 100, 4, 0, torch::fireGh, TRUE);
	//DrawRectRotaGraphF(150, 570, 40 + wk[UI::FIRE].aFrame * 100, 35, 20, 1 * parsent * 0.3f, 4, 0,  Graph2, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	if (torchFlg)
	{
		DrawRectRotaGraphF(70, 515, wk[EFCFIRE].aFrame * 100, yColor * 100, 100, 100, 5, 0, torchLight::effectGh, TRUE);
	}

	if (canSoul)
	{
		DrawRectGraphF(player.pl_S->pos.x - 50 - camera_pos.x, player.pl_S->pos.y - 80 - camera_pos.y, 45* wk[UI::STRING].aFrame, 128, 45, 32, string, TRUE);
	}
}

void UI::Init()
{
	UI::Graph = LoadGraph("resource/image/ui.png");
	UI::Graph2 = LoadGraph("resource/image/grayfire.png");
	UI::string = LoadGraph("resource/image/string.png");

}

void UI::DrawUpdate()
{
	//大きい数字
	switch (maxnum%10)
	{
	case 0:
		wk[UI::BIGNUM].aFrame = 0;
		break;
	case 1:
		wk[UI::BIGNUM].aFrame = 1;
		break;
	case 2:
		wk[UI::BIGNUM].aFrame = 2;
		break;
	case 3:
		wk[UI::BIGNUM].aFrame = 3;
		break;
	case 4:
		wk[UI::BIGNUM].aFrame = 4;
		break;
	case 5:
		wk[UI::BIGNUM].aFrame = 5;
		break;
	case 6:
		wk[UI::BIGNUM].aFrame = 6;
		break;
	case 7:
		wk[UI::BIGNUM].aFrame = 7;
		break;
	case 8:
		wk[UI::BIGNUM].aFrame = 8;
		break;
	case 9:
		wk[UI::BIGNUM].aFrame = 9;
		break;
	default:
		break;
	}
	switch (maxnum/10)
	{
	case 0:
		wk[UI::BIGNUM].aLine = 0;
		break;
	case 1:
		wk[UI::BIGNUM].aLine = 1;
		break;
	case 2:
		wk[UI::BIGNUM].aLine = 2;
		break;
	case 3:
		wk[UI::BIGNUM].aLine = 3;
		break;
	case 4:
		wk[UI::BIGNUM].aLine = 4;
		break;
	case 5:
		wk[UI::BIGNUM].aLine = 5;
		break;
	case 6:
		wk[UI::BIGNUM].aLine = 6;
		break;
	case 7:
		wk[UI::BIGNUM].aLine = 7;
		break;
	case 8:
		wk[UI::BIGNUM].aLine = 8;
		break;
	case 9:
		wk[UI::BIGNUM].aLine = 9;
		break;
	default:
		break;
	}

	//小さい数字
	switch (torch::maxnum % 10)
	{
	case 0:
		wk[UI::SMLNUM].aFrame = 0;
		break;
	case 1:
		wk[UI::SMLNUM].aFrame = 1;
		break;
	case 2:
		wk[UI::SMLNUM].aFrame = 2;
		break;
	case 3:
		wk[UI::SMLNUM].aFrame = 3;
		break;
	case 4:
		wk[UI::SMLNUM].aFrame = 4;
		break;
	case 5:
		wk[UI::SMLNUM].aFrame = 5;
		break;
	case 6:
		wk[UI::SMLNUM].aFrame = 6;
		break;
	case 7:
		wk[UI::SMLNUM].aFrame = 7;
		break;
	case 8:
		wk[UI::SMLNUM].aFrame = 8;
		break;
	case 9:
		wk[UI::SMLNUM].aFrame = 9;
		break;
	default:
		break;
	}
	switch (torch::maxnum / 10)
	{
	case 0:
		wk[UI::SMLNUM].aLine = 0;
		break;
	case 1:
		wk[UI::SMLNUM].aLine = 1;
		break;
	case 2:
		wk[UI::SMLNUM].aLine = 2;
		break;
	case 3:
		wk[UI::SMLNUM].aLine = 3;
		break;
	case 4:
		wk[UI::SMLNUM].aLine = 4;
		break;
	case 5:
		wk[UI::SMLNUM].aLine = 5;
		break;
	case 6:
		wk[UI::SMLNUM].aLine = 6;
		break;
	case 7:
		wk[UI::SMLNUM].aLine = 7;
		break;
	case 8:
		wk[UI::SMLNUM].aLine = 8;
		break;
	case 9:
		wk[UI::SMLNUM].aLine = 9;
		break;
	default:
		break;
	}

	wk[UI::FIRE].aCnt++;
	if (wk[UI::FIRE].aCnt > 120)
	{
		wk[UI::FIRE].aCnt = 0;
	}

	if (wk[UI::FIRE].aCnt % 6 == 0)
	{
		wk[UI::FIRE].aFrame++;
		if (wk[UI::FIRE].aFrame >= 10)
		{
			wk[UI::FIRE].aFrame = 0;
		}
	}

	if (wk[UI::FIRE].aCnt %20 == 1)
	{
		wk[UI::STRING].aFrame ^= 1;
	}
	
	if (torchFlg)
	{
		static int prev;
		if (prev != maxnum)
		{
			wk[UI::EFCFIRE].aCnt = 0;
			wk[UI::EFCFIRE].aFrame = 0;
			prev = maxnum;
		}
		wk[UI::EFCFIRE].aCnt++;
		if (wk[UI::EFCFIRE].aCnt > 120)
		{
			wk[UI::EFCFIRE].aCnt = 0;
		}
		if (wk[UI::EFCFIRE].aCnt % 5 == 1)
		{
			wk[UI::EFCFIRE].aFrame++;
			if (wk[UI::EFCFIRE].aFrame >= 9)
			{
				wk[UI::EFCFIRE].aFrame = 0;
				torchFlg = false;
			}
		}
	}
}

stageString::stageString()
{
	blendCnt = -1.f;
	gBlendCnt = 0.f;
	drawFlg = false;
	ghostFlg = 0;
	init();
}

void stageString::init()
{
}

void stageString::draw()
{
	if (drawFlg)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (int)blendCnt);
		SetFontSize(100);
		DrawFormatString(FONT1_POS_X, FONT1_POS_Y, GetColor(255, 255, 255), "S T A G E %d", stageNum);
		SetFontSize(50);
		DrawFormatString(FONT2_POS_X, FONT2_POS_Y, GetColor(255, 255, 255), "たイまツヲ%d本灯セ", torch::maxnum);
	}
	if (ghostFlg == 1)
	{
		int x = rand() % 11 - 5;
		int y = rand() % 11 - 5;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (int)gBlendCnt);
		SetFontSize(50);
		DrawFormatString(FONT2_POS_X + x, FONT2_POS_Y + y, GetColor(255, 255, 255), "ヲばケがアらワレた！");
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void stageString::update()
{
	if (!IsSameStage())
		drawFlg = true;

	if (drawFlg)
	{
		blendCnt += 0.5f;
		if (blendCnt > 255)
		{
			blendCnt = -1.f;
			drawFlg = false;
		}
	}

	if (!ghostFlg&&torch::maxnum - torchLight::maxnum >= torch::maxnum)
		ghostFlg++;

	if (ghostFlg == 1)
	{
		gBlendCnt += 1.f;
		if (gBlendCnt > 255)
		{
			gBlendCnt = -1.f;
			ghostFlg++;
		}
	}
}
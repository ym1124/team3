#include "DxLib.h"
#include "common.h"
#include "vector.h"
#include "Player.h"
#include "Collision.h"
#include "YSDBG.h"
#include "gameObject.h"

#define PL_INIT_X	(100)
#define PL_INIT_Y	(600)

char controlPL = PLcon::BODY;
Player player;

Player::Player()
{
	pl_b = new PlBody();

	pl_S = new PlSoul();

}

void Player::Init()
{
	pl_b->Init();

	pl_S->Init();
}

void Player::Update()
{
	

	if (pl_S->soultime < 0)
	{
		pl_S->soultime = 0;
		pl_S->Reflg = true;
	}
	if (controlPL == PLcon::SOUL)pl_S->soultime--;

	if (key[KEY_INPUT_Z] == 1)
	{
		switch (controlPL)
		{
		case PLcon::BODY: controlPL = PLcon::SOUL;
			pl_S->jumpflg = true;
			pl_S->soultime = 300;
			break;
		case PLcon::SOUL:
			if (fabs(pl_b->getPos(true) - pl_S->getPos(true)) < 50)
			{
				if (fabs(pl_b->getPos(false) - pl_S->getPos(false)) < 50)
				{
					pl_S->Reflg = true;
				}
			}
			for (int i = 0; i < WOODENBOX_MAX; i++)
			{
				woodenbox *box = woodenboxs;
				if (fabs(box[i].pos.x - pl_S->getPos(true)) < 50)
				{
					if (fabs(box[i].pos.y - pl_S->getPos(false)) < 50)
					{
						controlPL = PLcon::BOX;
						box[i].inSoul = true;
						break;
					}
				}
			}
			break;
		case PLcon::RETURN:
			break;
		case PLcon::BOX:
			controlPL = PLcon::SOUL;
			pl_S->jumpflg = true;
			pl_S->soultime = 300;
			for (int i = 0; i < WOODENBOX_MAX; i++)
			{
				woodenbox *box = woodenboxs;
				box[i].inSoul = false;
			}
			break;
		default:
			break;
		}
	}
	pl_b->Update();

	pl_S->Update();

	if (pl_S->Reflg)pl_S->Return(pl_b);
}

void PlBody::Update()
{
	Gravity();

	if (delta.y < 0)
	{
		if (isFloor(pos.x, pos.y, 15))
		{
			mapHoseiDown(this);
			onGround = true;
		}
	}
	if (delta.y > 0)
	{
		if (isCeiling(pos.x, pos.y - 50, 15))
		{
			mapHoseiUp(this);
			jumpTimer = 0;
		}
	}

	if (controlPL == 0)Move();

	if (delta.x > 0)
	{
		if (isWall(pos.x + 15, pos.y, 50))
		{
			mapHoseiRight(this);
		}
	}
	if (delta.x < 0)
	{
		if (isWall(pos.x - 15, pos.y, 50))
		{
			mapHoseiLeft(this);
		}
	}

	if (controlPL == 0)Jump();
	

	DrawUpdate();
}

void PlSoul::Update()
{
	Gravity();

	if (delta.y < 0)
	{
		if (isFloor(pos.x, pos.y, 15))
		{
			mapHoseiDown(this);
			onGround = true;
		}
	}
	if (delta.y > 0)
	{
		if (isCeiling(pos.x, pos.y - 50, 15))
		{
			mapHoseiUp(this);
			jumpTimer = 0;
		}
	}


	Move();

	if (delta.x > 0)
	{
		if (isWall(pos.x + 15, pos.y, 50))
		{
			mapHoseiRight(this);
		}
	}
	if (delta.x < 0)
	{
		if (isWall(pos.x - 15, pos.y, 50))
		{
			mapHoseiLeft(this);
		}
	}

	Jump();
	CameraMove(vector2(pos.x, pos.y));

	DrawUpdate();
}

void Player::Draw()
{
	pl_b->Draw();

	pl_S->Draw();
}
void PlBody::Draw()
{
	DrawRectGraphF(pos.x - 32 - camera_pos.x, pos.y - 64 - camera_pos.y, 64 * aFrame, 64 * aLine, 64, 64, pl_Gr, TRUE, isFlipX);
}

void PlSoul::Draw()
{
	if (controlPL != PLcon::SOUL)return;
	SetDrawBlendMode(DX_BLENDMODE_INVSRC, 255);
	DrawRectGraphF(pos.x - 32 - camera_pos.x, pos.y - 64 - camera_pos.y, 64 * aFrame, 64 * aLine, 64, 64, pl_Gr, TRUE, isFlipX);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 60);
}


void PlBase::Debug()
{

}


PlBody::PlBody()
{
	pos.x = PL_INIT_X;
	pos.y = PL_INIT_Y;
	speed.x = 0.0f;
	speed.y = 0.0f;
	size.x = 15.0f;
	size.y = 50.0f;
	tex_size.x = 0.0f;
	tex_size.y = 0.0f;
	isFlipX = false;
	this->form = form;
	onGround = false;
	jumpTimer = 0;
	aCnt = 0;
	aFrame = 0;
	aLine = 0;
}

PlSoul::PlSoul()
{
	pos.x = PL_INIT_X;
	pos.y = PL_INIT_Y;
	speed.x = 0.0f;
	speed.y = 0.0f;
	size.x = 15.0f;
	size.y = 50.0f;
	tex_size.x = 0.0f;
	tex_size.y = 0.0f;
	isFlipX = false;
	this->form = form;
	onGround = false;
	jumpTimer = 0;
	jumpflg = false;
	Reflg = false;
	aCnt = 0;
	aFrame = 0;
	aLine = 0;
}

void PlBase::Init()
{
	pl_Gr = LoadGraph("resource/image/player.png");
}

void PlBase::unInit()
{

}

void PlBase::reSetData()
{

}

void PlBase::reSetRect()
{

}


PlBase::~PlBase()
{

}

void PlBase::DrawUpdate()
{
	static char prev = 0;
	aLine = 0;
	if (speed.x != 0)
	{
		aLine = 1;
	}

	//アニメーションカウント
	if (aLine != prev)
	{
		aCnt = 0;
		aFrame = 0;
	}
	prev = aLine;
	aCnt++;
	if (aCnt > 120)
	{
		aCnt = 0;
	}

	switch (aLine)
	{
	case 0:
		if (aCnt % 12 == 0)
		{
			aFrame++;
			if (aFrame >= 3)
			{
				aFrame = 0;
			}
		}
		break;
	case 1:
		if (aCnt % 14 == 0)
		{
			aFrame++;
			if (aFrame >= 6)
			{
				aFrame = 0;
			}
		}
		break;
	case 2:
	default:
		break;
	}
}

void PlBase::RectUpdate()
{

}

void PlBase::Move()
{
	static constexpr float ACCEL = 0.5f;
	static constexpr float SPEED_MAX_X = 7.0f;


	//移動処理
	if (key[KEY_INPUT_LEFT])
	{
		if (speed.x > 0)
		{
			speed.x = 0;
		}
		speed.x -= ACCEL;
	}
	else if (key[KEY_INPUT_RIGHT])
	{
		if (speed.x < 0)
		{
			speed.x = 0;
		}
		speed.x += ACCEL;
	}
	else
	{
		speed.x = 0;
	}

	if (speed.x > 0)isFlipX = false;
	else if (speed.x < 0)isFlipX = true;
	clamp(speed.x, -SPEED_MAX_X, SPEED_MAX_X);
	old.x = pos.x;
	pos.x += speed.x;
	delta.x = pos.x - old.x;
}

void PlBase::Gravity()
{
	static constexpr float SPEED_MAX_Y = 12.0f;
	static constexpr float GRAVITY = 0.7f;
	//static constexpr float GROUND_POS = 700.0f;

	onGround = false;
	speed.y += GRAVITY;
	if (speed.y >= SPEED_MAX_Y)
	{
		speed.y = SPEED_MAX_Y;
	}
	old.y = pos.y;
	pos.y += speed.y;
	delta.y = old.y - pos.y;

	//if (pos.y > GROUND_POS)
	//{
	//	onGround = true;
	//	pos.y = GROUND_POS;
	//}
}

void PlBase::Jump()
{
	static constexpr float JUMP_SPEED_Y = -10.0f;

	if (onGround || jumpflg)
	{
		if (key[KEY_INPUT_SPACE] == 1)
		{
  			jumpTimer = 12;
			jumpflg = false;
		}
	}

	if (jumpTimer > 0)
	{
		if (/*(PAD1 & PAD_INPUT_1) || */key[KEY_INPUT_SPACE])
		{
			speed.y = JUMP_SPEED_Y;
			jumpTimer--;
		}
		else
		{
			jumpTimer = 0;
		}
		if (jumpTimer <= 0)
		{
			jumpTimer = 0;
		}
	}
}

void PlSoul::Return(PlBase *body)
{
	if (body->getPos(true) < pos.x)
	{
		pos.x *= 0.95f;
		if (body->getPos(true) >= pos.x)
		{
			pos.x = body->getPos(true);
			Reflg = false;
			controlPL = PLcon::BODY;
		}
	}
	else
	{
		pos.x *= 1.05f;
		if (body->getPos(true) <= pos.x)
		{
			pos.x = body->getPos(true);
			Reflg = false;
			controlPL = PLcon::BODY;
		}
	}

	if (body->getPos(false) < pos.y)
	{
		pos.y *= 0.95f;
		if (body->getPos(false) >= pos.y)
		{
			pos.y = body->getPos(false);
		}
	}
	else
	{
		pos.y *= 1.05f;
		if (body->getPos(false) < pos.y)
		{
			pos.y = body->getPos(false);
		}
	}
}
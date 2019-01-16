#include "DxLib.h"
#include "common.h"
#include "Player.h"

#define PL_INIT_X	(100)
#define PL_INIT_Y	(300)

char controlPL = PLcon::BODY;
Player pl;

Player::Player()
{
	pl_b = new PlBody();

	pl_S = new PlSoul();

}

void Player::Update()
{
	if (key[KEY_INPUT_Z] == 1)
	{
		switch (controlPL)
		{
		case PLcon::BODY: controlPL = PLcon::SOUL;
			break;
		case PLcon::SOUL: pl_S->Reflg = true;
			break;
		case 2:
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

	if (controlPL != 0)return;

	Jump();

	Move();
}

void PlSoul::Update()
{

	Gravity();

	Jump();

	Move();
}

void Player::Draw()
{
	pl_b->Draw();

	pl_S->Draw();
}

float Player::getBodyPos(bool isX)
{
	if (pl_b != nullptr)
	{
		return pl_b->getPos(isX);
	}
	else
	{
		return 0;
	}
}

void PlBody::Draw()
{
	//‚¢‚¶‚è‚Ü‚µ‚½byYSD
	static int test;
	if (!test)
		test = LoadGraph("resource/image/invader.png", false);
	SetDrawBright(142, 142, 142);
	DrawGraph(pos.x, pos.y, test, true);
	SetDrawBright(255, 255, 255);
}

void PlSoul::Draw()
{
	if (controlPL != PLcon::SOUL)return;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 60);
	DrawBox(pos.x - 16, pos.y - 64, pos.x + 16, pos.y, color.Blue, TRUE);
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
	size.x = 0.0f;
	size.y = 0.0f;
	tex_size.x = 0.0f;
	tex_size.y = 0.0f;
	this->form = form;
	onGround = false;
	jumpTimer = 0;
}

PlSoul::PlSoul()
{
	pos.x = PL_INIT_X;
	pos.y = PL_INIT_Y;
	speed.x = 0.0f;
	speed.y = 0.0f;
	size.x = 0.0f;
	size.y = 0.0f;
	tex_size.x = 0.0f;
	tex_size.y = 0.0f;
	this->form = form;
	onGround = false;
	jumpTimer = 0;
	Reflg = false;
}

void PlBase::Init()
{

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

}

void PlBase::RectUpdate()
{

}

void PlBase::Move()
{
	static constexpr float ACCEL = 0.5f;
	static constexpr float SPEED_MAX_X = 7.0f;


	//??g?????
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

	clamp(speed.x, -SPEED_MAX_X, SPEED_MAX_X);
	pos.x += speed.x;
	pos.y += speed.y;

}

void PlBase::Gravity()
{
	static constexpr float SPEED_MAX_Y = 8.0f;
	static constexpr float GRAVITY = 0.5f;
	static constexpr float GROUND_POS = 300.0f;

	onGround = false;
	speed.y += GRAVITY;
	if (speed.y >= SPEED_MAX_Y)
	{
		speed.y = SPEED_MAX_Y;
	}
	//oldY = pos.y;
	pos.y += speed.y;
	//deltaY = oldY - pos.y;

	if (pos.y > GROUND_POS)
	{
		onGround = true;
		pos.y = GROUND_POS;
	}
}

void PlBase::Jump()
{
	static constexpr float JUMP_SPEED_Y = -6.0f;

	if (onGround)
	{
		if (key[KEY_INPUT_SPACE] == 1)
		{
			jumpTimer = 12;
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
}
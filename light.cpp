#include "Player.h"
#include "light.h"
#include "OBJ2D.h"
#include "gameObject.h"

int torchLight::lightGh;
int torch::fireGh, torch::torchGh, torch::sound;
int torchLight::sum = 0;
int torch::sumNumber = 0;
bool torchLight::setFlg = false;
int lanthanum::fireGh, lanthanum::lanthanumGh, lanthanum::sumNumber = 0;
static int yColor=0;

//�z��ŏ���������
//t10�̓v���C���[�̉�
torch
t1(vector2(850, 480)),
t2(vector2(1050, 480)),
t3(vector2(430, 130)),
t4(vector2(30, 330)),
t5(vector2(230, 330)),
t6(vector2(430, 330)),
t7(vector2(630, 330)),
t8(vector2(230, 530)),
t9(vector2(430, 530)),
t10(vector2(0, 0)), //t10�̓v���C���[����
t11(vector2(1250, 530)),
t12(vector2(1450, 530)),
t13(vector2(1650, 530)),
t14(vector2(1850, 530)),
t15(vector2(2050, 530)),
t16(vector2(2250, 530)),
t17(vector2(2450, 530)),
t18(vector2(2650, 530)),
t19(vector2(2850, 530)),
t20(vector2(3050, 530));

torchLight
light1(&t1),
light2(&t2),
light3(&t3),
light4(&t4),
light5(&t5),
light6(&t6),
light7(&t7),
light8(&t8),
light9(&t9),
light10(&t11),//t10�͎g�p�ς�
light11(&t12),
light12(&t13),
light13(&t14),
light14(&t15),
light15(&t16),
light16(&t17),
light17(&t18),
light18(&t19),
light19(&t20);

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
		torch::sound = LoadSoundMem("resource/sound/torchSound.mp3", true);
		onceFlg = true;
	}
}

void torch::hitCheck()
{
	//�����蔻��
	if (plLight.pos.x + 47 > pos.x + 25 && plLight.pos.x + 47 < pos.x + 70 && plLight.pos.y + 60 > pos.y + 35 && plLight.pos.y + 60 < pos.y + 85)
	{
		if (!isAlive)
		{
			PlaySoundMem(torch::sound, DX_PLAYTYPE_BACK);
		}
		isAlive = true;
	}
}

void torch::drawTorch()
{
	//�v���C���[�̉�����Ȃ��Ȃ珼�������`�悷��
	if (number != plLight.t->number)
		DrawGraph(pos.x + 47 - camera_pos.x, pos.y + 64 - camera_pos.y, torch::torchGh, true);
	//�f�o�b�O�p
	DrawLine(pos.x + 25 - camera_pos.x, pos.y + 35 - camera_pos.y, pos.x + 70 - camera_pos.x, pos.y + 35 - camera_pos.y, GetColor(255, 0, 0));
	DrawLine(pos.x + 25 - camera_pos.x, pos.y + 35 - camera_pos.y, pos.x + 25 - camera_pos.x, pos.y + 85 - camera_pos.y, GetColor(255, 0, 0));
	DrawLine(pos.x + 25 - camera_pos.x, pos.y + 85 - camera_pos.y, pos.x + 70 - camera_pos.x, pos.y + 85 - camera_pos.y, GetColor(255, 0, 0));
	DrawLine(pos.x + 70 - camera_pos.x, pos.y + 35 - camera_pos.y, pos.x + 70 - camera_pos.x, pos.y + 85 - camera_pos.y, GetColor(255, 0, 0));
}

//�����Ɖ΂�`�悷��
void torch::drawTorchAll()
{
	if (isAlive)
	{
		//���Z�u�����h(�d���Ȃ邾���Ȃ�g��Ȃ��ق�������)(��E����͕��ʂ̉�������)
		//SetDrawBlendMode(DX_BLENDMODE_SUB, 255);//���Z
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);//���Z
		//SetDrawBlendMode(DX_BLENDMODE_INVSRC, 255);//���]
		torchAnimCnt++;
		DrawRectGraph(pos.x - camera_pos.x, pos.y - camera_pos.y, 100 * (torchAnimCnt / 9 % 10), yColor*100, 100, 100, torch::fireGh, true);
		DrawRectGraph(pos.x - camera_pos.x, pos.y - camera_pos.y, 100 * (torchAnimCnt / 9 % 10), yColor * 100, 100, 100, torch::fireGh, true);
		//DrawRectGraph(pos.x - camera_pos.x, pos.y - camera_pos.y, 100 * (torchAnimCnt / 9 % 10), yColor * 100, 100, 100, torch::fireGh, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	drawTorch();
}

void torch::updateTorch()
{
	//�摜�̓ǂݍ��ݓ�
	setTorch();
	//�����蔻��
	hitCheck();
}

torchLight::torchLight(torch *t)
{
	sway = vector2(0, 0);
	torchLight::sum++;
	number = sum;
	this->t = t;
	pos = t->pos;
	isAlive = false;
}

void torchLight::initLight()
{
	if (!torchLight::setFlg)
	{
		//��ŏꏊ�ς���
		torchLight::lightGh = LoadGraph("resource/image/lightCircleB.png", true);
		torchLight::setFlg = true;
	}

	if (!isAlive&&t->isAlive)
	{
		//�_�΂���
		isAlive = true;
	}

}

void torchLight::moveLight()
{
	//��ŕς���
	t->updateTorch();
	if (isAlive)
	{
		//�`�悷��g�[�`�ƈʒu�����킹��
		pos = t->pos;
	}
}

void torchLight::drawLight(BGsystem *bg, Player *pl)
{
	if (isAlive)
	{
		//�P�x�ݒ�
		SetDrawBright(195, 195, 195);
		//�`��͈͎w��
		SetDrawArea(t->pos.x - LIGHT_MARGINE_X - camera_pos.x, t->pos.y - LIGHT_MARGINE_Y - camera_pos.y, t->pos.x + 200 - LIGHT_MARGINE_X - camera_pos.x, t->pos.y + 200 - LIGHT_MARGINE_Y - camera_pos.y);
		//�w�i�摜�̕`��//��ŕς���
		/*static int a = LoadGraph("resource/image/tempBack.png", true);
		DrawGraph(0, 0, a, true);*/
		bg->draw();
		//�����`��
		t->drawTorchAll();
		//�v���C���[����
		//plTorch.drawLight();
		gameObjectDrawAll();
		//�v���C���[�����^��
		plLight.l->drawLanthanumAll();
		//�v���C���[�`��
		pl->Draw();
		//�I�u�W�F�N�g�̃����^���`��
		Lanthanums[1].draw();
		//�A���t�@�u�����h�ݒ�
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 145);
		//�~�`�摜��`��
		DrawGraph(t->pos.x - LIGHT_MARGINE_X + sway.x - camera_pos.x, t->pos.y - LIGHT_MARGINE_Y + sway.y - camera_pos.y, torchLight::lightGh, true);
		//�A���t�@�u�����h�ݒ�
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		//�P�x�Đݒ�
		//SetDrawBright(255, 255, 255);
		//�`��͈͐ݒ����
		SetDrawAreaFull();
	}
}

void torchLight::updateLight(BGsystem *bg, Player *pl)
{
	t->updateTorch();
	initLight();
	moveLight();
	drawLight(bg, pl);
}

//�R���X�g���N�^
playerLight::playerLight() :torchLight(&t10)
{
	isAlive = true;
	l = &lanthanum1;
	l->isAlive = true;
}

void playerLight::moveLight(Player *pl)
{
	//�v���C���[�̉��ړ�//�}�[�W���ňʒu����
	pos.x = pl->pl_b->getPos(true) - 30;
	pos.y = pl->pl_b->getPos(false) - 90;
}

void playerLight::drawLight(Player *pl)
{
	if (isAlive)
	{
		//�f�o�b�O�p�����蔻��{�b�N�X
		DrawCircle(pos.x + 47 - camera_pos.x, pos.y + 60 - camera_pos.y, 5, GetColor(0, 0, 255), false);
		//�v���C���[�����`��
		/*DrawGraph(t->pos.x, t->pos.y, pTorchGh, true);*/
		//t->drawTorchAll();
		//�����^�������`��
		l->updateLanthanum(pl);
		//�P�x�Đݒ�
		SetDrawBright(142, 142, 142);//���������ɂȂ�(142,142,142)
	}
}

lanthanum::lanthanum(/*vector2 pos*/) /*:pos(pos)*/
{
	lanthanum::sumNumber++;
	number = lanthanum::sumNumber;
	pos.x = 0.0f/*player.pl_b->getPos(true)*/;
	pos.y = 0.0f/*player.pl_b->getPos(false)*/;
}

void lanthanum::initLanthanum()
{
	if (!fireGh)
	{
		lanthanum::fireGh = LoadGraph("resource/image/lanthanumfire.png");
		lanthanum::lanthanumGh = LoadGraph("resource/image/playerlanthanum.png");
		switch (yourColor)
		{
		case 3:
		case 4:
			yColor = 0;
			break;
		case 1:
		case 2:
			yColor = 1;
			break;
		case 0:
			yColor = 2;
			break;
		case -1:
		case -2:
			yColor = 3;
			break;
		case -3:
		case -4:
			yColor = 4;
			break;
		}
	}
}

//�����^�������̂ݕ`��
void lanthanum::drawLanthanum()
{
	DrawGraph(pos.x - camera_pos.x, pos.y - camera_pos.y, lanthanum::lanthanumGh, true);
}

//�����^���̉��܂ŕ`��
void lanthanum::drawLanthanumAll()
{
	DrawRectGraph(pos.x - camera_pos.x, pos.y - camera_pos.y, (lanthanumAnimCnt / 6 % 15) * 100, yColor * 100, 100, 100, lanthanum::fireGh, true);
	drawLanthanum();
}

//�����^���̈ړ�
void lanthanum::moveLanthanum(Player *pl)
{
	//�v���C���[�|�W�V�����擾
	pos.x = pl->pl_b->getPos(true) - 30;
	pos.y = pl->pl_b->getPos(false) - 90;
}

void lanthanum::updateLanthanum(Player *pl)
{
	lanthanumAnimCnt++;
	drawLanthanumAll();
	moveLanthanum(pl);
}

//************�v�C���֐��̃R�[�i�[**************//

void torchLight::swayLight()
{
	//���̗h��//�J�N�J�N�Ȃ�
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

void updateAllTorchLight(BGsystem *bg, Player *pl)
{
	//�_�΂������C�g�̕`��n
	light1.updateLight(bg, pl);
	light2.updateLight(bg, pl);
	light3.updateLight(bg, pl);
	light4.updateLight(bg, pl);
	light5.updateLight(bg, pl);
	light6.updateLight(bg, pl);
	light7.updateLight(bg, pl);
	light8.updateLight(bg, pl);
	light9.updateLight(bg, pl);
	light10.updateLight(bg, pl);
	light11.updateLight(bg, pl);
	light12.updateLight(bg, pl);
	light13.updateLight(bg, pl);
	light14.updateLight(bg, pl);
	light15.updateLight(bg, pl);
	light16.updateLight(bg, pl);
	light17.updateLight(bg, pl);
	light18.updateLight(bg, pl);
	light19.updateLight(bg, pl);
}

void drawAlltorch()
{
	//���������݂̂̕`��
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
	//t10.drawTorch();
	t11.drawTorch();
	t12.drawTorch();
	t13.drawTorch();
	t14.drawTorch();
	t15.drawTorch();
	t16.drawTorch();
	t17.drawTorch();
	t18.drawTorch();
	t19.drawTorch();
	t20.drawTorch();
}
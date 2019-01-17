#include "OBJ2D.h"

OBJ2D::OBJ2D()
{
	clear();
}

void OBJ2D::clear()
{
	texture = 0;
	pos = vector2(0, 0);
	mover = nullptr;
}

void OBJ2D::update()
{
	//ŠÖ”ƒ|ƒCƒ“ƒ^‚É“ü—Í‚³‚ê‚½ŠÖ”‚ÌŽÀs
	mover(this);
}

void OBJ2D::draw()
{
	//‰æ‘œ‚ª“ü‚Á‚Ä‚¢‚ê‚Î•`‰æ
	if (texture)
		DrawGraph(pos.x, pos.y, texture, true);
	//‰æ‘œ‚ª“ü‚Á‚Ä‚¢‚È‚¯‚ê‚Î’âŽ~
	//assert(!texture);
}

void OBJ2D::setObject(vector2 pos)
{
}

void testMove(OBJ2D *obj)
{
	if (key[KEY_INPUT_RIGHT]  >1)
		obj->pos.x++;
	if (key[KEY_INPUT_LEFT] > 1)
		obj->pos.x--;
	if (key[KEY_INPUT_UP] >1)
		obj->pos.y--;
	if (key[KEY_INPUT_DOWN] >1)
		obj->pos.y++;
}
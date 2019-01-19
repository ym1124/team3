#pragma once
#include "myFunc.h"


class PlBase : public BaseObject
{
public:
	PlBase() {};
	virtual ~PlBase();
	void reSetRect();
	void reSetData();
	virtual void Init();
	void unInit();
	void DrawUpdate();
	void RectUpdate();
	void Debug();

	void Jump();
	void Gravity();
	void Move();

	bool jumpflg;
protected:
	int pl_Gr;
};

class PlBody : public PlBase
{
public:
	PlBody();
	void Update();
	void Draw();
}; 

class PlSoul : public PlBase
{
public:
	PlSoul();
	void Update();
	void Draw();
	void Return(PlBase * body);

	bool Reflg;
	int soultime;
};

class Player
{
public:
	Player();
	void Update();
	void Draw();
	void Init();

	PlBody *pl_b;
	PlSoul *pl_S;
};

extern Player player;

enum PLcon
{
	BODY,
	SOUL,
	RETURN,
};
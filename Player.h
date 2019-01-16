#pragma once
#pragma once
#include "myFunc.h"

class PlBase : public BaseObject
{
public:
	PlBase() {};
	virtual ~PlBase();
	void reSetRect();
	void reSetData();
	void Init();
	void unInit();
	void DrawUpdate();
	void RectUpdate();
	void Debug();

	void Jump();
	void Gravity();
	void Move();

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
};

class Player
{
public:
	Player();
	void Update();
	void Draw();
	float getBodyPos(bool isX);

private:
	PlBody *pl_b;
	PlSoul *pl_S;
};

extern Player pl;

enum PLcon
{
	BODY,
	SOUL,
	RETURN,
};
#ifndef _MYFUNC_H_
#define _MYFUNC_H_

#include "Dxlib.h"
#include <assert.h>
#include <algorithm>


#define ATKBOX_MAX	(3)

struct VECTOR2
{
	float x, y;
};

struct INT2
{
	int x, y;
};

class BaseObject
{
public:
	VECTOR2 pos;
	VECTOR2 delta;
	VECTOR2 old;
	VECTOR2 speed;
	VECTOR2 size;
	VECTOR2 tex_size;
	int hp;
	int atk;
	bool onGround;
	bool isFlipX;
	bool Lprev;
	char jumpTimer;
	char atkAlg;
	char form;

	//アニメーション
	char aCnt;
	char aFrame;
	char aLine;
	int alpha;
public:
	bool debug1;
	bool debug2;	
	bool start;
	bool damage;
	char noHitTime;
	RECT chara;
	RECT atkBox[ATKBOX_MAX];
	RECT hitBox;
	virtual ~BaseObject(){}
	virtual void reSetRect() {};
	virtual void reSetData() {};
	virtual void Init() {};
	virtual void unInit() {};
	virtual void Update() {};
	virtual void Draw() {};
	virtual void DrawUpdate() {};
	virtual void RectUpdate() {};
	virtual void Debug() {};

	virtual float getPos(bool isX)
	{
		if (isX)return pos.x;
		else return pos.y;
	}
	virtual float getSpeed(bool isX)
	{
		if (isX)return speed.x;
		else return speed.y;
	}
	virtual float getSize(bool isX)
	{
		if (isX)return size.x;
		else return size.y;
	}
	virtual int getHP() { return hp; }
	virtual float getFlipX() { return isFlipX; }
	virtual char getatkAlg() { return atkAlg; }
	virtual int getATK() { return atk; }
	virtual void subHP(BaseObject *obj) {};
	virtual char getForm() { return form; }
	void setPosX(float x)
	{
		pos.x = x;
	}
	void setPosY(float y)
	{
		pos.y = y;
	}
	void setSpeedX(float x)
	{
		speed.x = x;
	}
	void setSpeedY(float y)
	{
		speed.y = y;
	}
};

class BaseSkill
{
protected:
	VECTOR2 pos;
	VECTOR2 speed;
	VECTOR2 size;
	INT2 tex_size;
	int atk;
	float angle;
	bool isFlipX;
	bool Lprev;
	char atkAlg;
	char state;
	bool exist;
	//アニメーション
	char aCnt;
	char aFrame;
	char aLine;
	int alpha;


public:
	RECT atkBox[ATKBOX_MAX];
	virtual ~BaseSkill() {}
	virtual void reSetRect() {};
	virtual void reSetData() {};
	virtual void Init() {};
	virtual void Update() {};
	virtual void Draw() {};
	virtual void DrawUpdate() {};
	virtual void RectUpdate() {};
	virtual void Debug() {};
	virtual void setSkill(BaseSkill* obj, float x, float y, int atkAlg) {};
};


inline float clamp(float& v, const float& lo, const float& hi)
{
	assert(hi >= lo);

	v = (std::max)((std::min)(v, hi), lo);

	return v;
}

inline int wrap(const int v, const int lo, const int hi)
{
	assert(hi > lo);
	const int n = (v - lo) % (hi - lo); // 負数の剰余はc++11から使用可になった
	return n >= 0 ? (n + lo) : (n + hi);
}

// float版
inline float wrap(const float v, const float lo, const float hi)
{
	assert(hi > lo);
	const float n = std::fmod(v - lo, hi - lo);
	return n >= 0 ? (n + lo) : (n + hi);
}


#endif

#pragma once


struct work
{
	char aCnt;
	char aFrame;
	char aLine;
};

class UI
{
public:
	static int Graph;
	static int Graph2;
	static int string;
	static int maxnum;
	bool torchFlg;
	int parsent;
	bool canSoul;
	void Init();
	void Update();
	void Draw();
	void DrawUpdate();

	enum KIND
	{
		BIGNUM = 0,
		SMLNUM,
		BACK,
		FIRE,
		EFCFIRE,
		STRING,

		_END,
	};
	work wk[_END];
};

class stageString
{
public:
	float blendCnt, gBlendCnt;
	bool drawFlg;
	char ghostFlg;
	stageString();
	void init();
	void update();
	void draw();
};

#define FONT1_POS_X 400 
#define FONT1_POS_Y 300
#define FONT2_POS_X 450 
#define FONT2_POS_Y 400
extern stageString stst;

extern UI MTIui;
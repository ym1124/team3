////////////////////////////////////////////////////////
//
//			BG.h	マップチップ
//
////////////////////////////////////////////////////////
#define CHIP_NUMX (20) //チップ配列の数x
#define CHIP_NUMY (20) //チップ配列の数y
#define CHIP_DIV_X (10)//画像の区切りの数x
#define CHIP_DIV_Y (10)//画像の区切りの数y
#define CHIP_SIZE (64) //画像の1区切りの大きさ

class BGsystem
{
private:

public:
	
	void init();
	void update();
	void draw();
	//void uninit();//作る？

};

extern int chip_data[CHIP_NUMX][CHIP_NUMY];
//extern BGsystem bg;



enum TR_ATTR
	{
		TR_NONE = -1,   // -1:何もなし
		ALL_BLOCK,      //  0:四方ブロック
		UPPER_BLOCK,    //  1:上だけブロック
		HASHIGO,        //  2:はしご
	};

const TR_ATTR terrainAttr[CHIP_DIV_X][CHIP_DIV_Y] = {
	{ TR_ATTR::TR_NONE,   TR_ATTR::ALL_BLOCK,   TR_ATTR::ALL_BLOCK,   TR_ATTR::ALL_BLOCK,   TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK, },
	{ TR_ATTR::UPPER_BLOCK, TR_ATTR::UPPER_BLOCK, TR_ATTR::UPPER_BLOCK, TR_ATTR::UPPER_BLOCK, TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE, },
	{ TR_ATTR::HASHIGO,     TR_ATTR::HASHIGO,     TR_ATTR::TR_NONE,     TR_ATTR::TR_NONE,     TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE, },
	{ TR_ATTR::TR_NONE,     TR_ATTR::TR_NONE,     TR_ATTR::TR_NONE,     TR_ATTR::TR_NONE,     TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE, },
};






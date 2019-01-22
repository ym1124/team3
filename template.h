#pragma once
#include "DxLib.h"

//ゲ－ムオブジェクト描画用ジェネリック関数
template<typename T>
void tempGameObjectUpdate(T *temp, int max);

template<typename T>
//temp=ゲ－ムオブジェクト配列の先頭アドレス　max=配列の要素数
void tempGameObjectUpdate(T *temp, int max)
{
	for (int i = 0; i < max; i++)
	{
		temp[i].update();
	}
}

template <typename T>
void tempGameObjectDraw(T *temp, int max, bool animFlg);

template <typename T>
void tempGameObjectDraw(T *temp, int max, bool animFlg)
{
	for (int i = 0; i < max; i++)
	{
		temp[i].draw(animFlg);
	}
}

//ランタンは特殊構造なのでコッチ使う
template <typename T>
void updateLanthanums(T *temp,int max);

template<typename T>
void updateLanthanums(T *temp,int max)
{
	for (int i = 0; i < max;i++)
	{
		temp[i].update();
		temp[i].f.update();
	}
}

template <typename T>
void drawLanthanums(T *temp, int max);

template <typename T>
void drawLanthanums(T *temp, int max)
{
	for (int i = 0; i < max; i++)
	{
		temp[i].draw();
		temp[i].f.draw(true);
	}
}

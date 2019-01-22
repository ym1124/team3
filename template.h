#pragma once
#include "DxLib.h"

//�Q�|���I�u�W�F�N�g�`��p�W�F�l���b�N�֐�
template<typename T>
void tempGameObjectUpdate(T *temp, int max);

template<typename T>
//temp=�Q�|���I�u�W�F�N�g�z��̐擪�A�h���X�@max=�z��̗v�f��
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

//�����^���͓���\���Ȃ̂ŃR�b�`�g��
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

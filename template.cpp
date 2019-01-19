#include "template.h"

template<typename T>
void tempUpdate(T *t)
{
	for (auto &it : t)
	{
		t.update();
		t.f.update();
	}
}

template <typename T>
void tempDraw(T *t)
{
	for (auto &it : t)
	{
		t.Draw();
		t.f.Draw(true);
	}
}
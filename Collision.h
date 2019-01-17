#pragma once
#include "myFunc.h"


bool isHitDown(float x, float y);
bool isFloor(float x, float y, float width);
bool isCeiling(float x, float y, float width);
bool isWall(float x, float y, float height);

void mapHoseiDown(BaseObject* obj);
void mapHoseiUp(BaseObject* obj);
void mapHoseiRight(BaseObject* obj);
void mapHoseiLeft(BaseObject* obj);


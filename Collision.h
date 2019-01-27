#pragma once
#include "myFunc.h"
#include "OBJ2D.h"


bool isHitDown(float x, float y);
bool isFloor(float x, float y, float width);
bool isCeiling(float x, float y, float width);
bool isWall(float x, float y, float height);
bool isPassWall(float x, float y, float height);
bool isHitObject(BaseObject *obj1, OBJ2D *obj2);
bool isHitObject(OBJ2D *obj1, OBJ2D *obj2);

void mapHoseiDown(BaseObject* obj);
void mapHoseiUp(BaseObject* obj);
void mapHoseiRight(BaseObject* obj);
void mapHoseiLeft(BaseObject* obj);

void mapHoseiDown(OBJ2D* obj);
void mapHoseiUp(OBJ2D* obj);
void mapHoseiRight(OBJ2D* obj);
void mapHoseiLeft(OBJ2D* obj);

void objHoseiDown(BaseObject* obj);
void objHoseiDown(OBJ2D* obj);

#include "vector.h"

vector2 vector2::operator+(const vector2&vec)
{
	vector2 tempvec;
	tempvec.x = this->x + vec.x;
	tempvec.y = this->y + vec.y;

	return tempvec;
}

void vector2::operator+=(const vector2&vec)
{
	this->x += vec.x;
	this->y += vec.y;
}

vector2 vector2::operator*(const int&value)
{
	vector2 tempvec;
	tempvec.x = this->x * value;
	tempvec.y = this->y * value;

	return tempvec;
}

vector2::vector2() {}

vector2::vector2(float a,float b):x(a),y(b){}
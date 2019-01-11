#pragma once

class vector2
{
public:
	float x;
	float y;
	vector2();
	vector2(float a, float b);
	vector2 operator+(const vector2&vec);
	void operator+=(const vector2&vec);
	vector2 operator*(const int&value);
};
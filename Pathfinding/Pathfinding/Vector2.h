#pragma once
#include <string>

struct Vec2
{
	int x, y;
	Vec2(int _x = 0, int _y = 0) :x(_x), y(_y) {}
	bool operator==(const Vec2& goal) const;
	Vec2 operator-(const Vec2& vector2) const;
	int MagnitudeSquared();  
	std::string ToString();
};


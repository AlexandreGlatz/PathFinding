#include "Vector2.h"

#include <cmath>

bool Vec2::operator==(const Vec2& goal) const
{
	return x == goal.x && y == goal.y;
}

Vec2 Vec2::operator-(const Vec2& vector2) const
{
	return { x - vector2.x, y - vector2.y };
}

int Vec2::MagnitudeSquared()
{
	return std::sqrt(pow(x,2) + pow(y,2));
}

std::string Vec2::ToString()
{
	return "x : " + std::to_string(x) + ", y : " + std::to_string(y);
}

#include "Vector2.h"

#include <cmath>

bool Vector2::operator==(const Vector2& goal) const
{
	return x == goal.x && y == goal.y;
}

Vector2 Vector2::operator-(const Vector2& vector2) const
{
	return { x - vector2.x, y - vector2.y };
}

int Vector2::MagnitudeSquared()
{
	return std::sqrt(pow(x,2) + pow(y,2));
}

std::string Vector2::ToString()
{
	return "x : " + std::to_string(x) + ", y : " + std::to_string(y);
}

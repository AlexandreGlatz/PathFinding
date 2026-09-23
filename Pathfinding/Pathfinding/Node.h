#pragma once

#include "Vector2.h"

enum class HEURISTIC
{
	EUCLIDIAN,
	MANHATTAN
};

struct Node
{
    Vec2 position;
    int g, h, f;
    Node* pParent;
    Node(Vec2 _position = Vec2());
    ~Node();

    int GetDistance(Node* from, HEURISTIC heuristic);
};


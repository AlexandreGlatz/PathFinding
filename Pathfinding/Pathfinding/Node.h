#pragma once

#include "Vector2.h"

enum class HEURISTIC
{
	EUCLIDIAN,
	MANHATTAN
};

struct Node
{
    Vector2 position;
    int g, h, f;
    Node* pParent;
    Node(Vector2 _position = Vector2());
    ~Node();

    int GetDistance(Node* from, HEURISTIC heuristic);
};


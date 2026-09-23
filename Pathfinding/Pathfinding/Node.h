#pragma once

#include "Vector2.h"

struct Node
{
    Vector2 position;
    int g, h, f;
    Node* pParent;
    Node(Vector2 _position = Vector2());
    ~Node();

    int GetDistance(Node* from);
    int GetNeighbourDistance(Node* from);
};


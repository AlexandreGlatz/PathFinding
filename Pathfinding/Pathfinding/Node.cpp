#include "Node.h"
#include <cmath>


Node::Node(Vector2 _position) : f(0), g(0), h(0), pParent(nullptr)
{
	position = _position;
}

Node::~Node()
{
	pParent = nullptr;
}

int Node::GetDistance(Node* from)
{
	return from->position.x - position.x + from->position.y - position.y;
}

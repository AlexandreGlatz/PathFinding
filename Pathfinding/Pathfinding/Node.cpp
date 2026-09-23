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
	return std::abs(from->position.x - position.x) + std::abs(from->position.y - position.y);
}

int Node::GetNeighbourDistance(Node* from)
{
	if (position.x == from->position.x || position.y == from->position.y)
	{
		return 10;
	}
	return 14;
}

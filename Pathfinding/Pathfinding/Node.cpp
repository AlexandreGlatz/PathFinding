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

int Node::GetDistance(Node* from, HEURISTIC heuristic)
{
	switch(heuristic)
	{
	case HEURISTIC::MANHATTAN:
		return std::abs(from->position.x - position.x) + std::abs(from->position.y - position.y);
	case HEURISTIC::EUCLIDIAN:
		Vector2 diff = from->position - position;
		return diff.MagnitudeSquared();
	}
}
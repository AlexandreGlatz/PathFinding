#pragma once

#include "PathfindingAlgorithm.h"

class Dijkstra : public PathfindingAlgorithm
{
public:
	Dijkstra();
	~Dijkstra();

	void Execute() override;

private:
	Node* GetMinNode(std::vector<Node*> nodes);
	void OneToAll(Node* pStartNode);

private:
};

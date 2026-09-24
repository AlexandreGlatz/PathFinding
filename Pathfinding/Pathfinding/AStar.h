#pragma once

#include "PathfindingAlgorithm.h"

struct Vec2;
struct Node;
struct Color;
class AStar : public PathfindingAlgorithm
{
public:
	AStar(HEURISTIC heuristic = HEURISTIC::MANHATTAN);
	~AStar();

	void SetHeuristic(HEURISTIC heuristic);

	void Execute();
	void Print();

private:
	Node* GetMinNode(std::vector<Node*> nodeList);
	std::vector<Node*> InitChildren(Node* pCurrentNode);
	std::vector<Node*> FetchPath(Node* pCurrentNode);

private:
	std::vector<Node*> m_openNodes;
	std::vector<Node*> m_closedNodes;

	HEURISTIC m_heuristic;
};


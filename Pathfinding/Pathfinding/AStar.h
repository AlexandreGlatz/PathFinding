#pragma once

#include <vector>
#include "Node.h"

struct Vector2;
struct Node;
class AStar
{
public:
	AStar(int gridWidth, int gridHeight, int step, HEURISTIC heuristic = HEURISTIC::MANHATTAN);
	~AStar();

	std::vector<Node*> Execute(Vector2 const& origin, Vector2 const& goal);
	static void Print(std::vector<Node*> pPath);

private:
	Node* GetMinNode(std::vector<Node*> nodeList);
	std::vector<Node*> InitChildren(Node* pCurrentNode);
	std::vector<Node*> GetPath(Node* pCurrentNode);
	void GenerateNodeGrid(int width, int height, int step);

private:
	std::vector<Node*> m_openNodes;
	std::vector<Node*> m_closedNodes;

	std::vector<std::vector<Node*>> m_nodeGrid;
	int m_step;
	int m_width;
	int m_height;

	HEURISTIC m_heuristic;
};


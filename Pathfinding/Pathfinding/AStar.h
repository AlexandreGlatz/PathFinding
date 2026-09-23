#pragma once

#include <vector>
#include "Node.h"

struct Vec2;
struct Node;
struct Color;
class AStar
{
public:
	AStar(int gridWidth, int gridHeight, int step, HEURISTIC heuristic = HEURISTIC::MANHATTAN);
	~AStar();

	std::vector<Node*> Execute(Vec2 const& origin, Vec2 const& goal);
	static void Print(std::vector<Node*> pPath);
	void DisplayGrid();
	void DisplayPath(std::vector<Node*> pPath);
	void DisplayObjectives(Vec2 const& origin, Vec2 const& goal);

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

	std::vector<Color*> m_weightColors;

	HEURISTIC m_heuristic;
};


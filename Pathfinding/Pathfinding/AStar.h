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

	void SetHeuristic(HEURISTIC heuristic);

	void SetStartPosition(Vec2 const& position);
	void SetEndPosition(Vec2 const& position);

	std::vector<Node*> Execute();
	void Print();
	void DisplayGrid();
	void DisplayPath();
	void DisplayObjectives();
	void SwitchWeightAt(int mouseX, int mouseY);
	void ClearParents();

	void Update();

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

	Vec2 m_startPosition;
	Vec2 m_endPosition;

	std::vector<Node*> m_finalPath;
};


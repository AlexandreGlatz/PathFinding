#pragma once

#include "Node.h"
#include <vector>

struct Color;
struct Vec2;

enum class ALGORITHM
{
	DIJKSTRA,
	ASTAR
};

class PathfindingAlgorithm
{
public:
	PathfindingAlgorithm(ALGORITHM algorithm);
	~PathfindingAlgorithm();

	void InitGrid(int gridWidth, int gridHeight, int step);

	virtual void Execute() = 0;

	virtual void SwitchWeightAtIndex(int i, int j);

	virtual void SetStartPosition(Vec2 const& position);
	void SetEndPosition(Vec2 const& position);

	int GetStep();
	std::string GetTypeStr();
	ALGORITHM GetType();

	Vec2 const& GetStartPosition();
	Vec2 const& GetEndPosition();
	std::vector<Node*> GetFinalPath();
	std::vector<std::vector<Node*>> GetNodeGrid();

protected:
	void ClearPredecessors();
	std::vector<Node*> FetchPath(Node* pCurrentNode);

protected:
	std::vector<std::vector<Node*>> m_nodeGrid;
	std::vector<Node*> m_finalPath;

	std::vector<Node*> m_openNodes;
	std::vector<Node*> m_closedNodes;

	Vec2 m_startPosition;
	Vec2 m_endPosition;

	int m_width;
	int m_height;
	int m_step;

	ALGORITHM m_type;

};

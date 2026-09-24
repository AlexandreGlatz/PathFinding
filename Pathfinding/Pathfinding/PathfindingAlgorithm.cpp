#include "PathfindingAlgorithm.h"

PathfindingAlgorithm::PathfindingAlgorithm(ALGORITHM algorithm) :
	m_startPosition({ 0, 0 }),
	m_endPosition({ 0, 0 }),
	m_height(0),
	m_width(0),
	m_step(0)
{
}

PathfindingAlgorithm::~PathfindingAlgorithm()
{
}

void PathfindingAlgorithm::SetStartPosition(Vec2 const& position)
{
	m_startPosition = position;
}

void PathfindingAlgorithm::SetEndPosition(Vec2 const& position)
{
	m_endPosition = position;
}

int PathfindingAlgorithm::GetStep()
{
	return m_step;
}

Vec2 const& PathfindingAlgorithm::GetStartPosition()
{
	return m_startPosition;
}

Vec2 const& PathfindingAlgorithm::GetEndPosition()
{	
	return m_endPosition;
}

std::vector<Node*> PathfindingAlgorithm::GetFinalPath()
{
	return m_finalPath;
}

std::vector<std::vector<Node*>> PathfindingAlgorithm::GetNodeGrid()
{
	return m_nodeGrid;
}

void PathfindingAlgorithm::ClearPredecessors()
{
	for (std::vector<Node*> nodes : m_nodeGrid)
	{
		for (Node* pNode : nodes)
		{
			pNode->pPredecessor = nullptr;
		}
	}
}

void PathfindingAlgorithm::SwitchWeightAtIndex(int i, int j)
{
	Node* pNode = m_nodeGrid[i][j];
	pNode->weight = (pNode->weight + 1) % 4;
}


void PathfindingAlgorithm::InitGrid(int gridWidth, int gridHeight, int step)
{
	m_nodeGrid.resize(gridWidth);
	for (int i = 0; i < gridWidth; ++i)
	{
		m_nodeGrid[i].resize(gridHeight);
		for (int j = 0; j < gridHeight; ++j)
		{
			m_nodeGrid[i][j] = new Node({ i * step, j * step });
		}
	}
}
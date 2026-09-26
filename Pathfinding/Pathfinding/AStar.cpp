#include "AStar.h"
#include "Node.h"

#include <iostream>

#define inf std::numeric_limits<int>::max()

AStar::AStar(HEURISTIC heuristic) :
	PathfindingAlgorithm(ALGORITHM::ASTAR),
	m_heuristic(heuristic)
{
}

AStar::~AStar()
{
}

void AStar::SetHeuristic(HEURISTIC heuristic)
{
	m_heuristic = heuristic;
}

void AStar::Execute()
{
	m_finalPath.clear();
	m_openNodes.clear();
	m_closedNodes.clear();
	ClearPredecessors();

	Node* pStartNode = m_nodeGrid[m_startPosition.x / m_step][m_startPosition.y / m_step];
	Node* pEndNode = m_nodeGrid[m_endPosition.x / m_step][m_endPosition.y / m_step];
	pStartNode->f = 0;

	m_openNodes.push_back(pStartNode);

	while (m_openNodes.empty() == false)
	{
		Node* pCurrentNode = GetMinNode(m_openNodes);
		m_openNodes.erase(std::remove(m_openNodes.begin(), m_openNodes.end(), pCurrentNode), m_openNodes.end());
		m_closedNodes.push_back(pCurrentNode);

		if (pCurrentNode->position == m_endPosition)
		{
			m_finalPath = FetchPath(pCurrentNode);
			m_finalPath.push_back(pStartNode);
			return;
		}
		
		std::vector<Node*> children = InitChildren(pCurrentNode);

		for (Node* pChild : children)
		{
			auto it = std::find(m_closedNodes.begin(), m_closedNodes.end(), pChild);
			if (it != m_closedNodes.end())
				continue;

			int h = pEndNode->GetDistance(pChild, m_heuristic);
			int g = pCurrentNode->g + pCurrentNode->GetDistance(pChild, m_heuristic);
			int f = (g + h) * pChild->weight;

			if (pChild->pPredecessor != nullptr && pChild->f < f)
				continue;
			
			pChild->h = h;
			pChild->g = g;
			pChild->f = f;
			pChild->pPredecessor = pCurrentNode;

			auto childIt = std::find_if(m_openNodes.begin(), m_openNodes.end(), [pChild](Node* pNode) {return pNode->position == pChild->position; });
			if (childIt != m_openNodes.end())
			{
				Node* pSamePosition = *childIt;
				if (pChild->f > pSamePosition->f)
					continue;
			}

			m_openNodes.push_back(pChild);
		}
	}
}

void AStar::Print()
{
	for (Node* pNode : m_finalPath)
	{
		std::cout << pNode->position.ToString() << std::endl;
	}
}

Node* AStar::GetMinNode(std::vector<Node*> nodeList)
{
	int minFValue = inf;
	int minHValue = inf;
	Node* pResultNode = nullptr;

	for (Node* pNode : nodeList)
	{
		if (pNode->f < minFValue)
		{
			minFValue = pNode->f;
			minHValue = pNode->h;
			pResultNode = pNode;
		}

		if (pNode->f == minFValue && pNode->h < minHValue)
		{
			minFValue = pNode->f;
			minHValue = pNode->h;
			pResultNode = pNode;
		}
	}
	
	return pResultNode;
}

std::vector<Node*> AStar::InitChildren(Node* pCurrentNode)
{
	int w = pCurrentNode->position.x / m_step;
	int h = pCurrentNode->position.y / m_step;

	std::vector<Node*> children;
	for (int i = -1; i <= 1; ++i)
	{
		for (int j = -1; j <= 1; ++j)
		{
			int widthPos = w + i;
			int heightPos = h + j;

			if (widthPos < 0 || widthPos >= m_width || heightPos < 0 || heightPos >= m_height)
				continue;

			if (m_nodeGrid[widthPos][heightPos]->weight == 0)
				continue;

			if (i == 0 && j == 0)
				continue;
				
			auto it = std::find(m_closedNodes.begin(), m_closedNodes.end(), m_nodeGrid[widthPos][heightPos]);
			if (it != m_closedNodes.end())
				continue;

			children.push_back(m_nodeGrid[widthPos][heightPos]);
		}
	}

	return children;
}

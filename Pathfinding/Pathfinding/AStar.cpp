#include "AStar.h"
#include "Node.h"

#include <iostream>
#include <raylib.h>

#define inf std::numeric_limits<int>::max()

AStar::AStar(int gridWidth, int gridHeight, int step, HEURISTIC heuristic) : m_step(step), m_width(gridWidth), m_height(gridHeight), m_heuristic(heuristic)
{
	GenerateNodeGrid(gridWidth, gridHeight, step);
}

AStar::~AStar()
{
}

std::vector<Node*> AStar::Execute(Vec2 const& origin, Vec2 const& goal)
{
	Node* pStartNode = m_nodeGrid[origin.x / m_step][origin.y / m_step];
	Node* pEndNode = m_nodeGrid[goal.x / m_step][goal.y / m_step];
	pStartNode->f = 0;

	m_openNodes.push_back(pStartNode);

	while (m_openNodes.empty() == false)
	{
		Node* pCurrentNode = GetMinNode(m_openNodes);
		m_openNodes.erase(std::remove(m_openNodes.begin(), m_openNodes.end(), pCurrentNode), m_openNodes.end());
		m_closedNodes.push_back(pCurrentNode);

		if (pCurrentNode->position == goal)
		{
			std::vector<Node*> path = GetPath(pCurrentNode);
			path.push_back(pStartNode);
			return path;
		}
		
		std::vector<Node*> children = InitChildren(pCurrentNode);

		for (Node* pChild : children)
		{
			auto it = std::find(m_closedNodes.begin(), m_closedNodes.end(), pChild);
			if (it != m_closedNodes.end())
				continue;

			int h = pEndNode->GetDistance(pChild, m_heuristic);
			int g = pCurrentNode->g + pCurrentNode->GetDistance(pChild, m_heuristic);
			int f = g + h;

			if (pChild->pParent != nullptr && pChild->f < f)
				continue;
			
			pChild->h = h;
			pChild->g = g;
			pChild->f = f;
			pChild->pParent = pCurrentNode;

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

void AStar::Print(std::vector<Node*> pPath)
{
	for (Node* pNode : pPath)
	{
		std::cout << pNode->position.ToString() << std::endl;
	}
}

void AStar::DisplayGrid()
{
	for (int i = 0; i<m_width; ++i)
	{
		for (int j = 0; j<m_height; ++j)
		{
			Color color = WHITE;
			if (m_nodeGrid[i][j] == nullptr)
			{
				color = BLACK;
			}
			DrawRectangle(i * m_step, j * m_step, m_step, m_step, color);
			DrawRectangleLines(i * m_step, j * m_step, m_step, m_step, BLACK);
		}
	}
}

void AStar::DisplayPath(std::vector<Node*> path)
{
	for (Node const* pNode : path)
	{
		DrawRectangle(pNode->position.x, pNode->position.y, m_step, m_step, GREEN);
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

			if (m_nodeGrid[widthPos][heightPos] == nullptr)
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

std::vector<Node*> AStar::GetPath(Node* pCurrentNode)
{
	Node* pNode = pCurrentNode;
	std::vector<Node*> path;
	while (pNode->pParent != nullptr)
	{
		path.push_back(pNode);
		pNode = pNode->pParent;
	}

	return path;
}

void AStar::GenerateNodeGrid(int width, int height, int step)
{
	m_nodeGrid.resize(width);
	for (int i = 0; i < width; ++i)
	{
		m_nodeGrid[i].resize(height);
		for (int j = 0; j < height; ++j)
		{
			m_nodeGrid[i][j] = new Node({ i * step, j * step });
		}
	}

	m_nodeGrid[3][5] = nullptr;
	m_nodeGrid[3][4] = nullptr;
	m_nodeGrid[4][4] = nullptr;
	m_nodeGrid[5][4] = nullptr;
	m_nodeGrid[6][4] = nullptr;


}

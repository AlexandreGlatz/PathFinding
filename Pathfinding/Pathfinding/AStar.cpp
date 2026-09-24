#include "AStar.h"
#include "Node.h"

#include <iostream>
#include <raylib.h>

#define inf std::numeric_limits<int>::max()

AStar::AStar(int gridWidth, int gridHeight, int step, HEURISTIC heuristic) :
	m_step(step),
	m_width(gridWidth),
	m_height(gridHeight),
	m_heuristic(heuristic),
	m_startPosition({ 0,0 }),
	m_endPosition({1 * step, 0})

{
	GenerateNodeGrid(gridWidth, gridHeight, step);
	m_weightColors = {new Color(DARKGREEN), new Color(DARKBROWN), new Color(YELLOW)};
}

AStar::~AStar()
{
}

void AStar::SetHeuristic(HEURISTIC heuristic)
{
	m_heuristic = heuristic;
}

void AStar::SetStartPosition(Vec2 const& position)
{
	m_startPosition = position;
}

void AStar::SetEndPosition(Vec2 const& position)
{
	m_endPosition = position;
}

std::vector<Node*> AStar::Execute()
{
	m_finalPath.clear();
	m_openNodes.clear();
	m_closedNodes.clear();
	ClearParents();

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
			m_finalPath = GetPath(pCurrentNode);
			m_finalPath.push_back(pStartNode);
			return m_finalPath;
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

void AStar::Print()
{
	for (Node* pNode : m_finalPath)
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
			if (m_nodeGrid[i][j]->weight == 0)
			{
				color = BLACK;
			}
			else
			{
				color = *m_weightColors[m_nodeGrid[i][j]->weight - 1];
			}
			DrawRectangle(i * m_step, j * m_step, m_step, m_step, color);
			DrawRectangleLines(i * m_step, j * m_step, m_step, m_step, BLACK);
		}
	}
}

void AStar::DisplayPath()
{
	for (Node const* pNode : m_finalPath)
	{
		float radius = m_step / 4.0f;
		DrawCircle(pNode->position.x + m_step / 2, pNode->position.y + m_step / 2, radius, RED);
	}
}

void AStar::DisplayObjectives()
{
	DrawText("Start", m_startPosition.x, m_startPosition.y, 0.25 * m_step, WHITE);
	DrawText("Goal", m_endPosition.x, m_endPosition.y, 0.25 * m_step, WHITE);
}

void AStar::SwitchWeightAt(int mouseX, int mouseY)
{
	Node* pNode = m_nodeGrid[mouseX / m_step][mouseY / m_step];
	pNode->weight = (pNode->weight + 1) % 4;
}

void AStar::ClearParents()
{
	for (std::vector<Node*> nodes : m_nodeGrid)
	{
		for (Node* pNode : nodes)
		{
			pNode->pParent = nullptr;
		}
	}
}

void AStar::Update()
{
	DisplayGrid();
	DisplayPath();
	DisplayObjectives();

	if (IsKeyPressed(KEY_S))
	{
		Vector2 mousePos = GetMousePosition();
		SetStartPosition({ static_cast<int>(mousePos.x) / m_step * m_step, static_cast<int>(mousePos.y) / m_step * m_step });
	}

	if (IsKeyPressed(KEY_G))
	{
		Vector2 mousePos = GetMousePosition();
		SetEndPosition({ static_cast<int>(mousePos.x) / m_step * m_step, static_cast<int>(mousePos.y) / m_step  * m_step});
	}

	if (IsKeyPressed(KEY_X))
		Execute();

	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		Vector2 mousePos = GetMousePosition();
		SwitchWeightAt(mousePos.x, mousePos.y);
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
}

#include "Dijkstra.h"

#define inf std::numeric_limits<int>::max()

Dijkstra::Dijkstra() : PathfindingAlgorithm(ALGORITHM::DIJKSTRA)
{
}

Dijkstra::~Dijkstra()
{
}

void Dijkstra::Execute()
{
    m_finalPath.clear();
    m_openNodes.clear();
    m_closedNodes.clear();
    ClearPredecessors();
    int gridSize = m_width * m_height;
    //m_openNodes.resize(gridSize);

	Node* pStartNode = m_nodeGrid[m_startPosition.x / m_step][m_startPosition.y / m_step];
    OneToAll(pStartNode);

	Node* pEndNode = m_nodeGrid[m_endPosition.x / m_step][m_endPosition.y / m_step];

    m_finalPath = FetchPath(pEndNode);
    m_finalPath.push_back(pStartNode);
}

Node* Dijkstra::GetMinNode(std::vector<Node*> nodes)
{
	int minFValue = inf;
	Node* pResultNode = nullptr;

	for (Node* pNode : nodes)
	{
		if (pNode->f < minFValue)
		{
			minFValue = pNode->f;
			pResultNode = pNode;
		}
	}
	
	return pResultNode;
}

void Dijkstra::OneToAll(Node* pStartNode)
{
    for (int i = 0; i < m_width; ++i)
    {
        for (int j = 0; j < m_height; ++j)
        {
            m_nodeGrid[i][j]->f = inf;
            m_openNodes.push_back(m_nodeGrid[i][j]);
        }
    }

    pStartNode->f = 0;

    while (m_openNodes.empty() == false)
    {
        Node* pCurrentNode = GetMinNode(m_openNodes);
        m_openNodes.erase(std::remove(m_openNodes.begin(), m_openNodes.end(), pCurrentNode), m_openNodes.end());
		m_closedNodes.push_back(pCurrentNode);

        for (int i = 0; i < m_openNodes.size(); ++i)
        {
            int diffX = std::abs(m_openNodes[i]->position.x / m_step % m_width - pCurrentNode->position.x / m_step);
            int diffY = std::abs(m_openNodes[i]->position.y / m_step % m_height - pCurrentNode->position.y / m_step);
            if (m_openNodes[i]->weight == inf || (diffX > 1 || diffY > 1))
                continue;

            int diagonal = 0;
            if (diffX == diffY)
                diagonal = 1;
            int temp = pCurrentNode->f + m_openNodes[i]->weight + diagonal;
            
            if (temp < m_openNodes[i]->f)
            {
                m_openNodes[i]->f = temp;
                m_openNodes[i]->pPredecessor = pCurrentNode;
            }
        }

    }

}

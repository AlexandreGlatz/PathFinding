#pragma once

#include "PathfindingAlgorithm.h"

class Dijkstra : public PathfindingAlgorithm
{
public:
	Dijkstra();
	~Dijkstra();

	void Execute() override;

	void SetStartPosition(Vec2 const& position) override;
	void SwitchWeightAtIndex(int i, int j) override;

private:
	Node* GetMinNode(std::vector<Node*> nodes);
	void OneToAll(Node* pStartNode);

private:
	bool m_hasPathChanged;
};

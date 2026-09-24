#pragma once

#include "PathfindingAlgorithm.h"

class Dijkstra : public PathfindingAlgorithm
{
public:
	Dijkstra(int gridWidth, int gridHeight);
	~Dijkstra();

	void Execute() override;

};

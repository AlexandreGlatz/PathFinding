#pragma once

#include "Node.h"

#include <vector>

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

	void Init(int gridWidth, int gridHeight, HEURISTIC heuristic);

	void DisplayGrid();
	
private:

};


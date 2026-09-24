#pragma once

#include <vector>
	
class PathfindingAlgorithm;
struct Color;
struct Node;
struct Vec2;
class GridRenderer
{
public:
	GridRenderer(PathfindingAlgorithm* pAlgorithm);
	~GridRenderer();

	void Update();

private:
	void DisplayGrid(std::vector<std::vector<Node*>> nodeGrid, int step);
	void DisplayPath(std::vector<Node*> nodes, int step);
	void DisplayObjectives(Vec2 const& start, Vec2 const& end, int step);

private:
	std::vector<Color*> m_weightColors;
	PathfindingAlgorithm* m_pAlgorithm;

};


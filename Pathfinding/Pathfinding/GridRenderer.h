#pragma once

#include <vector>
#include <chrono>
#include <string>
#include <unordered_map>
	
class PathfindingAlgorithm;
class Dijkstra;
class AStar;
struct Color;
struct Node;
struct Vec2;
class GridRenderer
{
public:
	GridRenderer(PathfindingAlgorithm* pAlgorithm);
	~GridRenderer();

	void Update();

	void SwitchAlgorithm();

private:
	void DisplayGrid(std::vector<std::vector<Node*>> nodeGrid, int step);
	void DisplayPath(std::vector<Node*> nodes, int step);
	void DisplayObjectives(Vec2 const& start, Vec2 const& end, int step);
	void DisplayTutorial();

private:
	std::vector<Color*> m_weightColors;
	PathfindingAlgorithm* m_pAlgorithm;

	int m_gridWidth;
	int m_gridHeight;
	int m_algorithmIndex;

	std::chrono::time_point<std::chrono::steady_clock> m_beginning;
	std::string m_secondsTimer;

	std::vector<PathfindingAlgorithm*> m_algorithms;
};


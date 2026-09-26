#include "GridRenderer.h"
#include "PathfindingAlgorithm.h"

#include <raylib.h>

GridRenderer::GridRenderer(PathfindingAlgorithm* pAlgorithm): m_pAlgorithm(pAlgorithm)
{
	m_weightColors = { new Color(DARKGREEN), new Color(BROWN), new Color(YELLOW) };
}

GridRenderer::~GridRenderer()
{
}

void GridRenderer::Update()
{
	int step = m_pAlgorithm->GetStep();
	DisplayGrid(m_pAlgorithm->GetNodeGrid(), step);
	DisplayPath(m_pAlgorithm->GetFinalPath(), step);
	DisplayObjectives(m_pAlgorithm->GetStartPosition(), m_pAlgorithm->GetEndPosition(), step);
	DisplayTutorial();

	if (IsKeyPressed(KEY_S))
	{
		Vector2 mousePos = GetMousePosition();
		m_pAlgorithm->SetStartPosition({ static_cast<int>(mousePos.x) / step * step, static_cast<int>(mousePos.y) / step * step });
	}

	if (IsKeyPressed(KEY_G))
	{
		Vector2 mousePos = GetMousePosition();
		m_pAlgorithm->SetEndPosition({ static_cast<int>(mousePos.x) / step * step, static_cast<int>(mousePos.y) / step  * step});
	}

	if (IsKeyPressed(KEY_X))
	{
		m_beginning = std::chrono::steady_clock::now();
		m_pAlgorithm->Execute();
		double currentTimer = std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1>>>(std::chrono::steady_clock::now() - m_beginning).count();
		m_secondsTimer = std::to_string(currentTimer);
	}

	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		Vector2 mousePos = GetMousePosition();
		m_pAlgorithm->SwitchWeightAtIndex(static_cast<int>(mousePos.x) / step, static_cast<int>(mousePos.y) / step);
	}

}

void GridRenderer::DisplayGrid(std::vector<std::vector<Node*>> nodeGrid, int step)
{
	size_t width = nodeGrid.size();
	size_t height = nodeGrid[0].size();

	m_gridWidth = width * step;
	m_gridHeight = height * step;

	for (int i = 0; i<width; ++i)
	{
		for (int j = 0; j<height; ++j)
		{
			Color color = WHITE;
			if (nodeGrid[i][j]->weight == 0)
			{
				color = BLACK;
			}
			else
			{
				color = *m_weightColors[nodeGrid[i][j]->weight - 1];
			}
			DrawRectangle(i * step, j * step, step, step, color);
			DrawRectangleLines(i * step, j * step, step, step, BLACK);
		}
	}
}

void GridRenderer::DisplayPath(std::vector<Node*> nodes, int step)
{
	for (Node const* pNode : nodes)
	{
		float radius = step / 4.0f;
		DrawCircle(pNode->position.x + step / 2, pNode->position.y + step / 2, radius, RED);
	}
}

void GridRenderer::DisplayObjectives(Vec2 const& start, Vec2 const& end, int step)
{
	DrawText("Start", start.x, start.y, 0.25 * step, WHITE);
	DrawText("Goal", end.x, end.y, 0.25 * step, WHITE);
}

void GridRenderer::DisplayTutorial()
{
	DrawText("S -> Set Start", 20, m_gridHeight + 20, 20, WHITE);
	DrawText("G -> Set Goal", 20, m_gridHeight + 40, 20, WHITE);
	DrawText("X -> Execute Algorithm & display path", 20, m_gridHeight + 60, 20, WHITE);
	std::string timeString = "Time to execute" + m_secondsTimer;
	DrawText(timeString.c_str(), 20, m_gridHeight + 80, 20, WHITE);
	
}



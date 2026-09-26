// Pathfinding.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "PathfindingAlgorithm.h"
#include "AStar.h"
#include "Dijkstra.h"
#include "GridRenderer.h"

#include <raylib.h>

int main()
{
    int gridWidth = 20;
    int gridHeight = 20;
    int windowWidth = 800;
    int windowHeight = 800;
    int step = windowWidth / gridWidth;

    PathfindingAlgorithm* pAlgorithm = new Dijkstra();
    pAlgorithm->InitGrid(gridWidth, gridHeight, step);

    GridRenderer renderer(pAlgorithm);

    InitWindow(windowWidth, windowHeight + 200, "Pathfinding test");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGREEN);
        renderer.Update();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

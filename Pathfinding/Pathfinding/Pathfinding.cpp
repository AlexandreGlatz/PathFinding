// Pathfinding.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "PathfindingAlgorithm.h"
#include "AStar.h"
#include "Dijkstra.h"
#include "GridRenderer.h"

#include <raylib.h>

int main()
{
    /*std::vector<std::vector<int>> graph{
    {0, 10, 15, inf, 30, inf, inf},
    {inf, 0, inf, inf, inf, 57, inf},
    {15, inf, 0, 16, inf, inf, 52},
    {inf, inf, 13, 0, inf, inf, inf},
    {30, inf, inf, inf, 0, 11, 34},
    {inf, 49, inf, inf, 12, 0, inf},
    {inf, inf, 63, inf, 35, inf, 0 } };*/

    //Result result = DikjstraOneToAll('a', graph);
    
    int gridWidth = 100;
    int gridHeight = 100;
    int windowWidth = 1000;
    int windowHeight = 1000;
    int step = windowWidth / gridWidth;

    PathfindingAlgorithm* pAlgorithm = new Dijkstra();
    pAlgorithm->InitGrid(gridWidth, gridHeight, step);

    GridRenderer renderer(pAlgorithm);

    InitWindow(windowWidth, windowHeight, "Pathfinding test");
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

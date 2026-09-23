// Pathfinding.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Node.h"
#include "AStar.h"
#include <iostream>
#include <limits>
#include <vector>

#define inf std::numeric_limits<int>::max()

#include <raylib.h>

struct Result
{
    std::vector<int> dist;
    std::vector<char> pred;
};

char GetVertexWithMinDist(char origin, std::vector<char> openNodes, std::vector<std::vector<int>> matrix)
{
    int minDist = inf;
    char minDistVertex = ' ';

    int originInt = origin - 'a';
    for (int i = 0; i < openNodes.size(); ++i)
    {

        if (matrix[originInt][openNodes[i] - 'a'] <= minDist)
        {
            minDist = matrix[originInt][openNodes[i] - 'a'];
            minDistVertex = openNodes[i];
        }
    }

    return minDistVertex;

}

Result DikjstraOneToAll(char origin, std::vector<std::vector<int>> matrix)
{
    std::vector<char> openNodes(matrix.size());
    Result result;
    int originInt = origin - 'a';

    result.dist.resize(matrix.size());
    result.pred.resize(matrix.size());

    for (int i = 0; i < matrix.size(); ++i)
    {
        result.dist[i] = inf;
        openNodes[i] = i + 'a';
    }

    result.dist[originInt] = 0;

    while (openNodes.empty() == false)
    {
        char currentNode = GetVertexWithMinDist(origin, openNodes, matrix);
        openNodes.erase(std::remove(openNodes.begin(), openNodes.end(), currentNode), openNodes.end());

        int currentNodeInt = currentNode - 'a';
        for (int i = 0; i < openNodes.size(); ++i)
        {
            int currentIndex = openNodes[i] - 'a';

            if (matrix[currentNodeInt][currentIndex] == inf)
                continue;

            int temp = result.dist[currentNodeInt] + matrix[currentNodeInt][currentIndex];
            
            if (temp < result.dist[currentIndex])
            {
                result.dist[currentIndex] = temp;
                result.pred[currentIndex] = currentNode;
            }
        }

    }

    return result;

}




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
    
    int gridWidth = 7;
    int gridHeight = 7;
    int step = 100;
    AStar algo(gridWidth, gridHeight, step, HEURISTIC::MANHATTAN);

    std::vector<Node*> path = algo.Execute({100, 100}, {500, 500});
    AStar::Print(path);

    InitWindow(gridWidth * step, gridHeight * step, "A* test");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGREEN);
        algo.DisplayGrid();
        algo.DisplayPath(path);
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

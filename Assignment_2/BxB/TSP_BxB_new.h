#pragma once
#include <vector>
#include <limits>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>

class Node {
public:
    Node *parent;
    int vertex;
    int lowerBound;

    Node(int vertex, int lowerBound, Node *parent);
};

class TSP_BxB_new {
public:
    static std::pair<int, std::vector<int>> TSP_BESTFIRST_start(int num_of_vertices, const std::vector<std::vector<int>> &matrix);
    static std::pair<int, std::vector<int>> TSP_DFS_start(int num_of_vertices, const std::vector<std::vector<int>> &matrix);
    static std::pair<int, std::vector<int>> TSP_BFS_start(int num_of_vertices, const std::vector<std::vector<int>> &matrix);
private:
    static int *minWeights;
    static int graphSize;
    static int startingVertex;

    static std::vector<int> getAvailableVertices(Node *node);
    static std::vector<int> getPath(Node *node);
};


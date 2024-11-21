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
    int vertex;
    int lowerBound;
    std::vector<short> current_path;

    Node(int vertex, int lowerBound);
};

class TSP_BxB {
public:
    static std::pair<int, std::vector<int>> TSP_BFS_start(int num_of_vertices, const std::vector<std::vector<int>> &matrix, int initialUpperBound);
    static std::pair<int, std::vector<int>> TSP_DFS_start(int num_of_vertices, const std::vector<std::vector<int>> &matrix, int initialUpperBound);
    static std::pair<int, std::vector<int>> TSP_BESTFIRST_start(int num_of_vertices, const std::vector<std::vector<int>> &matrix, int initialUpperbound);

private:
    static int *minWeights;
    static int graphSize;
    static int startingVertex;

    static std::vector<short> getVerticesToVisit(Node *node);
};


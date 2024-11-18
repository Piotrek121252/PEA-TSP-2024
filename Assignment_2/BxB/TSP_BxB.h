#pragma once
#include <vector>
#include <limits>
#include <iostream>
#include <algorithm>


class TSP_BxB {
public:
    static std::pair<int, std::vector<int>> TSP_DFS_start(int num_of_vertices, const std::vector<std::vector<int>> &matrix);
    static std::pair<int, std::vector<int>> TSP_BFS_start(int num_of_vertices, const std::vector<std::vector<int>> &matrix);
    static std::pair<int, std::vector<int>> TSP_LOWCOST_start(int num_of_vertices, const std::vector<std::vector<int>> &matrix);
private:
    static int computeInitLB(int n, const std::vector<std::vector<int>> &matrix);
    static int getSmallestEdge(int n, int node, const std::vector<std::vector<int>> &matrix);
};


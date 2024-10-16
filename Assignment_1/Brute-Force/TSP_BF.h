#pragma once
#include <vector>
#include <limits>
#include <iostream>
#include <algorithm>

class TSP_BF {
public:
    static std::pair<int, std::vector<int>> TSP_BF_start(int num_of_vertices, const std::vector<std::vector<int>> &matrix);

};


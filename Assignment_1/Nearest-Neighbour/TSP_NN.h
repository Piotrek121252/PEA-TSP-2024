#pragma once
#include <vector>
#include <limits>
#include <iostream>
#include <algorithm>

class TSP_NN {
public:
    static std::pair<int, std::vector<int>> TSP_NN_start(int num_of_vertices, const std::vector<std::vector<int>> &matrix);

};


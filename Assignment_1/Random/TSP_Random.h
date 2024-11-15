#pragma once
#include <vector>
#include <limits>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

class TSP_Random {
public:
    static std::pair<int, std::vector<int>> TSP_Random_start(int num_of_vertices, const std::vector<std::vector<int>> &matrix, int time_limit_seconds, int optimal_cost);

};


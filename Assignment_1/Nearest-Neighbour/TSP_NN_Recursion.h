#pragma once
#include <vector>
#include <limits>
#include <iostream>
#include <algorithm>

class TSP_NN_Recursion {
public:
    static std::pair<int, std::vector<int>> TSP_NN_start(int num_of_vertices, const std::vector<std::vector<int>> &matrix);
private:
    static void nearest_neighbor_search(int current_city, const std::vector<std::vector<int>>& matrix, std::vector<bool>& visited, std::vector<int>& current_path,
                                        int current_cost, int& best_cost, std::vector<int>& best_path, int num_of_vertices);
};

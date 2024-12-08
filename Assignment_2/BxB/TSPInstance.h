#pragma once

#include <iostream>
#include <vector>
#include <string>


class TSPInstance {
private:
    int vertices;
    std::vector<std::vector<int>> adjacency_matrix;
    std::string filename;
    int repetitions;
    std::string method;
    int optimal_cost;
    int initial_upperbound;
    std::vector<int> optimal_path;

public:
    TSPInstance(int vertices, const std::vector<std::vector<int>>& adjacency_matrix, std::string filename, int repetitions, std::string method, int optimal_cost, int initial_upperbound, const std::vector<int>& optimal_path);

    void display() const;

    int getVertices() const;

    const std::vector<std::vector<int>> &getAdjacencyMatrix() const;

    const std::string &getFilename() const;

    const std::string &getMethod() const;

    int getRepetitions() const;

    int getOptimalCost() const;

    int getInitialUpperBound() const;

    const std::vector<int> &getOptimalPath() const;
};


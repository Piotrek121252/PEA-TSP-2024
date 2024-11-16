#include "TSPInstance.h"

// Constructor to initialize the TSP instance with adjacency matrix
TSPInstance::TSPInstance(int vertices, const std::vector<std::vector<int>>& adjacency_matrix, std::string filename, int repetitions, std::string method, int optimal_cost, const std::vector<int>& optimal_path)
        : vertices(vertices), adjacency_matrix(adjacency_matrix), filename(filename), repetitions(repetitions), method(method), optimal_cost(optimal_cost), optimal_path(optimal_path) {}

// Function to display the instance details (for testing)
void TSPInstance::display() const {
    std::cout << "Adjacency Matrix:\n";
    std::cout << vertices << std::endl;
    for (const auto& row : adjacency_matrix) {
        for (int value : row) {
            std::cout << value << " ";
        }
        std::cout << "\n";
    }

    std::cout << "Filename: " << filename << std::endl;
    std::cout << "Repetitions: " << repetitions << "\n";
    std::cout << "Method: " << method << "\n";
    std::cout << "Optimal Cost: " << optimal_cost << "\n";
    std::cout << "Optimal Path: ";
    for (const auto& node : optimal_path) {
        std::cout << node << " ";
    }
    std::cout << "\n";
}

int TSPInstance::getVertices() const {
    return vertices;
}

const std::vector<std::vector<int>> &TSPInstance::getAdjacencyMatrix() const {
    return adjacency_matrix;
}

const std::string &TSPInstance::getFilename() const {
    return filename;
}

const std::string &TSPInstance::getMethod() const {
    return method;
}

int TSPInstance::getRepetitions() const {
    return repetitions;
}

int TSPInstance::getOptimalCost() const {
    return optimal_cost;
}

const std::vector<int> &TSPInstance::getOptimalPath() const {
    return optimal_path;
}

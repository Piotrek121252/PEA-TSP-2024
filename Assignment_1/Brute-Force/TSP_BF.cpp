#include "TSP_BF.h"

 std::pair<int, std::vector<int>> TSP_BF::TSP_BF_start(int num_of_vertices, const std::vector<std::vector<int>> &matrix) {

    // Include all vertices including the starting vertex (0)
    std::vector<int> vertices(num_of_vertices);
    for (int i = 0; i < num_of_vertices; i++) {
        vertices[i] = i;
    }

    int optimal_cost = std::numeric_limits<int>::max();
    std::vector<int> optimal_path;

    // Generate all permutations including the starting vertex
    do {
        int current_cost = 0;

        // Calculate the cost for the current permutation
        for (int i = 0; i < num_of_vertices; i++) {
            int next_vertex = (i + 1) % num_of_vertices; // Wrap around to create a cycle
            current_cost += matrix[vertices[i]][vertices[next_vertex]];
        }
        
        // Update the optimal solution if the current path is better
        if (current_cost < optimal_cost) {
            optimal_cost = current_cost;
            optimal_path = vertices;
        }

    } while (std::next_permutation(vertices.begin(), vertices.end()));

    return {optimal_cost, optimal_path};
}

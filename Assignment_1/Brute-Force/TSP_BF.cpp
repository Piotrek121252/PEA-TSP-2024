#include "TSP_BF.h"

 std::pair<int, std::vector<int>> TSP_BF::TSP_BF_start(int num_of_vertices, const std::vector<std::vector<int>> &matrix) {

    // Tworzymy pierwszą ścieżkę
    std::vector<int> vertices(num_of_vertices);
    for (int i = 0; i < num_of_vertices; i++) {
        vertices[i] = i;
    }
    // Tworzymy zmienne przechowujące obecnie najlepsze rozwiązanie
    int optimal_cost = std::numeric_limits<int>::max();
    std::vector<int> optimal_path;

    do {
        int current_cost = 0;

        // Obliczamy koszt danej ścieżki
        for (int cur_vertex = 0; cur_vertex < num_of_vertices; cur_vertex++) {
            // Wykorzystujemy modulo, żeby uwzględnić powrót do pierwszego miasta
            int next_vertex = (cur_vertex + 1) % num_of_vertices;
            current_cost += matrix[vertices[cur_vertex]][vertices[next_vertex]];
        }
        
        // Aktualizujemy jak znajdziemy lepsze rozwiązanie
        if (current_cost < optimal_cost) {
            optimal_cost = current_cost;
            optimal_path = vertices;
        }

        // Iterujemy dopóki nie przejdziemy przez wszystkie permutacje
    } while (std::next_permutation(vertices.begin(), vertices.end()));

    return {optimal_cost, optimal_path};
}

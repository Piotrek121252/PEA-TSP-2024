#include "TSP_Random.h"

 std::pair<int, std::vector<int>> TSP_Random::TSP_Random_start(int num_of_vertices, const std::vector<std::vector<int>> &matrix, int number_of_iterations) {
    // zmienne przechowujące najlepszy koszt oraz ścieżkę
    int best_cost = std::numeric_limits<int>::max();
    std::vector<int> current_path(num_of_vertices);
    std::vector<int> best_path(num_of_vertices);

    // Tworzymy pierwszą ścieżkę, którą będziemy zmieniać
    for (int i = 0; i < num_of_vertices; i++) {
        current_path[i] = i;
    }
     // Tworzymy generator liczb losowych
     std::random_device rd;
     std::mt19937 g(rd());
    // Korzystając z shuffle zmieniamy kolejność miast w ścieżce tworząc nową ścieżkę
    for (int i = 0; i < number_of_iterations; i++) {
        std::shuffle(current_path.begin(), current_path.end(), g);

        int current_cost = 0;

        // Obliczamy koszt danej ścieżki
        for (int cur_vertex = 0; cur_vertex < num_of_vertices; cur_vertex++) {
            // Wykorzystujemy modulo, żeby uwzględnić powrót do pierwszego miasta
            int next_vertex = (cur_vertex + 1) % num_of_vertices;
            current_cost += matrix[current_path[cur_vertex]][current_path[next_vertex]];
        }

        // Aktualizujemy zmienne jak znajdziemy lepsze rozwiązanie
        if (current_cost < best_cost) {
            best_cost = current_cost;
            best_path = current_path;
        }
    }

     return {best_cost, best_path};
}

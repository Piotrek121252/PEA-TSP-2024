#include "TSP_Random.h"

 std::pair<int, std::vector<int>> TSP_Random::TSP_Random_start(int num_of_vertices, const std::vector<std::vector<int>> &matrix, int time_limit_seconds, int optimal_cost) {
    // Zmienne przechowujące najlepszy koszt oraz ścieżkę
    int best_cost = std::numeric_limits<int>::max();
    std::vector<int> best_path(num_of_vertices);

    std::vector<int> current_path(num_of_vertices);
    // Tworzymy pierwszą ścieżkę, którą będziemy zmieniać
    for (int i = 0; i < num_of_vertices; i++) {
        current_path[i] = i;
    }
     // Tworzymy generator liczb losowych
     std::random_device rd;
     std::mt19937 g(rd());

     // Start time tracking
     auto start_time = std::chrono::steady_clock::now();
     const auto time_limit = std::chrono::seconds(time_limit_seconds);

    // Korzystając z std::shuffle zmieniamy kolejność miast w ścieżce tworząc nową ścieżkę
    while (true) {
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
            // Warunek stopu, jak uda nam się znaleźć wynik optymalny podany razem z instancją
            if (best_cost == optimal_cost)
                return {best_cost, best_path};

        }

        // Sprawdzamy czy przekroczyliśmy limit czasu
        auto current_time = std::chrono::steady_clock::now();
        if (current_time - start_time >= time_limit) {
            break;
        }

    }
     return {best_cost, best_path};
}

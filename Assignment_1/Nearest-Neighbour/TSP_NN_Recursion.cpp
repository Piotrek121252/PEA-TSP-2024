#include "TSP_NN_Recursion.h"

void TSP_NN_Recursion::nearest_neighbor_search(int current_city, const std::vector<std::vector<int>>& matrix, std::vector<bool>& visited, std::vector<int>& current_path,
                                               int current_cost, int& best_cost, std::vector<int>& best_path, int num_of_vertices) {
    // Jeśli udało nam się odwiedzić wszystkie miasta to sprawdzamy czy ścieżka jest najlepsza do tej pory
    if (current_path.size() == num_of_vertices) {
        // Dodajemy koszt powrotu do startowego miasta
        current_cost += matrix[current_city][current_path[0]];
        if (current_cost < best_cost) {
            best_cost = current_cost;
            best_path = current_path;
        }

    }
    // Inicjalizujemy zmienne, które będą przechowywać najmniejszy koszt oraz wierzchołki do których prowadzi droga o takim koszcie
    int nearest_distance = std::numeric_limits<int>::max();
    std::vector<int> nearest_cities;

    // Przeglądamy wszystkie nieodwiedzone wierzchołki
    for (int j = 0; j < num_of_vertices; ++j) {
        if (!visited[j] && matrix[current_city][j] < nearest_distance) {
            // Gdy uda nam się znaleźć miasto o najmniejszym koszcie
            nearest_distance = matrix[current_city][j];
            nearest_cities = {j};
        } else if (!visited[j] && matrix[current_city][j] == nearest_distance) {
            // Gdy znajdziemy miasto o koszcie takim samym jak obecnie najmniejsze
            // To dodajemy je na koniec listy
            nearest_cities.push_back(j);
        }
    }

    // Przeglądamy wszystkie miasta z listy najbliższych miast
    for (int city : nearest_cities) {
        visited[city] = true;              // Dodajemy miasto do odwiedzonych wierzchołków
        current_path.push_back(city);      // Dodajemy do ścieżki
        current_cost += nearest_distance; // Dodajemy koszt do obecnego kosztu

        // Eksplorujemy kolejne wierzchołki
        nearest_neighbor_search(city, matrix, visited, current_path, current_cost,
                                best_cost, best_path, num_of_vertices);

        // Cofamy się w danym kroku aby móc przejrzeć kolejne miasto
        visited[city] = false;
        current_path.pop_back();
        current_cost -= nearest_distance;
    }
}

std::pair<int, std::vector<int>> TSP_NN_Recursion::TSP_NN_start(int num_of_vertices, const std::vector<std::vector<int>> &matrix) {
    // Inicjalizujemy zmienne przechowujące najlepszy koszt i ścieżke
    int best_cost = std::numeric_limits<int>::max();
    std::vector<int> best_path;

    // Sprawdzamy każde miasto
    for (int starting_city = 0; starting_city < num_of_vertices; starting_city++) {
        // Inicjalizujemy tablice z odwiedzonymi miastami dla danego miasta startowego
        std::vector<bool> visited(num_of_vertices, false);
        visited[starting_city] = true;
        std::vector<int> current_path = {starting_city};
        int current_cost = 0;

        // Wywołujemy metodę, która wykorzystuje rekurencję aby zachłannie stworzyć ścieżke
        nearest_neighbor_search(starting_city, matrix, visited, current_path, current_cost,
                                best_cost, best_path, num_of_vertices);

    }

    return {best_cost, best_path};
}

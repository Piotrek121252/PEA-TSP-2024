#include "TSP_NN.h"

 std::pair<int, std::vector<int>> TSP_NN::TSP_NN_start(int num_of_vertices, const std::vector<std::vector<int>> &matrix) {
    // Tworzymy zmienne przechowujące najlepszy koszt i ścieżkę
    int best_cost = std::numeric_limits<int>::max();
    std::vector<int> best_path;

     // Sprawdzamy dla każdego początkowego miasta najlepszą drogę
     for (int starting_city = 0; starting_city < num_of_vertices; starting_city++) {
         // Tworzymy tablicę odwiedzonych miast
         std::vector<bool> visited(num_of_vertices, false);
         visited[starting_city] = true;

         // zmienne przechowujące pośrednie wyniki - koszt i droga
         int current_cost = 0;
         std::vector<int> current_path = {starting_city};
         int current_city = starting_city;

         // Szukamy drogi dla danego miasta
         for (int i = 0; i < num_of_vertices - 1; ++i) {
             int nearest_distance = std::numeric_limits<int>::max();
             int nearest_city = -1;

             // Szukamy najbliższego miasta wychodzącego z tego miasta, którego jeszcze nie odwiedziliśmy
             for (int j = 0; j < num_of_vertices; ++j) {
                 if (!visited[j] && matrix[current_city][j] < nearest_distance) {
                     nearest_distance = matrix[current_city][j];
                     nearest_city = j;
                 }
             }
             // Jeśli nie da się stworzyć ścieżki to ustawiamy current cost na MAX_INT
             if (nearest_city == -1) {
                 current_cost = std::numeric_limits<int>::max();
                 break;
             }

             // Dodajemy najbliższe miasto do ścieżki
             visited[nearest_city] = true;
             current_cost += nearest_distance;
             current_city = nearest_city;
             current_path.push_back(current_city);
         }

         // Dodajemy koszt powrotu do początkowego miasta
         current_cost += matrix[current_city][starting_city];
//         current_path.push_back(starting_city);

         // Jeśli droga z danego miasta jest lepsza to aktualizujemy najlepszą ścieżkę i koszt
         if (current_cost < best_cost) {
             best_cost = current_cost;
             best_path = current_path;
         }
     }

     return {best_cost, best_path};
}

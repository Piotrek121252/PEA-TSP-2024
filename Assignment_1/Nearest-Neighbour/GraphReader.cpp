#include "GraphReader.h"
#include <fstream>

// Funkcja, której celem jest wczytanie informacji o grafie z pliku na dysku
std::pair<int, std::vector<std::vector<int>>> GraphReader::readGraph(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Problem z otworzeniem pliku: " + filename);
    }

    int vertices;
    file >> vertices;

    std::vector<std::vector<int>> matrix(vertices, std::vector<int>(vertices));

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            file >> matrix[i][j];

            if (file.fail()) {
                throw std::runtime_error("Problem ze strukturą danych w pliku: " + filename);
            }
        }
    }

    // Można jeszcze sprawdzić czy eof
    file.close();
    return {vertices, matrix};
}
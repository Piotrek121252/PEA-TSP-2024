#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include "TSPInstance.h"
#include "GraphReader.h"
#include "TSP_BF.h"


std::pair<std::vector<TSPInstance>, std::string> loadInstances(const std::string& filename) {

    std::vector<TSPInstance> instances;
    std::ifstream config_file(filename);
    std::string result_filename;

    // Sprawdzamy czy udało się otworzyć plik konfiguracyjny
    if (!config_file.is_open()) {
        std::cerr << "Nie udalo sie otworzyc pliku konfiguracyjnego: " << filename << std::endl;
        return {instances, result_filename};
    }

    // Czytamy wszystkie linie z pliku konfiguracyjnego
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(config_file, line)) {
        lines.push_back(line);
    }

    // Rozdzielamy linie z instancjami od ostatniej linii z nazwą pliku results
    std::string results_filename = lines.back();
    lines.pop_back();

    // Wyciągamy potrzebne informacje z każdej linii
    for (const auto& instanceLine : lines) {
        std::istringstream iss(instanceLine);
        std::string graph_file;
        int repetitions;
        int optimal_cost;
        std::vector<int> optimal_path;

        iss >> graph_file >> repetitions >> optimal_cost;

        // Czytamy optymalna ścieżke
        int node;
        while (iss >> node) {
            optimal_path.push_back(node);
        }

        // Próba wczytania pliku z dwóch ścieżek
        std::string primary_path = "Instances/" + graph_file;
        std::string fallback_path = "./" + graph_file;

        std::pair<int, std::vector<std::vector<int>>> graphModel;
        try {
            graphModel = GraphReader::readGraph(primary_path);
        } catch (const std::runtime_error& e) {
            try {
                graphModel = GraphReader::readGraph(fallback_path);
            } catch (const std::runtime_error& e) {
                std::cerr << e.what() << std::endl;
                continue;
            }
        }

        // Tworzymy instancję TSP do przebadania i dodajemy do listy instancji
        if (!graphModel.second.empty()) {
            TSPInstance tsp_instance(graphModel.first, graphModel.second, graph_file, repetitions, optimal_cost, optimal_path);
            instances.push_back(tsp_instance);
        }
    }
    // Zamykamy config file
    config_file.close();

    return {instances, results_filename};
}

int main() {
    std::string config_filename = "config.txt";

    // Czytamy plik konfiguracyjny i tworzymy instancje TSP do badań
    auto [instances, results_filename] = loadInstances(config_filename);

    std::ofstream results_file(results_filename, std::ios::app);

    // Dla każdej instancji wykonujemy badanie
    for (const auto& instance : instances) {
//        instance.display();
        results_file << "Instance Name,Repetitions,Optimal Cost,Optimal Path\n";
        results_file << instance.getFilename() << "," << instance.getRepetitions() << "," << instance.getOptimalCost() << ",";

        for (size_t i = 0; i < instance.getOptimalPath().size() - 1; i++) {
            results_file << instance.getOptimalPath()[i] << "-";
        }
        results_file << instance.getOptimalPath().back() << std::endl;

        results_file << "No.,Cost,Execution Times [ms]\n";

        std::cout << "Filename: " << instance.getFilename() << std::endl;

        for (int rep = 0; rep < instance.getRepetitions(); rep++) {
            std::pair<int, std::vector<int>> result;

            auto start_time = std::chrono::high_resolution_clock::now();

            result = TSP_BF::TSP_BF_start(instance.getVertices(), instance.getAdjacencyMatrix());

            auto end_time = std::chrono::high_resolution_clock::now();

            long long measured_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

            // Obliczamy błędy aby ocenić nasze rozwiązanie
            double absolute_error = std::abs(result.first - instance.getOptimalCost());
            double relative_error = (instance.getOptimalCost() != 0) ? absolute_error / std::abs(instance.getOptimalCost()) : 0.0;
            double relative_error_percentage = relative_error * 100;

            results_file << rep + 1 << ".," << result.first << "," << measured_time / 1000.0 << "\n";

            std::cout << "Repetition " << rep + 1 << " - Result: " << result.first << " - Execution Time: " << measured_time / 1000.0 << " [ms]\n";

            for (size_t j = 0; j < result.second.size() - 1; j++) {
                std::cout << result.second[j] << "->";
            }
                std::cout << result.second.back() << std::endl;

            if (result.first != instance.getOptimalCost()) {
                std::cout << "Different cost detected for " << instance.getFilename() << " - Repetition " << rep + 1 << std::endl;
            }
        }
    }

    results_file.close();

    int choice;
    std::cout << "Tests finished." << std::endl;
    std::cin >> choice;
    return 0;
}
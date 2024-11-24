#include <unordered_set>
#include <utility>
#include "TSP_BxB.h"

Node::Node(int vertex, int lowerBound) {
    this->vertex = vertex;
    this->lowerBound = lowerBound;
}

int *TSP_BxB::minWeights;
int TSP_BxB::startingVertex;
int TSP_BxB::graphSize;

std::pair<int, std::vector<int>>
TSP_BxB::TSP_BFS_start(int num_of_vertices, const std::vector<std::vector<int>> &matrix, int initialUpperBound) {

    startingVertex = 0;
    graphSize = num_of_vertices;
    // Tworzymy kolejkę do przechowywania aktywnych węzłów oraz zmienną przechowującą najlepsze znalezione rozwiązanie
    std::queue<Node *> queue;
    std::vector<short> bestPath;

    // Ustawiamy początkowe górne ograniczenie na podstawie parametru initialUpperBound
    int upperBound;
    if (initialUpperBound > 0) {
        upperBound = initialUpperBound;
    } else {
        upperBound = std::numeric_limits<int>::max();
    }

    // Wypełniamy tablicę z najmniejszą krawędzią dla każdego wierzchołka
    // oraz obliczamy pierwsze dolne ograniczenie korzystając z niej
    minWeights = new int[num_of_vertices];
    int lowerBound = 0;

    for (int i = 0; i < num_of_vertices; i++) {
        int minWeight = std::numeric_limits<int>::max();
        for (int j = 0; j < num_of_vertices; j++) {
            if (i != j) {
                int weight = matrix[i][j];
                if (weight < minWeight) {
                    minWeight = weight;
                }
            }
        }
        minWeights[i] = minWeight;
        lowerBound += minWeight;
    }
    // Tworzymy pierwszy węzeł, który będzie korzeniem i dodajemy go do kolejki
    short rootVertex = startingVertex;
    Node *root = new Node(startingVertex, lowerBound);
    root->current_path = {rootVertex};
    queue.push(root);

    // Przetwarzamy kolejne węzły dopóki kolejka dalej posiada węzły
    while (!queue.empty()) {
        Node *node = queue.front();
        queue.pop();

        // Jeśli mamy pełne rozwiązanie to dodajemy drogę powrotną i sprawdzamy
        // czy znalezione rozwiązanie jest lepsze od obecnie najlepszego
        if (node->current_path.size() == num_of_vertices) {
            node->lowerBound = node->lowerBound - minWeights[node->vertex] + matrix[node->vertex][startingVertex];
            if (node->lowerBound <= upperBound) {
                upperBound = node->lowerBound;
                bestPath = node->current_path;
                bestPath.push_back(startingVertex);
            }
            delete node;
            continue;
        }

        // Pobieramy listę wierzchołków, które można odwiedzić z danego wierzchołka
        std::vector<short> verticesToVisit = getVerticesToVisit(node, matrix);

        // Dla każdego węzła, który można odwiedzić obliczamy
        // dolne ograniczenie i decydujemy czy dodać go do kolejki
        for (short childVertex : verticesToVisit) {
            lowerBound = node->lowerBound - minWeights[node->vertex] + matrix[node->vertex][childVertex];

            if (lowerBound < upperBound) {
                // Tworzymy nowy węzeł i dodajemy go do kolejki
                Node *child = new Node(childVertex, lowerBound);
                child->current_path = std::vector<short>(node->current_path);
                child->current_path.push_back(childVertex);
                queue.push(child);
            }
        }
        // Po przetworzeniu węzła zwalniamy zasoby, które zajmował
        delete node;
    }
    // Zwalniamy pamięć używaną na tablice z najmniejszymi krawędziami
    delete[] minWeights;

    // Zamiamy najlepszą ścieżkę z short na int aby móc ją zwrócić
    std::vector<int> optimalPath;

    optimalPath.reserve(bestPath.size());
    optimalPath.insert(optimalPath.end(), bestPath.begin(), bestPath.end());

    return {upperBound, optimalPath};
}

std::vector<short> TSP_BxB::getVerticesToVisit(Node *node, const std::vector<std::vector<int>> &matrix) {
    std::unordered_set<int> verticesToVisit;
    for (int i = 0; i < graphSize; i++) {
        if (matrix[node->vertex][i] > 0) {
            verticesToVisit.insert(i);
        }
    }
    // Usuwamy elementy z hash table bazując
    // na zawartości obecnej ścieżki
    for (int vertex : node->current_path) {
        verticesToVisit.erase(vertex);
    }
    // Przekładamy elementy do tablicy i sortujemy ją rosnąco
    std::vector<short> orderedVertices(verticesToVisit.begin(), verticesToVisit.end());
    std::sort(orderedVertices.begin(), orderedVertices.end());

    return orderedVertices;
}

std::pair<int, std::vector<int>>
TSP_BxB::TSP_DFS_start(int num_of_vertices, const std::vector<std::vector<int>> &matrix, int initialUpperBound) {

    startingVertex = 0;
    graphSize = num_of_vertices;
    // Tworzymy stos przechowujący węzły do przetworzenia
    std::stack<Node *> stack;
    std::vector<short> bestPath;

    // Ustawiamy początkowe górne ograniczenie na podstawie parametru initialUpperBound
    int upperBound;
    if (initialUpperBound > 0) {
        upperBound = initialUpperBound;
    } else {
        upperBound = std::numeric_limits<int>::max();
    }

    // Wypełniamy tablicę z najmniejszą krawędzią dla każdego wierzchołka
    // oraz obliczamy pierwsze dolne ograniczenie korzystając z niej
    minWeights = new int[num_of_vertices];
    int lowerBound = 0;

    for (int i = 0; i < num_of_vertices; i++) {
        int minWeight = std::numeric_limits<int>::max();
        for (int j = 0; j < num_of_vertices; j++) {
            if (i != j) {
                int weight = matrix[i][j];
                if (weight < minWeight) {
                    minWeight = weight;
                }
            }
        }
        minWeights[i] = minWeight;
        lowerBound += minWeight;
    }

    // Tworzymy pierwszy węzeł, który będzie korzeniem i dodajemy go na stos
    short rootVertex = startingVertex;
    Node *root = new Node(startingVertex, lowerBound);
    root->current_path = {rootVertex};
    stack.push(root);

    // Przetwarzamy kolejne węzły dopóki stos nie jest pusty
    while (!stack.empty()) {
        // Pobieramy węzeł ze szczytu stosu
        Node *node = stack.top();
        stack.pop();

        // Jeśli mamy pełne rozwiązanie to dodajemy drogę powrotną i sprawdzamy
        // czy znalezione rozwiązanie jest lepsze od obecnie najlepszego
        if (node->current_path.size() == num_of_vertices) {
            node->lowerBound = node->lowerBound - minWeights[node->vertex] + matrix[node->vertex][startingVertex];
            if (node->lowerBound <= upperBound) {
                upperBound = node->lowerBound;
                bestPath = node->current_path;
                bestPath.push_back(startingVertex);
            }
            delete node;
            continue;
        }
        // Pobieramy listę wierzchołków, które można odwiedzić z danego wierzchołka
        std::vector<short> verticesToVisit = getVerticesToVisit(node, matrix);
        // Dla każdego węzła, który można odwiedzić obliczamy
        // dolne ograniczenie i decydujemy czy dodać go na stos
        // robimy to w odwrotnej kolejności aby na szczycie stostu był wierzchołek z najmniejszym indeksem
        for (int i = verticesToVisit.size() - 1; i >= 0; i--) {
            short childVertex = verticesToVisit[i];
            lowerBound = node->lowerBound - minWeights[node->vertex] + matrix[node->vertex][childVertex];

            if (lowerBound < upperBound) {
                // Tworzymy nowy węzeł i dodajemy go do kolejki
                Node *child = new Node(childVertex, lowerBound);
                child->current_path = std::vector<short>(node->current_path);
                child->current_path.push_back(childVertex);
                stack.push(child);
            }
        }
        // Po przetworzeniu węzła zwalniamy zasoby, które zajmował
        delete node;
    }
    // Zwalniamy pamięć używaną na tablice z najmniejszymi krawędziami
    delete[] minWeights;

    // Zamiamy najlepszą ścieżkę z short na int aby móc ją zwrócić
    std::vector<int> optimalPath;

    optimalPath.reserve(bestPath.size());
    optimalPath.insert(optimalPath.end(), bestPath.begin(), bestPath.end());

    return {upperBound, optimalPath};
}

struct compareNodes2 {
    bool operator()(const Node *a, const Node *b) const {
        return a->lowerBound > b->lowerBound;
    }
};

std::pair<int, std::vector<int>>
TSP_BxB::TSP_BESTFIRST_start(int num_of_vertices, const std::vector<std::vector<int>> &matrix, int initialUpperbound) {

    startingVertex = 0;
    graphSize = num_of_vertices;
    // Tworzymy kopiec minimalizacyjny, do którego przekazujemy komparator
    // porównujący węzły na podstawie wartości lowerBound
    std::priority_queue<Node *, std::vector<Node *>, compareNodes2> pq;
    std::vector<short> bestPath;

    // Ustawiamy początkowe górne ograniczenie na podstawie parametru initialUpperBound
    int upperBound;
    if (initialUpperbound > 0) {
        upperBound = initialUpperbound;
    } else {
        upperBound = std::numeric_limits<int>::max();
    }

    // Wypełniamy tablicę z najmniejszą krawędzią dla każdego wierzchołka
    // oraz obliczamy pierwsze dolne ograniczenie korzystając z niej
    minWeights = new int[num_of_vertices];

    int lowerBound = 0;
    for (int i = 0; i < num_of_vertices; i++) {
        int minWeight = std::numeric_limits<int>::max();
        for (int j = 0; j < num_of_vertices; j++) {
            if (i != j) {
                int weight = matrix[i][j];
                if (weight < minWeight) {
                    minWeight = weight;
                }
            }
        }
        minWeights[i] = minWeight;
        lowerBound += minWeight;
    }
    // Tworzymy pierwszy węzeł, który będzie korzeniem i dodajemy go do kopca
    short rootVertex = startingVertex;
    Node *root = new Node(startingVertex, lowerBound);
    root->current_path = {rootVertex};
    pq.push(root);

    // Przetwarzamy kolejne węzły dopóki kopiec nie jest pusty
    while (!pq.empty()) {
        Node *node = pq.top();
        pq.pop();

        if (node->current_path.size() == num_of_vertices) {
            // Jeśli mamy pełne rozwiązanie to dodajemy drogę powrotną i sprawdzamy
            // czy znalezione rozwiązanie jest lepsze od obecnie najlepszego
            node->lowerBound = node->lowerBound - minWeights[node->vertex] + matrix[node->vertex][startingVertex];
            if (node->lowerBound <= upperBound) {
                upperBound = node->lowerBound;
                bestPath = node->current_path;
                bestPath.push_back(startingVertex);
            }
            delete node;
            continue;
        }

        // Pobieramy listę wierzchołków, które można odwiedzić z danego wierzchołka
        std::vector<short> verticesToVisit = getVerticesToVisit(node, matrix);

        // Dla każdego węzła, który można odwiedzić obliczamy
        // dolne ograniczenie i decydujemy czy dodać go do kopca
        for (short childVertex : verticesToVisit) {
            lowerBound = node->lowerBound - minWeights[node->vertex] + matrix[node->vertex][childVertex];

            if (lowerBound < upperBound) {
                // Tworzymy nowy węzeł i dodajemy go do kopca
                Node *child = new Node(childVertex, lowerBound);
                child->current_path = std::vector<short>(node->current_path);
                child->current_path.push_back(childVertex);
                pq.push(child);
            }
        }
        // Po przetworzeniu węzła zwalniamy zasoby, które zajmował
        delete node;
    }
    // Zwalniamy pamięć używaną na tablice z najmniejszymi krawędziami
    delete[] minWeights;

    // Zamiamy najlepszą ścieżkę z short na int aby móc ją zwrócić
    std::vector<int> optimalPath;

    optimalPath.reserve(bestPath.size());
    optimalPath.insert(optimalPath.end(), bestPath.begin(), bestPath.end());

    return {upperBound, optimalPath};
}



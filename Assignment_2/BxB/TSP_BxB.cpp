#include <stack>
#include <queue>
#include "TSP_BxB.h"

const int INF = std::numeric_limits<int>::max();

struct NodeState {
    int node;
    std::vector<int> path;
    int pathCost;
    int lower_bound;
    std::vector<bool> visited;
};

struct CompareNodeState {
    bool operator()(const NodeState& a, const NodeState& b) {
        return a.pathCost > b.pathCost;
    }
};

std::pair<int, std::vector<int>> TSP_BxB::TSP_DFS_start(int num_of_vertices, const std::vector<std::vector<int>> &matrix) {
    // Tworzymy zmienne przechowujące obecnie najlepsze rozwiązanie
    int optimalCost = INF;
    std::vector<int> optimalPath;

    // Stos do przechowywania częściowych rozwiązań
    std::stack<NodeState> stack;

    // Inicjalizujemy początkowy stan dla wierzchołka startowego 0
    NodeState initialState = {0, {0}, 0, computeInitLB(num_of_vertices, matrix), std::vector<bool>(num_of_vertices, false)};
    initialState.visited[0] = true;
    stack.push(initialState);

    while (!stack.empty()) {
        NodeState current = stack.top();
        stack.pop();

        // Warunek końcowy jak ścieżka zawiera wszystkie wierzchołki, sprawdzamy cykl hamiltona
        if (current.path.size() == num_of_vertices) {
            // Powrót do startu
            int finalCost = current.pathCost + matrix[current.node][0];
            if (finalCost < optimalCost) {
                optimalCost = finalCost;
                // Ustawiamy optymalną ścieżkę na nową znalezioną i dodajemy powrót do wierzchołka startowego
                optimalPath = current.path;
                optimalPath.push_back(0);
            }
            continue;
        }
        // Sprawdzamy sąsiadujące wierzchołki
        for (int i = num_of_vertices - 1; i >= 0; i--) {
            // Sprawdzamy czy wierzchołek nie był jeszcze odwiedzony i czy istnieje krawędź
            if (!current.visited[i] && matrix[current.node][i] != 0) {
                // Aktualizujemy wartości ścieżki oraz lower bound
                int newPathCost = current.pathCost  + matrix[current.node][i];
                int newLB = current.lower_bound - getSmallestEdge(num_of_vertices, current.node, matrix);

                // Dodajemy potomka tylko wtedy gdy jest obiecujący (inaczej odcinamy)
                if (newLB + newPathCost < optimalCost) {
                    NodeState newState = {i, current.path, newPathCost, newLB, current.visited};
                    newState.path.push_back(i);
                    newState.visited[i] = true;
                    stack.push(newState);
                }
            }
        }
    }

    return {optimalCost, optimalPath};
}

std::pair<int, std::vector<int>> TSP_BxB::TSP_BFS_start(int num_of_vertices, const std::vector<std::vector<int>> &matrix) {
    // Tworzymy zmienne przechowujące obecnie najlepsze rozwiązanie
    int optimalCost = INF;
    std::vector<int> optimalPath;

    // Kolejka do przechowywania częściowych rozwiązań
    std::queue<NodeState> queue;

    // Inicjalizujemy początkowy stan dla wierzchołka startowego 0
    NodeState initialState = {0, {0}, 0, computeInitLB(num_of_vertices, matrix), std::vector<bool>(num_of_vertices, false)};
    initialState.visited[0] = true;
    queue.push(initialState);

    while (!queue.empty()) {
        NodeState current = queue.front();
        queue.pop();

        // Warunek końcowy jak ścieżka zawiera wszystkie wierzchołki, sprawdzamy cykl hamiltona
        if (current.path.size() == num_of_vertices) {
            // Powrót do startu
            int finalCost = current.pathCost + matrix[current.node][0];
            if (finalCost < optimalCost) {
                optimalCost = finalCost;
                // Ustawiamy optymalną ścieżkę na nową znalezioną i dodajemy powrót do wierzchołka startowego
                optimalPath = current.path;
                optimalPath.push_back(0);
            }
            continue;
        }
        // Sprawdzamy sąsiadujące wierzchołki
        for (int i = 0; i < num_of_vertices; i++) {
            // Sprawdzamy czy wierzchołek nie był jeszcze odwiedzony i czy istnieje krawędź
            if (!current.visited[i] && matrix[current.node][i] != 0) {
                // Aktualizujemy wartości ścieżki oraz lower bound
                int newPathCost = current.pathCost  + matrix[current.node][i];
                int newLB = current.lower_bound - getSmallestEdge(num_of_vertices, current.node, matrix);

                // Dodajemy potomka tylko wtedy gdy jest obiecujący (inaczej odcinamy)
                if (newLB + newPathCost < optimalCost) {
                    NodeState newState = {i, current.path, newPathCost, newLB, current.visited};
                    newState.path.push_back(i);
                    newState.visited[i] = true;
                    queue.push(newState);
                }
            }
        }
    }

    return {optimalCost, optimalPath};
}

std::pair<int, std::vector<int>> TSP_BxB::TSP_LOWCOST_start(int num_of_vertices, const std::vector<std::vector<int>> &matrix) {
    // Tworzymy zmienne przechowujące obecnie najlepsze rozwiązanie
    int optimalCost = INF;
    std::vector<int> optimalPath;

    // Stos do przechowywania częściowych rozwiązań
    std::priority_queue<NodeState, std::vector<NodeState>, CompareNodeState> pq;

    // Inicjalizujemy początkowy stan dla wierzchołka startowego 0
    NodeState initialState = {0, {0}, 0, computeInitLB(num_of_vertices, matrix), std::vector<bool>(num_of_vertices, false)};
    initialState.visited[0] = true;
    pq.push(initialState);

    while (!pq.empty()) {
        NodeState current = pq.top();
        pq.pop();

        // Warunek końcowy jak ścieżka zawiera wszystkie wierzchołki, sprawdzamy cykl hamiltona
        if (current.path.size() == num_of_vertices) {
            // Powrót do startu
            int finalCost = current.pathCost + matrix[current.node][0];
            if (finalCost < optimalCost) {
                optimalCost = finalCost;
                // Ustawiamy optymalną ścieżkę na nową znalezioną i dodajemy powrót do wierzchołka startowego
                optimalPath = current.path;
                optimalPath.push_back(0);
            }
            continue;
        }
        // Sprawdzamy sąsiadujące wierzchołki
        for (int i = num_of_vertices - 1; i >= 0; i--) {
            // Sprawdzamy czy wierzchołek nie był jeszcze odwiedzony i czy istnieje krawędź
            if (!current.visited[i] && matrix[current.node][i] != 0) {
                // Aktualizujemy wartości ścieżki oraz lower bound
                int newPathCost = current.pathCost  + matrix[current.node][i];
                int newLB = current.lower_bound - getSmallestEdge(num_of_vertices, current.node, matrix);

                // Dodajemy potomka tylko wtedy gdy jest obiecujący (inaczej odcinamy)
                if (newLB + newPathCost < optimalCost) {
                    NodeState newState = {i, current.path, newPathCost, newLB, current.visited};
                    newState.path.push_back(i);
                    newState.visited[i] = true;
                    pq.push(newState);
                }
            }
        }
    }
    return {optimalCost, optimalPath};
}

int TSP_BxB::computeInitLB(int n, const std::vector<std::vector<int>> &matrix) {
    int lb = 0;
    for (int i = 0; i < n; i++){
        lb += getSmallestEdge(n, i, matrix);
    }
    return lb;
}

int TSP_BxB::getSmallestEdge(int n, int node, const std::vector<std::vector<int>> &matrix) {
    int minEdge = INF;
    for (int j = 0; j < n; j++) {
        if (node != j && matrix[node][j] < minEdge) {
            minEdge = matrix[node][j];
        }
    }
    return minEdge;
}

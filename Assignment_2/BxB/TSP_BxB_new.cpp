#include <unordered_set>
#include <utility>
#include "TSP_BxB_new.h"

Node::Node(int vertex, int lowerBound, Node *parent) {
    this->vertex = vertex;
    this->lowerBound = lowerBound;
    this->parent = parent;
}

Node2::Node2(int vertex, int lowerBound) {
    this->vertex = vertex;
    this->lowerBound = lowerBound;
}

int *TSP_BxB_new::minWeights;
int TSP_BxB_new::startingVertex;
int TSP_BxB_new::graphSize;


// Komparator dla best-first
struct compareNodes {
    bool operator()(const Node *a, const Node *b) const {
        return a->lowerBound > b->lowerBound;
    }
};

std::pair<int, std::vector<int>>
TSP_BxB_new::TSP_BESTFIRST_start(int num_of_vertices, const std::vector<std::vector<int>> &matrix) {
    std::priority_queue<Node *, std::vector<Node *>, compareNodes> pq;
    std::vector<Node *> allNodes;
    std::vector<int> optimalPath;

    startingVertex = 0;

    // Trzeba tu wstawić parametr podawany jako początkowy lb.
    int upperBound = std::numeric_limits<int>::max();
    graphSize = num_of_vertices;
    minWeights = new int[num_of_vertices];

    // Wypełniamy tablice z najmniejszymi krawędziami do obliczania lb
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

    // Tworzymy węzeł początkowy
    Node *root = new Node(startingVertex, lowerBound, nullptr);
    allNodes.push_back(root);
    pq.push(root);

    while (!pq.empty()) {
        Node *node = pq.top();
        pq.pop();

        std::vector<int> availableVertices = getAvailableVertices(node);
        // Sprawdzamy czy złożyliśmy całą ścieżkę
        if (availableVertices.empty()) {

            node->lowerBound = node->lowerBound - minWeights[node->vertex] + matrix[node->vertex][startingVertex];
            if (node->lowerBound < upperBound) {
                upperBound = node->lowerBound;
                optimalPath = getPath(node);
            }
        }

        for (int childVertex : availableVertices) {
            lowerBound = node->lowerBound - minWeights[node->vertex] + matrix[node->vertex][childVertex];

            if (lowerBound < upperBound) {
                Node *child = new Node(childVertex, lowerBound, node);
                allNodes.push_back(child);
                pq.push(child);
            }
        }
    }

    delete[] minWeights;
    for (Node *node : allNodes) {
        delete node;
    }
    return {upperBound, optimalPath};
}

std::vector<int> TSP_BxB_new::getAvailableVertices(Node *node) {
    std::unordered_set<int> availableVertices;
    for (int i = 0; i < graphSize; i++) {
        availableVertices.insert(i);
    }

    while (node != nullptr) {
        availableVertices.erase(node->vertex);
        node = node->parent;
    }

    std::vector<int> orderedVertices(availableVertices.begin(), availableVertices.end());
    std::sort(orderedVertices.begin(), orderedVertices.end());

    return orderedVertices;
}

std::vector<int> TSP_BxB_new::getPath(Node *node) {
    std::vector<int> path;
    while (node != nullptr) {
        path.push_back(node->vertex);
        node = node->parent;
    }

    std::reverse(path.begin(), path.end());
    path.push_back(startingVertex);

    return path;
}

std::pair<int, std::vector<int>>
TSP_BxB_new::TSP_DFS_start(int num_of_vertices, const std::vector<std::vector<int>> &matrix) {
    std::stack<Node *> stack;
    std::vector<Node *> allNodes;
    std::vector<int> optimalPath;

    startingVertex = 0;

    // Trzeba tu wstawić parametr podawany jako początkowy lb.
    int upperBound = std::numeric_limits<int>::max();
    graphSize = num_of_vertices;
    minWeights = new int[num_of_vertices];

    // Wypełniamy tablice z najmniejszymi krawędziami do obliczania lb
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

    // Tworzymy węzeł początkowy
    Node *root = new Node(startingVertex, lowerBound, nullptr);
    allNodes.push_back(root);
    stack.push(root);

    while (!stack.empty()) {
        Node *node = stack.top();
        stack.pop();

        std::vector<int> availableVertices = getAvailableVertices(node);
        // Sprawdzamy czy złożyliśmy całą ścieżkę
        if (availableVertices.empty()) {

            node->lowerBound = node->lowerBound - minWeights[node->vertex] + matrix[node->vertex][startingVertex];
            if (node->lowerBound < upperBound) {
                upperBound = node->lowerBound;
                optimalPath = getPath(node);
            }
        }

        for (int i = availableVertices.size() - 1; i >= 0; i--) {
            int childVertex = availableVertices[i];
            lowerBound = node->lowerBound - minWeights[node->vertex] + matrix[node->vertex][childVertex];

            if (lowerBound < upperBound) {
                Node *child = new Node(childVertex, lowerBound, node);
                allNodes.push_back(child);
                stack.push(child);
            }
        }
    }

    delete[] minWeights;
    for (Node *node : allNodes) {
        delete node;
    }
    return {upperBound, optimalPath};
}

std::pair<int, std::vector<int>>
TSP_BxB_new::TSP_BFS_start(int num_of_vertices, const std::vector<std::vector<int>> &matrix) {

    std::queue<Node *> queue;
    std::vector<Node *> allNodes;
    std::vector<int> optimalPath;

    startingVertex = 0;

    // Trzeba tu wstawić parametr podawany jako początkowy lb.
    int upperBound = std::numeric_limits<int>::max();
    graphSize = num_of_vertices;
    minWeights = new int[num_of_vertices];

    // Wypełniamy tablice z najmniejszymi krawędziami do obliczania lb
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

    // Tworzymy węzeł początkowy
    Node *root = new Node(startingVertex, lowerBound, nullptr);
    allNodes.push_back(root);
    queue.push(root);

    while (!queue.empty()) {
        Node *node = queue.front();
        queue.pop();

        std::vector<int> availableVertices = getAvailableVertices(node);
        // Sprawdzamy czy złożyliśmy całą ścieżkę
        if (availableVertices.empty()) {

            node->lowerBound = node->lowerBound - minWeights[node->vertex] + matrix[node->vertex][startingVertex];
            if (node->lowerBound < upperBound) {
                upperBound = node->lowerBound;
                optimalPath = getPath(node);
            }
        }

        for (int childVertex : availableVertices) {
            lowerBound = node->lowerBound - minWeights[node->vertex] + matrix[node->vertex][childVertex];

            if (lowerBound < upperBound) {
                Node *child = new Node(childVertex, lowerBound, node);
                allNodes.push_back(child);
                queue.push(child);
            }
        }
    }

    delete[] minWeights;
    for (Node *node : allNodes) {
        delete node;
    }
    return {upperBound, optimalPath};;
}

std::pair<int, std::vector<int>>
TSP_BxB_new::new_TSP_BFS_start(int num_of_vertices, const std::vector<std::vector<int>> &matrix, int initialUpperbound) {

    startingVertex = 0;
    std::queue<Node2 *> queue;
    std::vector<short> bestPath = {0};

    int upperBound;

    if (initialUpperbound > 0) {
        upperBound = initialUpperbound;
    } else {
        upperBound = std::numeric_limits<int>::max();
    }

    graphSize = num_of_vertices;
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
    short rootVertex = startingVertex;

    Node2 *root = new Node2(startingVertex, lowerBound);
    root->current_path = {rootVertex};
    queue.push(root);

    while (!queue.empty()) {
        Node2 *node = queue.front();
        queue.pop();

        std::vector<short> verticesToVisit = getVerticesToVisit(node);
        if (verticesToVisit.empty()) {

            node->lowerBound = node->lowerBound - minWeights[node->vertex] + matrix[node->vertex][startingVertex];
            if (node->lowerBound < upperBound) {
                upperBound = node->lowerBound;
                bestPath = node->current_path;
                bestPath.push_back(startingVertex);
            }
        }

        for (short childVertex : verticesToVisit) {
            lowerBound = node->lowerBound - minWeights[node->vertex] + matrix[node->vertex][childVertex];

            if (lowerBound < upperBound) {
                Node2 *child = new Node2(childVertex, lowerBound);
                child->current_path = std::vector<short>(node->current_path);
                child->current_path.push_back(childVertex);
                queue.push(child);
            }
        }
        delete node;
    }

    delete[] minWeights;

    // Create the result vector of type int
    std::vector<int> optimalPath;

    // Copy the elements from orderedVertices (short) to result (int)
    optimalPath.reserve(bestPath.size());
    optimalPath.insert(optimalPath.end(), bestPath.begin(), bestPath.end());

    return {upperBound, optimalPath};
}

std::vector<short> TSP_BxB_new::getVerticesToVisit(Node2 *node) {
    std::unordered_set<int> verticesToVisit;
    for (int i = 0; i < graphSize; i++) {
        verticesToVisit.insert(i);
    }

    for (int vertex : node->current_path) {
        verticesToVisit.erase(vertex);
    }

    std::vector<short> orderedVertices(verticesToVisit.begin(), verticesToVisit.end());
    std::sort(orderedVertices.begin(), orderedVertices.end());

    return orderedVertices;
}

std::pair<int, std::vector<int>>
TSP_BxB_new::new_TSP_DFS_start(int num_of_vertices, const std::vector<std::vector<int>> &matrix, int initialUpperbound) {

    startingVertex = 0;
    std::stack<Node2 *> stack;
    std::vector<short> bestPath = {0};


    int upperBound;
    if (initialUpperbound > 0) {
        upperBound = initialUpperbound;
    } else {
        upperBound = std::numeric_limits<int>::max();
    }

    graphSize = num_of_vertices;
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
    short rootVertex = startingVertex;

    Node2 *root = new Node2(startingVertex, lowerBound);
    root->current_path = {rootVertex};
    stack.push(root);

    while (!stack.empty()) {
        Node2 *node = stack.top();
        stack.pop();

        std::vector<short> verticesToVisit = getVerticesToVisit(node);
        if (verticesToVisit.empty()) {

            node->lowerBound = node->lowerBound - minWeights[node->vertex] + matrix[node->vertex][startingVertex];
            if (node->lowerBound < upperBound) {
                upperBound = node->lowerBound;
                bestPath = node->current_path;
                bestPath.push_back(startingVertex);
            }
        }

        for (int i = verticesToVisit.size() - 1; i >= 0; i--) {
            short childVertex = verticesToVisit[i];
            lowerBound = node->lowerBound - minWeights[node->vertex] + matrix[node->vertex][childVertex];

            if (lowerBound < upperBound) {
                Node2 *child = new Node2(childVertex, lowerBound);
                child->current_path = std::vector<short>(node->current_path);
                child->current_path.push_back(childVertex);
                stack.push(child);
            }
        }
        delete node;
    }

    delete[] minWeights;

    // Create the result vector of type int
    std::vector<int> optimalPath;

    // Copy the elements from orderedVertices (short) to result (int)
    optimalPath.reserve(bestPath.size());
    optimalPath.insert(optimalPath.end(), bestPath.begin(), bestPath.end());

    return {upperBound, optimalPath};
}

struct compareNodes2 {
    bool operator()(const Node2 *a, const Node2 *b) const {
        return a->lowerBound > b->lowerBound;
    }
};

std::pair<int, std::vector<int>>
TSP_BxB_new::new_TSP_BESTFIRST_start(int num_of_vertices, const std::vector<std::vector<int>> &matrix, int initialUpperbound) {

    startingVertex = 0;
    std::priority_queue<Node2 *, std::vector<Node2 *>, compareNodes2> pq;
    std::vector<short> bestPath = {0};

    int upperBound;
    if (initialUpperbound > 0) {
        upperBound = initialUpperbound;
    } else {
        upperBound = std::numeric_limits<int>::max();
    }

    graphSize = num_of_vertices;
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
    short rootVertex = startingVertex;

    Node2 *root = new Node2(startingVertex, lowerBound);
    root->current_path = {rootVertex};
    pq.push(root);

    while (!pq.empty()) {
        Node2 *node = pq.top();
        pq.pop();

        std::vector<short> verticesToVisit = getVerticesToVisit(node);
        if (verticesToVisit.empty()) {

            node->lowerBound = node->lowerBound - minWeights[node->vertex] + matrix[node->vertex][startingVertex];
            if (node->lowerBound < upperBound) {
                upperBound = node->lowerBound;
                bestPath = node->current_path;
                bestPath.push_back(startingVertex);
            }
        }

        for (short childVertex : verticesToVisit) {
            lowerBound = node->lowerBound - minWeights[node->vertex] + matrix[node->vertex][childVertex];

            if (lowerBound < upperBound) {
                Node2 *child = new Node2(childVertex, lowerBound);
                child->current_path = std::vector<short>(node->current_path);
                child->current_path.push_back(childVertex);
                pq.push(child);
            }
        }
        delete node;
    }

    delete[] minWeights;

    // Create the result vector of type int
    std::vector<int> optimalPath;

    // Copy the elements from orderedVertices (short) to result (int)
    optimalPath.reserve(bestPath.size());
    optimalPath.insert(optimalPath.end(), bestPath.begin(), bestPath.end());

    return {upperBound, optimalPath};
}



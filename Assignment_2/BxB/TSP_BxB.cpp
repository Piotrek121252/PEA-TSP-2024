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
TSP_BxB::new_TSP_BFS_start(int num_of_vertices, const std::vector<std::vector<int>> &matrix, int initialUpperbound) {

    startingVertex = 0;
    std::queue<Node *> queue;
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

    Node *root = new Node(startingVertex, lowerBound);
    root->current_path = {rootVertex};
    queue.push(root);

    while (!queue.empty()) {
        Node *node = queue.front();
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
                Node *child = new Node(childVertex, lowerBound);
                child->current_path = std::vector<short>(node->current_path);
                child->current_path.push_back(childVertex);
                queue.push(child);
            }
        }
        delete node;
    }

    delete[] minWeights;


    std::vector<int> optimalPath;

    optimalPath.reserve(bestPath.size());
    optimalPath.insert(optimalPath.end(), bestPath.begin(), bestPath.end());

    return {upperBound, optimalPath};
}

std::vector<short> TSP_BxB::getVerticesToVisit(Node *node) {
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
TSP_BxB::new_TSP_DFS_start(int num_of_vertices, const std::vector<std::vector<int>> &matrix, int initialUpperbound) {

    startingVertex = 0;
    std::stack<Node *> stack;
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

    Node *root = new Node(startingVertex, lowerBound);
    root->current_path = {rootVertex};
    stack.push(root);

    while (!stack.empty()) {
        Node *node = stack.top();
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
                Node *child = new Node(childVertex, lowerBound);
                child->current_path = std::vector<short>(node->current_path);
                child->current_path.push_back(childVertex);
                stack.push(child);
            }
        }
        delete node;
    }

    delete[] minWeights;

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
TSP_BxB::new_TSP_BESTFIRST_start(int num_of_vertices, const std::vector<std::vector<int>> &matrix, int initialUpperbound) {

    startingVertex = 0;
    std::priority_queue<Node *, std::vector<Node *>, compareNodes2> pq;
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

    Node *root = new Node(startingVertex, lowerBound);
    root->current_path = {rootVertex};
    pq.push(root);

    while (!pq.empty()) {
        Node *node = pq.top();
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
                Node *child = new Node(childVertex, lowerBound);
                child->current_path = std::vector<short>(node->current_path);
                child->current_path.push_back(childVertex);
                pq.push(child);
            }
        }
        delete node;
    }

    delete[] minWeights;

    std::vector<int> optimalPath;

    optimalPath.reserve(bestPath.size());
    optimalPath.insert(optimalPath.end(), bestPath.begin(), bestPath.end());

    return {upperBound, optimalPath};
}



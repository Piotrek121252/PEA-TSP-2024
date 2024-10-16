#pragma once
#include <vector>
#include <string>

class GraphReader {
public:
    static std::pair<int, std::vector<std::vector<int>>> readGraph(const std::string& filename);
};
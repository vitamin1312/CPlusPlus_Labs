#include "Graph.h"


std::stack<int> Graph::topologicalSort()
{
    std::vector<int> graphNumeration;
    std::unordered_set<int> visited;
    int N = adjacentVertixes.size();

    std::stack<int> Stack;

    for (auto& [v, neighbours] : adjacentVertixes)
    {
        if (visited.find(v) == visited.end())
            topologicalSortUtil(v, visited, Stack);
    }

    return Stack;
}


void Graph::setNewState(std::unordered_map<int, std::vector<int>> edges)
{
    vertexesInEdge = edges;

    adjacentVertixes.clear();
    for (auto& [edge, vertexes] : vertexesInEdge)
    {
        adjacentVertixes[vertexes[0]].insert(vertexes[1]);
    }
}

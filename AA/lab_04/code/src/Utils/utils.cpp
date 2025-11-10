#include "utils.hpp"
#include <limits>

vector<vector<uint>> graph_to_adjecencyMatrix(const graph &g)
{
    size_t n = g.vertices.size();

    uint INF = numeric_limits<uint>::max();
    vector<vector<uint>> adjMatrix(n, vector<uint>(n, INF));

    for (size_t i = 0; i < n; ++i)
    {
        adjMatrix[i][i] = 0;
    }

    for (const auto &e : g.edges)
    {
        adjMatrix[e->from->index][e->to->index] = e->value;
    }

    return adjMatrix;
}
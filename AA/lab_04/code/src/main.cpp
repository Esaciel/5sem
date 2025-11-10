#include "definitions.hpp"
#include "io.hpp"
#include "measurements.hpp"
#include "solution.hpp"
#include "utils.hpp"

int main()
{
    graph g;
    parse_graphviz(g);
    print_graphviz(g);
    auto adj = graph_to_adjecencyMatrix(g);
    print_adjMatrix(adj);
    auto seq = floyd_warshall_sequential(adj, 10);
    print_pairs(seq, g);
    auto par = floyd_warshall_parallel(adj, 10, 8);
    print_pairs(par, g);
    return 0;
}
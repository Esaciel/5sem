#pragma once

#include "definitions.hpp"
#include <iostream>
void parse_graphviz(graph &g, istream &in = cin);
void print_graphviz(const graph &g, ostream &out = cout);
void print_pairs(const vector<Pair> &vec, const graph &g, ostream &out = cout);
void print_adjMatrix(const vector<vector<uint>> &adj, ostream &out = cout);
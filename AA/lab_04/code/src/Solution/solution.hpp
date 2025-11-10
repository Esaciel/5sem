#pragma once

#include "definitions.hpp"

vector<Pair> floyd_warshall_sequential(const vector<vector<uint>> &adj, double max_distance);
vector<Pair> floyd_warshall_parallel(vector<vector<uint>> &adj, double max_dist, size_t thread_count);
#pragma once

#include "definitions.hpp"

vector<Pair>
find_pairs_within_range__sequential(const vector<vector<uint>> &adj,
                                    double max_distance);
vector<Pair> find_pairs_within_range__parallel(vector<vector<uint>> &adj,
                                               double max_dist,
                                               size_t thread_count);
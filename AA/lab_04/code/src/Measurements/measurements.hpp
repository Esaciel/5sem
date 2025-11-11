#pragma once
#include "definitions.hpp"

double measure(vector<vector<uint>> adj, double max_gap, uint threads_num,
               size_t itercount);
#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
using uint = unsigned int;
using Pair = pair<uint, uint>;

struct edge;
struct vertex;
struct graph;

struct edge {
  uint value;
  shared_ptr<vertex> from, to;
};

struct vertex {
  uint index;
  string label;
  vector<shared_ptr<edge>> incoming, outcoming;
};

struct graph {
  unordered_map<uint, shared_ptr<vertex>> vertices;
  vector<shared_ptr<edge>> edges;
};
#include "io.hpp"
#include <limits>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>

shared_ptr<vertex>
find_or_create_vertex(unordered_map<string, shared_ptr<vertex>> &vmap,
                      const string &label, uint &index) {
  auto it = vmap.find(label);
  if (it != vmap.end())
    return it->second;
  auto v = make_shared<vertex>();
  v->label = label;
  v->index = index++;
  vmap[label] = v;
  return v;
}

void parse_graphviz(graph &g, istream &in) {
  unordered_map<string, shared_ptr<vertex>> vmap;
  string line;
  regex edge_regex(
      R"(^\s*([\w.-]+)\s*->\s*([\w.-]+)\s*\[\s*label\s*=\s*(\d+)\s*\]\s*;?\s*$)");
  smatch match;
  uint vertex_index = 0;

  while (getline(in, line) && line.length() > 1) {
    if (regex_match(line, match, edge_regex)) {
      string from_label = match[1].str();
      string to_label = match[2].str();
      uint value = static_cast<uint>(stoi(match[3]));

      auto from_v = find_or_create_vertex(vmap, from_label, vertex_index);
      auto to_v = find_or_create_vertex(vmap, to_label, vertex_index);

      auto e = make_shared<edge>();
      e->value = value;
      e->from = from_v;
      e->to = to_v;

      from_v->outcoming.push_back(e);
      to_v->incoming.push_back(e);

      g.edges.push_back(e);
    }
  }

  for (auto &kv : vmap) {
    g.vertices[kv.second->index] = kv.second;
  }
}

void print_graphviz(const graph &g, ostream &out) {
  out << "digraph G {\n";
  for (const auto &e : g.edges) {
    if (e->from && e->to) {
      out << "    " << e->from->label << " -> " << e->to->label << " [label=<"
          << e->value << ">];\n";
    }
  }
  out << "}\n";
}

void print_pairs(const vector<Pair> &vec, const graph &g, ostream &out) {
  out << "[";
  bool f = false;
  for (const auto &p : vec) {
    if (f)
      out << ",";
    out << "[" << g.vertices.find(p.first)->second->label << ","
        << g.vertices.find(p.second)->second->label << "]";
    f = true;
  }
  out << "]" << endl;
}

void print_adjMatrix(const vector<vector<uint>> &adj, const graph &g,
                     ostream &out) {
  out << "\t";
  for (size_t i = 0; i < g.vertices.size(); ++i) {
    out << g.vertices.find(static_cast<uint>(i))->second->label << "\t";
  }
  out << "\n";
  int i = 0;
  for (const auto &row : adj) {
    out << g.vertices.find(i++)->second->label << "\t";
    for (const auto &val : row) {
      if (val != numeric_limits<uint>::infinity())
        out << val << '\t';
      else
        out << "x" << '\t';
    }
    out << '\n';
  }
}
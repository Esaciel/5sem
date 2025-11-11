#include "utils.hpp"
#include <limits>

#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>

void timestamp(const char *msg) {
  stringstream ss;
  ss << this_thread::get_id();
  string thread_id_str = ss.str();

  string filename = "out_" + thread_id_str;

  auto now = chrono::system_clock::now();
  auto now_ns = chrono::time_point_cast<chrono::nanoseconds>(now);
  auto epoch = now_ns.time_since_epoch();
  auto value = epoch.count();

  ofstream outfile(filename, ios::app);
  if (!outfile) {
    cerr << "Ошибка открытия файла\n";
    return;
  }

  time_t tt = chrono::system_clock::to_time_t(now);
  tm tm = *localtime(&tt);

  outfile << put_time(&tm, "%T");
  outfile << "." << setfill('0') << setw(9) << (value % 1000000000);
  outfile << "\t\t\t\t" << msg << endl;
}

vector<vector<uint>> graph_to_adjecencyMatrix(const graph &g) {
  size_t n = g.vertices.size();

  uint INF = numeric_limits<uint>::infinity();
  vector<vector<uint>> adjMatrix(n, vector<uint>(n, INF));

  for (size_t i = 0; i < n; ++i) {
    adjMatrix[i][i] = 0;
  }

  for (const auto &e : g.edges) {
    adjMatrix[e->from->index][e->to->index] = e->value;
  }

  return adjMatrix;
}
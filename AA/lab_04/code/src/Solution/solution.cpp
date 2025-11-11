#include "solution.hpp"
#include "threadpool.hpp"
#include <cmath>
#include <limits>

using namespace std;

vector<Pair>
find_pairs_within_range__sequential(const vector<vector<uint>> &adj,
                                    double max_distance) {
  size_t n = adj.size();
  double INF = numeric_limits<double>::infinity();
  vector<vector<double>> dist(n, vector<double>(n, INF));
  for (size_t i = 0; i < n; ++i) {
    dist[i][i] = 0;
    for (size_t j = 0; j < n; ++j) {
      if (adj[i][j] == numeric_limits<uint>::infinity())
        continue;
      if (adj[i][j] > 0)
        dist[i][j] = static_cast<double>(adj[i][j]);
    }
  }
  for (size_t k = 0; k < n; ++k) {
    for (size_t i = 0; i < n; ++i) {
      for (size_t j = 0; j < n; ++j) {
        double new_dist = dist[i][k] + dist[k][j];
        if (new_dist < dist[i][j]) {
          dist[i][j] = new_dist;
        }
      }
    }
  }

  vector<Pair> pairs;
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      if (i != j && dist[i][j] <= max_distance)
        pairs.emplace_back(i, j);
    }
  }
  return pairs;
}

void floyd_warshall_block(vector<vector<double>> &dist, int blockSize,
                          int blockRow, int blockCol, int kBlock, int n) {
  int rowStart = blockRow * blockSize;
  int colStart = blockCol * blockSize;
  int kStart = kBlock * blockSize;

  int rowEnd = min(rowStart + blockSize, n);
  int colEnd = min(colStart + blockSize, n);
  int kEnd = min(kStart + blockSize, n);

  for (int k = kStart; k < kEnd; ++k)
    for (int i = rowStart; i < rowEnd; ++i)
      for (int j = colStart; j < colEnd; ++j)
        if (dist[i][k] + dist[k][j] < dist[i][j])
          dist[i][j] = dist[i][k] + dist[k][j];
}

vector<Pair> find_pairs_within_range__parallel(vector<vector<uint>> &adj,
                                               double max_dist,
                                               size_t thread_count) {
  size_t n = adj.size();
  int blockSize = static_cast<double>(n) / sqrt(thread_count);
  blockSize = max(blockSize, 1);
  int numBlocks = (static_cast<int>(n) + blockSize - 1) / blockSize;
  const double INF = numeric_limits<double>::infinity();
  vector<vector<double>> dist(n, vector<double>(n, INF));
  for (size_t i = 0; i < n; ++i) {
    dist[i][i] = 0;
    for (size_t j = 0; j < n; ++j) {
      if (adj[i][j] == numeric_limits<uint>::infinity())
        continue;
      if (adj[i][j] > 0)
        dist[i][j] = static_cast<double>(adj[i][j]);
    }
  }

  ThreadPool pool(thread_count);

  for (int kBlock = 0; kBlock < numBlocks; ++kBlock) {
    floyd_warshall_block(dist, blockSize, kBlock, kBlock, kBlock, n);

    for (int jBlock = 0; jBlock < numBlocks; ++jBlock) {
      if (jBlock != kBlock) {
        pool.enqueue([&, kBlock, jBlock, n, blockSize]() {
          floyd_warshall_block(dist, blockSize, kBlock, jBlock, kBlock, n);
        });
      }
    }

    for (int iBlock = 0; iBlock < numBlocks; ++iBlock) {
      if (iBlock != kBlock) {
        pool.enqueue([&, kBlock, iBlock, n, blockSize]() {
          floyd_warshall_block(dist, blockSize, iBlock, kBlock, kBlock, n);
        });
      }
    }
    pool.wait_done();
    for (int iBlock = 0; iBlock < numBlocks; ++iBlock) {
      if (iBlock == kBlock)
        continue;
      for (int jBlock = 0; jBlock < numBlocks; ++jBlock) {
        if (jBlock == kBlock)
          continue;
        pool.enqueue([&, iBlock, jBlock, kBlock, n, blockSize]() {
          floyd_warshall_block(dist, blockSize, iBlock, jBlock, kBlock, n);
        });
      }
    }
    pool.wait_done();
  }

  vector<Pair> result;
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      if (i != j && dist[i][j] <= max_dist) {
        result.emplace_back(i, j);
      }
    }
  }

  return result;
}
#include "io.hpp"
#include "solution.hpp"
#include "utils.hpp"
#include <fstream>
#include <gtest/gtest.h>
#include <sstream>

class GraphTest : public ::testing::Test {
protected:
  uint INF = numeric_limits<uint>::infinity();
  const char *digraph = "digraph G {"
                        "\n    3 -> 0 [label=3];"
                        "\n    0 -> 1 [label=5];"
                        "\n    4 -> 1 [label=10];"
                        "\n    2 -> 1 [label=1];"
                        "\n    2 -> 3 [label=8];"
                        "\n    0 -> 3 [label=3];"
                        "\n    2 -> 0 [label=1];"
                        "\n    3 -> 2 [label=8];"
                        "\n    1 -> 3 [label=6];"
                        "\n    0 -> 4 [label=6];"
                        "\n    1 -> 0 [label=6];"
                        "\n    4 -> 2 [label=5];"
                        "\n    0 -> 2 [label=3];"
                        "\n    3 -> 4 [label=4];"
                        "\n    3 -> 1 [label=6];"
                        "\n    2 -> 4 [label=2];"
                        "\n    1 -> 2 [label=2];"
                        "\n    4 -> 3 [label=6];"
                        "\n}";
  graph g;
  vector<vector<uint>> adj;
  void SetUp() override {
    istringstream fin(digraph);
    parse_graphviz(g, fin);
    adj = graph_to_adjecencyMatrix(g);
  }
};

TEST_F(GraphTest, ParseGraphviz) {
  ASSERT_TRUE(g.vertices.size() == 5);
  ASSERT_TRUE(g.edges.size() == 18);
}

TEST_F(GraphTest, AdjacencyMatrixCorrect) {
  std::vector<uint> r1 = {INF, 3, 6, 4, 8};
  std::vector<uint> r2 = {3, INF, 5, 6, 3};
  std::vector<uint> r3 = {6, 6, INF, INF, 2};
  std::vector<uint> r4 = {6, INF, 10, INF, 5};
  std::vector<uint> r5 = {8, 1, 1, 2, INF};

  ASSERT_EQ(adj.size(), 5);

  ASSERT_EQ(adj[0].size(), r1.size());
  EXPECT_EQ(adj[0], r1);

  ASSERT_EQ(adj[1].size(), r2.size());
  EXPECT_EQ(adj[1], r2);

  ASSERT_EQ(adj[2].size(), r3.size());
  EXPECT_EQ(adj[2], r3);

  ASSERT_EQ(adj[3].size(), r4.size());
  EXPECT_EQ(adj[3], r4);

  ASSERT_EQ(adj[4].size(), r5.size());
  EXPECT_EQ(adj[4], r5);
}

TEST_F(GraphTest, FindPairsWithinRangeSequential) {
  double max_dist = 2.0;
  auto pairs = find_pairs_within_range__sequential(adj, max_dist);
  vector<Pair> expect = {{1, 2}, {2, 0}, {2, 1}, {2, 4}};
  vector<Pair> realpairs;
  for (const auto &p : pairs) {
    Pair tmp = {stoi(g.vertices.find(p.first)->second->label),
                stoi(g.vertices.find(p.second)->second->label)};
    realpairs.push_back(tmp);
  }
  ASSERT_FALSE(realpairs.empty());
  std::sort(realpairs.begin(), realpairs.end());
  std::sort(expect.begin(), expect.end());
  EXPECT_EQ(realpairs, expect);
}

TEST_F(GraphTest, FindPairsWithinRangeParallelMatchSequential) {
  double max_dist = 2.0;
  auto pairs = find_pairs_within_range__parallel(adj, max_dist, 16);
  vector<Pair> expect = {{1, 2}, {2, 0}, {2, 1}, {2, 4}};
  vector<Pair> realpairs;
  for (const auto &p : pairs) {
    Pair tmp = {stoi(g.vertices.find(p.first)->second->label),
                stoi(g.vertices.find(p.second)->second->label)};
    realpairs.push_back(tmp);
  }
  ASSERT_FALSE(realpairs.empty());
  std::sort(realpairs.begin(), realpairs.end());
  std::sort(expect.begin(), expect.end());
  EXPECT_EQ(realpairs, expect);
}

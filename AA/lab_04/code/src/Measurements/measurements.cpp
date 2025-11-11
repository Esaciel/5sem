#include "measurements.hpp"
#include "solution.hpp"
#include "utils.hpp"
#include <chrono>

auto seq_wrap(vector<vector<uint>> adj, double max_gap, uint threads_num) {
  (void)threads_num;
  auto start_time = chrono::high_resolution_clock::now();
  find_pairs_within_range__sequential(adj, max_gap);
  auto end_time = chrono::high_resolution_clock::now();
  return chrono::duration_cast<chrono::nanoseconds>(end_time - start_time)
      .count();
}

auto par_wrap(vector<vector<uint>> adj, double max_gap, uint threads_num) {
  auto start_time = chrono::high_resolution_clock::now();
  find_pairs_within_range__parallel(adj, max_gap, threads_num);
  auto end_time = chrono::high_resolution_clock::now();
  return chrono::duration_cast<chrono::nanoseconds>(end_time - start_time)
      .count();
}

double measure(vector<vector<uint>> adj, double max_gap, uint threads_num,
               size_t itercount) {
  if (itercount <= 0)
    throw invalid_argument("Число итераций должно быть положительным");
  auto func = seq_wrap;
  if (threads_num != 0) {
    func = par_wrap;
  }
  std::chrono::_V2::system_clock::rep summary_time{};
  for (size_t i = 0; i < itercount; ++i) {
    summary_time += func(adj, max_gap, threads_num);
  }
  double average_nanos = static_cast<double>(summary_time) / itercount;
  double seconds = average_nanos / 1e9; // наносекунды в секунды
  return seconds;
}
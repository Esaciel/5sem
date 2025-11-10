#include "measurements.hpp"

#include "measurements.hpp"
#include "solution.hpp"
#include <ctime>

clock_t seq_wrap(vector<vector<uint>> adj, double max_gap, uint threads_num)
{
    (void)threads_num;
    clock_t time;
    time = clock();
    find_pairs_within_range__sequential(adj, max_gap);
    time = clock() - time;
    return time;
}

clock_t par_wrap(vector<vector<uint>> adj, double max_gap, uint threads_num)
{
    clock_t time;
    time = clock();
    find_pairs_within_range__parallel(adj, max_gap, threads_num);
    time = clock() - time;
    return time;
}

double measure(vector<vector<uint>> adj, double max_gap, uint threads_num, size_t itercount)
{
    if (itercount <= 0)
        throw std::invalid_argument("Число итераций должно быть положительным");
    auto func = seq_wrap;
    if (threads_num)
    {
        func = par_wrap;
    }
    clock_t summary_time{};
    for (size_t i = 0; i < itercount; ++i)
    {
        summary_time += func(adj, max_gap, threads_num);
    }
    return static_cast<double>(summary_time) / (itercount * CLOCKS_PER_SEC);
}
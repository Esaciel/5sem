#include "solution.hpp"
#include "threadpool.hpp"
#include <limits>

using namespace std;

vector<Pair> find_pairs_within_range__sequential(const vector<vector<uint>> &adj, double max_distance)
{
    size_t n = adj.size();
    double INF = numeric_limits<double>::max();
    vector<vector<double>> dist(n, vector<double>(n, INF));

    for (size_t i = 0; i < n; ++i)
    {
        dist[i][i] = 0;
        for (size_t j = 0; j < n; ++j)
        {
            if (adj[i][j] > 0)
                dist[i][j] = static_cast<double>(adj[i][j]);
        }
    }

    for (size_t k = 0; k < n; ++k)
    {
        for (size_t i = 0; i < n; ++i)
        {
            if (dist[i][k] == INF)
                continue;
            for (size_t j = 0; j < n; ++j)
            {
                if (dist[k][j] == INF)
                    continue;
                double new_dist = dist[i][k] + dist[k][j];
                if (new_dist < dist[i][j])
                {
                    dist[i][j] = new_dist;
                }
            }
        }
    }

    vector<Pair> pairs;
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            if (i != j && dist[i][j] <= max_distance)
                pairs.emplace_back(i, j);
        }
    }
    return pairs;
}

void floyd_warshall_worker(size_t start, size_t end, size_t k, size_t n, vector<vector<double>> &dist)
{
    const double INF = numeric_limits<double>::max();
    for (size_t i = start; i < end; ++i)
    {
        if (dist[i][k] == INF)
            continue;
        for (size_t j = 0; j < n; ++j)
        {
            if (dist[k][j] == INF)
                continue;
            double new_dist = dist[i][k] + dist[k][j];
            if (new_dist < dist[i][j])
            {
                dist[i][j] = new_dist;
            }
        }
    }
}

vector<Pair> find_pairs_within_range__parallel(vector<vector<uint>> &adj, double max_dist, size_t thread_count)
{
    size_t n = adj.size();
    const double INF = numeric_limits<double>::max();
    vector<vector<double>> dist(n, vector<double>(n, INF));

    for (size_t i = 0; i < n; ++i)
    {
        dist[i][i] = 0;
        for (size_t j = 0; j < n; ++j)
        {
            if (adj[i][j] > 0)
                dist[i][j] = static_cast<double>(adj[i][j]);
        }
    }

    ThreadPool pool(thread_count);

    for (size_t k = 0; k < n; ++k)
    {
        size_t chunk_size = (n + thread_count - 1) / thread_count;
        for (size_t t = 0; t < thread_count; ++t)
        {
            size_t start = t * chunk_size;
            size_t end = min(n, start + chunk_size);
            pool.enqueue([start, end, k, n, &dist]() { floyd_warshall_worker(start, end, k, n, dist); });
        }
        pool.wait_done();
    }

    vector<Pair> result;
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            if (i != j && dist[i][j] <= max_dist)
            {
                result.emplace_back(i, j);
            }
        }
    }

    return result;
}

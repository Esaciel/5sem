#pragma once

#include "definitions.hpp"

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>

class ThreadPool
{
  public:
    ThreadPool(size_t thread_count);
    ~ThreadPool();
    void enqueue(function<void()> task);
    void wait_done();

  private:
    vector<jthread> workers;
    queue<function<void()>> tasks;
    std::mutex m;
    condition_variable_any cv;
    condition_variable done_cv;
    size_t pending_tasks = 0;
    void worker_thread(stop_token stoken);
};
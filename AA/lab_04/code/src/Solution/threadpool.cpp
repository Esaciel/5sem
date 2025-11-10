#include "threadpool.hpp"

ThreadPool::ThreadPool(size_t thread_count)
{
    for (size_t i = 0; i < thread_count; ++i)
    {
        workers.emplace_back([this](stop_token stoken) { worker_thread(stoken); });
    }
}

ThreadPool::~ThreadPool()
{
    for (auto &worker : workers)
    {
        worker.request_stop();
    }

    {
        std::unique_lock lock(m);
        cv.notify_all();
    }
}

void ThreadPool::enqueue(function<void()> task)
{
    {
        unique_lock lock(m);
        tasks.emplace(move(task));
        ++pending_tasks;
    }
    cv.notify_one();
}

void ThreadPool::wait_done()
{
    unique_lock lock(m);
    done_cv.wait(lock, [this]() { return pending_tasks == 0; });
}

void ThreadPool::worker_thread(stop_token stoken)
{
    while (!stoken.stop_requested())
    {
        function<void()> task;
        {
            unique_lock lock(m);
            cv.wait(lock, stoken, [this, &stoken] { return stoken.stop_requested() || !tasks.empty(); });

            if (stoken.stop_requested() && tasks.empty())
                break;

            if (!tasks.empty())
            {
                task = move(tasks.front());
                tasks.pop();
            }
            else
            {
                continue;
            }
        }

        task();

        {
            unique_lock lock(m);
            --pending_tasks;
            if (pending_tasks == 0)
            {
                done_cv.notify_all();
            }
        }
    }
}
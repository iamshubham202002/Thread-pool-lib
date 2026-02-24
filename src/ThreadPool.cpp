#include "thread_pool/ThreadPool.hpp"

namespace thread_pool {

ThreadPool::ThreadPool(size_t thread_count, size_t max_tasks)
    : stop_(false), max_tasks_(max_tasks)
{
    for (size_t i = 0; i < thread_count; ++i) {
        workers_.emplace_back(&ThreadPool::worker_loop, this);
    }
}

void ThreadPool::worker_loop() {
    while (true) {
        std::function<void()> task;

        {
            std::unique_lock<std::mutex> lock(mutex_);

            cv_task_.wait(lock, [this] {
                return stop_ || !tasks_.empty();
            });

            if (stop_ && tasks_.empty())
                return;

            task = std::move(tasks_.front());
            tasks_.pop();
        }

        cv_space_.notify_one();
        task();
    }
}

void ThreadPool::shutdown() {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        stop_ = true;
    }

    cv_task_.notify_all();
    cv_space_.notify_all();

    for (auto& worker : workers_) {
        if (worker.joinable())
            worker.join();
    }
}

ThreadPool::~ThreadPool() {
    shutdown();
}

} 

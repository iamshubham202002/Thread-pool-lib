#pragma once

#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>
#include <future>
#include <stdexcept>

namespace thread_pool {

class ThreadPool {
public:
    explicit ThreadPool(size_t thread_count,
                        size_t max_tasks = 1024);

    ~ThreadPool();

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    template <typename F>
    auto enqueue(F&& f) -> std::future<decltype(f())>;
    void shutdown();

private:
    void worker_loop();

    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> tasks_;

    std::mutex mutex_;
    std::condition_variable cv_task_;
    std::condition_variable cv_space_;

    std::atomic<bool> stop_;
    size_t max_tasks_;
};

template <typename F>
auto ThreadPool::enqueue(F&& f) -> std::future<decltype(f())>
{
    using return_type = decltype(f());

    auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::forward<F>(f)
    );

    std::future<return_type> result = task->get_future();

    {
        std::unique_lock<std::mutex> lock(mutex_);

        cv_space_.wait(lock, [this] {
            return tasks_.size() < max_tasks_ || stop_;
        });

        if (stop_)
            throw std::runtime_error("enqueue on stopped ThreadPool");

        tasks_.emplace([task]() { (*task)(); });
    }

    cv_task_.notify_one();
    return result;
}

} 

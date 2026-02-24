#include <iostream>
#include <thread>
#include <vector>
#include "thread_pool/ThreadPool.hpp"

int main() {
    thread_pool::ThreadPool pool(4, 5);

    std::vector<std::future<int>> results;

    for (int i = 0; i < 10; ++i) {
        results.emplace_back(
            pool.enqueue([i]() {
                std::this_thread::sleep_for(
                    std::chrono::milliseconds(200)
                );
                std::cout << "Task " << i
                          << " executed by thread "
                          << std::this_thread::get_id()
                          << std::endl;
                return i * i;
            })
        );
    }

    for (auto& r : results) {
        std::cout << "Result: " << r.get() << std::endl;
    }

    return 0;
}

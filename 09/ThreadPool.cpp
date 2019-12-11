#include "ThreadPool.hpp"

ThreadPool::ThreadPool(size_t poolSize) {
    pool.reserve(poolSize);
    for (size_t i = 0; i < poolSize; ++i) {
        pool.push_back(std::thread([&]() {
            while (true) {
                std::unique_ptr<QueueTaskBase> task;
                {
                    std::unique_lock<std::mutex> lock(mutex);
                    while (!shutdown && tasks.empty())
                        condition.wait(lock);
                    
                    if (!tasks.empty()) {
                         task = std::move(tasks.front());
                         tasks.pop();
                    } else { // shutdown
                        break;
                    }
                }
                task->run();
            }
        }));
    }
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(mutex);
        shutdown = true;
    }
    condition.notify_all();
    for (auto& thread: pool) {
        thread.join();
    }
}

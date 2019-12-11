#ifndef ThreadPool_hpp
#define ThreadPool_hpp

#include <stdio.h>
#include <vector>
#include <queue>
#include <future>
#include <mutex>

class ThreadPool {
public:
    explicit ThreadPool(size_t poolSize);
    
    ~ThreadPool();
    
    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))> {
        auto task = std::make_unique<QueueTask<decltype(func(args...))>>(std::bind(func, args...));
        auto future = task->task.get_future();
        
        {
            std::unique_lock<std::mutex> lock(mutex);
            tasks.push(std::move(task));
        }
        condition.notify_one();
        return future;
    }
private:
    struct QueueTaskBase {
        virtual void run() = 0;
        virtual ~QueueTaskBase() {};
    };

    template <class RetType>
    struct QueueTask: public QueueTaskBase {
        template<class FuncType>
        QueueTask(FuncType func): task(func) {}
        
        std::packaged_task<RetType()> task;
        
        void run() {
            task();
        }
        
        virtual ~QueueTask() {}
    };
    
    std::condition_variable condition;
    std::mutex mutex;
    std::queue<std::unique_ptr<QueueTaskBase>> tasks;
    std::vector<std::thread> pool;
    bool shutdown;
};

#endif /* ThreadPool_hpp */

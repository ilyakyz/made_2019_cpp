#include <iostream>

#include "ThreadPool.hpp"


struct A {};

void foo(const A&, int) {}

int main(int argc, const char * argv[]) {
    {
        ThreadPool pool(8);
        auto task1 = pool.exec(foo, A(), 3);
        task1.get();
        auto task2 = pool.exec([]() { return 1; });
        assert(task2.get() == 1);
    }
    
    {
        ThreadPool pool(4);
        std::vector<std::future<int>> vec;
        for (size_t i = 0; i < 10; ++i) {
            vec.push_back(pool.exec([i]() {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                return int(i);
            }));
        }
        for (size_t i = 0; i < vec.size(); ++i) {
            assert(vec[i].get() == i);
        }
    }
    
    {
        ThreadPool pool(4);
        std::vector<std::future<int>> vec;
        for (size_t i = 0; i < 5; ++i) {
            vec.push_back(pool.exec([i]() ->int {
                throw std::runtime_error("");
            }));
        }
        for (size_t i = 5; i < 10; ++i) {
            vec.push_back(pool.exec([i]() {
                return int(i);
            }));
        }
        for (size_t i = 0; i < 5; ++i) {
            try {
                vec[i].get();
                assert(false);
            } catch (std::runtime_error&) {
            }
        }
        for (size_t i = 5; i < vec.size(); ++i) {
            assert(vec[i].get() == i);
        }
    }
    
    std::vector<std::future<int>> vec;
    {
        ThreadPool pool(4);
        std::vector<std::future<int>> vec;
        for (size_t i = 0; i < 10; ++i) {
            vec.push_back(pool.exec([i]() {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                return int(i);
            }));
        }
    }
    for (size_t i = 0; i < vec.size(); ++i) {
        assert(vec[i].get() == i);
    }
    
    std::cout << "OK\n";
    
    return 0;
}

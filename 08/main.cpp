#include <iostream>

#include "Vector.h"

struct Counter {
    Counter() {
        ++count;
    }
    
    Counter(const Counter& c) {
        ++count;
    }
    
    Counter(Counter&& c) {
        ++count;
    }
    
    ~Counter() {
        --count;
    }
    
    static int count;
};

int Counter::count = 0;

int main(int argc, const char * argv[]) {
    {
        Vector<int> v;
        assert(v.size() == 0);
    }
    
    {
        Vector<int> v(2);
        assert(v.size() == 2);
        assert(v[0] == 0);
        assert(v[1] == 0);
    }
    
    {
        Vector<int> v(2, 3);
        assert(v.size() == 2);
        assert(v[0] == 3);
        assert(v[1] == 3);
    }
    
    {
        Vector<int> v = {1, 2};
        assert(v.size() == 2);
        assert(v[0] == 1);
        assert(v[1] == 2);
    }
    
    {
        Vector<int> v;
        assert(v.size() == 0);
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);
        assert(v.size() == 3);
        assert(v[0] == 1);
        assert(v[1] == 2);
        assert(v[2] == 3);
        v.pop_back();
        assert(v.size() == 2);
        assert(v[0] == 1);
        assert(v[1] == 2);
        v.resize(4, 7);
        assert(v.size() == 4);
        assert(v[0] == 1);
        assert(v[1] == 2);
        assert(v[2] == 7);
        assert(v[3] == 7);
        v.resize(3);
        assert(v.size() == 3);
        assert(v[0] == 1);
        assert(v[1] == 2);
        assert(v[2] == 7);
        v.reserve(10);
        assert(v.size() == 3);
        v.clear();
        assert(v.size() == 0);
    }

    {
        Vector<int> v = {1, 2, 3};
        
        assert(v.end() - v.begin() == 3);
        assert(v.end() > v.begin());
        assert(v.rend() > v.rbegin());
        
        int i = 0;
        for (auto it = v.begin(); it != v.end(); ++it, ++i) {
            assert(*it == v[i]);
        }
        assert(i == 3);
        
        i = 0;
        for (auto it = v.rbegin(); it != v.rend(); ++it, ++i) {
            assert(*it == v[2-i]);
        }
        assert(i == 3);
        
        auto it = v.begin();
        it = it + 2;
        assert(*it == 3);
        assert(*(it--) == 3);
        assert(*it == 2);
        assert(it[1] == 3);
    }
    
    {
        struct A {
            int k;
        };
        Vector<A> v;
        v.push_back({3});
        assert(v.begin()->k == 3);
    }
    
    {
        Counter c;
        Counter::count = 0;
        Vector<Counter> v;
        assert(Counter::count == 0);
        v.push_back(c);
        v.push_back(Counter());
        assert(Counter::count == 2);
        v.reserve(5);
        assert(Counter::count == 2);
        v.resize(6);
        assert(Counter::count == 6);
        v.pop_back();
        assert(Counter::count == 5);
        v.resize(3);
        assert(Counter::count == 3);
    }
    assert(Counter::count == -1);
    
    std::cout << "OK\n";
    
    return 0;
}

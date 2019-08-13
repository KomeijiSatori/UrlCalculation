#ifndef HEAP_H
#define HEAP_H

#include <queue>
#include <string>
#include <vector>
#include <functional>

using namespace std;

template <typename T>
class heap {
    public:
        heap(int const _capacity, function<bool(T const &, T const &)> _cmp) : capacity(_capacity), cmp(_cmp), que(_cmp) {}

        void add(T &val) {
            if (que.size() < capacity) {
                // if not reach capacity, then add
                que.push(val);
            } else if (cmp(val, que.top())) {
                // if bigger than the smallest in heap, pop the smallest and add the element
                que.pop();
                que.push(val);
            }
        }

        // clear the heap and get elements inside
        vector<T> clearHeap() {
            vector<T> res;
            while (!que.empty()) {
                res.insert(res.begin(), que.top());
                que.pop();
            }
            return res;
        }

    private:
        int const capacity;
        function<bool(T const &, T const &)> cmp;
        priority_queue<T, vector<T>, function<bool(T const &, T const &)> > que;
};

#endif
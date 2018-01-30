#ifndef SAFE_QUEUE
#define SAFE_QUEUE

#include <condition_variable>
#include <mutex>
#include <queue>

template <class T>
class SafeQueue
{
public:
    SafeQueue(void) : q(), m(), c()
    {
    }

    ~SafeQueue(void)
    {
    }

    void enqueue(const T& t)
    {
        std::lock_guard<std::mutex> lock(m);
        q.push(t);
        c.notify_one();
    }

    T dequeue(void)
    {
        std::unique_lock<std::mutex> lock(m);
        while (q.empty())
        {
            c.wait(lock);
        }
        T val = q.front();
        q.pop();
        return val;
    }

    size_t size() const
    {
        return q.size();
    }

private:
    std::queue<T> q;
    mutable std::mutex m;
    std::condition_variable c;
};
#endif

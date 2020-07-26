#pragma once

#include <mutex>
#include <condition_variable>
#include <atomic>


class DiningScheduler
{
    public:
    DiningScheduler();
    ~DiningScheduler() = default;

    void wait();
    void notifyAllThreads();
    bool isDinnerOver();
    void stopDinner();

    private:
    std::atomic<bool> _isDinnerOver;
    std::mutex _mutex;
    std::condition_variable _scheduler;
};

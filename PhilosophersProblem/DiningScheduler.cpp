#include <PhilosophersProblem/DiningScheduler.hpp>


DiningScheduler::DiningScheduler()
    : _isDinnerOver(false)
{ }

void DiningScheduler::wait()
{
    std::unique_lock<std::mutex> lock(_mutex);
    _scheduler.wait(lock);
}

void DiningScheduler::notifyAllThreads()
{
    std::unique_lock<std::mutex> lock(_mutex);
    _scheduler.notify_one();
}

bool DiningScheduler::isDinnerOver()
{
    return _isDinnerOver;
}

void DiningScheduler::stopDinner()
{
    _isDinnerOver = true;
}

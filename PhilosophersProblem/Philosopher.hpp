#pragma once

#include <string>
#include <cstdint>
#include <thread>
#include <memory>
#include <Console/Graphics.hpp>
#include <PhilosophersProblem/Fork.hpp>
#include <PhilosophersProblem/DiningScheduler.hpp>


class Philosopher
{
    public:
    enum PhilosopherState
    {
        THINKING,
        EATING,
        WAITING_FOR_FORKS,
        WAITING_FOR_RIGHT_FORK,
        WAITING_FOR_LEFT_FORK
    };

    Philosopher(uint32_t id, const std::string& philosopherName, Fork& leftFork,
                                                                 Fork& rightFork, DiningScheduler& diningScheduler,
                                                                                  std::unique_ptr<Graphics>& graphics);
    Philosopher(Philosopher&& other);
    ~Philosopher();

    uint32_t getId() const;
    std::string getName() const;
    PhilosopherState getState() const;
    void performStateTransitionTo(PhilosopherState philosopherState);
    std::string convertStateToString(PhilosopherState philosopherState);


    private:
    void startDinner();

    uint32_t _id;
    const std::string _philosopherName;
    PhilosopherState _philosopherCurrentState;
    Fork& _leftFork;
    Fork& _rightFork;
    DiningScheduler& _diningScheduler;
    std::unique_ptr<Graphics>& _graphics;
    std::thread _philosopherThread;
};

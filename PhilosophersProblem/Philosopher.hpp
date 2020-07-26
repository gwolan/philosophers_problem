#pragma once

#include <string>
#include <PhilosophersProblem/Fork.hpp>


class Philosopher
{
    public:
    enum PhilosopherState
    {
        THINKING,
        EATING,
        WAITING_FOR_FORKS,
        HAS_LEFT_FORK,
        HAS_RIGHT_FORK
    };

    Philosopher(const std::string& philosopherName, Fork& leftFork, Fork& rightFork);
    ~Philosopher();

    std::string getName() const;
    PhilosopherState getState() const;
    std::string convertStateToString(PhilosopherState philosopherState);


    private:
    const std::string _philosopherName;
    PhilosopherState _philosopherCurrentState;
    Fork& _leftFork;
    Fork& _rightFork;
};

#include <PhilosophersProblem/Philosopher.hpp>


Philosopher::Philosopher(const std::string& philosopherName, Fork& leftFork, Fork& rightFork)
    : _philosopherName(philosopherName)
    , _philosopherCurrentState(THINKING)
    , _leftFork(leftFork)
    , _rightFork(rightFork)
{ }

Philosopher::~Philosopher()
{ }

std::string Philosopher::getName() const
{
    return _philosopherName;
}

Philosopher::PhilosopherState Philosopher::getState() const
{
    return _philosopherCurrentState;
}

std::string Philosopher::convertStateToString(PhilosopherState philosopherState)
{
    switch(philosopherState)
    {
        case THINKING:          return "THINKING";
        case EATING:            return "EATING";
        case WAITING_FOR_FORKS: return "WAITING_FOR_FORKS";
        case HAS_LEFT_FORK:     return "HAS_LEFT_FORK";
        case HAS_RIGHT_FORK:    return "HAS_RIGHT_FORK";
    };

    return "UNKNOWN";
}

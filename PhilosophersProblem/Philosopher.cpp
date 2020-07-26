#include <vector>
#include <PhilosophersProblem/Philosopher.hpp>


Philosopher::Philosopher(uint32_t id, const std::string& philosopherName, Fork& leftFork,
                                                                          Fork& rightFork, DiningScheduler& diningScheduler,
                                                                                           std::unique_ptr<Graphics>& graphics)
    : _id(id)
    , _philosopherName(philosopherName)
    , _philosopherCurrentState(THINKING)
    , _leftFork(leftFork)
    , _rightFork(rightFork)
    , _diningScheduler(diningScheduler)
    , _graphics(graphics)
    , _philosopherThread(&Philosopher::startDinner, this)
{ }

Philosopher::Philosopher(Philosopher&& other)
    : _id(other._id)
    , _philosopherName(other._philosopherName)
    , _philosopherCurrentState(other._philosopherCurrentState)
    , _leftFork(other._leftFork)
    , _rightFork(other._rightFork)
    , _diningScheduler(other._diningScheduler)
    , _graphics(other._graphics)
    , _philosopherThread(std::move(other._philosopherThread))
{ }

Philosopher::~Philosopher()
{
    if(_philosopherThread.joinable())
    {
        _philosopherThread.detach();
    }
}

uint32_t Philosopher::getId() const
{
    return _id;
}

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
        case THINKING:               return "THINKING";
        case EATING:                 return "EATING";
        case WAITING_FOR_FORKS:      return "WAITING_FOR_FORKS";
        case WAITING_FOR_RIGHT_FORK: return "WAITING_FOR_RIGHT_FORK";
        case WAITING_FOR_LEFT_FORK:  return "WAITING_FOR_LEFT_FORK";
    };

    return "UNKNOWN";
}

void Philosopher::startDinner()
{
    _diningScheduler.wait();
    _philosopherCurrentState = EATING;

    std::vector<std::string> newRow { getName(),
                                      convertStateToString(getState()),
                                      _leftFork.getName(),
                                      _leftFork.getOwnerName(),
                                      _leftFork.convertStateToString(_leftFork.getState()) };
    _graphics->updateRow(_id, newRow);
}

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
    , _activityTimeDice(1500, 3000)
    , _forkLeftOrRightDice(1, 2)
    , _philosopherThread(&Philosopher::startDinner, this)
    , log("Philosopher::")
{ }

Philosopher::Philosopher(Philosopher&& other)
    : _id(other._id)
    , _philosopherName(other._philosopherName)
    , _philosopherCurrentState(other._philosopherCurrentState)
    , _leftFork(other._leftFork)
    , _rightFork(other._rightFork)
    , _diningScheduler(other._diningScheduler)
    , _graphics(other._graphics)
    , _activityTimeDice(other._activityTimeDice)
    , _forkLeftOrRightDice(other._forkLeftOrRightDice)
    , _philosopherThread(std::move(other._philosopherThread))
    , log("Philosopher::")
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

void Philosopher::performStateTransitionTo(Philosopher::PhilosopherState philosopherState)
{
    log.log(_philosopherName, __FUNCTION__);
    _philosopherCurrentState = philosopherState;

    std::vector<std::string> newRow { getName(),
                                      convertStateToString(getState()),
                                      _leftFork.getName(),
                                      _leftFork.getOwnerName(),
                                      _leftFork.convertStateToString(_leftFork.getState()) };

    log.log(_philosopherName + ": " + newRow[0] + " | "
                                    + newRow[1] + " | "
                                    + newRow[2] + " | "
                                    + newRow[3] + " | "
                                    + newRow[4] + " | ", __FUNCTION__);
    _graphics->updateRow(_id, newRow);
}

bool Philosopher::stoppedDining()
{
    log.log(_philosopherName, __FUNCTION__);
    if(_diningScheduler.isDinnerOver())
    {
        log.log(_philosopherName + " - TRUE", __FUNCTION__);
        _leftFork.free();
        _rightFork.free();

        if(_philosopherThread.joinable())
        {
            _philosopherThread.detach();
        }

        return true;
    }

    log.log(_philosopherName + " - FALSE", __FUNCTION__);
    return false;
}

void Philosopher::aquireForks()
{
    log.log(_philosopherName, __FUNCTION__);
    performStateTransitionTo(WAITING_FOR_FORKS);

    if(_forkLeftOrRightDice.rollUnsignedInt() == 1)
    {
        log.log(_philosopherName + " left", __FUNCTION__);
        _leftFork.aquire(_philosopherName);
        performStateTransitionTo(WAITING_FOR_RIGHT_FORK);
        _rightFork.aquire(_philosopherName);
    }
    else
    {
        log.log(_philosopherName + " right", __FUNCTION__);
        _rightFork.aquire(_philosopherName);
        performStateTransitionTo(WAITING_FOR_LEFT_FORK);
        _leftFork.aquire(_philosopherName);
    }
}

void Philosopher::startThinking()
{
    log.log(_philosopherName, __FUNCTION__);
    performStateTransitionTo(THINKING);
    std::this_thread::sleep_for(std::chrono::milliseconds(_activityTimeDice.rollUnsignedInt()));
}

void Philosopher::startEating()
{
    log.log(_philosopherName, __FUNCTION__);
    aquireForks();
    performStateTransitionTo(EATING);
    std::this_thread::sleep_for(std::chrono::milliseconds(_activityTimeDice.rollUnsignedInt()));

    _leftFork.free();
    _rightFork.free();
}

void Philosopher::startDinner()
{
    _diningScheduler.wait();

    log.log(_philosopherName, __FUNCTION__);

    while(true)
    {
        startThinking();
        startEating();

        if(stoppedDining())
        {
            break;
        }
    }
}

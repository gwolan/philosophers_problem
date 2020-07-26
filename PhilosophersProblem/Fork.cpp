#include <PhilosophersProblem/Fork.hpp>


Fork::Fork(uint32_t id, const std::string& forkName,
                        const std::string& ownerName, DiningScheduler& diningScheduler)
    : _id(id)
    , _forkName(forkName)
    , _ownerName(ownerName)
    , _forkCurrentState(FREE)
    , _diningScheduler(diningScheduler)
{ }

Fork::~Fork()
{ }

uint32_t Fork::getId() const
{
    return _id;
}

std::string Fork::getName() const
{
    return _forkName;
}

std::string Fork::getOwnerName() const
{
    return _ownerName;
}

Fork::ForkState Fork::getState() const
{
    return _forkCurrentState;
}

std::string Fork::convertStateToString(ForkState forkState)
{
    switch(forkState)
    {
        case FREE:   return "FREE";
        case IN_USE: return "IN_USE";
    };

    return "UNKNOWN";
}

bool Fork::isFree()
{
    return _forkCurrentState == FREE;
}

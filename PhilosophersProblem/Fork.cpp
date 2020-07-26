#include <PhilosophersProblem/Fork.hpp>


Fork::Fork(const std::string& forkName, const std::string& ownerName)
    : _forkName(forkName)
    , _ownerName(ownerName)
    , _forkCurrentState(FREE)
{ }

Fork::~Fork()
{ }

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

#pragma once

#include <string>
#include <PhilosophersProblem/DiningScheduler.hpp>


class Fork
{
    public:
    enum ForkState
    {
        FREE,
        IN_USE
    };

    Fork(uint32_t id, const std::string& forkName,
                      const std::string& ownerName, DiningScheduler& diningScheduler);
    ~Fork();

    uint32_t getId() const;
    std::string getName() const;
    std::string getOwnerName() const;
    ForkState getState() const;
    bool isFree();
    std::string convertStateToString(ForkState forkState);


    private:
    uint32_t _id;
    const std::string _forkName;
    std::string _ownerName;
    ForkState _forkCurrentState;
    DiningScheduler& _diningScheduler;
};

#pragma once

#include <string>


class Fork
{
    public:
    enum ForkState
    {
        FREE,
        IN_USE
    };

    Fork(const std::string& forkName, const std::string& ownerName);
    ~Fork();

    std::string getName() const;
    std::string getOwnerName() const;
    ForkState getState() const;
    bool isFree();
    std::string convertStateToString(ForkState forkState);


    private:
    const std::string _forkName;
    std::string _ownerName;
    ForkState _forkCurrentState;
};

#include <utility>
#include <vector>
#include <PhilosophersProblem/DiningTable.hpp>


DiningTable::DiningTable(uint32_t philosophersCount)
    : _diningTableStateGraphicsPtr(nullptr)
{
    createForks(philosophersCount);
    createPhilosophers(philosophersCount);
    initTable();
}

DiningTable::~DiningTable()
{ }

void DiningTable::initTableRows(std::vector<std::vector<std::string>>& rows)
{
    auto forkIt = _forksMap.begin();
    auto philosopherIt = _philosophersMap.begin();
    for(; philosopherIt != _philosophersMap.end(); ++philosopherIt, ++forkIt)
    {
        rows.push_back({ philosopherIt->second.getName(),
                         philosopherIt->second.convertStateToString(philosopherIt->second.getState()),
                         forkIt->second.getName(),
                         forkIt->second.getOwnerName(),
                         forkIt->second.convertStateToString(forkIt->second.getState()) });
    }
}

void DiningTable::initTable()
{
    std::vector<std::string> columns { "Philosopher", "Phil. State", "Fork", "Fork Owner", "Fork State" };
    std::vector<std::vector<std::string>> rows;

    initTableRows(rows);

    _diningTableStateGraphicsPtr = std::make_unique<Graphics>(columns, rows);
}

void DiningTable::createForks(uint32_t philosophersCount)
{
    for(uint32_t forkId = 0; forkId < philosophersCount; ++forkId)
    {
        std::string ownerName;
        std::string forkName = "Fork" + std::to_string(forkId);

        if(forkId == philosophersCount - 1)
        {
            ownerName = "Phil" + std::to_string(0);
        }
        else
        {
            ownerName = "Phil" + std::to_string(forkId);
        }

        _forksMap.emplace(std::make_pair(forkName, Fork(forkName, ownerName)));
    }
}

void DiningTable::createPhilosophers(uint32_t philosophersCount)
{
    for(uint32_t philosopherId = 0; philosopherId < philosophersCount; ++philosopherId)
    {
        std::string philosopherName = "Phil" + std::to_string(philosopherId);
        std::string leftForkName = "Fork" + std::to_string(philosopherId);
        std::string rightForkName;

        if(philosopherId == philosophersCount - 1)
        {
            rightForkName = "Fork" + std::to_string(0);
        }
        else
        {
            rightForkName = "Fork" + std::to_string(philosopherId + 1);
        }

        _philosophersMap.emplace(std::make_pair(philosopherName, Philosopher(philosopherName, _forksMap.at(leftForkName)
                                                                                            , _forksMap.at(rightForkName))));
    }
}

void DiningTable::startDinner()
{
    _diningTableStateGraphicsPtr->display();
}

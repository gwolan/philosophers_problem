#include <utility>
#include <vector>
#include <PhilosophersProblem/DiningTable.hpp>


DiningTable::DiningTable(uint32_t philosophersCount)
    : _diningTableStateGraphicsPtr(nullptr)
    , _diningScheduler()
{
    createForks(philosophersCount);
    createPhilosophers(philosophersCount);
    initTable();
}

DiningTable::~DiningTable()
{ }

void DiningTable::initTableRows(std::vector<std::vector<std::string>>& rows)
{
    auto forkIt = _forks.begin();
    auto philosopherIt = _philosophers.begin();
    for(; philosopherIt != _philosophers.end(); ++philosopherIt, ++forkIt)
    {
        rows.push_back({ philosopherIt->getName(),
                         philosopherIt->convertStateToString(philosopherIt->getState()),
                         forkIt->getName(),
                         forkIt->getOwnerName(),
                         forkIt->convertStateToString(forkIt->getState()) });
    }
}

void DiningTable::initTable()
{
    std::vector<std::string> columns { "Philosopher", "Phil. State", "Fork", "Fork Owner", "Fork State" };
    std::vector<std::vector<std::string>> rows;

    initTableRows(rows);

    _diningTableStateGraphicsPtr = std::make_unique<Graphics>(columns, rows, _diningScheduler);
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

        _forks.emplace_back(forkId, forkName, ownerName, _diningScheduler);
    }
}

void DiningTable::createPhilosophers(uint32_t philosophersCount)
{
    for(uint32_t philosopherId = 0; philosopherId < philosophersCount; ++philosopherId)
    {
        std::string philosopherName = "Phil" + std::to_string(philosopherId);

        if(philosopherId == philosophersCount - 1)
        {
            _philosophers.emplace_back(philosopherId, philosopherName, _forks[philosopherId], _forks[0], _diningScheduler, _diningTableStateGraphicsPtr);
        }
        else
        {
            _philosophers.emplace_back(philosopherId, philosopherName, _forks[philosopherId], _forks[philosopherId + 1], _diningScheduler, _diningTableStateGraphicsPtr);
        }

    }
}

void DiningTable::startDinner()
{
    std::this_thread::sleep_for(std::chrono::seconds(2));
    _diningScheduler.notifyAllThreads();
    _diningTableStateGraphicsPtr->display();
}

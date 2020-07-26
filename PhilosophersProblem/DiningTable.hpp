#pragma once

#include <string>
#include <cstdint>
#include <memory>
#include <vector>
#include <Console/Graphics.hpp>
#include <PhilosophersProblem/Fork.hpp>
#include <PhilosophersProblem/Philosopher.hpp>
#include <PhilosophersProblem/DiningScheduler.hpp>


class DiningTable
{
    public:
    DiningTable(uint32_t philosophersCount);
    ~DiningTable();

    void startDinner();


    private:
    void initTable();
    void initTableRows(std::vector<std::vector<std::string>>& rows);
    void createForks(uint32_t philosophersCount);
    void createPhilosophers(uint32_t philosophersCount);

    std::vector<Fork> _forks;
    std::vector<Philosopher> _philosophers;
    std::unique_ptr<Graphics> _diningTableStateGraphicsPtr;
    DiningScheduler _diningScheduler;
};
